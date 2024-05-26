#ifndef CPU_HPP
#define CPU_HPP

#include <cstdint>
#include <vector>
#include <functional>
#include "bus.hpp"

size_t instruction_length(uint8_t opcode);

struct CPU {
    // General-purpose registers
    uint64_t rax, rbx, rcx, rdx;
    uint64_t rsi, rdi, rsp, rbp;
    uint64_t r8, r9, r10, r11, r12, r13, r14, r15;
    uint64_t rip;           // Instruction pointer
    bool zf, sf, cf, of;    //Flag Updates
    uint64_t rflags;        // Flags register
    bool interruptsEnabled; // Flag indicating if interrupts are enabled
    std::vector<std::function<void(CPU&)>> interruptHandlers; // Vector of interrupt handler functions
    CPU(); // Constructor

    //The reason for using friend declarations in the CPU class is to allow certain functions to access its private and protected members.
    friend uint64_t& get_register(CPU& cpu, uint8_t index);
    friend void update_zero_flag(CPU& cpu, uint64_t result);
    friend void update_sign_flag(CPU& cpu, uint64_t result);
    friend void update_carry_flag(CPU& cpu, uint64_t operand1, uint64_t operand2, uint64_t result);
    friend void update_overflow_flag(CPU& cpu, uint64_t operand1, uint64_t operand2, uint64_t result);
    friend void update_flags_add(CPU& cpu, uint64_t operand1, uint64_t operand2, uint64_t result);
    friend void execute(Bus& bus, CPU& cpu, uint8_t opcode);
};

// Fetch an instruction byte from memory
uint8_t fetch(Bus& bus, CPU& cpu);
// Decode and execute an instruction based on the fetched opcode
void execute(Bus& bus, CPU& cpu, uint8_t opcode);
// Utility function to get a reference to a register by its index
uint64_t& get_register(CPU& cpu, uint8_t index);
// Set an interrupt handler for a specific vector
void setInterruptHandler(CPU& cpu, uint8_t vector, std::function<void(CPU&)> handler);
// Trigger an interrupt for a specific vector
void triggerInterrupt(CPU& cpu, uint8_t vector);

#endif // CPU_HPP