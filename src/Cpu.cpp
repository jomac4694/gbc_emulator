#include "Cpu.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "Opcode.h"
#include "Memory.h"
namespace gbc
{

    Cpu::Cpu() : A(new register8_t(0x00, "A")),
                 B(new register8_t(0x00, "B")),
                 C(new register8_t(0x00, "C")),
                 D(new register8_t(0x00, "D")),
                 E(new register8_t(0x00, "E")),
                 F(new register8_t(0x00, "F")),
                 H(new register8_t(0x00, "H")),
                 L(new register8_t(0x00, "L")),
                 PC(new Register16(0x100, "Program Counter")),
                 SP(new Register16(0xFFFE, "Stack Pointer")),
                 FLAGS(new flag_register_t(0x50, "Flag Register")),
                 AF(new Register16(A, FLAGS, "AF")),
                 BC(new Register16(B, C, "BC")),
                 DE(new Register16(D, E, "DE")),
                 HL(new Register16(H, L, "HL"))
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
