#include "cpu.hpp"
#include <iostream>
#include <stdexcept>
#include <functional>

// Constructor for CPU
CPU::CPU() : rax(0), rbx(0), rcx(0), rdx(0), rsi(0), rdi(0), rsp(0), rbp(0), 
             r8(0), r9(0), r10(0), r11(0), r12(0), r13(0), r14(0), r15(0),
             rip(0), rflags(0), interruptsEnabled(true) {}

// Set interrupt handler
void setInterruptHandler(CPU& cpu, uint8_t vector, std::function<void(CPU&)> handler) {
    if (vector >= cpu.interruptHandlers.size()) {
        cpu.interruptHandlers.resize(vector + 1);
    }
    cpu.interruptHandlers[vector] = handler;
}

// Trigger an interrupt
void triggerInterrupt(CPU& cpu, uint8_t vector) {
    if (vector < cpu.interruptHandlers.size() && cpu.interruptHandlers[vector]) {
        cpu.interruptHandlers[vector](cpu);
    }
}

// Fetch a single byte from memory
uint8_t fetch(Bus& bus, CPU& cpu) {
    return bus.read8(cpu.rip++);
}

// Fetch a 32-bit value from memory
uint32_t fetch32(Bus& bus, CPU& cpu) {
    uint32_t value = bus.read32(cpu.rip);
    cpu.rip += 4;
    return value;
}

// Fetch a 64-bit value from memory
uint64_t fetch64(Bus& bus, CPU& cpu) {
    uint64_t value = bus.read64(cpu.rip);
    cpu.rip += 8;
    return value;
}

// Determine instruction length based on opcode
size_t instruction_length(uint8_t opcode) {
    switch (opcode) {
        case 0x01: // ADD instruction
            return 3;
        default:
            return 1;
    }
}

// Get register by index
uint64_t& get_register(CPU& cpu, uint8_t index) {
    switch (index) {
        case 0: return cpu.rax;
        case 1: return cpu.rcx;
        case 2: return cpu.rdx;
        case 3: return cpu.rbx;
        case 4: return cpu.rsp;
        case 5: return cpu.rbp;
        case 6: return cpu.rsi;
        case 7: return cpu.rdi;
        case 8: return cpu.r8;
        case 9: return cpu.r9;
        case 10: return cpu.r10;
        case 11: return cpu.r11;
        case 12: return cpu.r12;
        case 13: return cpu.r13;
        case 14: return cpu.r14;
        case 15: return cpu.r15;
        default: throw std::runtime_error("Invalid register index");
    }
}

// Update zero flag
void update_zero_flag(CPU& cpu, uint64_t result) {
    cpu.zf = (result == 0);
}

// Update sign flag
void update_sign_flag(CPU& cpu, uint64_t result) {
    cpu.sf = (result >> 63) & 1;
}

// Update carry flag
void update_carry_flag(CPU& cpu, uint64_t operand1, uint64_t operand2, uint64_t result) {
    cpu.cf = (result < operand1);
}

// Update overflow flag
void update_overflow_flag(CPU& cpu, uint64_t operand1, uint64_t operand2, uint64_t result) {
    bool sign1 = (operand1 >> 63) & 1;
    bool sign2 = (operand2 >> 63) & 1;
    bool signr = (result >> 63) & 1;
    cpu.of = (sign1 == sign2) && (sign1 != signr);
}

// Update flags

void update_flags_add(CPU& cpu, uint64_t operand1, uint64_t operand2, uint64_t result) {
    update_zero_flag(cpu, result);
    update_sign_flag(cpu, result);
    update_carry_flag(cpu, operand1, operand2, result);
    update_overflow_flag(cpu, operand1, operand2, result);
}

