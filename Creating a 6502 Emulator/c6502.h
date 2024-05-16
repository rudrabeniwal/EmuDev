#pragma once
#include <stdint.h>
#include "bus.h"

class c6502 {
    Bus &bus_;
    uint8_t regA, regX, regY;
    uint8_t regSP;
    uint8_t regStatus;
    uint8_t regPCL, regPCH; // splitting PC to low and high

public:
    explicit c6502(Bus &bus) : bus_(bus) {};

    void runCPU();

private:
    void handleInstruction();
};