#include "readmem.h"

#include "Bus.h"

#include "c6502.h"

#include <assert.h>
#include <unordered_map>
#include <unordered_set>

class TestDone {};

class TestBus : public Bus {
    static constexpr size_t StartGraceCycles = 50;

    std::array<std::uint8_t, 65536> memory;
    ReadMem<8,8,16,4>   test_plan;
    size_t              cycles_until_start = StartGraceCycles;
    bool                cpuInReset = true;
    size_t              cycle_num = 0;

    enum class Signals {
        ReadyOn, ReadyOff, SoOn, SoOff, NmiOn, NmiOff, ResetOn, ResetOff, IrqOn, IrqOff
    };

    std::unordered_map< size_t, std::unordered_set< Signals > > delayed_actions;


public:
    TestBus(const char *memory_image_file, const char *test_plan_file) : test_plan(test_plan_file) {
        ReadMem<8> memory_image(memory_image_file);

        while( memory_image.read_line() ) {
            memory[memory_image.address()] = memory_image[0];
        }
    }

    virtual uint8_t read( c6502 *cpu, Addr address, bool sync = false ) override {
        perform_io(cpu);

        uint8_t ret = memory[address];

        if( cycles_until_start>0 ) {
            if( StartGraceCycles-cycles_until_start == 2 ) {
                cpu->setReset(false);
                cpuInReset = false;
            }

            if( address==0xfffc && !cpuInReset ) {
                cycles_until_start = 0;
                cycle_num = 1;
                std::cout<<"Reset vector read detected\n";
            } else {
                if( --cycles_until_start == 0 ) {
                    std::cerr<<"CPU failed to read the reset vector\n";
                    abort();
                }
            }
        }

        if( cycles_until_start==0 ) {
            std::cout<<std::dec<<cycle_num<<" R: "<<std::hex<<address<<" "<<int(ret)<<"\n";
            cycle_num++;
            bool valid = test_plan.read_line();
            assert(valid);

            check( cpu, test_plan[0], 1, "Read operation where write was expected", address, ret );
            check( cpu, test_plan[2], address, "Read from wrong address", address, ret );
            check( cpu, test_plan[1], ret, "Read wrong value from memory", address, ret );
        }

        return ret;
    }
    virtual void write( c6502 *cpu, Addr address, uint8_t value ) override {
        perform_io(cpu);

        std::cout<<std::dec<<cycle_num<<" W: "<<std::hex<<address<<" "<<int(value)<<"\n";
        cycle_num++;

        bool valid = test_plan.read_line();
        if( valid ) {
            check( cpu, test_plan[0], 0, "Write operation where read was expected", address, value );
            check( cpu, test_plan[2], address, "Write to wrong address", address, value );
            check( cpu, test_plan[1], value, "Write of wrong value to memory", address, value );
        }

        memory[address] = value;

        if( (address>>8) == 0x02 ) {
            switch( address & 0xff ) {
            case 0x00:
                throw TestDone();
                break;
            case 0x81:
                delayed_actions.try_emplace( cycle_num+value-1 ).first->second.emplace(Signals::ReadyOn);
                delayed_actions.try_emplace( cycle_num+value-1+memory[0x280] ).first->second.emplace(Signals::ReadyOff);
                break;
            case 0x83:
                delayed_actions.try_emplace( cycle_num+value ).first->second.emplace(Signals::SoOn);
                delayed_actions.try_emplace( cycle_num+value+memory[0x282] ).first->second.emplace(Signals::SoOff);
                break;
            case 0xfb:
                delayed_actions.try_emplace( cycle_num+value ).first->second.emplace(Signals::NmiOn);
                delayed_actions.try_emplace( cycle_num+value+memory[0x2fa] ).first->second.emplace(Signals::NmiOff);
                break;
            case 0xfd:
                delayed_actions.try_emplace( cycle_num+value ).first->second.emplace(Signals::ResetOn);
                delayed_actions.try_emplace( cycle_num+value+memory[0x2fc] ).first->second.emplace(Signals::ResetOff);
                break;
            case 0xff:
                delayed_actions.try_emplace( cycle_num+value ).first->second.emplace(Signals::IrqOn);
                delayed_actions.try_emplace( cycle_num+value+memory[0x2fe] ).first->second.emplace(Signals::IrqOff);
                break;
            }
        }
    }

private:
    void check(
            const c6502 *cpu,
            ReadMemSupport::DataContainer expected,
            ReadMemSupport::DataContainer actual,
            const char *message,
            Addr address,
            uint8_t data )
    {
        if( actual==expected )
            return;

        std::cerr<<"Validation failed on plan line "<<std::dec<<test_plan.lineNumber()<<
                ": "<<message<<" Expected "<<std::hex<<expected<<" got "<<actual<<
                " @"<<address<<" data "<<int(data);
        if( cpu->isIncompatible() ) {
            std::cerr<<" known incompatibility\n";
        } else {
            std::cerr<<"\n";
            abort();
        }
    }

    void perform_io(c6502 *cpu) {
        auto action_iter = delayed_actions.find( cycle_num );
        if( action_iter==delayed_actions.end() )
            return;

        for( auto action : action_iter->second ) {
            switch( action ) {
            case Signals::ReadyOn:
                cpu->setReady(true);
                break;
            case Signals::ReadyOff:
                cpu->setReady(false);
                break;
            case Signals::SoOn:
                cpu->setSo(true);
                break;
            case Signals::SoOff:
                cpu->setSo(false);
                break;
            case Signals::NmiOn:
                cpu->setNmi(true);
                break;
            case Signals::NmiOff:
                cpu->setNmi(false);
                break;
            case Signals::ResetOn:
                cpu->setReset(true);
                break;
            case Signals::ResetOff:
                cpu->setReset(false);
                break;
            case Signals::IrqOn:
                cpu->setIrq(true);
                break;
            case Signals::IrqOff:
                cpu->setIrq(false);
                break;
            }
        }

        delayed_actions.erase( action_iter );
    }
};

int main(int argc, char *argv[]) {
    TestBus bus(argv[1], argv[2]);

    c6502 cpu(bus);

    cpu.setReset(true);

    try {
        cpu.runCpu();
    } catch(TestDone ex) {
    }

    std::cout<<"Test finished successfully\n";
}