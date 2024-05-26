#include "cpu.hpp"
#include <iostream>
CPU::CPU() : rax(0), rbx(0), rcx(0), rdx(0), rsi(0), rdi(0), rsp(0), rbp(0), 
             r8(0), r9(0), r10(0), r11(0), r12(0), r13(0), r14(0), r15(0),
             rip(0), rflags(0), interruptsEnabled(true) {}
void setInterruptHandler(CPU& cpu, uint8_t vector, std::function<void(CPU&)> handler) {
    if (vector >= cpu.interruptHandlers.size()) {
        // Resize the vector if necessary
        cpu.interruptHandlers.resize(vector + 1); 
    }
     // Set the handler for the specified vector
    cpu.interruptHandlers[vector] = handler;
}
// Method to trigger an interrupt
void triggerInterrupt(CPU& cpu, uint8_t vector) {
    if (vector < cpu.interruptHandlers.size() && cpu.interruptHandlers[vector]) {
        // Check if a handler is registered for the vector and call it if it exists
        cpu.interruptHandlers[vector](cpu);
    }
}
// Fetch a single byte from memory
uint8_t fetch(Bus& bus,CPU& cpu) {
    return bus.read8(cpu.rip++);
}
// Fetch a 32-bit value from memory
uint32_t fetch32(Bus& bus, CPU& cpu) {
    uint32_t value = bus.read32(cpu.rip);
    cpu.rip += 4;
    return value;
}
size_t instruction_length(uint8_t opcode) {
    // Implement logic to determine instruction length based on opcode
    // Example implementation:
    switch (opcode) {
        case 0x01: // ADD instruction
            return 3; // Assuming ADD instruction is 3 bytes long
        // Add more cases for other instructions as needed
        default:
            return 1; // Default to 1 byte if opcode not recognized
    }
}
uint64_t &get_register(CPU &cpu, uint8_t index)
{
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
void update_zero_flag(CPU& cpu, uint64_t result) {
    cpu.zf = (result == 0);
}

void update_sign_flag(CPU& cpu, uint64_t result) {
    cpu.sf = (result >> 63) & 1;
}

void update_carry_flag(CPU& cpu, uint64_t operand1, uint64_t operand2, uint64_t result) {
    cpu.cf = (result < operand1);
}

void update_overflow_flag(CPU& cpu, uint64_t operand1, uint64_t operand2, uint64_t result) {
    bool sign1 = (operand1 >> 63) & 1;
    bool sign2 = (operand2 >> 63) & 1;
    bool signr = (result >> 63) & 1;
    cpu.of = (sign1 == sign2) && (sign1 != signr);
}

void update_flags_add(CPU& cpu, uint64_t operand1, uint64_t operand2, uint64_t result) {
    update_zero_flag(cpu, result);
    update_sign_flag(cpu, result);
    update_carry_flag(cpu, operand1, operand2, result);
    update_overflow_flag(cpu, operand1, operand2, result);
}

void execute(Bus &bus, CPU &cpu, uint8_t opcode)
{
    switch (opcode) {
        case 0x48: // MOV rax, imm64 (Move 64-bit immediate value into rax register)
            {
                uint8_t next_byte = fetch(bus, cpu);
                if (next_byte == 0xB8) {
                    cpu.rax = bus.read64(cpu.rip);
                    cpu.rip += 8;
                } else {
                    throw std::runtime_error("Unsupported MOV instruction");
                }
            }
            break;
        case 0x01: // ADD r/m64, r64
        {
            uint8_t modrm = fetch(bus, cpu);
            uint8_t mod = modrm >> 6;
            uint8_t reg = (modrm >> 3) & 0x7;
            uint8_t rm = modrm & 0x7;

            if (mod == 3) {
                // Register-register operation
                uint64_t& reg_value = get_register(cpu, reg);
                uint64_t& rm_value = get_register(cpu, rm);
                uint64_t result = reg_value + rm_value;
                update_flags_add(cpu, reg_value, rm_value, result);
                reg_value = result;
            } else {
                // Memory addressing modes
                uint64_t effective_address = 0;
                if (mod == 0) {
                    if (rm == 5) {
                        // [disp32]
                        effective_address = cpu.rip + fetch32(bus, cpu);
                    } else {
                        // [r64]
                        effective_address = get_register(cpu, rm);
                    }
                } else if (mod == 1) {
                    // [r64 + disp8]
                    effective_address = get_register(cpu, rm) + static_cast<int8_t>(fetch(bus, cpu));
                } else if (mod == 2) {
                    // [r64 + disp32]
                    effective_address = get_register(cpu, rm) + fetch32(bus, cpu);
                } else {
                    throw std::runtime_error("Invalid ModR/M mode");
                }

                // Perform the addition with memory
                uint64_t memory_value = bus.read64(effective_address);
                uint64_t reg_value = get_register(cpu, reg);
                uint64_t result = memory_value + reg_value;
                update_flags_add(cpu, memory_value, reg_value, result);
                bus.write64(effective_address, result);
            }
        }
            break;
        case 0xF7: // MUL r/m64
            {
                uint8_t modrm = fetch(bus, cpu);
                uint8_t mod = modrm >> 6;
                uint8_t rm = modrm & 0x7;

                if (mod == 3) {
                    // Register-register operation
                    uint64_t& rm_value = get_register(cpu, rm);
                    cpu.rax *= rm_value;
                } else {
                    // ModRM addressing mode
                    // Placeholder for memory addressing (not fully implemented here)
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
                int32_t offset = bus.read64(cpu.rip);
                cpu.rip += 4;
                cpu.rsp -= 8;
                bus.write64(cpu.rsp, cpu.rip);
                cpu.rip += offset;
            }
            break;
         // Add more cases here for other instructions
        default:
            std::cerr << "Unknown opcode: " << std::hex << +opcode << std::endl;
            exit(1);
    }
}