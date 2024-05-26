#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/cpu.hpp"
#include "../src/memory.hpp"
#include "../src/bus.hpp"

TEST_CASE("CPU basic operations", "[cpu]") {
    Memory memory(0x10000); // 64 KB of memory
    Bus bus(memory);
    CPU cpu;
    SECTION("MOV and ADD instructions") {
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
            execute(cpu, bus, opcode);
        }
        REQUIRE(cpu.rax == 0x30); // rax should be 0x30 (0x10 + 0x20)
    }
}