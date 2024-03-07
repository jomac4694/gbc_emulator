#ifndef CPU_H
#define CPU_H

#include <vector>
#include <stack>
#include <array>
#include <cstdint>
#include <chrono>
#include "Register.h"
#include "Memory.h"

namespace gbc
{

typedef unsigned char byte;
const int16_t MEM_SIZE = 4096;
const int16_t ROM_OFFSET_START = 0x200;

const byte DISPLAY_SCALE = 1;
static const byte DISPLAY_WIDTH = 64 * DISPLAY_SCALE;
static const byte DISPLAY_HEIGHT = 32 * DISPLAY_SCALE;
typedef std::array<byte, MEM_SIZE> RAM;
typedef std::stack<unsigned short> ProgramStack;


/*
    struct Instruction
    {
        Instruction(uint16_t instruction)
        {
            ins = instruction;
            I = instruction >> 12 & 0xF;
            X = instruction >> 8 & 0xF;
            Y = instruction >> 4 & 0xF;
            N = instruction & 0xF;
            NN = instruction & 0xFF;
            NNN = instruction & 0xFFF;
        }
        
        uint16_t ins;
        uint16_t I;
        uint16_t X;
        uint16_t Y;
        uint16_t N;
        uint16_t NN;
        uint16_t NNN;

    };
*/

constexpr uint32_t CPU_SPEED = 4194304; // ~4.2 million cycles per second

namespace Registers
{
    static register8_t A(0x0, "A");
    static register8_t B(0x0, "B");
    static register8_t C(0x0, "C");
    static register8_t D(0x0, "D");
    static register8_t E(0x0, "E");
    static register8_t F(0x0, "F");
    static register8_t H(0x0, "H");
    static register8_t L(0x0, "L");
    static address16_t PC(0x100, "Program Counter");
    static address16_t SP(0xFFFE, "Stack Pointer");
    static register16_t AF(0x0, "AF");
    static register16_t BC(0x0, "BC");
    static register16_t DE(0x0, "DE");
    static register16_t HL(0x0, "HL");
    static flag_register_t FLAGS(0x0, "Flag Register");
}
 

class Cpu
{

public:
    Cpu();

    void Execute();

    static void StackPush(register16_t value) { Memory::WriteWord(Registers::PC, value, true); }
    static uint16_t StackPop() { Memory::ReadWord(Registers::PC); }

    static byte GetByteFromPC() { return Memory::ReadByte(Registers::PC); }
    static uint16_t GetWordFromPC() { return Memory::ReadWord(Registers::PC); }

    static void WriteBytePC(register8_t value) { Memory::WriteByte(Registers::PC, value); }
    static void WriteWordPC(register16_t value) { Memory::WriteWord(Registers::PC, value); }
 

};
}
#endif
