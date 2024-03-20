#ifndef CPU_H
#define CPU_H

#include <vector>
#include <stack>
#include <array>
#include <cstdint>
#include <chrono>

#include "Register.h"


namespace gbc
{

const int16_t MEM_SIZE = 4096;
const int16_t ROM_OFFSET_START = 0x200;

const byte DISPLAY_SCALE = 1;
const byte DISPLAY_WIDTH = 64 * DISPLAY_SCALE;
const byte DISPLAY_HEIGHT = 32 * DISPLAY_SCALE;
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

 

class Cpu
{

public:
    Cpu();

    void Execute();

    void StackPush(register16_t value);
    uint16_t StackPop();

    byte GetByteFromPC();
    uint16_t GetWordFromPC();

    void WriteBytePC(register8_t value);
    void WriteWordPC(register16_t value);

    static std::shared_ptr<Cpu> Instance();

    register8_t A;
    register8_t B;
    register8_t C;
    register8_t D;
    register8_t E;
    register8_t F;
    register8_t H;
    register8_t L;
    address16_t PC;
    address16_t SP;
    register16_t AF;
    register16_t BC;
    register16_t DE;
    register16_t HL;
    flag_register_t FLAGS;
    
};
}
#endif
