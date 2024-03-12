#include "Opcode.h"

#include "Memory.h"

namespace gbc
{

    Opcode::Opcode()
    {
        opcode_map = 
            {
// 8-bit LD                
{0x7F, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->A), &(Cpu::Instance()->A)), 4)},
{0x78, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->A), &(Cpu::Instance()->B)), 4)},
{0x79, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->A), &(Cpu::Instance()->C)), 4)},
{0x7A, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->A), &(Cpu::Instance()->D)), 4)},
{0x7B, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->A), &(Cpu::Instance()->E)), 4)},
{0x7C, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->A), &(Cpu::Instance()->H)), 4)},
{0x7D, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->A), &(Cpu::Instance()->L)), 4)},
{0x40, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->B), &(Cpu::Instance()->B)), 4)},
{0x41, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->B), &(Cpu::Instance()->C)), 4)},
{0x42, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->B), &(Cpu::Instance()->D)), 4)},
{0x43, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->B), &(Cpu::Instance()->E)), 4)},
{0x44, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->B), &(Cpu::Instance()->H)), 4)},
{0x45, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->B), &(Cpu::Instance()->L)), 4)},
{0x48, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->C), &(Cpu::Instance()->B)), 4)},
{0x49, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->C), &(Cpu::Instance()->C)), 4)},
{0x4A, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->C), &(Cpu::Instance()->D)), 4)},
{0x4B, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->C), &(Cpu::Instance()->E)), 4)},
{0x4C, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->C), &(Cpu::Instance()->H)), 4)},
{0x4D, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->C), &(Cpu::Instance()->L)), 4)},
{0x50, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->D), &(Cpu::Instance()->B)), 4)},
{0x51, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->D), &(Cpu::Instance()->C)), 4)},
{0x52, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->D), &(Cpu::Instance()->D)), 4)},
{0x53, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->D), &(Cpu::Instance()->E)), 4)},
{0x54, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->D), &(Cpu::Instance()->H)), 4)},
{0x55, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->D), &(Cpu::Instance()->L)), 4)},
{0x58, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->E), &(Cpu::Instance()->B)), 4)},
{0x59, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->E), &(Cpu::Instance()->C)), 4)},
{0x5A, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->E), &(Cpu::Instance()->D)), 4)},
{0x5B, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->E), &(Cpu::Instance()->E)), 4)},
{0x5C, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->E), &(Cpu::Instance()->H)), 4)},
{0x5D, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->E), &(Cpu::Instance()->L)), 4)},
{0x60, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->H), &(Cpu::Instance()->B)), 4)},
{0x61, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->H), &(Cpu::Instance()->C)), 4)},
{0x62, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->H), &(Cpu::Instance()->D)), 4)},
{0x63, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->H), &(Cpu::Instance()->E)), 4)},
{0x64, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->H), &(Cpu::Instance()->H)), 4)},
{0x65, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->H), &(Cpu::Instance()->L)), 4)},
{0x68, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->L), &(Cpu::Instance()->B)), 4)},
{0x69, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->L), &(Cpu::Instance()->C)), 4)},
{0x6A, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->L), &(Cpu::Instance()->D)), 4)},
{0x6B, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->L), &(Cpu::Instance()->E)), 4)},
{0x6C, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->L), &(Cpu::Instance()->H)), 4)},
{0x6D, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, &(Cpu::Instance()->L), &(Cpu::Instance()->L)), 4)},

