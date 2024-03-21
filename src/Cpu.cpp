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

    Cpu::Cpu() : A(new register8_t(0xAA, "A")),
                 B(new register8_t(0xAC, "B")),
                 C(new register8_t(0xAD, "C")),
                 D(new register8_t(0xFF, "D")),
                 E(new register8_t(0xCD, "E")),
                 F(new register8_t(0xDE, "F")),
                 H(new register8_t(0xDE, "H")),
                 L(new register8_t(0xAF, "L")),
                 PC(new Register16(0x100, "Program Counter")),
                 SP(new Register16(0xFFFE, "Stack Pointer")),
                 FLAGS(new flag_register_t(0x50, "Flag Register")),
                 AF(new Register16(A, FLAGS)),
                 BC(new Register16(B, C)),
                 DE(new Register16(D, E)),
                 HL(new Register16(H, L))
    {
    }

    void Cpu::Execute()
    {
        byte next_byte = GetByteFromPC();
        
        if (next_byte == 0xCB)
        {
            next_byte = GetByteFromPC();
            address16_t next_instruction = address16_t((0xCB << 8) | next_byte, "CB Instruction");
            auto itr = Opcode::Instance()->opcode_map.find(next_instruction.value());
            if (itr != Opcode::Instance()->opcode_map.end())
            {
                BOOST_LOG_TRIVIAL(debug) << "Found CB instruction";
                auto cmd = itr->second;
                cmd.Execute(next_instruction);
            }
            else
            {
                BOOST_LOG_TRIVIAL(debug) << "Failed to find a mapped function for " << next_instruction << std::endl;
            }
        }
        else
        {
            auto itr = Opcode::Instance()->opcode_map.find(next_byte);
            address16_t next_instruction = address16_t(next_byte, "Instruction");
            if (itr != Opcode::Instance()->opcode_map.end())
            {
                BOOST_LOG_TRIVIAL(debug) << "Found instruction";
                auto cmd = itr->second;
                cmd.Execute(next_instruction);
            }
            else
            {
                BOOST_LOG_TRIVIAL(debug) << "Failed to find a mapped function for " << next_instruction << std::endl;
            }
        }

    }

    void Cpu::StackPush(register16_t value)
    {
        gbc::Ram::Instance()->WriteWordStack(SP->value(), value);
        SP->Set(SP->value() - 2);
    }

    uint16_t Cpu::StackPop()
    {
        uint16_t ret = gbc::Ram::Instance()->ReadWordStack(SP->value());
        SP->Set(SP->value() + 2);
        return ret;
    }

    byte Cpu::GetByteFromPC()
    {
        byte ret = gbc::Ram::Instance()->ReadByte(PC->value());
        PC->Set(PC->value() + 1);
        return ret;
    }

    uint16_t Cpu::GetWordFromPC()
    {
        uint16_t ret = gbc::Ram::Instance()->ReadWord(PC->value());
        PC->Set(PC->value() + 2);
        return ret;
    }

    void Cpu::WriteBytePC(register8_t value)
    {
        gbc::Ram::Instance()->WriteByte(PC->value(), value);
        PC->Set(PC->value() + 1);
    }

    void Cpu::WriteWordPC(register16_t value)
    {
        gbc::Ram::Instance()->WriteWord(PC->value(), value);
        PC->Set(PC->value() + 2);
    }

    std::shared_ptr<Cpu> Cpu::Instance()
    {
        static std::shared_ptr<Cpu> inst = std::make_shared<Cpu>(Cpu());
        return inst;
    }

}
