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

    int Execute();

    void StackPush(register16_t value);
    uint16_t StackPop();

    byte GetByteFromPC();
    uint16_t GetWordFromPC();

    void WriteBytePC(register8_t value);
    void WriteWordPC(register16_t value);

    static std::shared_ptr<Cpu> Instance();

    std::shared_ptr<register8_t> A;
    std::shared_ptr<register8_t> B;
    std::shared_ptr<register8_t> C;
    std::shared_ptr<register8_t> D;
    std::shared_ptr<register8_t> E;
    std::shared_ptr<register8_t> F;
    std::shared_ptr<flag_register_t> FLAGS;
    std::shared_ptr<register8_t> H;
    std::shared_ptr<register8_t> L;
    std::shared_ptr<Register16> PC;
    std::shared_ptr<Register16> SP;
    std::shared_ptr<Register16> AF;
    std::shared_ptr<Register16> BC;
    std::shared_ptr<Register16> DE;
    std::shared_ptr<Register16> HL;

    void SetIME(bool val);
    void SetIF(bool val);

    void ProcessInterrupts();
    bool mVblankInt{false};

private:
    bool mInterruptFlag{false};
    bool mMasterInterrupt{false};   

};
}
#endif
