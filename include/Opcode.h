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
            BOOST_LOG_TRIVIAL(debug) << ins.Hex() << " Executing Opcode Instruction " << mName << " Cycles: " << mCycles;
         //   BOOST_LOG_TRIVIAL(debug) << ins;
            mCommand();
            return mCycles;
        }

    };

struct Opcode
{

    Opcode();

    std::map<uint16_t, OpcodeCommand> opcode_map;

    // 1. LD nn, n
    void LdReadByte(std::shared_ptr<register8_t> r1);

    void LdWriteByte(std::shared_ptr<register8_t> r1);

    void LdWriteWord(std::shared_ptr<Register16> r1);

    void LdReadWord(std::shared_ptr<Register16> r1);

    void Ld_A(std::shared_ptr<Register16> r1);

    void Ld_Write_A(std::shared_ptr<Register16> r1);

    void Ld_Write_A_PC();

    void Ld_HL(std::shared_ptr<register8_t> r1);

    void Ld_HL_Write(std::shared_ptr<register8_t> r1);

    void Ld_HL_WritePC();

    // 2. LD r1, r2
    void LdR1R2(std::shared_ptr<register8_t> r1, std::shared_ptr<register8_t> r2);

    void LdR1R2_16(std::shared_ptr<Register16> r1, std::shared_ptr<Register16> r2);

    // Add 8-bit
    void AddA(std::shared_ptr<register8_t> r1, std::shared_ptr<register8_t> r2);

    void AddA_HL();

    void AddA_PC();

    // Adc 8-bit. Very redundant code but more explicit i guess
    void AdcA(std::shared_ptr<register8_t> r1, std::shared_ptr<register8_t> r2);

    void AdcA_HL();

    void AdcA_PC();

    // SubA
    void SubA(std::shared_ptr<register8_t> r1, std::shared_ptr<register8_t> r2);

    void SubA_HL();

    void SubA_PC();

    // SbcA
    void SbcA(std::shared_ptr<register8_t> r1, std::shared_ptr<register8_t> r2);

    void SbcA_HL();

    void SbcA_PC();

    void AndA(std::shared_ptr<register8_t> r1, std::shared_ptr<register8_t> r2);

    void AndA_HL();

    void AndA_PC();

    void OrA(std::shared_ptr<register8_t> r1, std::shared_ptr<register8_t> r2);

    void OrA_HL();

    void OrA_PC();

    void XorA(std::shared_ptr<register8_t> r1, std::shared_ptr<register8_t> r2);

    void XorA_HL();

    void XorA_PC();

    void CpA(std::shared_ptr<register8_t> r1, std::shared_ptr<register8_t> r2);

    void CpA_HL();

    void CpA_PC();

    void IncN(std::shared_ptr<register8_t> r1);

    void DecN(std::shared_ptr<register8_t> r1);

    // Add 16-bit
    void AddHL(std::shared_ptr<Register16> r1, std::shared_ptr<Register16> r2);

    void AddSP();

    void IncN16(std::shared_ptr<Register16> r1);

    void DecN16(std::shared_ptr<Register16> r1);

    void Swap(std::shared_ptr<register8_t> r1);

    void SwapHL();

    void Push(std::shared_ptr<Register16> r1);

    void Pop(std::shared_ptr<Register16> r1);

    void DAA();

    void CCF();

    void SCF();

    void NOP();

    void HALT();

    void STOP();

    void DI();

    void EI();

    void RlcA(std::shared_ptr<register8_t> r1);

    void RlcA2(std::shared_ptr<register8_t> r1);

    void RrcA(std::shared_ptr<register8_t> r1);

    void Rla(std::shared_ptr<register8_t> r1);

    void RrA(std::shared_ptr<register8_t> r1);

    void Sla(std::shared_ptr<register8_t> r1);

    void Sra(std::shared_ptr<register8_t> r1);

    void Srl(std::shared_ptr<register8_t> r1);

    void RlcA_HL();

    void RrcA_HL();

    void Rla_HL();

    void RrA_HL();

    void Sla_HL();

    void Sra_HL();

    void Srl_HL();

    void JpNN();

    void JpCCNN(std::function<bool()> bit);

    void JpHL();

    void JrN();

    void JrCCN(std::function<bool()> bit);

    void CallNN();

    void CallCCNN(std::function<bool()> bit);

    void Rst(uint8_t address);

    void Ret();

    void RetCC(std::function<bool()> bit);

    void RetI();

    void BitBR(byte b, std::shared_ptr<register8_t> r1);

    void BitBR_HL(byte b);

    void SetBR(byte b, std::shared_ptr<register8_t> r1);

    void SetBR_HL(byte b);

    void ResBR(byte b, std::shared_ptr<register8_t> r1);

    void ResBR_HL(byte b);

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