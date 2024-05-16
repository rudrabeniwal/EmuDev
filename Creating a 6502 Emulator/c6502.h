#pragma once
#include <stdint.h>
#include "bus.h"

class c6502 {
    Bus &bus_;
    uint8_t regA, regX, regY;
    uint8_t regSP;
    uint8_t regStatus;
    uint8_t regPCL, regPCH; // splitting PC to low and high
    using Addr = uint16_t;
public:
    explicit c6502(Bus &bus) : bus_(bus) {};
    uint8_t current_opcode;

    void runCPU();

private:
    void handleInstruction();
    void advance_pc();
    //address modes
    Addr addrmode_immediate();
    //operations
    void op_lda(Addr addr);
};