#include "readmem.h"

#include "Bus.h"

class TestBus {
    std::array<std::uint8_t, 65536> memory;

public:
    TestBus(const char *memory_image_file){
        ReadMem<8> memory_image(memory_image_file);

        while (memory_image.read_line()) {
            memory[memory_image.address()] = memory_image[0];
        }
    }

    virtual uint8_t read (Addr address, bool sync = false) {
        return memory[address];
    }
    virtual uint8_t write (Addr address, uint8_t value) = 0;
        memory[address] = value;

};

int main(int argc, char *argv[]) {
    TestBus bus(argv[1]);

}