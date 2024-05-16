#include "c6502.h"

static uint16_t compose(uint8_t high, uint8_t low) {
    return high<<8 | low;
}

void c6502::runCPU() {
    while (true)
    {
        handleInstruction();
    }
    
}

void c6502::handleInstruction() {
    current_opcode = bus_.read( compose(regPCH, regPCL), true);
    advance_pc();

    switch(current_opcode) {
        case 0xa9:
            op_lda(addrmode_immediate());
            break;
    }
}

void c6502::advance_pc() {
    Addr pc = compose(regPCH, regPCL);
    pc++;
    // splitting the program counter into high and low bytes after incrementing it allows the CPU to efficiently address memory, utilize its limited number of address pins, and support various addressing modes required for executing instructions accurately. This splitting ensures that the CPU can access individual bytes of the memory address and move to the next instruction in memory seamlessl
    regPCH = pc >> 8;
    regPCL = pc & 0xff;
}

// address modes
Addr c6502::addrmode_immediate() {
    Addr pc = compose(regPCH, regPCL);
    advance_pc();

    return pc;
}

//operation
void c6502::op_lda (Addr addr) {
    regA = bus_.read( addr );
}