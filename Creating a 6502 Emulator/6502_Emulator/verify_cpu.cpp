#include "readmem.h"

#include "Bus.h"

#include "c6502.h"

class TestBus: public Bus {
    static constexpr size_t StartGraceCycles = 50;
    std::array<std::uint8_t, 65536> memory;
    ReadMem<8,8,16,4> test_plan;
    size_t cycles_until_start = StartGraceCycles;
    bool cpuInReset = true;

public:
    TestBus(const char *memory_image_file, const char *test_plan_file) : test_plan(test_plan_file){
        ReadMem<8> memory_image(memory_image_file);

        while (memory_image.read_line()) {
            memory[memory_image.address()] = memory_image[0];
        }
    }

    virtual uint8_t read (c6502 *cpu, Addr address, bool sync = false) override {
        uint8_t ret = memory[address];
        if (cycles_until_start >0) {
            if (StartGraceCycles - cycles_until_start == 2) {
                cpu->setReset(false);
                cpuInReset = false;
            }
            if(address == 0xfffc && !cpuInReset) {
                cycles_until_start = 0;
                std::cout<<"Reset vector read detected\n";
            } else {
                if ( --cycles_until_start  == 0) {
                    std::cerr<<"CPU Failed to read the reset vector\n";
                    abort();
                }
            }
        }
        return ret;
    }
    virtual uint8_t write (c6502 *cpu, Addr address, uint8_t value) override {
        memory[address] = value;
        return value;
    }
};  

int main(int argc, char *argv[]) {
    TestBus bus(argv[1], argv[2]);

    c6502 cpu(bus);
    cpu.setReset(true);
    cpu.runCPU();
}