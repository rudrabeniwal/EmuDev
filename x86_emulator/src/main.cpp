#include <iostream>
#include "cpu.h"
#include "bus.h"
#include "memory.h"

void load_program(Memory& memory) {
    // Example program: ADD rax, rbx
    memory.write8(0, 0x48); // REX.W prefix (indicating 64-bit operand)
    memory.write8(1, 0x01); // ADD opcode
    memory.write8(2, 0xD8); // ModR/M byte: 11 000 011 (mod=3, reg=rax, rm=rbx)
}

void run_emulator() {
    // Initialize memory
    Memory memory(1024);

    // Load the program into memory
    load_program(memory);

    // Initialize the bus
    Bus bus(memory);

    // Initialize the CPU
    CPU cpu;

    // Set initial register values
    cpu.rax = 5;
    cpu.rbx = 10;
    cpu.rip = 0;

    // Execute instructions
    try {
        while (true) {
            execute(bus, cpu);
            // For demonstration, we limit to one instruction
            break;
        }
    } catch (const std::runtime_error& e) {
        std::cerr << "Emulator error: " << e.what() << std::endl;
    }

    // Display the result
    std::cout << "Final RAX: " << cpu.rax << std::endl;
}

int main() {
    run_emulator();
    return 0;
}