// 8-bit ALU section
// AddA
{0x87, OpcodeCommand("0x87 AddA A:A", std::bind(&Opcode::AddA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->A)), 4)},
{0x80, OpcodeCommand("0x80 AddA A:B", std::bind(&Opcode::AddA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->B)), 4)},
{0x81, OpcodeCommand("0x81 AddA A:C", std::bind(&Opcode::AddA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->C)), 4)},
{0x82, OpcodeCommand("0x82 AddA A:D", std::bind(&Opcode::AddA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->D)), 4)},
{0x83, OpcodeCommand("0x83 AddA A:E", std::bind(&Opcode::AddA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->E)), 4)},
{0x84, OpcodeCommand("0x84 AddA A:H", std::bind(&Opcode::AddA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->H)), 4)},
{0x85, OpcodeCommand("0x85 AddA A:L", std::bind(&Opcode::AddA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->L)), 4)},
{0x86, OpcodeCommand("0x86 AddA_HL A:(HL)", std::bind(&Opcode::AddA_HL, this), 8)},
{0xC6, OpcodeCommand("0xC6 AddA_PC A:#", std::bind(&Opcode::AddA_PC, this), 8)},
// AdcA
{0x8F, OpcodeCommand("0x8F AdcA A:A", std::bind(&Opcode::AdcA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->A)), 4)},
{0x88, OpcodeCommand("0x88 AdcA A:B", std::bind(&Opcode::AdcA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->B)), 4)},
{0x89, OpcodeCommand("0x89 AdcA A:C", std::bind(&Opcode::AdcA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->C)), 4)},
{0x8A, OpcodeCommand("0x8A AdcA A:D", std::bind(&Opcode::AdcA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->D)), 4)},
{0x8B, OpcodeCommand("0x8B AdcA A:E", std::bind(&Opcode::AdcA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->E)), 4)},
{0x8C, OpcodeCommand("0x8C AdcA A:H", std::bind(&Opcode::AdcA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->H)), 4)},
{0x8D, OpcodeCommand("0x8D AdcA A:L", std::bind(&Opcode::AdcA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->L)), 4)},
{0x8E, OpcodeCommand("0x8E AdcA_HL A:(HL)", std::bind(&Opcode::AdcA_HL, this), 8)},
{0xCE, OpcodeCommand("0xCE AdcA_PC A:#", std::bind(&Opcode::AdcA_PC, this), 8)},
// SubA
{0x97, OpcodeCommand("0x97 SubA A:A", std::bind(&Opcode::SubA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->A)), 4)},
{0x90, OpcodeCommand("0x90 SubA A:B", std::bind(&Opcode::SubA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->B)), 4)},
{0x91, OpcodeCommand("0x91 SubA A:C", std::bind(&Opcode::SubA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->C)), 4)},
{0x92, OpcodeCommand("0x92 SubA A:D", std::bind(&Opcode::SubA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->D)), 4)},
{0x93, OpcodeCommand("0x93 SubA A:E", std::bind(&Opcode::SubA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->E)), 4)},
{0x94, OpcodeCommand("0x94 SubA A:H", std::bind(&Opcode::SubA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->H)), 4)},
{0x95, OpcodeCommand("0x95 SubA A:L", std::bind(&Opcode::SubA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->L)), 4)},
{0x96, OpcodeCommand("0x96 SubA_HL (HL):", std::bind(&Opcode::SubA_HL, this), 8)},
{0xD6, OpcodeCommand("0xD6 SubA_PC #:", std::bind(&Opcode::SubA_PC, this), 8)},
{0x9F, OpcodeCommand("0x9F SbcA A:A", std::bind(&Opcode::SbcA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->A)), 4)},
{0x98, OpcodeCommand("0x98 SbcA A:B", std::bind(&Opcode::SbcA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->B)), 4)},
{0x99, OpcodeCommand("0x99 SbcA A:C", std::bind(&Opcode::SbcA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->C)), 4)},
{0x9A, OpcodeCommand("0x9A SbcA A:D", std::bind(&Opcode::SbcA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->D)), 4)},
{0x9B, OpcodeCommand("0x9B SbcA A:E", std::bind(&Opcode::SbcA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->E)), 4)},
{0x9C, OpcodeCommand("0x9C SbcA A:H", std::bind(&Opcode::SbcA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->H)), 4)},
{0x9D, OpcodeCommand("0x9D SbcA A:L", std::bind(&Opcode::SbcA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->L)), 4)},
{0x9E, OpcodeCommand("0x9E SbcA_HL A:(HL)", std::bind(&Opcode::SbcA_HL, this), 8)},
{0xA7, OpcodeCommand("0xA7 AndA A:A", std::bind(&Opcode::AndA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->A)), 4)},
{0xA0, OpcodeCommand("0xA0 AndA A:B", std::bind(&Opcode::AndA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->B)), 4)},
{0xA1, OpcodeCommand("0xA1 AndA A:C", std::bind(&Opcode::AndA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->C)), 4)},
{0xA2, OpcodeCommand("0xA2 AndA A:D", std::bind(&Opcode::AndA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->D)), 4)},
{0xA3, OpcodeCommand("0xA3 AndA A:E", std::bind(&Opcode::AndA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->E)), 4)},
{0xA4, OpcodeCommand("0xA4 AndA A:H", std::bind(&Opcode::AndA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->H)), 4)},
{0xA5, OpcodeCommand("0xA5 AndA A:L", std::bind(&Opcode::AndA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->L)), 4)},
{0xA6, OpcodeCommand("0xA6 AndA_HL (HL):", std::bind(&Opcode::AndA_HL, this), 8)},
{0xE6, OpcodeCommand("0xE6 AndA_PC #:", std::bind(&Opcode::AndA_PC, this), 8)},
{0xB7, OpcodeCommand("0xB7 OrA A:A", std::bind(&Opcode::OrA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->A)), 4)},
{0xB0, OpcodeCommand("0xB0 OrA A:B", std::bind(&Opcode::OrA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->B)), 4)},
{0xB1, OpcodeCommand("0xB1 OrA A:C", std::bind(&Opcode::OrA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->C)), 4)},
{0xB2, OpcodeCommand("0xB2 OrA A:D", std::bind(&Opcode::OrA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->D)), 4)},
{0xB3, OpcodeCommand("0xB3 OrA A:E", std::bind(&Opcode::OrA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->E)), 4)},
{0xB4, OpcodeCommand("0xB4 OrA A:H", std::bind(&Opcode::OrA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->H)), 4)},
{0xB5, OpcodeCommand("0xB5 OrA A:L", std::bind(&Opcode::OrA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->L)), 4)},
{0xB6, OpcodeCommand("0xB6 OrA_HL (HL):", std::bind(&Opcode::OrA_HL, this), 8)},
{0xF6, OpcodeCommand("0xF6 OrA_PC #:", std::bind(&Opcode::OrA_PC, this), 8)},
{0xAF, OpcodeCommand("0xAF XorA A:A", std::bind(&Opcode::XorA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->A)), 4)},
{0xA8, OpcodeCommand("0xA8 XorA A:B", std::bind(&Opcode::XorA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->B)), 4)},
{0xA9, OpcodeCommand("0xA9 XorA A:C", std::bind(&Opcode::XorA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->C)), 4)},
{0xAA, OpcodeCommand("0xAA XorA A:D", std::bind(&Opcode::XorA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->D)), 4)},
{0xAB, OpcodeCommand("0xAB XorA A:E", std::bind(&Opcode::XorA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->E)), 4)},
{0xAC, OpcodeCommand("0xAC XorA A:H", std::bind(&Opcode::XorA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->H)), 4)},
{0xAD, OpcodeCommand("0xAD XorA A:L", std::bind(&Opcode::XorA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->L)), 4)},
{0xAE, OpcodeCommand("0xAE XorA_HL A:(HL)", std::bind(&Opcode::XorA_HL, this), 8)},
{0xEE, OpcodeCommand("0xEE XorA_PC A:#", std::bind(&Opcode::XorA_PC, this), 8)},
{0xBF, OpcodeCommand("0xBF CpA A:A", std::bind(&Opcode::CpA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->A)), 4)},
{0xB8, OpcodeCommand("0xB8 CpA A:B", std::bind(&Opcode::CpA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->B)), 4)},
{0xB9, OpcodeCommand("0xB9 CpA A:C", std::bind(&Opcode::CpA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->C)), 4)},
{0xBA, OpcodeCommand("0xBA CpA A:D", std::bind(&Opcode::CpA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->D)), 4)},
{0xBB, OpcodeCommand("0xBB CpA A:E", std::bind(&Opcode::CpA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->E)), 4)},
{0xBC, OpcodeCommand("0xBC CpA A:H", std::bind(&Opcode::CpA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->H)), 4)},
{0xBD, OpcodeCommand("0xBD CpA A:L", std::bind(&Opcode::CpA, this, &(Cpu::Instance()->A), &(Cpu::Instance()->L)), 4)},
{0xBE, OpcodeCommand("0xBE CpA_HL A:(HL)", std::bind(&Opcode::CpA_HL, this), 8)},
{0xFE, OpcodeCommand("0xFE CpA_PC A:#", std::bind(&Opcode::CpA_PC, this), 8)},
            };
    }

    // 1. LD nn, n
    void Opcode::LdReadByte(register8_t* r1)
    {
        byte read = Cpu::Instance()->GetByteFromPC();
        *r1 = read;
    }

    void Opcode::LdWriteByte(register8_t* r1)
    {
        Cpu::Instance()->WriteBytePC(*r1);
    }

    void Opcode::LdWriteWord(register16_t* r1)
    {
        Cpu::Instance()->WriteWordPC(*r1);
    }

    void Opcode::LdReadWord(register16_t* r1)
    {
        uint16_t read = Cpu::Instance()->GetWordFromPC();
        *r1 = read;
    }

    void Opcode::Ld_HL(register8_t* r1)
    {
        byte read = gbc::Ram::Instance()->ReadByte(Cpu::Instance()->HL.value());
        *r1 = read;
    }

    // 2. LD r1, r2
    void Opcode::LdR1R2(register8_t* r1, register8_t* r2)
    {
        r1->mValue = r2->mValue;
        BOOST_LOG_TRIVIAL(debug) << r1;
        BOOST_LOG_TRIVIAL(debug) << r2;
    }

    void Opcode::LdR1R2_16(register16_t* r1, register16_t* r2)
    {
        r1->mValue = r2->mValue;
        BOOST_LOG_TRIVIAL(debug) << r1;
        BOOST_LOG_TRIVIAL(debug) << r2;
    }

    // Add 8-bit
    void Opcode::AddA(register8_t* r1, register8_t* r2)
    {
        uint32_t result = r1->value() + r2->value();

        Cpu::Instance()->FLAGS.SetZeroFlag(result == 0x0);
        Cpu::Instance()->FLAGS.SetSubtractFlag(false);
        Cpu::Instance()->FLAGS.SetHalfCarryFlag((0xF & r1->value()) + (0xF & r2->value()) > 0xF);
        Cpu::Instance()->FLAGS.SetCarryFlag((result & 0x100) != 0);

        r1->mValue = static_cast<byte>(result);
    }

    void Opcode::AddA_HL()
    {
        register8_t byte = register8_t(gbc::Ram::Instance()->ReadByte(Cpu::Instance()->HL.value()));
        AddA(&(Cpu::Instance()->A), &byte);
    }

    void Opcode::AddA_PC()
    {
        register8_t byte = Cpu::Instance()->GetByteFromPC();
        AddA(&(Cpu::Instance()->A), &byte);
    }

    // Adc 8-bit. Very redundant code but more explicit i guess
    void Opcode::AdcA(register8_t* r1, register8_t* r2)
    {
        uint32_t result = r1->value() + r2->value() + Cpu::Instance()->FLAGS.CarryFlag();

        Cpu::Instance()->FLAGS.SetZeroFlag(result == 0x0);
        Cpu::Instance()->FLAGS.SetSubtractFlag(false);
        Cpu::Instance()->FLAGS.SetHalfCarryFlag((0xF & r1->value()) + (0xF & r2->value() + Cpu::Instance()->FLAGS.CarryFlag()) > 0xF);
        Cpu::Instance()->FLAGS.SetCarryFlag((result & 0x100) != 0);

        r1->mValue = static_cast<byte>(result);
    }

    void Opcode::AdcA_HL()
    {
        register8_t byte = register8_t(gbc::Ram::Instance()->ReadByte(Cpu::Instance()->HL.value()));
        AdcA(&(Cpu::Instance()->A), &byte);
    }

    void Opcode::AdcA_PC()
    {
        register8_t byte = Cpu::Instance()->GetByteFromPC();
        AdcA(&(Cpu::Instance()->A), &byte);
    }

    // SubA
    void Opcode::SubA(register8_t* r1, register8_t* r2)
    {
        byte result = r1->value() - r2->value();

        Cpu::Instance()->FLAGS.SetZeroFlag(result == 0x0);
        Cpu::Instance()->FLAGS.SetSubtractFlag(true);
        Cpu::Instance()->FLAGS.SetHalfCarryFlag(((0xF & r1->value()) - (0xF & r2->value())) < 0);
        Cpu::Instance()->FLAGS.SetCarryFlag(r1->value() < r2->value());

        r1->mValue = result;
    }

    void Opcode::SubA_HL()
    {
        register8_t byte = register8_t(gbc::Ram::Instance()->ReadByte(Cpu::Instance()->HL.value()));
        SubA(&(Cpu::Instance()->A), &byte);
    }

    void Opcode::SubA_PC()
    {
        register8_t byte = Cpu::Instance()->GetByteFromPC();
        SubA(&(Cpu::Instance()->A), &byte);
    }

    // SbcA
    void Opcode::SbcA(register8_t* r1, register8_t* r2)
    {
        byte result = r1->value() - r2->value() - Cpu::Instance()->FLAGS.CarryFlag();

        Cpu::Instance()->FLAGS.SetZeroFlag(result == 0x0);
        Cpu::Instance()->FLAGS.SetSubtractFlag(true);
        Cpu::Instance()->FLAGS.SetHalfCarryFlag((0xF & r1->value()) - (0xF & r2->value()) - Cpu::Instance()->FLAGS.CarryFlag() < 0);
        Cpu::Instance()->FLAGS.SetCarryFlag(r1->value() < r2->value());

        r1->mValue = result;
    }

    void Opcode::SbcA_HL()
    {
        register8_t byte = register8_t(gbc::Ram::Instance()->ReadByte(Cpu::Instance()->HL.value()));
        SbcA(&(Cpu::Instance()->A), &byte);
    }

    void Opcode::SbcA_PC()
    {
        register8_t byte = Cpu::Instance()->GetByteFromPC();
        SbcA(&(Cpu::Instance()->A), &byte);
    }

    void Opcode::AndA(register8_t* r1, register8_t* r2)
    {
        byte result = r1->mValue & r2->mValue;

        Cpu::Instance()->FLAGS.SetZeroFlag(result == 0x0);
        Cpu::Instance()->FLAGS.SetSubtractFlag(false);
        Cpu::Instance()->FLAGS.SetHalfCarryFlag(true);
        Cpu::Instance()->FLAGS.SetCarryFlag(false);

        r1->mValue = result;
    }

    void Opcode::AndA_HL()
    {
        register8_t byte = register8_t(gbc::Ram::Instance()->ReadByte(Cpu::Instance()->HL.value()));
        AndA(&(Cpu::Instance()->A), &byte);
    }

    void Opcode::AndA_PC()
    {
        register8_t byte = Cpu::Instance()->GetByteFromPC();
        AndA(&(Cpu::Instance()->A), &byte);
    }

    void Opcode::OrA(register8_t* r1, register8_t* r2)
    {
        byte result = r1->mValue | r2->mValue;

        Cpu::Instance()->FLAGS.SetZeroFlag(result == 0x0);
        Cpu::Instance()->FLAGS.SetSubtractFlag(false);
        Cpu::Instance()->FLAGS.SetHalfCarryFlag(false);
        Cpu::Instance()->FLAGS.SetCarryFlag(false);

        r1->mValue = result;
    }

    void Opcode::OrA_HL()
    {
        register8_t byte = register8_t(gbc::Ram::Instance()->ReadByte(Cpu::Instance()->HL.value()));
        OrA(&(Cpu::Instance()->A), &byte);
    }

    void Opcode::OrA_PC()
    {
        register8_t byte = Cpu::Instance()->GetByteFromPC();
        OrA(&(Cpu::Instance()->A), &byte);
    }

    void Opcode::XorA(register8_t* r1, register8_t* r2)
    {
        byte result = r1->mValue ^ r2->mValue;

        Cpu::Instance()->FLAGS.SetZeroFlag(result == 0x0);
        Cpu::Instance()->FLAGS.SetSubtractFlag(false);
        Cpu::Instance()->FLAGS.SetHalfCarryFlag(false);
        Cpu::Instance()->FLAGS.SetCarryFlag(false);

        r1->mValue = result;
    }

    void Opcode::XorA_HL()
    {
        register8_t byte = register8_t(gbc::Ram::Instance()->ReadByte(Cpu::Instance()->HL.value()));
        XorA(&(Cpu::Instance()->A), &byte);
    }

    void Opcode::XorA_PC()
    {
        register8_t byte = Cpu::Instance()->GetByteFromPC();
        XorA(&(Cpu::Instance()->A), &byte);
    }

    void Opcode::CpA(register8_t* r1, register8_t* r2)
    {
        byte result = r1->value() - r2->value();

        Cpu::Instance()->FLAGS.SetZeroFlag(result == 0x0);
        Cpu::Instance()->FLAGS.SetSubtractFlag(true);
        Cpu::Instance()->FLAGS.SetHalfCarryFlag((0xF & r1->value()) - (0xF & r2->value()) < 0);
        Cpu::Instance()->FLAGS.SetCarryFlag(r1->value() < r2->value());
    }

    void Opcode::CpA_HL()
    {
        register8_t byte = register8_t(gbc::Ram::Instance()->ReadByte(Cpu::Instance()->HL.value()));
        CpA(&(Cpu::Instance()->A), &byte);
    }

    void Opcode::CpA_PC()
    {
        register8_t byte = Cpu::Instance()->GetByteFromPC();
        CpA(&(Cpu::Instance()->A), &byte);
    }

    void Opcode::IncN(register8_t* r1)
    {
        (r1)++;
        Cpu::Instance()->FLAGS.SetZeroFlag(r1->value() == 0x0);
        Cpu::Instance()->FLAGS.SetSubtractFlag(false);
        Cpu::Instance()->FLAGS.SetHalfCarryFlag((0x10 & r1->value()) != 0);
    }

    void Opcode::DecN(register8_t* r1)
    {
        (r1)--;
        Cpu::Instance()->FLAGS.SetZeroFlag(r1->value() == 0x0);
        Cpu::Instance()->FLAGS.SetSubtractFlag(true);
        Cpu::Instance()->FLAGS.SetHalfCarryFlag((r1->value() & 0xF) < 0);
    }

    // Add 16-bit
    void Opcode::AddHL(register16_t* r1, register16_t* r2)
    {
        uint32_t result = r1->value() + r2->value();

        Cpu::Instance()->FLAGS.SetZeroFlag(result == 0x0);
        Cpu::Instance()->FLAGS.SetSubtractFlag(false);
        Cpu::Instance()->FLAGS.SetHalfCarryFlag((0xFFF & r1->value()) + (0xFFF & r2->value()) > 0xF);
        Cpu::Instance()->FLAGS.SetCarryFlag((result & 0x10000) != 0);

        r1->mValue = static_cast<uint16_t>(result);
    }

    void Opcode::IncN16(register16_t* r1)
    {
        (r1)++;
    }

    void Opcode::DecN16(register16_t* r1)
    {
        (r1)--;
    }

    void Opcode::Swap(register8_t* r1)
    {
        byte high = r1->High();
        byte low = r1->Low();
        r1->mValue = (low << 4) | high;
        Cpu::Instance()->FLAGS.SetZeroFlag(r1->value() == 0x0);
        Cpu::Instance()->FLAGS.SetSubtractFlag(false);
        Cpu::Instance()->FLAGS.SetHalfCarryFlag(false);
        Cpu::Instance()->FLAGS.SetCarryFlag(false);
    }

    void Opcode::SwapHL()
    {
        register8_t byte = gbc::Ram::Instance()->ReadByte(Cpu::Instance()->HL.value());
        Swap(&byte);
        gbc::Ram::Instance()->WriteByte(Cpu::Instance()->HL.value(), byte.value());
    }

    void Opcode::Push(register16_t* r1)
    {
        Cpu::Instance()->StackPush(*r1);
    }

    void Opcode::Pop(register16_t* r1)
    {
        uint16_t read = Cpu::Instance()->StackPop();
        r1->mValue = read;
    }



    std::shared_ptr<Opcode> Opcode::Instance()
    {
        static std::shared_ptr<Opcode> inst = std::make_shared<Opcode>(Opcode());
        return inst;
    }

    //  std::map<uint16_t, std::shared_ptr<OpcodeCommand>> Opcode::opcode_map()
    // {

    // return opcode_map;
    // }

}