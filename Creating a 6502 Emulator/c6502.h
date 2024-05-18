#pragma once
#include <stdint.h>
#include "bus.h"

class c6502 {
    Bus &bus_;
    uint8_t regA, regX, regY;
    uint8_t regSP;
    uint8_t regStatus;
    uint8_t regPCL, regPCH; // splitting PC to low and high
    uint8_t current_opcode;

    //CC -> Condition Code (flag)
    enum class CC {
           Carry,
           Zero,
           Intmask,
           Decimal,
           NA,
           NA2,
           oVerflow,
           Negative
       };


public:
    explicit c6502(Bus &bus) : bus_(bus) {};

    void runCPU();

private:
    void handleInstruction();
    void advance_pc();

    Addr pc() const;

    uint8_t ccGet(CC cc) const;
    void ccSet(CC cc, bool value);


    //address modes
    Addr addrmode_immediate();
    Addr addrmode_zp();
    Addr addrmode_abs();
    Addr addrmode_stack();

    //operations
    void op_lda(Addr addr);
    void op_rol(Addr addr);
    void op_sta(Addr addr);
    void op_pha(Addr addr);

};