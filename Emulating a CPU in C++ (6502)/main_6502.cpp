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

    Byte FetchByte ( u32 cycles, Mem& memory) 
    {
        Byte Data = memory[PC];
        PC++;
        cycles--;
        return Data;
    }

    //opcodes
    static constexpr Byte
        INS_LDA_IM = 0xA9; //LDA = Load Accumulator(eg-> Z = Zero flag, N = Negative flag)

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
                Z = (A ==0);
                N = (A &0b10000000) > 0;
            } break;
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
    //start of a little inline program
    mem[0xFFFC] = CPU::INS_LDA_IM;
    mem[0xFFFD] = 0x42; //for example we want to load hex value 0x42
    //end of a little inline program
    cpu.Execute( 2, mem );
    return 0;
}