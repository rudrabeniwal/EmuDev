#include <stdio.h>
#include <stdio.h>
#include <cstdint>
#include <stdlib.h>
#include "c6502.h"

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

    //write 1 byte in memory
    Byte& operator[] (u32 Address)
    {
        return Data[Address];
    }

    //write 2 bytes in memory
    void WriteWord(Word Value, u32 Address, u32& Cycles)
    {
        Data[Address] = Value & 0xFF;
        Data[Address + 1] = (Value >> 8);
        Cycles -= 2;
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
        cycles--;
        Byte Data = memory[PC];
        PC++;
        cycles--;
        return Data;
    }

    Byte FetchWord ( u32& cycles, Mem& memory) 
    {
        /*
        For Example - Fetching the first byte:
        memory[0x00] contains 0xAB.
        We store 0xAB in the lower-order byte of the Data variable.
        Incrementing the Program Counter (PC): PC becomes 0x01.
        Fetching the second byte:
        memory[0x01] contains 0xCD.
        We shift 0xCD left by 8 bits to position it in the higher-order byte of Data.
        Now, the Data variable contains 0xCD00.
        Decrementing the cycle count by 2.
        Finally, Data holds the assembled 16-bit word 0xCDAB.
        So, after executing FetchWord, the resulting Data variable contains the 16-bit word 0xCDAB, which was assembled from 
        the two consecutive bytes 0xAB and 0xCD fetched from memory. This process allows us to correctly interpret and use 16-bit values
        stored in memory in our CPU simulation.

        */
        u32 Data = memory[PC];/*By using u32, you ensure that you have at least 32 bits of storage space, which is sufficient to hold
        a 16-bit word without any risk of overflow or truncation */
        PC++;

        Data |= (memory[PC] << 8);
        PC++;

        cycles -= 2;
        /*
        If you wanted to handle endianess
        you would have to swap bytes here

        if ( PLATFORM_BIG_ENDIAN )
        SwapBytesInWord(Data)
        */
        return Data;
    }

    Byte ReadByte ( u32& cycles, Byte address, Mem& memory) 
    {
        //6502 is little endian
        Byte Data = memory[address];
        cycles--;
        return Data;
    }

    //opcodes

    /*

    LDA = Load Accumulator
    The 6502 Load Accumulator (LDA) instruction loads the accumulator with a value or the contents of a memory location.
    The accumulator is a special-purpose register found in many central processing units (CPUs). It's used for performing arithmetic 
    and logic operations, as well as storing intermediate results within the CPU during program execution.
    In simpler terms, think of the accumulator as a temporary storage area within the CPU where calculations happen. 
    It holds data that's being actively worked on
    by the CPU, like numbers being added or subtracted, results of logical comparisons, or data being moved around.
    The accumulator is often involved in various instructions and operations, and it plays a central role in the execution of programs by the CPU.
    It's a key component in processing data and executing instructions effectively.
    
    JSR - Jump to Subroutine
    The JSR instruction pushes the address (minus one) of the return point on to the stack and then sets the program counter
    to the target memory address.

    Operation:
    Save Return Address: The CPU pushes the address of the instruction following the JSR onto the stack. This address is typically the address of
     the next instruction after the JSR.
    Jump to Subroutine: The CPU then jumps to the specified subroutine address, which is provided as the operand of the JSR instruction.
    Execution of Subroutine: The subroutine code executes.
    Return: Upon completion of the subroutine, a return instruction (RTS - Return from Subroutine) is typically used to transfer control back to
    the instruction immediately following the JSR.
    Restore Return Address: The CPU pops the return address from the stack and resumes execution from that address.
    
    
    
    
    */
    static constexpr Byte
        INS_LDA_IM = 0xA9,
        INS_LDA_ZP = 0XA5, 
        INS_LDA_ZPX = 0XB5,
        INS_JSR = 0X20;

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
            } break;

            case INS_LDA_ZP: //the next byte after the opcode is the address in zero page
            {
                Byte ZeroPageAddr = FetchByte( Cycles, memory);
                //we want to only read a byte, not to increase the program counter -> ReadByte
                A = ReadByte( Cycles, ZeroPageAddr, memory);
                LDASetStatus();
            } break;

            case INS_LDA_ZPX: 
            {
                Byte ZeroPageAddr = FetchByte( Cycles, memory);
                ZeroPageAddr += X;
                Cycles--;
                A = ReadByte( Cycles, ZeroPageAddr, memory);
                LDASetStatus();
            } break;
            
            case INS_JSR:
            {
                Word SubAddr = FetchWord( Cycles, memory);
                memory.WriteWord(PC - 1, SP, Cycles);
                SP += 2;
                PC = SubAddr;
                Cycles--;
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
    /*
    
    Test for Immediate 

    Theory:INS_LDA_IM - Load Accumulator with Immediate value:
    This instruction loads a value directly into the Accumulator register from the immediate operand, 
    meaning the value to be loaded follows the instruction in memory.

    Operation:
    Fetch: The CPU fetches the next byte from memory after the opcode, which represents the immediate value.
    Load: The fetched byte is then loaded into the Accumulator register (A).

    Code:
    //start of a little inline program 
    mem[0xFFFC] = CPU::INS_LDA_IM;
    mem[0xFFFD] = 0x42; //for example we want to load hex value 0x42
    //end of a little inline program
    cpu.Execute( 2, mem );

    */

    /*

    Test for Zero Page

    INS_LDA_ZP - Load Accumulator from Zero Page:
    This instruction loads a value from the zero page (first 256 bytes of memory) into the Accumulator register.
    
    Operation:
    Fetch: The CPU fetches the next byte from memory after the opcode, which represents the address in the zero page.
    Read: It reads the byte from memory at the address specified in the zero page.
    Load: The value read from the zero page is then loaded into the Accumulator register (A).
    
    
    //Code:
    //start of a little inline program
    mem[0xFFFC] = CPU::INS_LDA_ZP;
    mem[0xFFFD] = 0x42; //for example we want to load zero page value address 0x42
    mem[0x0042] = 0x84; //at the zero page address 42 we want to stick an actual piece of data which is 84
    //end of a little inline program 
    cpu.Execute( 3, mem );

    */

   /*

   Test for Zero Page X

   The instruction INS_LDA_ZPX is a variation of the LDA (Load Accumulator) instruction, specifically designed to load data 
   into the accumulator from a memory location in the zero page, with an additional offset provided by the X register. 

   Here's a detailed explanation:
   Instruction Name:
   Mnemonic: LDA (Load Accumulator)
   Addressing Mode: Zero Page Indexed with X (ZPX)
   Operation:
   Fetch Operand: The CPU fetches the opcode INS_LDA_ZPX from memory.
   Calculate Address: It then fetches the next byte, which represents the base address in the zero page. 
   The value of the X register is added to this base address to calculate the effective address.
   Load Data: The CPU reads the byte stored at the calculated effective address and loads it into the Accumulator register (A).
   
   Code:

   //start of a little inline program
    mem[0xFFFC] = CPU::INS_LDA_ZP;
    mem[0xFFFD] = 0x42;
    mem[0x0042] = 0x84;
    //end of a little inline program 
    cpu.Execute( 4, mem );
   
   */


   //start of a little inline program
    mem[0xFFFC] = CPU::INS_JSR;
    mem[0xFFFD] = 0x42;
    mem[0xFFFE] = 0x42;
    mem[0x4242] = CPU::INS_LDA_IM;
    mem[0x4243] = 0x84;
    //end of a little inline program 
    cpu.Execute( 9, mem );
   

    return 0;
}