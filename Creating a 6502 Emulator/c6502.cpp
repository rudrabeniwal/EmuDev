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
    uint8_t opcode = bus_.read( compose(regPCH, regPCL), true);
}