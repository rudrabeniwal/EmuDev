#include <gtest/gtest.h>
#include <iostream> // For std::cout and std::endl
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

    std::cout << "Running BasicOperations test..." << std::endl;
    std::cout << "Input: MOV rax, 0x10; ADD rax, 0x20; RET" << std::endl;
    
    // Emulation loop
    while (cpu.rip < 17) {
        uint8_t opcode = fetch(bus, cpu);
        execute(bus, cpu, opcode);
    }

    std::cout << "Expected output: rax = 0x30" << std::endl;
    EXPECT_EQ(cpu.rax, 0x30); // rax should be 0x30 (0x10 + 0x20)
}

TEST(CPU, MovImmediateToRegister) {
    Memory memory(0x10000);
    Bus bus(memory);
    CPU cpu;

    // MOV rbx, 0x12345678
    memory.write8(0, 0x48); // REX.W prefix
    memory.write8(1, 0xBB); // MOV rbx, imm64
    memory.write64(2, 0x12345678);
    memory.write8(10, 0xC3); // RET
    cpu.rip = 0;

    std::cout << "Running MovImmediateToRegister test..." << std::endl;
    std::cout << "Input: MOV rbx, 0x12345678; RET" << std::endl;

    while (cpu.rip < 11) {
        uint8_t opcode = fetch(bus, cpu);
        execute(bus, cpu, opcode);
    }

    std::cout << "Expected output: rbx = 0x12345678" << std::endl;
    EXPECT_EQ(cpu.rbx, 0x12345678);
}

TEST(CPU, MulRegister) {
    Memory memory(0x10000);
    Bus bus(memory);
    CPU cpu;

    cpu.rax = 2;
    cpu.rbx = 3;

    // MUL rbx
    memory.write8(0, 0x48); // REX.W prefix
    memory.write8(1, 0xF7); // MUL r/m64
    memory.write8(2, 0xE3); // ModR/M byte (register-direct addressing mode, rbx)
    memory.write8(3, 0xC3); // RET
    cpu.rip = 0;

    std::cout << "Running MulRegister test..." << std::endl;
    std::cout << "Input: MUL rbx; RET" << std::endl;

    while (cpu.rip < 4) {
        uint8_t opcode = fetch(bus, cpu);
        execute(bus, cpu, opcode);
    }

    std::cout << "Expected output: rax = 6 (2 * 3)" << std::endl;
    EXPECT_EQ(cpu.rax, 6); // 2 * 3 = 6
}

TEST(CPU, PushPop) {
    Memory memory(0x10000);
    Bus bus(memory);
    CPU cpu;

    cpu.rsp = 0x10000; // Stack pointer at the end of memory
    cpu.rax = 0xDEADBEEF;

    // PUSH rax
    memory.write8(0, 0x50);
    // POP rbx
    memory.write8(1, 0x58 | 3); // 3 is the index for rbx
    memory.write8(2, 0xC3); // RET
    cpu.rip = 0;

    std::cout << "Running PushPop test..." << std::endl;
    std::cout << "Input: PUSH rax; POP rbx; RET" << std::endl;

    while (cpu.rip < 3) {
        uint8_t opcode = fetch(bus, cpu);
        execute(bus, cpu, opcode);
    }

    std::cout << "Expected output: rbx = 0xDEADBEEF" << std::endl;
    EXPECT_EQ(cpu.rbx, 0xDEADBEEF);
}

TEST(CPU, CallRet) {
    Memory memory(0x10000);
    Bus bus(memory);
    CPU cpu;

    cpu.rsp = 0x10000; // Stack pointer at the end of memory

    // CALL 0x5 (relative address)
    memory.write8(0, 0xE8);
    memory.write32(1, 0x5);
    // RET
    memory.write8(5, 0xC3);
    // NOP (should not be executed)
    memory.write8(6, 0x90);
    cpu.rip = 0;

    std::cout << "Running CallRet test..." << std::endl;
    std::cout << "Input: CALL 0x5; RET" << std::endl;

    while (cpu.rip != 6) {
        uint8_t opcode = fetch(bus, cpu);
        execute(bus, cpu, opcode);
    }

    std::cout << "Expected output: rip = 6" << std::endl;
    EXPECT_EQ(cpu.rip, 6);
}
