#ifndef OPCODE_H
#define OPCODE_H

#include <map>
#include <string>
#include <functional>
#include <iostream>
#include <boost/log/trivial.hpp>
#include "Register.h"
#include "Cpu.h"
#include <memory>
namespace gbc
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
            BOOST_LOG_TRIVIAL(debug) << "Executing Opcode Instruction " << mName << " Cycles: " << mCycles;
            BOOST_LOG_TRIVIAL(debug) << ins;
            mCommand();
            return mCycles;
        }

    };

struct Opcode
{

    Opcode();

    std::map<uint16_t, OpcodeCommand> opcode_map;

    // 1. LD nn, n
    void LdReadByte(register8_t* r1);

    void LdWriteByte(register8_t* r1);

    void LdWriteWord(register16_t* r1);

    void LdReadWord(register16_t* r1);

    void Ld_A(register16_t* r1);

    void Ld_HL(register8_t* r1);

    void Ld_HL_Write(register8_t* r1);

    void Ld_HL_WritePC();

    // 2. LD r1, r2
    void LdR1R2(register8_t* r1, register8_t* r2);

    void LdR1R2_16(register16_t* r1, register16_t* r2);

    // Add 8-bit
    void AddA(register8_t* r1, register8_t* r2);

    void AddA_HL();

    void AddA_PC();

    // Adc 8-bit. Very redundant code but more explicit i guess
    void AdcA(register8_t* r1, register8_t* r2);

    void AdcA_HL();

    void AdcA_PC();

    // SubA
    void SubA(register8_t* r1, register8_t* r2);

    void SubA_HL();

    void SubA_PC();

    // SbcA
    void SbcA(register8_t* r1, register8_t* r2);

    void SbcA_HL();

    void SbcA_PC();

    void AndA(register8_t* r1, register8_t* r2);

    void AndA_HL();

    void AndA_PC();

    void OrA(register8_t* r1, register8_t* r2);

    void OrA_HL();

    void OrA_PC();

    void XorA(register8_t* r1, register8_t* r2);

    void XorA_HL();

    void XorA_PC();

    void CpA(register8_t* r1, register8_t* r2);

    void CpA_HL();

    void CpA_PC();

    void IncN(register8_t* r1);

    void DecN(register8_t* r1);

    // Add 16-bit
    void AddHL(register16_t* r1, register16_t* r2);

    void AddSP();

    void IncN16(register16_t* r1);

    void DecN16(register16_t* r1);

    void Swap(register8_t* r1);

    void SwapHL();

    void Push(register16_t* r1);

    void Pop(register16_t* r1);

    static std::shared_ptr<Opcode> Instance();

    // =
    //{
        // LD r1,r2
        // Put value r2 into r1
      //  {0xF8, std::shared_ptr<OpcodeCommand>(new OpcodeCommand("LdR1R2->A:A", std::bind(&LdR1R2, Registers::A.get(), Registers::A.get()), 4))},
      //  {0xF9, std::shared_ptr<OpcodeCommand>(new OpcodeCommand("LdR1R2->A:B", std::bind(&LdR1R2, Registers::A.get(), Registers::B.get()), 4))},
    //};

};


}
#endif