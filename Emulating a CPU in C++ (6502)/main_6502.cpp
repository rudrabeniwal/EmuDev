#include <stdio.h>
#include <stdlib.h>

    using Byte = unsigned char;
    using Word = unsigned short;
    using u32 = unsigned int;

struct Mem
{
    static constexpr u32 MAX_MEM = 1024 * 64;
    Byte Data[MAX_MEM];

    void Initialise()
    {
        for (u32 i = 0; i < MAX_MEM; i++)
        {
            Data[i]=0;
        }
    }

    //read 1 byte from memory
    Byte operator[] (u32 Address) const
    {
        return Data[Address];
    }
    //write 1 byte from memory
    Byte& operator[] (u32 Address)
    {
        return Data[Address];
    }

};

struct CPU
{
    Word PC; //program counter
    Word SP; //stack pointer

    Byte A, X, Y; //registers

    Byte C : 1; //status flag
    Byte Z : 1; //status flag
    Byte I : 1; //status flag
    Byte D : 1; //status flag
    Byte B : 1; //status flag
    Byte V : 1; //status flag
    Byte N : 1; //status flag

    void Reset ( Mem& memory)
    {
        PC = 0xFFFC;
        SP = 0X0100;
        C = Z = I = D = B = V = N = 0;
        A = X = Y = 0;
        memory.Initialise();

    }

    Byte FetchByte ( u32& cycles, Mem& memory) 
    {
        Byte Data = memory[PC];
        PC++;
        cycles--;
        return Data;
    }

     Byte ReadByte ( u32& cycles, Byte address, Mem& memory) 
    {
        Byte Data = memory[address];
        cycles--;
        return Data;
    }

    //opcodes
    /*
    LDA = Load Accumulator
    The 6502 Load Accumulator (LDA) instruction loads the accumulator with a value or the contents of a memory location.
    The accumulator is a CPU register that is used for arithmetic and data manipulation. The 6502 instruction set includes six instructions that deal with the accumulator.
    The 6502 instruction set also includes instructions to load the X and Y registers:
    LDX: Load X register
    LDY: Load Y register
    The 6502 instruction set also includes instructions to store the accumulator and X registers:
    STA: Store Accumulator
    STX: Store X register
    The 6502 instruction set also includes instructions to clear the carry and shift left one bit:
    CLC: Clear carry
    ASL: Arithmetic shift left
    */
    static constexpr Byte
        INS_LDA_IM = 0xA9;
    static constexpr Byte
        INS_LDA_ZP = 0XA5; 

    void LDASetStatus()
    {
        Z = (A ==0);
        N = (A &0b10000000) > 0;
    }
    void Execute ( u32 Cycles, Mem& memory)
    {
        while (Cycles >0)
        {
            Byte Ins = FetchByte( Cycles, memory);
            switch (Ins)
            {
            case INS_LDA_IM:
            {
                Byte Value = FetchByte( Cycles, memory);
                A = Value;
                LDASetStatus();
            }
            case INS_LDA_ZP: //the next byte after the opcode is the address in zero page
            {
                Byte ZeroPageAddress = FetchByte( Cycles, memory);
                //we want to only read a byte, not to increase the program counter -> ReadByte
                A = ReadByte( Cycles, ZeroPageAddress, memory);
                LDASetStatus();
            }
            default:
            {
                printf("Instruction not handled %d", Ins);
            } break;
            }

        }
    }
};

int main()
{
    Mem mem;
    CPU cpu;
    cpu.Reset( mem );
    /*                 Test for Immediate 
    //start of a little inline program 
    mem[0xFFFC] = CPU::INS_LDA_IM;
    mem[0xFFFD] = 0x42; //for example we want to load hex value 0x42
    //end of a little inline program
    cpu.Execute( 2, mem );
    */

    //start of a little inline program
    mem[0xFFFC] = CPU::INS_LDA_ZP;
    mem[0xFFFD] = 0x42; //for example we want to load zero page value address 0x42
    mem[0x0042] = 0x84; //at the zero page address 42 we want to stick an actual piece of data which is 84
    //end of a little inline program 
    cpu.Execute( 3, mem );
    return 0;
}