void update_flags_mul(CPU& cpu, uint64_t operand1, uint64_t operand2) {
    // Multiplication doesn't affect zero flag (ZF) and sign flag (SF) directly
    // Clear them explicitly if necessary

    // Multiplication doesn't affect carry flag (CF) directly in x86, typically cleared
    cpu.cf = false; // Adjust as per your CPU architecture

    // Multiplication overflow flag (OF) is set if the result exceeds the bounds of the operand size
    // For x86, the overflow flag is not directly set by MUL, but can be affected by the high bits of the result
    // This is a basic example; adjust as per your CPU architecture
    cpu.of = false; // Adjust as per your CPU architecture
}

// Execute instruction based on opcode
void execute(Bus& bus, CPU& cpu, uint8_t opcode) {
    switch (opcode) {
        case 0x48: // REX.W prefix for 64-bit operand size
            opcode = fetch(bus, cpu);
        if (opcode == 0xB8) { // MOV rax, imm64
            cpu.rax = fetch64(bus, cpu);
        } else if (opcode == 0x05) { // ADD rax, imm32
            uint32_t imm32 = fetch32(bus, cpu);
            uint64_t result = cpu.rax + imm32;
            update_flags_add(cpu, cpu.rax, imm32, result);
            cpu.rax = result;
        } else if (opcode == 0xBB) { // MOV rbx, imm64
            cpu.rbx = fetch64(bus, cpu);
        } else if (opcode == 0xF7 && fetch(bus, cpu) == 0xE3) { // MUL rbx
            uint64_t operand = cpu.rbx;
            uint64_t result = cpu.rax * operand;
            cpu.rax = result & 0xFFFFFFFFFFFFFFFF;
            cpu.rdx = (result >> 64) & 0xFFFFFFFFFFFFFFFF;
            update_flags_mul(cpu, cpu.rax, operand);
        } else {
            throw std::runtime_error("Unsupported instruction after REX.W prefix");
        }
        break;
        case 0x01: // ADD r/m64, r64
            {
                uint8_t modrm = fetch(bus, cpu);
                uint8_t mod = modrm >> 6;
                uint8_t reg = (modrm >> 3) & 0x7;
                uint8_t rm = modrm & 0x7;

                if (mod == 3) { // Register mode
                    uint64_t& reg_value = get_register(cpu, reg);
                    uint64_t& rm_value = get_register(cpu, rm);
                    uint64_t result = reg_value + rm_value;
                    update_flags_add(cpu, reg_value, rm_value, result);
                    reg_value = result;
                } else {
                    // Memory mode (not fully implemented here)
                }
            }
            break;

        case 0xF7: // MUL r/m64
            {
                uint8_t modrm = fetch(bus, cpu);
                uint8_t mod = modrm >> 6;
                uint8_t rm = modrm & 0x7;

                if (mod == 3) { // Register mode
                    uint64_t& rm_value = get_register(cpu, rm);
                    cpu.rax *= rm_value;
                } else {
                    // Memory mode (not fully implemented here)
                }
            }
            break;

        case 0x50: // PUSH r64
            {
                uint8_t reg = opcode & 0x7;
                uint64_t& reg_value = get_register(cpu, reg);
                cpu.rsp -= 8;
                bus.write64(cpu.rsp, reg_value);
            }
            break;

        case 0x58: // POP r64
            {
                uint8_t reg = opcode & 0x7;
                uint64_t& reg_value = get_register(cpu, reg);
                reg_value = bus.read64(cpu.rsp);
                cpu.rsp += 8;
            }
            break;

        case 0xE8: // CALL rel32
            {
                int32_t offset = fetch32(bus, cpu);
                cpu.rsp -= 8;
                bus.write64(cpu.rsp, cpu.rip);
                cpu.rip += offset;
            }
            break;

        case 0xC3: // RET
            {
                cpu.rip = bus.read64(cpu.rsp);
                cpu.rsp += 8;
            }
            break;

        default:
            std::cerr << "Unknown opcode: " << std::hex << +opcode << std::endl;
            exit(1);
    }
}