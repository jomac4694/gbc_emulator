#include "Cpu.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "Opcode.h"
#include "Memory.h"
namespace gbc
{

    /*
    void PrintInstruction(Instruction ins)
    {
        std::cout << "X: " << (int) ins.X << std::endl;
        std::cout << "Y: " << (int) ins.Y << std::endl;
        std::cout << "N: " << (int) ins.N << std::endl;
        std::cout << "NN: " << (int) ins.NN << std::endl;
        std::cout << "NNN: " << (int) ins.NNN << std::endl;
    }
    */

    Cpu::Cpu() : A(0xAA, "A"),
                 B(0xAC, "B"),
                 C(0xAD, "C"),
                 D(0xFF, "D"),
                 E(0xCD, "E"),
                 F(0xDE, "F"),
                 H(0xDE, "H"),
                 L(0xAF, "L"),
                 PC(0x100, "Program Counter"),
                 SP(0xFFFE, "Stack Pointer"),
                 AF(0xFFFF, "AF"),
                 BC(0xFBFB, "BC"),
                 DE(0xBFBF, "DE"),
                 HL(0xFFFF, "HL"),
                 FLAGS(0x0, "Flag Register")
    {
    }

    void Cpu::Execute()
    {
        address16_t next_instruction = address16_t(GetWordFromPC(), "Instruction");
        std::cout << "nibs=" << (uint16_t)next_instruction.GetNibbles(0, 1) << std::endl;
        auto itr = Opcode::Instance()->opcode_map.find((uint16_t)next_instruction.GetNibbles(0, 3));
        if (itr != Opcode::Instance()->opcode_map.end())
        {
            BOOST_LOG_TRIVIAL(debug) << "Found instruction";
            auto cmd = itr->second;
            std::cout << (int)itr->first << std::endl;
            std::cout << "executing" << std::endl;
            cmd.Execute(next_instruction);
        }
        else
        {
            BOOST_LOG_TRIVIAL(debug) << "Failed to find a mapped function for " << next_instruction << std::endl;
        }
    }

    void Cpu::StackPush(register16_t value)
    {
        gbc::Ram::Instance()->WriteWord(SP, value);
        SP--;
        SP--;
    }

    uint16_t Cpu::StackPop()
    {
        uint16_t ret = gbc::Ram::Instance()->ReadWord(SP);
        SP++;
        SP++;
        return ret;
    }

    byte Cpu::GetByteFromPC()
    {
        byte ret = gbc::Ram::Instance()->ReadByte(PC);
        PC++;
        return ret;
    }

    uint16_t Cpu::GetWordFromPC()
    {
        uint16_t ret = gbc::Ram::Instance()->ReadWord(PC);
        PC++;
        PC++;
        return ret;
    }

    void Cpu::WriteBytePC(register8_t value)
    {
        gbc::Ram::Instance()->WriteByte(PC, value);
        PC++;
    }

    void Cpu::WriteWordPC(register16_t value)
    {
        gbc::Ram::Instance()->WriteWord(PC, value);
        PC++;
        PC++;
    }

    std::shared_ptr<Cpu> Cpu::Instance()
    {
        static std::shared_ptr<Cpu> inst = std::make_shared<Cpu>(Cpu());
        return inst;
    }

}
