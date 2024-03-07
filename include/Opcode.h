#ifndef OPCODE_H
#define OPCODE_H

#include <map>
#include <string>
#include <functional>
#include <iostream>
#include "Cpu.h"
#include <boost/log/trivial.hpp>
#include "Memory.h"
namespace gbc
{
namespace Opcode
{
    struct OpcodeCommand
    {
        OpcodeCommand(std::string name, std::function<void()> command, int cycles)
        : mName(name),
          mCommand(command),
          mCycles(cycles)
        {

        }
        std::function<void()> mCommand;
        std::string mName;
        int mCycles;

        int Execute(address16_t ins)
        {
            BOOST_LOG_TRIVIAL(debug) << "Executing Opcode Instruction " << mName;
            BOOST_LOG_TRIVIAL(debug) << ins;
            mCommand();
            return mCycles;
        }

    };

namespace Commands
{
    // 1. LD nn, n
    void LdReadByte(register8_t* r1)
    {
        byte read = Cpu::GetByteFromPC();
    }

    void LdWriteByte(register8_t* r1)
    {
        Cpu::WriteBytePC(r1->value());
    }



    // 2. LD r1, r2
    void LdR1R2(register8_t* r1, register8_t* r2)
    {
        BOOST_LOG_TRIVIAL(debug) << *r1;
        BOOST_LOG_TRIVIAL(debug) << *r2;
        *r1 = *r2;
    }

    void AddA(register8_t* r1, register8_t* r2)
    {
        *r1 = r1->value() + r2->value();
    }

    void Push(register16_t* r1)
    {
        Cpu::StackPush(*r1);
    }
}

    using namespace Registers;
    using namespace Commands;
    static std::map<unsigned short, OpcodeCommand> opcode_map =
    {
        // LD r1,r2
        // Put value r2 into r1
        {0xF8, OpcodeCommand("LdR1R2->A:A", std::bind(&LdR1R2, &A, &A), 4)},
        {0xF9, OpcodeCommand("LdR1R2->A:B", std::bind(&LdR1R2, &A, &B), 4)},
    };
};
}
#endif