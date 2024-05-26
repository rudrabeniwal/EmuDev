#include <gtest/gtest.h>
#include "../src/cpu.hpp"
#include "../src/memory.hpp"
#include "../src/bus.hpp"

TEST(CPU, BasicOperations) {
    Memory memory(0x10000); // 64 KB of memory
    Bus bus(memory);
    CPU cpu;

    // MOV and ADD instructions
    memory.write8(0, 0x48); // MOV rax, 0x10
    memory.write8(1, 0xB8);
    memory.write64(2, 0x10);
    memory.write8(10, 0x48); // ADD rax, 0x20
    memory.write8(11, 0x05);
    memory.write32(12, 0x20);
    memory.write8(16, 0xC3); // RET
    cpu.rip = 0;
    
    // Emulation loop
    while (cpu.rip < 17) {
        uint8_t opcode = fetch(bus, cpu);
        execute(bus, cpu, opcode);
    }

    EXPECT_EQ(cpu.rax, 0x30); // rax should be 0x30 (0x10 + 0x20)
}

// int main(int argc, char **argv) {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }
