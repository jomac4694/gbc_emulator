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

    Cpu::Cpu() : A(0x0, "A"),
                 B(0x0, "B"),
                 C(0x0, "C"),
                 D(0x0, "D"),
                 E(0x0, "E"),
                 F(0x0, "F"),
                 H(0x0, "H"),
                 L(0x0, "L"),
                 PC(0x100, "Program Counter"),
                 SP(0xFFFE, "Stack Pointer"),
                 AF(0x0, "AF"),
                 BC(0x0, "BC"),
                 DE(0x0, "DE"),
                 HL(0x0, "HL"),
                 FLAGS(0x0, "Flag Register")
    {


    }

    void Cpu::Execute()
    {
        address16_t next_instruction = 0x8000;
        std::cout << "nibs=" << (uint16_t)next_instruction.GetNibbles(0, 1) << std::endl;
        auto itr = Opcode::Instance()->opcode_map.find((uint16_t)next_instruction.GetNibbles(0, 1));
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
            BOOST_LOG_TRIVIAL(debug) << "Failed to find a mapped function" << std::endl;
        }
    }

    void Cpu::StackPush(register16_t value) { gbc::Ram::Instance()->WriteWord(PC, value, true); }
    uint16_t Cpu::StackPop() { gbc::Ram::Instance()->ReadWord(PC); }

    byte Cpu::GetByteFromPC() { return gbc::Ram::Instance()->ReadByte(PC); }
    uint16_t Cpu::GetWordFromPC() { return gbc::Ram::Instance()->ReadWord(PC); }

    void Cpu::WriteBytePC(register8_t value) { gbc::Ram::Instance()->WriteByte(PC, value); }
    void Cpu::WriteWordPC(register16_t value) { gbc::Ram::Instance()->WriteWord(PC, value); }

    std::shared_ptr<Cpu> Cpu::Instance()
    {
        static std::shared_ptr<Cpu> inst = std::make_shared<Cpu>(Cpu());
        return inst;
    }

}
