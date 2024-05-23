#include "c6502.h"
#include <iostream>
static Addr compose(uint8_t high, uint8_t low) {
    return high<<8 | low;
}

void c6502::runCPU() {
    while (true)
    {
        try{
            if (reset)
            resetSequence(); 
        else    
            handleInstruction();
        } catch (CpuReset ex){
        }
    }
    
}

void c6502::setReset (bool state) {
    reset = state;
    std::cout<<"CPU reset "<<state<<"\n";
} 
void c6502::setIrq (bool state) {
    irq= state;
    std::cout<<"CPU IRQ "<<state<<"\n";
}
void c6502::setNmi (bool state) {
    nmi= state;
    std::cout<<"CPU NMI "<<state<<"\n";
}
void c6502::setReady (bool state) {
    ready= state;
    std::cout<<"CPU ready "<<state<<"\n";
}
void c6502::setSo (bool state) {
    so= state;
    std::cout<<"CPU SO "<<state<<"\n";
}


void c6502::handleInstruction() {
    current_opcode = read( pc(), true);
    advance_pc();

    switch(current_opcode) {
        case 0x26:
            op_rol(addrmode_zp());
            break;
        case 0x2e:
            op_rol(addrmode_abs());
            break;
        case 0x48:
            op_pha(addrmode_stack());
            break;
        case 0x68:
            op_pla(addrmode_stack());
            break;
        case 0x85: 
            op_sta( addrmode_zp());
            break;
        case 0xa2:
            op_ldx(addrmode_immediate());
            break;
        case 0xa5:
            op_lda(addrmode_zp());
            break;
        case 0xa9:
            op_lda(addrmode_immediate());
            break;
        case 0xad:
            op_lda(addrmode_abs());
            break;
        default: std::cerr<<"Unknown command "<<std::hex<<int{current_opcode}<<" at "<<(pc() -1 )<<"\n"; abort();
    }
}

void c6502::resetSequence() {
    regPCL = read(0xfffc);
    regPCH = read(0xfffd);
}

void c6502::advance_pc() { //increment the program counter 
    Addr pc_ = pc();
    pc_++;
    // splitting the program counter into high and low bytes after incrementing it allows the CPU to efficiently address memory, utilize its limited number of address pins, and support various addressing modes required for executing instructions accurately. This splitting ensures that the CPU can access individual bytes of the memory address and move to the next instruction in memory seamlessl
    regPCH = pc_ >> 8;
    regPCL = pc_ & 0xff;
}

Addr c6502::pc() const {
    return compose(regPCH, regPCL);
}

uint8_t c6502::read(Addr address, bool sync)
{
    uint8_t result = bus_.read( this, address, sync );
    if  (reset) {
        throw CpuReset();
    }
    return result;
}
   
void c6502::write (Addr address, uint8_t data) {
    if (reset){
        bus_.read(this, address);
        throw CpuReset();
    }
    bus_.write(this, address, data);
}


uint8_t c6502::ccGet( CC cc) const {
    return bool( regStatus & (1<<int(cc)));
}

void c6502::ccSet(CC cc, bool value) {
    if(value) {
        regStatus |= 1<<int(cc);
    }
    else {
        regStatus &= ~( 1<<int(cc));
    }
}

//ADDRESS MODES

Addr c6502::addrmode_abs() {
    Addr res = read( pc() );
    advance_pc();

    res |= read( pc() ) << 8;
    advance_pc();

    return res;
}

Addr c6502::addrmode_stack () {   
    read( pc() );
    return compose(0x01, regSP);
}

Addr c6502::addrmode_immediate() {
    Addr stored_pc = pc();
    advance_pc();

    return stored_pc;
}

Addr c6502::addrmode_zp() {
    Addr addr = read( compose(regPCH, regPCL ));
    advance_pc();

    return addr;
}

//operation

//LDA (Load Accumulator) is an instruction that loads a byte of memory into the accumulator (A) register. The accumulator is a central register in the 6502 CPU, used for arithmetic and logic operations, so loading it with specific values is a common and necessary operation.
void c6502::op_lda (Addr addr) {
    regA = read( addr );
}

void c6502::op_ldx (Addr addr) {
    regX = read( addr );
}

//The function op_rol is meant to perform the Rotate Left (ROL) operation on a value stored at a specific memory address. The ROL operation shifts all bits of a value to the left by one position and rotates the most significant bit (MSB) into the carry flag, and the carry flag into the least significant bit (LSB).
void c6502::op_rol(Addr addr) {
    uint16_t value = read(addr);
    write(addr, value);

    value <<= 1;
    value |= ccGet(CC::Carry);
    ccSet( CC::Carry, value & 0x100);//copy the 8th bit
    ccSet( CC::Negative, value & 0x80);//copy the 7th bit
    ccSet( CC::Carry, (value & 0xff) == 0 );


    write(addr, value);
}


void c6502::op_sta (Addr addr) {
    write( addr, regA );
}

//The push A operation stores the contents of the accumulator register (A) onto the stack.
void c6502::op_pha (Addr addr) {
    write( addr, regA );

    regSP--;
}

//The pull A operation retrieves the value from the stack and stores it in the accumulator (A).
void c6502::op_pla(Addr addr) {
    regA = read( compose( 0x01, regSP));

    ccSet( CC::Negative, regA & 0x80);
    ccSet( CC::Zero, regA == 0);
}