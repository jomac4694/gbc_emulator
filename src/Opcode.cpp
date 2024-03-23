#include "Opcode.h"

#include "Memory.h"
#define CPU gbc::Cpu::Instance()
namespace gbc
{

    // little helper functions to grab the flags dynamically
    bool GetCarryFlag()
    {
        return CPU->FLAGS->CarryFlag();
    }

    bool GetCarryFlagN()
    {
        return !CPU->FLAGS->CarryFlag();
    }

    bool GetZeroFlag()
    {
        return CPU->FLAGS->ZeroFlag();
    }

    bool GetZeroFlagN()
    {
        return !CPU->FLAGS->ZeroFlag();
    }

    // big ugly monolithic map of every CPU instruction
    Opcode::Opcode()
    {
        opcode_map =
            {
                // 8-bit LD
                // Load R1 into R2
                {0x7F, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->A, CPU->A), 4)},
                {0x78, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->A, CPU->B), 4)},
                {0x79, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->A, CPU->C), 4)},
                {0x7A, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->A, CPU->D), 4)},
                {0x7B, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->A, CPU->E), 4)},
                {0x7C, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->A, CPU->H), 4)},
                {0x7D, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->A, CPU->L), 4)},
                {0x40, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->B, CPU->B), 4)},
                {0x41, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->B, CPU->C), 4)},
                {0x42, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->B, CPU->D), 4)},
                {0x43, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->B, CPU->E), 4)},
                {0x44, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->B, CPU->H), 4)},
                {0x45, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->B, CPU->L), 4)},
                {0x48, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->C, CPU->B), 4)},
                {0x49, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->C, CPU->C), 4)},
                {0x4A, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->C, CPU->D), 4)},
                {0x4B, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->C, CPU->E), 4)},
                {0x4C, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->C, CPU->H), 4)},
                {0x4D, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->C, CPU->L), 4)},
                {0x50, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->D, CPU->B), 4)},
                {0x51, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->D, CPU->C), 4)},
                {0x52, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->D, CPU->D), 4)},
                {0x53, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->D, CPU->E), 4)},
                {0x54, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->D, CPU->H), 4)},
                {0x55, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->D, CPU->L), 4)},
                {0x58, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->E, CPU->B), 4)},
                {0x59, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->E, CPU->C), 4)},
                {0x5A, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->E, CPU->D), 4)},
                {0x5B, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->E, CPU->E), 4)},
                {0x5C, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->E, CPU->H), 4)},
                {0x5D, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->E, CPU->L), 4)},
                {0x60, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->H, CPU->B), 4)},
                {0x61, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->H, CPU->C), 4)},
                {0x62, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->H, CPU->D), 4)},
                {0x63, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->H, CPU->E), 4)},
                {0x64, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->H, CPU->H), 4)},
                {0x65, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->H, CPU->L), 4)},
                {0x68, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->L, CPU->B), 4)},
                {0x69, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->L, CPU->C), 4)},
                {0x6A, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->L, CPU->D), 4)},
                {0x6B, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->L, CPU->E), 4)},
                {0x6C, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->L, CPU->H), 4)},
                {0x6D, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->L, CPU->L), 4)},
                // LD from HL
                {0x7E, OpcodeCommand("LD from HL", std::bind(&Opcode::Ld_HL, this, CPU->A), 8)},
                {0x46, OpcodeCommand("LD from HL", std::bind(&Opcode::Ld_HL, this, CPU->B), 8)},
                {0x4E, OpcodeCommand("LD from HL", std::bind(&Opcode::Ld_HL, this, CPU->C), 8)},
                {0x56, OpcodeCommand("LD from HL", std::bind(&Opcode::Ld_HL, this, CPU->D), 8)},
                {0x5E, OpcodeCommand("LD from HL", std::bind(&Opcode::Ld_HL, this, CPU->E), 8)},
                {0x66, OpcodeCommand("LD from HL", std::bind(&Opcode::Ld_HL, this, CPU->H), 8)},
                {0x6E, OpcodeCommand("LD from HL", std::bind(&Opcode::Ld_HL, this, CPU->L), 8)},
                // LD write to HL
                {0x70, OpcodeCommand("LD to HL", std::bind(&Opcode::Ld_HL_Write, this, CPU->B), 8)},
                {0x71, OpcodeCommand("LD to HL", std::bind(&Opcode::Ld_HL_Write, this, CPU->C), 8)},
                {0x72, OpcodeCommand("LD to HL", std::bind(&Opcode::Ld_HL_Write, this, CPU->D), 8)},
                {0x73, OpcodeCommand("LD to HL", std::bind(&Opcode::Ld_HL_Write, this, CPU->E), 8)},
                {0x74, OpcodeCommand("LD to HL", std::bind(&Opcode::Ld_HL_Write, this, CPU->H), 8)},
                {0x75, OpcodeCommand("LD to HL", std::bind(&Opcode::Ld_HL_Write, this, CPU->L), 8)},
                // LD write to HL from PC
                {0x36, OpcodeCommand("LD to HL", std::bind(&Opcode::Ld_HL_WritePC, this), 12)},
                // ld (nn), SP
                {0x08, OpcodeCommand("LD to HL", std::bind(&Opcode::Ld_Write_SP, this), 20)},
                // LD into register A
                {0x0A, OpcodeCommand("LD to A:BC", std::bind(&Opcode::Ld_An, this, CPU->BC), 8)},
                {0x1A, OpcodeCommand("LD to A", std::bind(&Opcode::Ld_An, this, CPU->DE), 8)},
                {0x7E, OpcodeCommand("LD to A", std::bind(&Opcode::Ld_An, this, CPU->HL), 8)},
                {0xFA, OpcodeCommand("LD to A:nn", std::bind(&Opcode::Ld_An_PC2, this), 16)},
                {0x3E, OpcodeCommand("LD to A:n", std::bind(&Opcode::Ld_An_PC, this), 8)},

                // more ld
                {0x47, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->B, CPU->A), 4)},
                {0x4F, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->C, CPU->A), 4)},
                {0x57, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->D, CPU->A), 4)},
                {0x5F, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->E, CPU->A), 4)},
                {0x67, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->H, CPU->A), 4)},
                {0x6F, OpcodeCommand("LdR1R2", std::bind(&Opcode::LdR1R2, this, CPU->L, CPU->A), 4)},

                {0x01, OpcodeCommand("LD n,nn BC", std::bind(&Opcode::LdReadWord, this, CPU->BC), 12)},
                {0x11, OpcodeCommand("LD n,nn DE", std::bind(&Opcode::LdReadWord, this, CPU->DE), 12)},
                {0x21, OpcodeCommand("LD n,nn HL", std::bind(&Opcode::LdReadWord, this, CPU->HL), 12)},
                {0x31, OpcodeCommand("LD n,nn SP", std::bind(&Opcode::LdReadWord, this, CPU->SP), 12)},
                {0xF9, OpcodeCommand("LD SP,HL", std::bind(&Opcode::LdR1R2_16, this, CPU->SP, CPU->HL), 8)},
                {0xF8, OpcodeCommand("LD SP,HL", std::bind(&Opcode::LdHL_SP, this), 12)},
                

                // ld n,a
                {0x02, OpcodeCommand("LD n,a BC", std::bind(&Opcode::Ld_Write_A, this, CPU->BC), 8)},
                {0x12, OpcodeCommand("LD n,a DE", std::bind(&Opcode::Ld_Write_A, this, CPU->DE), 8)},
                {0x77, OpcodeCommand("LD n,a HL", std::bind(&Opcode::Ld_Write_A, this, CPU->HL), 8)},
                {0xEA, OpcodeCommand("LD n,a nn", std::bind(&Opcode::Ld_Write_A_PC, this), 16)},

                // LD nn,n I think?
                {0x06, OpcodeCommand("Ldnn,n", std::bind(&Opcode::LdReadByte, this, CPU->B), 8)},
                {0x0E, OpcodeCommand("Ldnn,n", std::bind(&Opcode::LdReadByte, this, CPU->C), 8)},
                {0x16, OpcodeCommand("Ldnn,n", std::bind(&Opcode::LdReadByte, this, CPU->D), 8)},
                {0x1E, OpcodeCommand("Ldnn,n", std::bind(&Opcode::LdReadByte, this, CPU->E), 8)},
                {0x26, OpcodeCommand("Ldnn,n", std::bind(&Opcode::LdReadByte, this, CPU->H), 8)},
                {0x2E, OpcodeCommand("Ldnn,n", std::bind(&Opcode::LdReadByte, this, CPU->L), 8)},
                // HLD
                {0x2A, OpcodeCommand("Ld A, (HL+)", std::bind(&Opcode::Ld_HL_Inc, this), 8)},
                {0x3A, OpcodeCommand("Ld A, (HL-)", std::bind(&Opcode::Ld_HL_Dec, this), 8)},
                {0x22, OpcodeCommand("Ld (HL+), A", std::bind(&Opcode::Ld_Write_A_IncHL, this), 8)},
                {0x32, OpcodeCommand("Ld (HL-), A", std::bind(&Opcode::Ld_Write_A_DecHL, this), 8)},

                // LDH?
                {0xE0, OpcodeCommand("Ld (0xFF00 + n), A", std::bind(&Opcode::Ldh_nA, this), 12)},
                {0xF0, OpcodeCommand("Ld A, (0xFF00 + n)", std::bind(&Opcode::Ldh_An, this), 12)},

                // LDC
                {0xF2, OpcodeCommand("Ld (0xFF00 + n), A", std::bind(&Opcode::Ldh_AC, this), 8)},
                {0xE2, OpcodeCommand("Ld A, (0xFF00 + n)", std::bind(&Opcode::Ldh_CA, this), 8)},

                // PUSH
                {0xF5, OpcodeCommand("PUSH Register AF", std::bind(&Opcode::Push, this, CPU->AF), 16)},
                {0xC5, OpcodeCommand("PUSH Register BC", std::bind(&Opcode::Push, this, CPU->BC), 16)},
                {0xD5, OpcodeCommand("PUSH Register DE", std::bind(&Opcode::Push, this, CPU->DE), 16)},
                {0xE5, OpcodeCommand("PUSH Register HL", std::bind(&Opcode::Push, this, CPU->HL), 16)},
                // POP
                {0xF1, OpcodeCommand("POP Register AF", std::bind(&Opcode::Pop, this, CPU->AF), 12)},
                {0xC1, OpcodeCommand("POP Register BC", std::bind(&Opcode::Pop, this, CPU->BC), 12)},
                {0xD1, OpcodeCommand("POP Register DE", std::bind(&Opcode::Pop, this, CPU->DE), 12)},
                {0xE1, OpcodeCommand("POP Register HL", std::bind(&Opcode::Pop, this, CPU->HL), 12)},

                // 8-bit ALU section
                // AddA
                {0x87, OpcodeCommand("0x87 AddA A:A", std::bind(&Opcode::AddA, this, CPU->A, CPU->A), 4)},
                {0x80, OpcodeCommand("0x80 AddA A:B", std::bind(&Opcode::AddA, this, CPU->A, CPU->B), 4)},
                {0x81, OpcodeCommand("0x81 AddA A:C", std::bind(&Opcode::AddA, this, CPU->A, CPU->C), 4)},
                {0x82, OpcodeCommand("0x82 AddA A:D", std::bind(&Opcode::AddA, this, CPU->A, CPU->D), 4)},
                {0x83, OpcodeCommand("0x83 AddA A:E", std::bind(&Opcode::AddA, this, CPU->A, CPU->E), 4)},
                {0x84, OpcodeCommand("0x84 AddA A:H", std::bind(&Opcode::AddA, this, CPU->A, CPU->H), 4)},
                {0x85, OpcodeCommand("0x85 AddA A:L", std::bind(&Opcode::AddA, this, CPU->A, CPU->L), 4)},
                {0x86, OpcodeCommand("0x86 AddA_HL A:(HL)", std::bind(&Opcode::AddA_HL, this), 8)},
                {0xC6, OpcodeCommand("0xC6 AddA_PC A:#", std::bind(&Opcode::AddA_PC, this), 8)},
                // AdcA
                {0x8F, OpcodeCommand("0x8F AdcA A:A", std::bind(&Opcode::AdcA, this, CPU->A, CPU->A), 4)},
                {0x88, OpcodeCommand("0x88 AdcA A:B", std::bind(&Opcode::AdcA, this, CPU->A, CPU->B), 4)},
                {0x89, OpcodeCommand("0x89 AdcA A:C", std::bind(&Opcode::AdcA, this, CPU->A, CPU->C), 4)},
                {0x8A, OpcodeCommand("0x8A AdcA A:D", std::bind(&Opcode::AdcA, this, CPU->A, CPU->D), 4)},
                {0x8B, OpcodeCommand("0x8B AdcA A:E", std::bind(&Opcode::AdcA, this, CPU->A, CPU->E), 4)},
                {0x8C, OpcodeCommand("0x8C AdcA A:H", std::bind(&Opcode::AdcA, this, CPU->A, CPU->H), 4)},
                {0x8D, OpcodeCommand("0x8D AdcA A:L", std::bind(&Opcode::AdcA, this, CPU->A, CPU->L), 4)},
                {0x8E, OpcodeCommand("0x8E AdcA_HL A:(HL)", std::bind(&Opcode::AdcA_HL, this), 8)},
                {0xCE, OpcodeCommand("0xCE AdcA_PC A:#", std::bind(&Opcode::AdcA_PC, this), 8)},
                // SubA
                {0x97, OpcodeCommand("0x97 SubA A:A", std::bind(&Opcode::SubA, this, CPU->A, CPU->A), 4)},
                {0x90, OpcodeCommand("0x90 SubA A:B", std::bind(&Opcode::SubA, this, CPU->A, CPU->B), 4)},
                {0x91, OpcodeCommand("0x91 SubA A:C", std::bind(&Opcode::SubA, this, CPU->A, CPU->C), 4)},
                {0x92, OpcodeCommand("0x92 SubA A:D", std::bind(&Opcode::SubA, this, CPU->A, CPU->D), 4)},
                {0x93, OpcodeCommand("0x93 SubA A:E", std::bind(&Opcode::SubA, this, CPU->A, CPU->E), 4)},
                {0x94, OpcodeCommand("0x94 SubA A:H", std::bind(&Opcode::SubA, this, CPU->A, CPU->H), 4)},
                {0x95, OpcodeCommand("0x95 SubA A:L", std::bind(&Opcode::SubA, this, CPU->A, CPU->L), 4)},
                {0x96, OpcodeCommand("0x96 SubA_HL (HL):", std::bind(&Opcode::SubA_HL, this), 8)},
                {0xD6, OpcodeCommand("0xD6 SubA_PC #:", std::bind(&Opcode::SubA_PC, this), 8)},
                {0x9F, OpcodeCommand("0x9F SbcA A:A", std::bind(&Opcode::SbcA, this, CPU->A, CPU->A), 4)},
                {0x98, OpcodeCommand("0x98 SbcA A:B", std::bind(&Opcode::SbcA, this, CPU->A, CPU->B), 4)},
                {0x99, OpcodeCommand("0x99 SbcA A:C", std::bind(&Opcode::SbcA, this, CPU->A, CPU->C), 4)},
                {0x9A, OpcodeCommand("0x9A SbcA A:D", std::bind(&Opcode::SbcA, this, CPU->A, CPU->D), 4)},
                {0x9B, OpcodeCommand("0x9B SbcA A:E", std::bind(&Opcode::SbcA, this, CPU->A, CPU->E), 4)},
                {0x9C, OpcodeCommand("0x9C SbcA A:H", std::bind(&Opcode::SbcA, this, CPU->A, CPU->H), 4)},
                {0x9D, OpcodeCommand("0x9D SbcA A:L", std::bind(&Opcode::SbcA, this, CPU->A, CPU->L), 4)},
                {0x9E, OpcodeCommand("0x9E SbcA_HL A:(HL)", std::bind(&Opcode::SbcA_HL, this), 8)},
                {0xDE, OpcodeCommand("0xDE SbcA_PC #:", std::bind(&Opcode::SbcA_PC, this), 8)},
                {0xA7, OpcodeCommand("0xA7 AndA A:A", std::bind(&Opcode::AndA, this, CPU->A, CPU->A), 4)},
                {0xA0, OpcodeCommand("0xA0 AndA A:B", std::bind(&Opcode::AndA, this, CPU->A, CPU->B), 4)},
                {0xA1, OpcodeCommand("0xA1 AndA A:C", std::bind(&Opcode::AndA, this, CPU->A, CPU->C), 4)},
                {0xA2, OpcodeCommand("0xA2 AndA A:D", std::bind(&Opcode::AndA, this, CPU->A, CPU->D), 4)},
                {0xA3, OpcodeCommand("0xA3 AndA A:E", std::bind(&Opcode::AndA, this, CPU->A, CPU->E), 4)},
                {0xA4, OpcodeCommand("0xA4 AndA A:H", std::bind(&Opcode::AndA, this, CPU->A, CPU->H), 4)},
                {0xA5, OpcodeCommand("0xA5 AndA A:L", std::bind(&Opcode::AndA, this, CPU->A, CPU->L), 4)},
                {0xA6, OpcodeCommand("0xA6 AndA_HL (HL):", std::bind(&Opcode::AndA_HL, this), 8)},
                {0xE6, OpcodeCommand("0xE6 AndA_PC #:", std::bind(&Opcode::AndA_PC, this), 8)},
                {0xB7, OpcodeCommand("0xB7 OrA A:A", std::bind(&Opcode::OrA, this, CPU->A, CPU->A), 4)},
                {0xB0, OpcodeCommand("0xB0 OrA A:B", std::bind(&Opcode::OrA, this, CPU->A, CPU->B), 4)},
                {0xB1, OpcodeCommand("0xB1 OrA A:C", std::bind(&Opcode::OrA, this, CPU->A, CPU->C), 4)},
                {0xB2, OpcodeCommand("0xB2 OrA A:D", std::bind(&Opcode::OrA, this, CPU->A, CPU->D), 4)},
                {0xB3, OpcodeCommand("0xB3 OrA A:E", std::bind(&Opcode::OrA, this, CPU->A, CPU->E), 4)},
                {0xB4, OpcodeCommand("0xB4 OrA A:H", std::bind(&Opcode::OrA, this, CPU->A, CPU->H), 4)},
                {0xB5, OpcodeCommand("0xB5 OrA A:L", std::bind(&Opcode::OrA, this, CPU->A, CPU->L), 4)},
                {0xB6, OpcodeCommand("0xB6 OrA_HL (HL):", std::bind(&Opcode::OrA_HL, this), 8)},
                {0xF6, OpcodeCommand("0xF6 OrA_PC #:", std::bind(&Opcode::OrA_PC, this), 8)},
                {0xAF, OpcodeCommand("0xAF XorA A:A", std::bind(&Opcode::XorA, this, CPU->A, CPU->A), 4)},
                {0xA8, OpcodeCommand("0xA8 XorA A:B", std::bind(&Opcode::XorA, this, CPU->A, CPU->B), 4)},
                {0xA9, OpcodeCommand("0xA9 XorA A:C", std::bind(&Opcode::XorA, this, CPU->A, CPU->C), 4)},
                {0xAA, OpcodeCommand("0xAA XorA A:D", std::bind(&Opcode::XorA, this, CPU->A, CPU->D), 4)},
                {0xAB, OpcodeCommand("0xAB XorA A:E", std::bind(&Opcode::XorA, this, CPU->A, CPU->E), 4)},
                {0xAC, OpcodeCommand("0xAC XorA A:H", std::bind(&Opcode::XorA, this, CPU->A, CPU->H), 4)},
                {0xAD, OpcodeCommand("0xAD XorA A:L", std::bind(&Opcode::XorA, this, CPU->A, CPU->L), 4)},
                {0xAE, OpcodeCommand("0xAE XorA_HL A:(HL)", std::bind(&Opcode::XorA_HL, this), 8)},
                {0xEE, OpcodeCommand("0xEE XorA_PC A:#", std::bind(&Opcode::XorA_PC, this), 8)},
                {0xBF, OpcodeCommand("0xBF CpA A:A", std::bind(&Opcode::CpA, this, CPU->A, CPU->A), 4)},
                {0xB8, OpcodeCommand("0xB8 CpA A:B", std::bind(&Opcode::CpA, this, CPU->A, CPU->B), 4)},
                {0xB9, OpcodeCommand("0xB9 CpA A:C", std::bind(&Opcode::CpA, this, CPU->A, CPU->C), 4)},
                {0xBA, OpcodeCommand("0xBA CpA A:D", std::bind(&Opcode::CpA, this, CPU->A, CPU->D), 4)},
                {0xBB, OpcodeCommand("0xBB CpA A:E", std::bind(&Opcode::CpA, this, CPU->A, CPU->E), 4)},
                {0xBC, OpcodeCommand("0xBC CpA A:H", std::bind(&Opcode::CpA, this, CPU->A, CPU->H), 4)},
                {0xBD, OpcodeCommand("0xBD CpA A:L", std::bind(&Opcode::CpA, this, CPU->A, CPU->L), 4)},
                {0xBE, OpcodeCommand("0xBE CpA_HL A:(HL)", std::bind(&Opcode::CpA_HL, this), 8)},
                {0xFE, OpcodeCommand("0xFE CpA_PC A:#", std::bind(&Opcode::CpA_PC, this), 8)},

                // INC register n
                {0x3C, OpcodeCommand("INC Reg A", std::bind(&Opcode::IncN, this, CPU->A), 4)},
                {0x04, OpcodeCommand("INC Reg B", std::bind(&Opcode::IncN, this, CPU->B), 4)},
                {0x0C, OpcodeCommand("INC Reg C", std::bind(&Opcode::IncN, this, CPU->C), 4)},
                {0x14, OpcodeCommand("INC Reg D", std::bind(&Opcode::IncN, this, CPU->D), 4)},
                {0x1C, OpcodeCommand("INC Reg E", std::bind(&Opcode::IncN, this, CPU->E), 4)},
                {0x24, OpcodeCommand("INC Reg H", std::bind(&Opcode::IncN, this, CPU->H), 4)},
                {0x2C, OpcodeCommand("INC Reg L", std::bind(&Opcode::IncN, this, CPU->L), 4)},
                {0x34, OpcodeCommand("INC Reg (HL)", std::bind(&Opcode::IncN_HL, this), 12)},
                // INC todo: add in hl read

                // DEC register n
                {0x3D, OpcodeCommand("DEC Reg A", std::bind(&Opcode::DecN, this, CPU->A), 4)},
                {0x05, OpcodeCommand("DEC Reg B", std::bind(&Opcode::DecN, this, CPU->B), 4)},
                {0x0D, OpcodeCommand("DEC Reg C", std::bind(&Opcode::DecN, this, CPU->C), 4)},
                {0x15, OpcodeCommand("DEC Reg D", std::bind(&Opcode::DecN, this, CPU->D), 4)},
                {0x1D, OpcodeCommand("DEC Reg E", std::bind(&Opcode::DecN, this, CPU->E), 4)},
                {0x25, OpcodeCommand("DEC Reg H", std::bind(&Opcode::DecN, this, CPU->H), 4)},
                {0x2D, OpcodeCommand("DEC Reg L", std::bind(&Opcode::DecN, this, CPU->L), 4)},
                {0x35, OpcodeCommand("DEC Reg (HL)", std::bind(&Opcode::DecN_HL, this), 12)},
                // DEC todo: add in HL read

                // 16-bit ALU ops
                {0x09, OpcodeCommand("AddHL HL:BC", std::bind(&Opcode::AddHL, this, CPU->HL, CPU->BC), 8)},
                {0x19, OpcodeCommand("AddHL HL:DE", std::bind(&Opcode::AddHL, this, CPU->HL, CPU->DE), 8)},
                {0x29, OpcodeCommand("AddHL HL:HL", std::bind(&Opcode::AddHL, this, CPU->HL, CPU->HL), 8)},
                {0x39, OpcodeCommand("AddHL HL:SP", std::bind(&Opcode::AddHL, this, CPU->HL, CPU->SP), 8)},
                {0xE8, OpcodeCommand("AddSP", std::bind(&Opcode::AddSP, this), 16)},
                // INC
                {0x03, OpcodeCommand("INC Reg BC", std::bind(&Opcode::IncN16, this, CPU->BC), 8)},
                {0x13, OpcodeCommand("INC Reg DE", std::bind(&Opcode::IncN16, this, CPU->DE), 8)},
                {0x23, OpcodeCommand("INC Reg HL", std::bind(&Opcode::IncN16, this, CPU->HL), 8)},
                {0x33, OpcodeCommand("INC Reg SP", std::bind(&Opcode::IncN16, this, CPU->SP), 8)},
                // DEC
                {0x0B, OpcodeCommand("DEC Reg BC", std::bind(&Opcode::DecN16, this, CPU->BC), 8)},
                {0x1B, OpcodeCommand("DEC Reg DE", std::bind(&Opcode::DecN16, this, CPU->DE), 8)},
                {0x2B, OpcodeCommand("DEC Reg HL", std::bind(&Opcode::DecN16, this, CPU->HL), 8)},
                {0x3B, OpcodeCommand("DEC Reg SP", std::bind(&Opcode::DecN16, this, CPU->SP), 8)},

                // Misc commands
                // Swap upper and lower nibbles of n
                {0xCB37, OpcodeCommand("SWAP Reg A", std::bind(&Opcode::Swap, this, CPU->A), 8)},
                {0xCB30, OpcodeCommand("SWAP Reg B", std::bind(&Opcode::Swap, this, CPU->B), 8)},
                {0xCB31, OpcodeCommand("SWAP Reg C", std::bind(&Opcode::Swap, this, CPU->C), 8)},
                {0xCB32, OpcodeCommand("SWAP Reg D", std::bind(&Opcode::Swap, this, CPU->D), 8)},
                {0xCB33, OpcodeCommand("SWAP Reg E", std::bind(&Opcode::Swap, this, CPU->E), 8)},
                {0xCB34, OpcodeCommand("SWAP Reg H", std::bind(&Opcode::Swap, this, CPU->H), 8)},
                {0xCB35, OpcodeCommand("SWAP Reg L", std::bind(&Opcode::Swap, this, CPU->L), 8)},
                {0xCB36, OpcodeCommand("SWAP Reg (HL)", std::bind(&Opcode::SwapHL, this), 16)},

                // DAA
                {0x27, OpcodeCommand("DAA", std::bind(&Opcode::DAA, this), 4)},

                // CPL
                {0x2F, OpcodeCommand("CPL", std::bind(&Opcode::CPL, this), 4)},
                // SCF
                {0x37, OpcodeCommand("SCF", std::bind(&Opcode::SCF, this), 4)},
                // CCF
                {0x3F, OpcodeCommand("SCF", std::bind(&Opcode::CCF, this), 4)},

                // NOP
                {0x00, OpcodeCommand("NOP", std::bind(&Opcode::NOP, this), 4)},
                // HALT
                {0x76, OpcodeCommand("HALT", std::bind(&Opcode::HALT, this), 4)},
                // STOP
                {0x1000, OpcodeCommand("STOP", std::bind(&Opcode::STOP, this), 4)},
                // DI
                {0xF3, OpcodeCommand("DI", std::bind(&Opcode::DI, this), 4)},
                //EI
                {0xFB, OpcodeCommand("EI", std::bind(&Opcode::EI, this), 4)},
                // Jumps
                // JP nn
                {0xC3, OpcodeCommand("JP nn", std::bind(&Opcode::JpNN, this), 12)},

                // Jp cc,nn
                {0xC2, OpcodeCommand("JP cc,nn", std::bind(&Opcode::JpCCNN, this, &GetZeroFlagN), 12)},
                {0xCA, OpcodeCommand("JP cc,nn", std::bind(&Opcode::JpCCNN, this, &GetZeroFlag), 12)},
                {0xD2, OpcodeCommand("JP cc,nn", std::bind(&Opcode::JpCCNN, this, &GetCarryFlagN), 12)},
                {0xDA, OpcodeCommand("JP cc,nn", std::bind(&Opcode::JpCCNN, this, &GetCarryFlag), 12)},
                // JP HL
                {0xE9, OpcodeCommand("JP (HL)", std::bind(&Opcode::JpHL, this), 4)},
                // JR n
                {0x18, OpcodeCommand("JR n", std::bind(&Opcode::JrN, this), 8)},
                // JR cc,n
                {0x20, OpcodeCommand("JR cc,n", std::bind(&Opcode::JrCCN, this, &GetZeroFlagN), 8)},
                {0x28, OpcodeCommand("JR cc,n", std::bind(&Opcode::JrCCN, this, &GetZeroFlag), 8)},
                {0x30, OpcodeCommand("JR cc,n", std::bind(&Opcode::JrCCN, this, &GetCarryFlagN), 8)},
                {0x38, OpcodeCommand("JR cc,n", std::bind(&Opcode::JrCCN, this, &GetCarryFlag), 8)},
                // Calls
                // Call nn
                {0xCD, OpcodeCommand("CALL nn", std::bind(&Opcode::CallNN, this), 12)},
                // Call cc,nn
                {0xC4, OpcodeCommand("CALL cc,nn", std::bind(&Opcode::CallCCNN, this, &GetZeroFlagN), 12)},
                {0xCC, OpcodeCommand("CALL cc,nn", std::bind(&Opcode::CallCCNN, this, &GetZeroFlag), 12)},
                {0xD4, OpcodeCommand("CALL cc,nn", std::bind(&Opcode::CallCCNN, this, &GetCarryFlagN), 12)},
                {0xDC, OpcodeCommand("CALL cc,nn", std::bind(&Opcode::CallCCNN, this, &GetCarryFlag), 12)},
                // Restarts
                // RST n
                {0xC7, OpcodeCommand("RST n", std::bind(&Opcode::Rst, this, 0x00), 32)},
                {0xCF, OpcodeCommand("RST n", std::bind(&Opcode::Rst, this, 0x08), 32)},
                {0xD7, OpcodeCommand("RST n", std::bind(&Opcode::Rst, this, 0x10), 32)},
                {0xDF, OpcodeCommand("RST n", std::bind(&Opcode::Rst, this, 0x18), 32)},
                {0xE7, OpcodeCommand("RST n", std::bind(&Opcode::Rst, this, 0x20), 32)},
                {0xEF, OpcodeCommand("RST n", std::bind(&Opcode::Rst, this, 0x28), 32)},
                {0xF7, OpcodeCommand("RST n", std::bind(&Opcode::Rst, this, 0x30), 32)},
                {0xFF, OpcodeCommand("RST n", std::bind(&Opcode::Rst, this, 0x38), 32)},
                // Returns
                // RET
                {0xC9, OpcodeCommand("RET", std::bind(&Opcode::Ret, this), 8)},
                // RET cc
                {0xC0, OpcodeCommand("RET cc", std::bind(&Opcode::RetCC, this, &GetZeroFlagN), 8)},
                {0xC8, OpcodeCommand("RET cc", std::bind(&Opcode::RetCC, this, &GetZeroFlag), 8)},
                {0xD0, OpcodeCommand("RET cc", std::bind(&Opcode::RetCC, this, &GetCarryFlagN), 8)},
                {0xD8, OpcodeCommand("RET cc", std::bind(&Opcode::RetCC, this, &GetCarryFlag), 8)},
                // RETI
                {0xD9, OpcodeCommand("RETI", std::bind(&Opcode::RetI, this), 8)},

                // Test bit b in register r
                {0xCB40, OpcodeCommand(" BitBR 0:b", std::bind(&Opcode::BitBR, this, 0, CPU->B), 8)},
                {0xCB41, OpcodeCommand(" BitBR 0:c", std::bind(&Opcode::BitBR, this, 0, CPU->C), 8)},
                {0xCB42, OpcodeCommand(" BitBR 0:d", std::bind(&Opcode::BitBR, this, 0, CPU->D), 8)},
                {0xCB43, OpcodeCommand(" BitBR 0:e", std::bind(&Opcode::BitBR, this, 0, CPU->E), 8)},
                {0xCB44, OpcodeCommand(" BitBR 0:h", std::bind(&Opcode::BitBR, this, 0, CPU->H), 8)},
                {0xCB45, OpcodeCommand(" BitBR 0:l", std::bind(&Opcode::BitBR, this, 0, CPU->L), 8)},
                {0xCB46, OpcodeCommand(" BitBR 0:hl", std::bind(&Opcode::BitBR_HL, this, 0), 16)},
                {0xCB47, OpcodeCommand(" BitBR 0:a", std::bind(&Opcode::BitBR, this, 0, CPU->A), 8)},
                {0xCB48, OpcodeCommand(" BitBR 1:b", std::bind(&Opcode::BitBR, this, 1, CPU->B), 8)},
                {0xCB49, OpcodeCommand(" BitBR 1:c", std::bind(&Opcode::BitBR, this, 1, CPU->C), 8)},
                {0xCB4A, OpcodeCommand(" BitBR 1:d", std::bind(&Opcode::BitBR, this, 1, CPU->D), 8)},
                {0xCB4B, OpcodeCommand(" BitBR 1:e", std::bind(&Opcode::BitBR, this, 1, CPU->E), 8)},
                {0xCB4C, OpcodeCommand(" BitBR 1:h", std::bind(&Opcode::BitBR, this, 1, CPU->H), 8)},
                {0xCB4D, OpcodeCommand(" BitBR 1:l", std::bind(&Opcode::BitBR, this, 1, CPU->L), 8)},
                {0xCB4E, OpcodeCommand(" BitBR 1:hl", std::bind(&Opcode::BitBR_HL, this, 1), 16)},
                {0xCB4F, OpcodeCommand(" BitBR 1:a", std::bind(&Opcode::BitBR, this, 1, CPU->A), 8)},
                {0xCB50, OpcodeCommand(" BitBR 2:b", std::bind(&Opcode::BitBR, this, 2, CPU->B), 8)},
                {0xCB51, OpcodeCommand(" BitBR 2:c", std::bind(&Opcode::BitBR, this, 2, CPU->C), 8)},
                {0xCB52, OpcodeCommand(" BitBR 2:d", std::bind(&Opcode::BitBR, this, 2, CPU->D), 8)},
                {0xCB53, OpcodeCommand(" BitBR 2:e", std::bind(&Opcode::BitBR, this, 2, CPU->E), 8)},
                {0xCB54, OpcodeCommand(" BitBR 2:h", std::bind(&Opcode::BitBR, this, 2, CPU->H), 8)},
                {0xCB55, OpcodeCommand(" BitBR 2:l", std::bind(&Opcode::BitBR, this, 2, CPU->L), 8)},
                {0xCB56, OpcodeCommand(" BitBR 2:hl", std::bind(&Opcode::BitBR_HL, this, 2), 16)},
                {0xCB57, OpcodeCommand(" BitBR 2:a", std::bind(&Opcode::BitBR, this, 2, CPU->A), 8)},
                {0xCB58, OpcodeCommand(" BitBR 3:b", std::bind(&Opcode::BitBR, this, 3, CPU->B), 8)},
                {0xCB59, OpcodeCommand(" BitBR 3:c", std::bind(&Opcode::BitBR, this, 3, CPU->C), 8)},
                {0xCB5A, OpcodeCommand(" BitBR 3:d", std::bind(&Opcode::BitBR, this, 3, CPU->D), 8)},
                {0xCB5B, OpcodeCommand(" BitBR 3:e", std::bind(&Opcode::BitBR, this, 3, CPU->E), 8)},
                {0xCB5C, OpcodeCommand(" BitBR 3:h", std::bind(&Opcode::BitBR, this, 3, CPU->H), 8)},
                {0xCB5D, OpcodeCommand(" BitBR 3:l", std::bind(&Opcode::BitBR, this, 3, CPU->L), 8)},
                {0xCB5E, OpcodeCommand(" BitBR 3:hl", std::bind(&Opcode::BitBR_HL, this, 3), 16)},
                {0xCB5F, OpcodeCommand(" BitBR 3:a", std::bind(&Opcode::BitBR, this, 3, CPU->A), 8)},
                {0xCB60, OpcodeCommand(" BitBR 4:b", std::bind(&Opcode::BitBR, this, 4, CPU->B), 8)},
                {0xCB61, OpcodeCommand(" BitBR 4:c", std::bind(&Opcode::BitBR, this, 4, CPU->C), 8)},
                {0xCB62, OpcodeCommand(" BitBR 4:d", std::bind(&Opcode::BitBR, this, 4, CPU->D), 8)},
                {0xCB63, OpcodeCommand(" BitBR 4:e", std::bind(&Opcode::BitBR, this, 4, CPU->E), 8)},
                {0xCB64, OpcodeCommand(" BitBR 4:h", std::bind(&Opcode::BitBR, this, 4, CPU->H), 8)},
                {0xCB65, OpcodeCommand(" BitBR 4:l", std::bind(&Opcode::BitBR, this, 4, CPU->L), 8)},
                {0xCB66, OpcodeCommand(" BitBR 4:hl", std::bind(&Opcode::BitBR_HL, this, 4), 16)},
                {0xCB67, OpcodeCommand(" BitBR 4:a", std::bind(&Opcode::BitBR, this, 4, CPU->A), 8)},
                {0xCB68, OpcodeCommand(" BitBR 5:b", std::bind(&Opcode::BitBR, this, 5, CPU->B), 8)},
                {0xCB69, OpcodeCommand(" BitBR 5:c", std::bind(&Opcode::BitBR, this, 5, CPU->C), 8)},
                {0xCB6A, OpcodeCommand(" BitBR 5:d", std::bind(&Opcode::BitBR, this, 5, CPU->D), 8)},
                {0xCB6B, OpcodeCommand(" BitBR 5:e", std::bind(&Opcode::BitBR, this, 5, CPU->E), 8)},
                {0xCB6C, OpcodeCommand(" BitBR 5:h", std::bind(&Opcode::BitBR, this, 5, CPU->H), 8)},
                {0xCB6D, OpcodeCommand(" BitBR 5:l", std::bind(&Opcode::BitBR, this, 5, CPU->L), 8)},
                {0xCB6E, OpcodeCommand(" BitBR 5:hl", std::bind(&Opcode::BitBR_HL, this, 5), 16)},
                {0xCB6F, OpcodeCommand(" BitBR 5:a", std::bind(&Opcode::BitBR, this, 5, CPU->A), 8)},
                {0xCB70, OpcodeCommand(" BitBR 6:b", std::bind(&Opcode::BitBR, this, 6, CPU->B), 8)},
                {0xCB71, OpcodeCommand(" BitBR 6:c", std::bind(&Opcode::BitBR, this, 6, CPU->C), 8)},
                {0xCB72, OpcodeCommand(" BitBR 6:d", std::bind(&Opcode::BitBR, this, 6, CPU->D), 8)},
                {0xCB73, OpcodeCommand(" BitBR 6:e", std::bind(&Opcode::BitBR, this, 6, CPU->E), 8)},
                {0xCB74, OpcodeCommand(" BitBR 6:h", std::bind(&Opcode::BitBR, this, 6, CPU->H), 8)},
                {0xCB75, OpcodeCommand(" BitBR 6:l", std::bind(&Opcode::BitBR, this, 6, CPU->L), 8)},
                {0xCB76, OpcodeCommand(" BitBR 6:hl", std::bind(&Opcode::BitBR_HL, this, 6), 16)},
                {0xCB77, OpcodeCommand(" BitBR 6:a", std::bind(&Opcode::BitBR, this, 6, CPU->A), 8)},
                {0xCB78, OpcodeCommand(" BitBR 7:b", std::bind(&Opcode::BitBR, this, 7, CPU->B), 8)},
                {0xCB79, OpcodeCommand(" BitBR 7:c", std::bind(&Opcode::BitBR, this, 7, CPU->C), 8)},
                {0xCB7A, OpcodeCommand(" BitBR 7:d", std::bind(&Opcode::BitBR, this, 7, CPU->D), 8)},
                {0xCB7B, OpcodeCommand(" BitBR 7:e", std::bind(&Opcode::BitBR, this, 7, CPU->E), 8)},
                {0xCB7C, OpcodeCommand(" BitBR 7:h", std::bind(&Opcode::BitBR, this, 7, CPU->H), 8)},
                {0xCB7D, OpcodeCommand(" BitBR 7:l", std::bind(&Opcode::BitBR, this, 7, CPU->L), 8)},
                {0xCB7E, OpcodeCommand(" BitBR 7:hl", std::bind(&Opcode::BitBR_HL, this, 7), 16)},
                {0xCB7F, OpcodeCommand(" BitBR 7:a", std::bind(&Opcode::BitBR, this, 7, CPU->A), 8)},

                // Reset bit b in register r
                {0xCB80, OpcodeCommand(" ResBR 0:b", std::bind(&Opcode::ResBR, this, 0, CPU->B), 8)},
                {0xCB81, OpcodeCommand(" ResBR 0:c", std::bind(&Opcode::ResBR, this, 0, CPU->C), 8)},
                {0xCB82, OpcodeCommand(" ResBR 0:d", std::bind(&Opcode::ResBR, this, 0, CPU->D), 8)},
                {0xCB83, OpcodeCommand(" ResBR 0:e", std::bind(&Opcode::ResBR, this, 0, CPU->E), 8)},
                {0xCB84, OpcodeCommand(" ResBR 0:h", std::bind(&Opcode::ResBR, this, 0, CPU->H), 8)},
                {0xCB85, OpcodeCommand(" ResBR 0:l", std::bind(&Opcode::ResBR, this, 0, CPU->L), 8)},
                {0xCB86, OpcodeCommand(" ResBR 0:hl", std::bind(&Opcode::ResBR_HL, this, 0), 16)},
                {0xCB87, OpcodeCommand(" ResBR 0:a", std::bind(&Opcode::ResBR, this, 0, CPU->A), 8)},
                {0xCB88, OpcodeCommand(" ResBR 1:b", std::bind(&Opcode::ResBR, this, 1, CPU->B), 8)},
                {0xCB89, OpcodeCommand(" ResBR 1:c", std::bind(&Opcode::ResBR, this, 1, CPU->C), 8)},
                {0xCB8A, OpcodeCommand(" ResBR 1:d", std::bind(&Opcode::ResBR, this, 1, CPU->D), 8)},
                {0xCB8B, OpcodeCommand(" ResBR 1:e", std::bind(&Opcode::ResBR, this, 1, CPU->E), 8)},
                {0xCB8C, OpcodeCommand(" ResBR 1:h", std::bind(&Opcode::ResBR, this, 1, CPU->H), 8)},
                {0xCB8D, OpcodeCommand(" ResBR 1:l", std::bind(&Opcode::ResBR, this, 1, CPU->L), 8)},
                {0xCB8E, OpcodeCommand(" ResBR 1:hl", std::bind(&Opcode::ResBR_HL, this, 1), 16)},
                {0xCB8F, OpcodeCommand(" ResBR 1:a", std::bind(&Opcode::ResBR, this, 1, CPU->A), 8)},
                {0xCB90, OpcodeCommand(" ResBR 2:b", std::bind(&Opcode::ResBR, this, 2, CPU->B), 8)},
                {0xCB91, OpcodeCommand(" ResBR 2:c", std::bind(&Opcode::ResBR, this, 2, CPU->C), 8)},
                {0xCB92, OpcodeCommand(" ResBR 2:d", std::bind(&Opcode::ResBR, this, 2, CPU->D), 8)},
                {0xCB93, OpcodeCommand(" ResBR 2:e", std::bind(&Opcode::ResBR, this, 2, CPU->E), 8)},
                {0xCB94, OpcodeCommand(" ResBR 2:h", std::bind(&Opcode::ResBR, this, 2, CPU->H), 8)},
                {0xCB95, OpcodeCommand(" ResBR 2:l", std::bind(&Opcode::ResBR, this, 2, CPU->L), 8)},
                {0xCB96, OpcodeCommand(" ResBR 2:hl", std::bind(&Opcode::ResBR_HL, this, 2), 16)},
                {0xCB97, OpcodeCommand(" ResBR 2:a", std::bind(&Opcode::ResBR, this, 2, CPU->A), 8)},
                {0xCB98, OpcodeCommand(" ResBR 3:b", std::bind(&Opcode::ResBR, this, 3, CPU->B), 8)},
                {0xCB99, OpcodeCommand(" ResBR 3:c", std::bind(&Opcode::ResBR, this, 3, CPU->C), 8)},
                {0xCB9A, OpcodeCommand(" ResBR 3:d", std::bind(&Opcode::ResBR, this, 3, CPU->D), 8)},
                {0xCB9B, OpcodeCommand(" ResBR 3:e", std::bind(&Opcode::ResBR, this, 3, CPU->E), 8)},
                {0xCB9C, OpcodeCommand(" ResBR 3:h", std::bind(&Opcode::ResBR, this, 3, CPU->H), 8)},
                {0xCB9D, OpcodeCommand(" ResBR 3:l", std::bind(&Opcode::ResBR, this, 3, CPU->L), 8)},
                {0xCB9E, OpcodeCommand(" ResBR 3:hl", std::bind(&Opcode::ResBR_HL, this, 3), 16)},
                {0xCB9F, OpcodeCommand(" ResBR 3:a", std::bind(&Opcode::ResBR, this, 3, CPU->A), 8)},
                {0xCBA0, OpcodeCommand(" ResBR 4:b", std::bind(&Opcode::ResBR, this, 4, CPU->B), 8)},
                {0xCBA1, OpcodeCommand(" ResBR 4:c", std::bind(&Opcode::ResBR, this, 4, CPU->C), 8)},
                {0xCBA2, OpcodeCommand(" ResBR 4:d", std::bind(&Opcode::ResBR, this, 4, CPU->D), 8)},
                {0xCBA3, OpcodeCommand(" ResBR 4:e", std::bind(&Opcode::ResBR, this, 4, CPU->E), 8)},
                {0xCBA4, OpcodeCommand(" ResBR 4:h", std::bind(&Opcode::ResBR, this, 4, CPU->H), 8)},
                {0xCBA5, OpcodeCommand(" ResBR 4:l", std::bind(&Opcode::ResBR, this, 4, CPU->L), 8)},
                {0xCBA6, OpcodeCommand(" ResBR 4:hl", std::bind(&Opcode::ResBR_HL, this, 4), 16)},
                {0xCBA7, OpcodeCommand(" ResBR 4:a", std::bind(&Opcode::ResBR, this, 4, CPU->A), 8)},
                {0xCBA8, OpcodeCommand(" ResBR 5:b", std::bind(&Opcode::ResBR, this, 5, CPU->B), 8)},
                {0xCBA9, OpcodeCommand(" ResBR 5:c", std::bind(&Opcode::ResBR, this, 5, CPU->C), 8)},
                {0xCBAA, OpcodeCommand(" ResBR 5:d", std::bind(&Opcode::ResBR, this, 5, CPU->D), 8)},
                {0xCBAB, OpcodeCommand(" ResBR 5:e", std::bind(&Opcode::ResBR, this, 5, CPU->E), 8)},
                {0xCBAC, OpcodeCommand(" ResBR 5:h", std::bind(&Opcode::ResBR, this, 5, CPU->H), 8)},
                {0xCBAD, OpcodeCommand(" ResBR 5:l", std::bind(&Opcode::ResBR, this, 5, CPU->L), 8)},
                {0xCBAE, OpcodeCommand(" ResBR 5:hl", std::bind(&Opcode::ResBR_HL, this, 5), 16)},
                {0xCBAF, OpcodeCommand(" ResBR 5:a", std::bind(&Opcode::ResBR, this, 5, CPU->A), 8)},
                {0xCBB0, OpcodeCommand(" ResBR 6:b", std::bind(&Opcode::ResBR, this, 6, CPU->B), 8)},
                {0xCBB1, OpcodeCommand(" ResBR 6:c", std::bind(&Opcode::ResBR, this, 6, CPU->C), 8)},
                {0xCBB2, OpcodeCommand(" ResBR 6:d", std::bind(&Opcode::ResBR, this, 6, CPU->D), 8)},
                {0xCBB3, OpcodeCommand(" ResBR 6:e", std::bind(&Opcode::ResBR, this, 6, CPU->E), 8)},
                {0xCBB4, OpcodeCommand(" ResBR 6:h", std::bind(&Opcode::ResBR, this, 6, CPU->H), 8)},
                {0xCBB5, OpcodeCommand(" ResBR 6:l", std::bind(&Opcode::ResBR, this, 6, CPU->L), 8)},
                {0xCBB6, OpcodeCommand(" ResBR 6:hl", std::bind(&Opcode::ResBR_HL, this, 6), 16)},
                {0xCBB7, OpcodeCommand(" ResBR 6:a", std::bind(&Opcode::ResBR, this, 6, CPU->A), 8)},
                {0xCBB8, OpcodeCommand(" ResBR 7:b", std::bind(&Opcode::ResBR, this, 7, CPU->B), 8)},
                {0xCBB9, OpcodeCommand(" ResBR 7:c", std::bind(&Opcode::ResBR, this, 7, CPU->C), 8)},
                {0xCBBA, OpcodeCommand(" ResBR 7:d", std::bind(&Opcode::ResBR, this, 7, CPU->D), 8)},
                {0xCBBB, OpcodeCommand(" ResBR 7:e", std::bind(&Opcode::ResBR, this, 7, CPU->E), 8)},
                {0xCBBC, OpcodeCommand(" ResBR 7:h", std::bind(&Opcode::ResBR, this, 7, CPU->H), 8)},
                {0xCBBD, OpcodeCommand(" ResBR 7:l", std::bind(&Opcode::ResBR, this, 7, CPU->L), 8)},
                {0xCBBE, OpcodeCommand(" ResBR 7:hl", std::bind(&Opcode::ResBR_HL, this, 7), 16)},
                {0xCBBF, OpcodeCommand(" ResBR 7:a", std::bind(&Opcode::ResBR, this, 7, CPU->A), 8)},
                // Set bit b in register r
                {0xCBC0, OpcodeCommand(" SetBR 0:b", std::bind(&Opcode::SetBR, this, 0, CPU->B), 8)},
                {0xCBC1, OpcodeCommand(" SetBR 0:c", std::bind(&Opcode::SetBR, this, 0, CPU->C), 8)},
                {0xCBC2, OpcodeCommand(" SetBR 0:d", std::bind(&Opcode::SetBR, this, 0, CPU->D), 8)},
                {0xCBC3, OpcodeCommand(" SetBR 0:e", std::bind(&Opcode::SetBR, this, 0, CPU->E), 8)},
                {0xCBC4, OpcodeCommand(" SetBR 0:h", std::bind(&Opcode::SetBR, this, 0, CPU->H), 8)},
                {0xCBC5, OpcodeCommand(" SetBR 0:l", std::bind(&Opcode::SetBR, this, 0, CPU->L), 8)},
                {0xCBC6, OpcodeCommand(" SetBR 0:hl", std::bind(&Opcode::SetBR_HL, this, 0), 16)},
                {0xCBC7, OpcodeCommand(" SetBR 0:a", std::bind(&Opcode::SetBR, this, 0, CPU->A), 8)},
                {0xCBC8, OpcodeCommand(" SetBR 1:b", std::bind(&Opcode::SetBR, this, 1, CPU->B), 8)},
                {0xCBC9, OpcodeCommand(" SetBR 1:c", std::bind(&Opcode::SetBR, this, 1, CPU->C), 8)},
                {0xCBCA, OpcodeCommand(" SetBR 1:d", std::bind(&Opcode::SetBR, this, 1, CPU->D), 8)},
                {0xCBCB, OpcodeCommand(" SetBR 1:e", std::bind(&Opcode::SetBR, this, 1, CPU->E), 8)},
                {0xCBCC, OpcodeCommand(" SetBR 1:h", std::bind(&Opcode::SetBR, this, 1, CPU->H), 8)},
                {0xCBCD, OpcodeCommand(" SetBR 1:l", std::bind(&Opcode::SetBR, this, 1, CPU->L), 8)},
                {0xCBCE, OpcodeCommand(" SetBR 1:hl", std::bind(&Opcode::SetBR_HL, this, 1), 16)},
                {0xCBCF, OpcodeCommand(" SetBR 1:a", std::bind(&Opcode::SetBR, this, 1, CPU->A), 8)},
                {0xCBD0, OpcodeCommand(" SetBR 2:b", std::bind(&Opcode::SetBR, this, 2, CPU->B), 8)},
                {0xCBD1, OpcodeCommand(" SetBR 2:c", std::bind(&Opcode::SetBR, this, 2, CPU->C), 8)},
                {0xCBD2, OpcodeCommand(" SetBR 2:d", std::bind(&Opcode::SetBR, this, 2, CPU->D), 8)},
                {0xCBD3, OpcodeCommand(" SetBR 2:e", std::bind(&Opcode::SetBR, this, 2, CPU->E), 8)},
                {0xCBD4, OpcodeCommand(" SetBR 2:h", std::bind(&Opcode::SetBR, this, 2, CPU->H), 8)},
                {0xCBD5, OpcodeCommand(" SetBR 2:l", std::bind(&Opcode::SetBR, this, 2, CPU->L), 8)},
                {0xCBD6, OpcodeCommand(" SetBR 2:hl", std::bind(&Opcode::SetBR_HL, this, 2), 16)},
                {0xCBD7, OpcodeCommand(" SetBR 2:a", std::bind(&Opcode::SetBR, this, 2, CPU->A), 8)},
                {0xCBD8, OpcodeCommand(" SetBR 3:b", std::bind(&Opcode::SetBR, this, 3, CPU->B), 8)},
                {0xCBD9, OpcodeCommand(" SetBR 3:c", std::bind(&Opcode::SetBR, this, 3, CPU->C), 8)},
                {0xCBDA, OpcodeCommand(" SetBR 3:d", std::bind(&Opcode::SetBR, this, 3, CPU->D), 8)},
                {0xCBDB, OpcodeCommand(" SetBR 3:e", std::bind(&Opcode::SetBR, this, 3, CPU->E), 8)},
                {0xCBDC, OpcodeCommand(" SetBR 3:h", std::bind(&Opcode::SetBR, this, 3, CPU->H), 8)},
                {0xCBDD, OpcodeCommand(" SetBR 3:l", std::bind(&Opcode::SetBR, this, 3, CPU->L), 8)},
                {0xCBDE, OpcodeCommand(" SetBR 3:hl", std::bind(&Opcode::SetBR_HL, this, 3), 16)},
                {0xCBDF, OpcodeCommand(" SetBR 3:a", std::bind(&Opcode::SetBR, this, 3, CPU->A), 8)},
                {0xCBE0, OpcodeCommand(" SetBR 4:b", std::bind(&Opcode::SetBR, this, 4, CPU->B), 8)},
                {0xCBE1, OpcodeCommand(" SetBR 4:c", std::bind(&Opcode::SetBR, this, 4, CPU->C), 8)},
                {0xCBE2, OpcodeCommand(" SetBR 4:d", std::bind(&Opcode::SetBR, this, 4, CPU->D), 8)},
                {0xCBE3, OpcodeCommand(" SetBR 4:e", std::bind(&Opcode::SetBR, this, 4, CPU->E), 8)},
                {0xCBE4, OpcodeCommand(" SetBR 4:h", std::bind(&Opcode::SetBR, this, 4, CPU->H), 8)},
                {0xCBE5, OpcodeCommand(" SetBR 4:l", std::bind(&Opcode::SetBR, this, 4, CPU->L), 8)},
                {0xCBE6, OpcodeCommand(" SetBR 4:hl", std::bind(&Opcode::SetBR_HL, this, 4), 16)},
                {0xCBE7, OpcodeCommand(" SetBR 4:a", std::bind(&Opcode::SetBR, this, 4, CPU->A), 8)},
                {0xCBE8, OpcodeCommand(" SetBR 5:b", std::bind(&Opcode::SetBR, this, 5, CPU->B), 8)},
                {0xCBE9, OpcodeCommand(" SetBR 5:c", std::bind(&Opcode::SetBR, this, 5, CPU->C), 8)},
                {0xCBEA, OpcodeCommand(" SetBR 5:d", std::bind(&Opcode::SetBR, this, 5, CPU->D), 8)},
                {0xCBEB, OpcodeCommand(" SetBR 5:e", std::bind(&Opcode::SetBR, this, 5, CPU->E), 8)},
                {0xCBEC, OpcodeCommand(" SetBR 5:h", std::bind(&Opcode::SetBR, this, 5, CPU->H), 8)},
                {0xCBED, OpcodeCommand(" SetBR 5:l", std::bind(&Opcode::SetBR, this, 5, CPU->L), 8)},
                {0xCBEE, OpcodeCommand(" SetBR 5:hl", std::bind(&Opcode::SetBR_HL, this, 5), 16)},
                {0xCBEF, OpcodeCommand(" SetBR 5:a", std::bind(&Opcode::SetBR, this, 5, CPU->A), 8)},
                {0xCBF0, OpcodeCommand(" SetBR 6:b", std::bind(&Opcode::SetBR, this, 6, CPU->B), 8)},
                {0xCBF1, OpcodeCommand(" SetBR 6:c", std::bind(&Opcode::SetBR, this, 6, CPU->C), 8)},
                {0xCBF2, OpcodeCommand(" SetBR 6:d", std::bind(&Opcode::SetBR, this, 6, CPU->D), 8)},
                {0xCBF3, OpcodeCommand(" SetBR 6:e", std::bind(&Opcode::SetBR, this, 6, CPU->E), 8)},
                {0xCBF4, OpcodeCommand(" SetBR 6:h", std::bind(&Opcode::SetBR, this, 6, CPU->H), 8)},
                {0xCBF5, OpcodeCommand(" SetBR 6:l", std::bind(&Opcode::SetBR, this, 6, CPU->L), 8)},
                {0xCBF6, OpcodeCommand(" SetBR 6:hl", std::bind(&Opcode::SetBR_HL, this, 6), 16)},
                {0xCBF7, OpcodeCommand(" SetBR 6:a", std::bind(&Opcode::SetBR, this, 6, CPU->A), 8)},
                {0xCBF8, OpcodeCommand(" SetBR 7:b", std::bind(&Opcode::SetBR, this, 7, CPU->B), 8)},
                {0xCBF9, OpcodeCommand(" SetBR 7:c", std::bind(&Opcode::SetBR, this, 7, CPU->C), 8)},
                {0xCBFA, OpcodeCommand(" SetBR 7:d", std::bind(&Opcode::SetBR, this, 7, CPU->D), 8)},
                {0xCBFB, OpcodeCommand(" SetBR 7:e", std::bind(&Opcode::SetBR, this, 7, CPU->E), 8)},
                {0xCBFC, OpcodeCommand(" SetBR 7:h", std::bind(&Opcode::SetBR, this, 7, CPU->H), 8)},
                {0xCBFD, OpcodeCommand(" SetBR 7:l", std::bind(&Opcode::SetBR, this, 7, CPU->L), 8)},
                {0xCBFE, OpcodeCommand(" SetBR 7:hl", std::bind(&Opcode::SetBR_HL, this, 7), 16)},
                {0xCBFF, OpcodeCommand(" SetBR 7:a", std::bind(&Opcode::SetBR, this, 7, CPU->A), 8)},
                // rotate register r left
                {0xCB00, OpcodeCommand(" RlcA b", std::bind(&Opcode::RlcA, this, CPU->B), 8)},
                {0xCB01, OpcodeCommand(" RlcA c", std::bind(&Opcode::RlcA, this, CPU->C), 8)},
                {0xCB02, OpcodeCommand(" RlcA d", std::bind(&Opcode::RlcA, this, CPU->D), 8)},
                {0xCB03, OpcodeCommand(" RlcA e", std::bind(&Opcode::RlcA, this, CPU->E), 8)},
                {0xCB04, OpcodeCommand(" RlcA h", std::bind(&Opcode::RlcA, this, CPU->H), 8)},
                {0xCB05, OpcodeCommand(" RlcA l", std::bind(&Opcode::RlcA, this, CPU->L), 8)},
                {0xCB06, OpcodeCommand(" RlcA hl", std::bind(&Opcode::RlcA_HL, this), 16)},
                {0xCB07, OpcodeCommand(" RlcA a 0xCB07", std::bind(&Opcode::RlcA, this, CPU->A), 8)},
                {0x07, OpcodeCommand(" RlcA a 0x07", std::bind(&Opcode::RlcA2, this, CPU->A), 4)},
                // rotate register r right
                {0xCB08, OpcodeCommand(" RrcA b", std::bind(&Opcode::RrcA, this, CPU->B), 8)},
                {0xCB09, OpcodeCommand(" RrcA c", std::bind(&Opcode::RrcA, this, CPU->C), 8)},
                {0xCB0A, OpcodeCommand(" RrcA d", std::bind(&Opcode::RrcA, this, CPU->D), 8)},
                {0xCB0B, OpcodeCommand(" RrcA e", std::bind(&Opcode::RrcA, this, CPU->E), 8)},
                {0xCB0C, OpcodeCommand(" RrcA h", std::bind(&Opcode::RrcA, this, CPU->H), 8)},
                {0xCB0D, OpcodeCommand(" RrcA l", std::bind(&Opcode::RrcA, this, CPU->L), 8)},
                {0xCB0E, OpcodeCommand(" RrcA hl", std::bind(&Opcode::RrcA_HL, this), 16)},
                {0xCB0F, OpcodeCommand(" RrcA a", std::bind(&Opcode::RrcA, this, CPU->A), 8)},
                {0x0F, OpcodeCommand(" RrcA a", std::bind(&Opcode::RrcA2, this, CPU->A), 4)},
                // rotate left
                {0xCB10, OpcodeCommand(" Rla b", std::bind(&Opcode::Rla, this, CPU->B), 8)},
                {0xCB11, OpcodeCommand(" Rla c", std::bind(&Opcode::Rla, this, CPU->C), 8)},
                {0xCB12, OpcodeCommand(" Rla d", std::bind(&Opcode::Rla, this, CPU->D), 8)},
                {0xCB13, OpcodeCommand(" Rla e", std::bind(&Opcode::Rla, this, CPU->E), 8)},
                {0xCB14, OpcodeCommand(" Rla h", std::bind(&Opcode::Rla, this, CPU->H), 8)},
                {0xCB15, OpcodeCommand(" Rla l", std::bind(&Opcode::Rla, this, CPU->L), 8)},
                {0xCB16, OpcodeCommand(" Rla hl", std::bind(&Opcode::Rla_HL, this), 16)},
                {0xCB17, OpcodeCommand(" Rla a", std::bind(&Opcode::Rla, this, CPU->A), 8)},
                {0x17, OpcodeCommand(" Rla a", std::bind(&Opcode::Rla2, this, CPU->A), 4)},
                // rotate right
                {0xCB18, OpcodeCommand(" RrA b", std::bind(&Opcode::RrA, this, CPU->B), 8)},
                {0xCB19, OpcodeCommand(" RrA c", std::bind(&Opcode::RrA, this, CPU->C), 8)},
                {0xCB1A, OpcodeCommand(" RrA d", std::bind(&Opcode::RrA, this, CPU->D), 8)},
                {0xCB1B, OpcodeCommand(" RrA e", std::bind(&Opcode::RrA, this, CPU->E), 8)},
                {0xCB1C, OpcodeCommand(" RrA h", std::bind(&Opcode::RrA, this, CPU->H), 8)},
                {0xCB1D, OpcodeCommand(" RrA l", std::bind(&Opcode::RrA, this, CPU->L), 8)},
                {0xCB1E, OpcodeCommand(" RrA hl", std::bind(&Opcode::RrA_HL, this), 16)},
                {0xCB1F, OpcodeCommand(" RrA a", std::bind(&Opcode::RrA, this, CPU->A), 8)},
                {0x1F, OpcodeCommand(" RrA a ", std::bind(&Opcode::RrA2, this, CPU->A), 4)},
                // shift left
                {0xCB20, OpcodeCommand(" Sla b", std::bind(&Opcode::Sla, this, CPU->B), 8)},
                {0xCB21, OpcodeCommand(" Sla c", std::bind(&Opcode::Sla, this, CPU->C), 8)},
                {0xCB22, OpcodeCommand(" Sla d", std::bind(&Opcode::Sla, this, CPU->D), 8)},
                {0xCB23, OpcodeCommand(" Sla e", std::bind(&Opcode::Sla, this, CPU->E), 8)},
                {0xCB24, OpcodeCommand(" Sla h", std::bind(&Opcode::Sla, this, CPU->H), 8)},
                {0xCB25, OpcodeCommand(" Sla l", std::bind(&Opcode::Sla, this, CPU->L), 8)},
                {0xCB26, OpcodeCommand(" Sla hl", std::bind(&Opcode::Sla_HL, this), 16)},
                {0xCB27, OpcodeCommand(" Sla a", std::bind(&Opcode::Sla, this, CPU->A), 8)},
                // shift right
                {0xCB28, OpcodeCommand(" Sra b", std::bind(&Opcode::Sra, this, CPU->B), 8)},
                {0xCB29, OpcodeCommand(" Sra c", std::bind(&Opcode::Sra, this, CPU->C), 8)},
                {0xCB2A, OpcodeCommand(" Sra d", std::bind(&Opcode::Sra, this, CPU->D), 8)},
                {0xCB2B, OpcodeCommand(" Sra e", std::bind(&Opcode::Sra, this, CPU->E), 8)},
                {0xCB2C, OpcodeCommand(" Sra h", std::bind(&Opcode::Sra, this, CPU->H), 8)},
                {0xCB2D, OpcodeCommand(" Sra l", std::bind(&Opcode::Sra, this, CPU->L), 8)},
                {0xCB2E, OpcodeCommand(" Sra hl", std::bind(&Opcode::Sra_HL, this), 16)},
                {0xCB2F, OpcodeCommand(" Sra a", std::bind(&Opcode::Sra, this, CPU->A), 8)},
                // shift left
                {0xCB38, OpcodeCommand(" Srl b", std::bind(&Opcode::Srl, this, CPU->B), 8)},
                {0xCB39, OpcodeCommand(" Srl c", std::bind(&Opcode::Srl, this, CPU->C), 8)},
                {0xCB3A, OpcodeCommand(" Srl d", std::bind(&Opcode::Srl, this, CPU->D), 8)},
                {0xCB3B, OpcodeCommand(" Srl e", std::bind(&Opcode::Srl, this, CPU->E), 8)},
                {0xCB3C, OpcodeCommand(" Srl h", std::bind(&Opcode::Srl, this, CPU->H), 8)},
                {0xCB3D, OpcodeCommand(" Srl l", std::bind(&Opcode::Srl, this, CPU->L), 8)},
                {0xCB3E, OpcodeCommand(" Srl hl", std::bind(&Opcode::Srl_HL, this), 16)},
                {0xCB3F, OpcodeCommand(" Srl a", std::bind(&Opcode::Srl, this, CPU->A), 8)},
            };
    }

    void Opcode::LdReadByte(std::shared_ptr<register8_t> r1)
    {
        byte read = CPU->GetByteFromPC();
        *r1 = read;
    }

    // 1. LD nn, n
    void Opcode::LdWriteByte(std::shared_ptr<register8_t> r1)
    {
        CPU->WriteBytePC(*r1);
    }

    void Opcode::LdWriteWord(std::shared_ptr<Register16> r1)
    {
        CPU->WriteWordPC(register16_t(r1->value()));
    }

    void Opcode::LdReadWord(std::shared_ptr<Register16> r1)
    {
        uint16_t read = CPU->GetWordFromPC();
        r1->Set(read);
    }

    void Opcode::Ld_A(std::shared_ptr<Register16> r1)
    {
        byte read = gbc::Ram::Instance()->ReadByte(r1->value());
        r1->Set(read);
    }

    void Opcode::Ld_An(std::shared_ptr<Register16> r1)
    {
        byte read = gbc::Ram::Instance()->ReadByte(r1->value());
        CPU->A->Set(read);
    }

    void Opcode::Ld_An_PC()
    {
        CPU->A->Set(CPU->GetByteFromPC());
    }

    void Opcode::Ld_An_PC2()
    {
        uint16_t addr = CPU->GetWordFromPC();
        byte read = gbc::Ram::Instance()->ReadByte(addr);
        CPU->A->Set(read);
    }

    void Opcode::Ld_Write_A(std::shared_ptr<Register16> r1)
    {
        gbc::Ram::Instance()->WriteByte(r1->value(), CPU->A->value());
    }

    void Opcode::Ld_Write_A_IncHL()
    {
        gbc::Ram::Instance()->WriteByte(CPU->HL->value(), CPU->A->value());
        IncN16(CPU->HL);
    }

    void Opcode::Ld_Write_A_DecHL()
    {
        gbc::Ram::Instance()->WriteByte(CPU->HL->value(), CPU->A->value());
        DecN16(CPU->HL);
    }

    void Opcode::Ld_HL(std::shared_ptr<register8_t> r1)
    {
        byte read = gbc::Ram::Instance()->ReadByte(CPU->HL->value());
        r1->Set(read);
    }

    void Opcode::Ld_HL_Inc()
    {
        byte read = gbc::Ram::Instance()->ReadByte(CPU->HL->value());
        CPU->A->Set(read);
        IncN16(CPU->HL);
    }

    void Opcode::Ld_HL_Dec()
    {
        byte read = gbc::Ram::Instance()->ReadByte(CPU->HL->value());
        CPU->A->Set(read);
        DecN16(CPU->HL);
    }

    void Opcode::Ld_HL_Write(std::shared_ptr<register8_t> r1)
    {
        gbc::Ram::Instance()->WriteByte(CPU->HL->value(), r1->value());
    }

    void Opcode::Ld_HL_WritePC()
    {
        gbc::Ram::Instance()->WriteByte(CPU->HL->value(), CPU->GetByteFromPC());
    }

    void Opcode::Ld_Write_SP()
    {
        register16_t sp_tmp = CPU->SP->value();
        uint16_t addr = CPU->GetWordFromPC();
        gbc::Ram::Instance()->WriteByte(addr, sp_tmp.Low());
        gbc::Ram::Instance()->WriteByte(addr + 1, sp_tmp.High());

    }

    void Opcode::Ld_Write_A_PC()
    {
        gbc::Ram::Instance()->WriteByte(CPU->GetWordFromPC(), CPU->A->value());
    }

    // 2. LD r1, r2
    void Opcode::LdR1R2(std::shared_ptr<register8_t> r1, std::shared_ptr<register8_t> r2)
    {
        r1->Set( r2->mValue);
        BOOST_LOG_TRIVIAL(debug) << *r1;
        BOOST_LOG_TRIVIAL(debug) << *r2;
    }

    void Opcode::LdR1R2_16(std::shared_ptr<Register16> r1, std::shared_ptr<Register16> r2)
    {
        r1->Set( r2->value());
    }

    void Opcode::LdHL_SP()
    {
        int8_t n = static_cast<int8_t>(CPU->GetByteFromPC());
        uint16_t sp = CPU->SP->value();
        int result = sp + n;

        CPU->FLAGS->SetZeroFlag(false);
        CPU->FLAGS->SetSubtractFlag(false);
        CPU->FLAGS->SetHalfCarryFlag(((sp ^ n ^ (result & 0xFFFF)) & 0x10) == 0x10);
        CPU->FLAGS->SetCarryFlag(((sp ^ n ^ (result & 0xFFFF)) & 0x100) == 0x100);

        CPU->HL->Set(result);
    }

    void Opcode::Ldh_nA()
    {
        byte n = CPU->GetByteFromPC();
        address16_t write_addr = 0xFF00 + n;
        gbc::Ram::Instance()->WriteByte(write_addr, CPU->A->value());
    }

    void Opcode::Ldh_An()
    {
        byte n = CPU->GetByteFromPC();
        byte read = gbc::Ram::Instance()->ReadByte(0xFF00 + n);
        CPU->A->Set(read);
    }

    void Opcode::Ldh_CA()
    {
        address16_t write_addr = 0xFF00 + CPU->C->value();
        gbc::Ram::Instance()->WriteByte(write_addr, CPU->A->value());
    }

    void Opcode::Ldh_AC()
    {
        byte read = gbc::Ram::Instance()->ReadByte(0xFF00 + CPU->C->value());
        CPU->A->Set(read);
    }
    // Add 8-bit
    void Opcode::AddA(std::shared_ptr<register8_t> r1, std::shared_ptr<register8_t> r2)
    {
        BOOST_LOG_TRIVIAL(debug) << *r1;
        BOOST_LOG_TRIVIAL(debug) << *r2;
        uint32_t result = r1->value() + r2->value();

        CPU->FLAGS->SetZeroFlag((byte) result == 0x0);
        CPU->FLAGS->SetSubtractFlag(false);
        CPU->FLAGS->SetHalfCarryFlag((0xF & r1->value()) + (0xF & r2->value()) > 0xF);
        CPU->FLAGS->SetCarryFlag((result & 0x100) != 0);

        r1->Set( static_cast<byte>(result));
    }

    void Opcode::AddA_HL()
    {
        register8_t byte = register8_t(gbc::Ram::Instance()->ReadByte(CPU->HL->value()));
        AddA(CPU->A, std::make_shared<register8_t>(byte));
    }

    void Opcode::AddA_PC()
    {
        register8_t byte = CPU->GetByteFromPC();
        AddA(CPU->A, std::make_shared<register8_t>(byte));
    }

    // Adc 8-bit. Very redundant code but more explicit i guess
    void Opcode::AdcA(std::shared_ptr<register8_t> r1, std::shared_ptr<register8_t> r2)
    {
        uint32_t result = r1->value() + r2->value() + CPU->FLAGS->CarryFlag();

        CPU->FLAGS->SetZeroFlag((byte) result == 0x0);
        CPU->FLAGS->SetSubtractFlag(false);
        CPU->FLAGS->SetHalfCarryFlag( ((0xF & r1->value()) + (0xF & r2->value()) + CPU->FLAGS->CarryFlag() > 0xF));
        CPU->FLAGS->SetCarryFlag((result & 0x100) != 0);

        r1->Set( static_cast<byte>(result));
    }

    void Opcode::AdcA_HL()
    {
        register8_t byte = register8_t(gbc::Ram::Instance()->ReadByte(CPU->HL->value()));
        AdcA(CPU->A, std::make_shared<register8_t>(byte));
    }

    void Opcode::AdcA_PC()
    {
        register8_t byte = CPU->GetByteFromPC();
        AdcA(CPU->A, std::make_shared<register8_t>(byte));
    }

    // SubA
    void Opcode::SubA(std::shared_ptr<register8_t> r1, std::shared_ptr<register8_t> r2)
    {
        byte result = r1->value() - r2->value();

        CPU->FLAGS->SetZeroFlag(result == 0x0);
        CPU->FLAGS->SetSubtractFlag(true);
        CPU->FLAGS->SetHalfCarryFlag(((0xF & r1->value()) - (0xF & r2->value())) < 0);
        CPU->FLAGS->SetCarryFlag(r1->value() < r2->value());

        r1->Set( result);
    }

    void Opcode::SubA_HL()
    {
        register8_t byte = register8_t(gbc::Ram::Instance()->ReadByte(CPU->HL->value()));
        SubA(CPU->A, std::make_shared<register8_t>(byte));
    }

    void Opcode::SubA_PC()
    {
        register8_t byte = CPU->GetByteFromPC();
        SubA(CPU->A, std::make_shared<register8_t>(byte));
    }

    // SbcA
    void Opcode::SbcA(std::shared_ptr<register8_t> r1, std::shared_ptr<register8_t> r2)
    {
        int8_t result = r1->value() - r2->value() - CPU->FLAGS->CarryFlag();

        CPU->FLAGS->SetZeroFlag(result == 0x0);
        CPU->FLAGS->SetSubtractFlag(true);
        CPU->FLAGS->SetHalfCarryFlag( ((0xF & r1->value()) - (0xF & r2->value())) - CPU->FLAGS->CarryFlag() < 0);
        CPU->FLAGS->SetCarryFlag(r1->value() - CPU->FLAGS->CarryFlag() < r2->value());

        r1->Set( static_cast<byte>(result));
    }

    void Opcode::SbcA_HL()
    {
        register8_t byte = register8_t(gbc::Ram::Instance()->ReadByte(CPU->HL->value()));
        SbcA(CPU->A, std::make_shared<register8_t>(byte));
    }

    void Opcode::SbcA_PC()
    {
        register8_t byte = CPU->GetByteFromPC();
        SbcA(CPU->A, std::make_shared<register8_t>(byte));
    }

    void Opcode::AndA(std::shared_ptr<register8_t> r1, std::shared_ptr<register8_t> r2)
    {
        byte result = r1->mValue & r2->mValue;

        CPU->FLAGS->SetZeroFlag(result == 0x0);
        CPU->FLAGS->SetSubtractFlag(false);
        CPU->FLAGS->SetHalfCarryFlag(true);
        CPU->FLAGS->SetCarryFlag(false);

        r1->Set( result);
    }

    void Opcode::AndA_HL()
    {
        register8_t byte = register8_t(gbc::Ram::Instance()->ReadByte(CPU->HL->value()));
        AndA(CPU->A, std::make_shared<register8_t>(byte));
    }

    void Opcode::AndA_PC()
    {
        register8_t byte = CPU->GetByteFromPC();
        AndA(CPU->A, std::make_shared<register8_t>(byte));
    }

    void Opcode::OrA(std::shared_ptr<register8_t> r1, std::shared_ptr<register8_t> r2)
    {
        byte result = r1->mValue | r2->mValue;

        CPU->FLAGS->SetZeroFlag(result == 0x0);
        CPU->FLAGS->SetSubtractFlag(false);
        CPU->FLAGS->SetHalfCarryFlag(false);
        CPU->FLAGS->SetCarryFlag(false);

        r1->Set( result);
    }

    void Opcode::OrA_HL()
    {
        register8_t byte = register8_t(gbc::Ram::Instance()->ReadByte(CPU->HL->value()));
        OrA(CPU->A, std::make_shared<register8_t>(byte));
    }

    void Opcode::OrA_PC()
    {
        register8_t byte = CPU->GetByteFromPC();
        OrA(CPU->A, std::make_shared<register8_t>(byte));
    }

    void Opcode::XorA(std::shared_ptr<register8_t> r1, std::shared_ptr<register8_t> r2)
    {
        byte result = r1->mValue ^ r2->mValue;

        CPU->FLAGS->SetZeroFlag(result == 0x0);
        CPU->FLAGS->SetSubtractFlag(false);
        CPU->FLAGS->SetHalfCarryFlag(false);
        CPU->FLAGS->SetCarryFlag(false);

        r1->Set( result);
    }

    void Opcode::XorA_HL()
    {
        register8_t byte = register8_t(gbc::Ram::Instance()->ReadByte(CPU->HL->value()));
        XorA(CPU->A, std::make_shared<register8_t>(byte));
    }

    void Opcode::XorA_PC()
    {
        register8_t byte = CPU->GetByteFromPC();
        XorA(CPU->A, std::make_shared<register8_t>(byte));
    }

    void Opcode::CpA(std::shared_ptr<register8_t> r1, std::shared_ptr<register8_t> r2)
    {
        byte result = r1->value() - r2->value();

        CPU->FLAGS->SetZeroFlag(result == 0x0);
        CPU->FLAGS->SetSubtractFlag(true);
        CPU->FLAGS->SetHalfCarryFlag((0xF & r1->value()) - (0xF & r2->value()) < 0);
        CPU->FLAGS->SetCarryFlag(r1->value() < r2->value());
    }

    void Opcode::CpA_HL()
    {
        register8_t byte = register8_t(gbc::Ram::Instance()->ReadByte(CPU->HL->value()));
        CpA(CPU->A, std::make_shared<register8_t>(byte));
    }

    void Opcode::CpA_PC()
    {
        register8_t byte = CPU->GetByteFromPC();
        CpA(CPU->A, std::make_shared<register8_t>(byte));
    }

    void Opcode::IncN(std::shared_ptr<register8_t> r1)
    {
        CPU->FLAGS->SetHalfCarryFlag((0xF & r1->value()) + 1 > 0xF);
        r1->Set(r1->value() + 1);
        CPU->FLAGS->SetZeroFlag(r1->value() == 0x0);
        CPU->FLAGS->SetSubtractFlag(false);

    }

    void Opcode::IncN_HL()
    {
        byte read = gbc::Ram::Instance()->ReadByte(CPU->HL->value());
        CPU->FLAGS->SetHalfCarryFlag((0xF & read) + 1 > 0xF);
        read++;
        CPU->FLAGS->SetZeroFlag(read == 0x0);
        CPU->FLAGS->SetSubtractFlag(false);
        gbc::Ram::Instance()->WriteByte(CPU->HL->value(), read);

    }

    void Opcode::DecN(std::shared_ptr<register8_t> r1)
    {
        CPU->FLAGS->SetHalfCarryFlag((r1->value() & 0xF) - 1 < 0);
        r1->Set(r1->value() - 1);
        CPU->FLAGS->SetZeroFlag(r1->value() == 0x0);
        CPU->FLAGS->SetSubtractFlag(true);

    }

    void Opcode::DecN_HL()
    {
        byte read = gbc::Ram::Instance()->ReadByte(CPU->HL->value());
        CPU->FLAGS->SetHalfCarryFlag((read & 0xF) - 1 < 0);
        read--;
        CPU->FLAGS->SetZeroFlag(read == 0x0);
        CPU->FLAGS->SetSubtractFlag(true);
        gbc::Ram::Instance()->WriteByte(CPU->HL->value(), read);

    }

    

    // Add 16-bit
    void Opcode::AddHL(std::shared_ptr<Register16> r1, std::shared_ptr<Register16> r2)
    {
        int32_t result = r1->value() + r2->value();

       // CPU->FLAGS->SetZeroFlag(result == 0x0);
        CPU->FLAGS->SetSubtractFlag(false);
        CPU->FLAGS->SetHalfCarryFlag(((0xFFF & r1->value()) + (0xFFF & r2->value())) > 0xFFF);
        CPU->FLAGS->SetCarryFlag((result & 0x10000) != 0);

        r1->Set( static_cast<uint16_t>(result));
    }

    void Opcode::AddSP()
    {
        int8_t n = static_cast<int8_t>(CPU->GetByteFromPC());
        uint16_t sp = CPU->SP->value();
        int result = sp + n;

        CPU->FLAGS->SetZeroFlag(false);
        CPU->FLAGS->SetSubtractFlag(false);
        CPU->FLAGS->SetHalfCarryFlag(((sp ^ n ^ (result & 0xFFFF)) & 0x10) == 0x10);
        CPU->FLAGS->SetCarryFlag(((sp ^ n ^ (result & 0xFFFF)) & 0x100) == 0x100);

        CPU->SP->Set(CPU->SP->value() + n);
    }

    void Opcode::IncN16(std::shared_ptr<Register16> r1)
    {
        r1->Set(r1->value() + 1);
    }

    void Opcode::DecN16(std::shared_ptr<Register16> r1)
    {
        r1->Set(r1->value() - 1);
    }

    void Opcode::Swap(std::shared_ptr<register8_t> r1)
    {
        byte high = r1->High();
        byte low = r1->Low();
        r1->Set( (low << 4) | high);
        CPU->FLAGS->SetZeroFlag(r1->value() == 0x0);
        CPU->FLAGS->SetSubtractFlag(false);
        CPU->FLAGS->SetHalfCarryFlag(false);
        CPU->FLAGS->SetCarryFlag(false);
    }

    void Opcode::SwapHL()
    {
        std::shared_ptr<register8_t> byte = std::shared_ptr<register8_t>(new register8_t(gbc::Ram::Instance()->ReadByte(CPU->HL->value())));
        Swap(byte);
        gbc::Ram::Instance()->WriteByte(CPU->HL->value(), byte->value());
    }

    void Opcode::Push(std::shared_ptr<Register16> r1)
    {
        CPU->StackPush(r1->value());
    }

    void Opcode::Pop(std::shared_ptr<Register16> r1)
    {
        uint16_t read = CPU->StackPop();
        r1->Set( read);

        if (r1->name() == "AF") 
        {
            for (int i = 0; i <= 3; i++)
            {
                // apparently these need to always be 0'd out
                r1->Low()->ResetBitLSB(i);
            }
        }
    }
    // binary coded decimal conversion
    void Opcode::DAA()
    {
        byte val_a = CPU->A->value();
        uint16_t correct = CPU->FLAGS->CarryFlag() ? 0x60 : 0x00;

        if (CPU->FLAGS->HalfCarryFlag() || (!CPU->FLAGS->SubtractFlag() && ((val_a & 0x0F) > 9)))
        {
            correct |= 0x06;
        }

        if (CPU->FLAGS->CarryFlag() || (!CPU->FLAGS->SubtractFlag() && (val_a > 0x99)))
        {
            correct |= 0x60;
        }

        val_a = CPU->FLAGS->SubtractFlag() ? static_cast<byte>(val_a - correct) : static_cast<byte>(val_a + correct);
        CPU->FLAGS->SetZeroFlag(val_a == 0x0);
        CPU->FLAGS->SetHalfCarryFlag(false);
        CPU->FLAGS->SetCarryFlag(((correct << 2) & 0x100) != 0);
        CPU->A->Set(val_a);

    }

    void Opcode::CPL()
    {
        byte res = CPU->A->value() ^ 0xFF;
        CPU->FLAGS->SetSubtractFlag(true);
        CPU->FLAGS->SetHalfCarryFlag(true);
        CPU->A->Set(res);
    }
    // complement carry flag
    void Opcode::CCF()
    {

        if (CPU->FLAGS->CarryFlag())
            CPU->FLAGS->SetCarryFlag(false);
        else
            CPU->FLAGS->SetCarryFlag(true);

        CPU->FLAGS->SetSubtractFlag(false);
        CPU->FLAGS->SetHalfCarryFlag(false);
    }
    // set carry flag
    void Opcode::SCF()
    {
        CPU->FLAGS->SetSubtractFlag(false);
        CPU->FLAGS->SetHalfCarryFlag(false);
        CPU->FLAGS->SetCarryFlag(true);
    }

    void Opcode::NOP()
    {
        // do literally nothing
    }

    void Opcode::HALT()
    {
        // also do literally nothing?
    }

    void Opcode::STOP()
    {
    }

    // disable interrupts
    void Opcode::DI()
    {
        // set a flag?
    }
    // enable interrupts
    void Opcode::EI()
    {
        // set a flag?
    }

    void Opcode::RlcA(std::shared_ptr<register8_t> r1)
    {
        bool bit_7 = r1->BitAtLSB(7);
        r1->Set( (r1->value() << 1) | bit_7);

        CPU->FLAGS->SetZeroFlag(r1->value() == 0x0);
        CPU->FLAGS->SetSubtractFlag(false);
        CPU->FLAGS->SetHalfCarryFlag(false);
        CPU->FLAGS->SetCarryFlag(bit_7);
    }

    void Opcode::RlcA2(std::shared_ptr<register8_t> r1)
    {
        RlcA(r1);
        CPU->FLAGS->SetZeroFlag(false);
    }

    void Opcode::Rla(std::shared_ptr<register8_t> r1)
    {
        bool carry = CPU->FLAGS->CarryFlag();
        bool bit_7 = r1->BitAtLSB(7);
        r1->Set( (r1->value() << 1) | carry);

        CPU->FLAGS->SetZeroFlag(r1->value() == 0x0);
        CPU->FLAGS->SetSubtractFlag(false);
        CPU->FLAGS->SetHalfCarryFlag(false);
        CPU->FLAGS->SetCarryFlag(bit_7);
    }

    void Opcode::Rla2(std::shared_ptr<register8_t> r1)
    {
        Rla(r1);
        CPU->FLAGS->SetZeroFlag(false);
    }

    void Opcode::RrcA(std::shared_ptr<register8_t> r1)
    {
        bool bit_0 = r1->BitAtLSB(0);
        r1->Set( (r1->value() >> 1) | (bit_0 << 7));

        CPU->FLAGS->SetZeroFlag(r1->value() == 0x0);
        CPU->FLAGS->SetSubtractFlag(false);
        CPU->FLAGS->SetHalfCarryFlag(false);
        CPU->FLAGS->SetCarryFlag(bit_0);
    }

    void Opcode::RrcA2(std::shared_ptr<register8_t> r1)
    {
        RrcA(r1);
        CPU->FLAGS->SetZeroFlag(false);
    }

    void Opcode::RrA(std::shared_ptr<register8_t> r1)
    {
        bool carry = CPU->FLAGS->CarryFlag();
        bool bit_0 = r1->BitAtLSB(0);
        r1->Set( (r1->value() >> 1) | (carry << 7));

        CPU->FLAGS->SetZeroFlag(r1->value() == 0x0);
        CPU->FLAGS->SetSubtractFlag(false);
        CPU->FLAGS->SetHalfCarryFlag(false);
        CPU->FLAGS->SetCarryFlag(bit_0);
    }

    void Opcode::RrA2(std::shared_ptr<register8_t> r1)
    {
        RrA(r1);
        CPU->FLAGS->SetZeroFlag(false);
    }

    void Opcode::Sla(std::shared_ptr<register8_t> r1)
    {

        bool bit_7 = r1->BitAtLSB(7);
        r1->Set( r1->value() << 1);
        r1->SetBitLSB(0, false);

        CPU->FLAGS->SetZeroFlag(r1->value() == 0x0);
        CPU->FLAGS->SetSubtractFlag(false);
        CPU->FLAGS->SetHalfCarryFlag(false);
        CPU->FLAGS->SetCarryFlag(bit_7);
    }

    void Opcode::Sra(std::shared_ptr<register8_t> r1)
    {
        bool bit_0 = r1->BitAtLSB(0);
        bool msb = r1->BitAtLSB(7);
        r1->Set( r1->value() >> 1);
        r1->SetBitLSB(7, msb);

        CPU->FLAGS->SetZeroFlag(r1->value() == 0x0);
        CPU->FLAGS->SetSubtractFlag(false);
        CPU->FLAGS->SetHalfCarryFlag(false);
        CPU->FLAGS->SetCarryFlag(bit_0);
    }

    void Opcode::Srl(std::shared_ptr<register8_t> r1)
    {
        bool bit_0 = r1->BitAtLSB(0);
        bool msb = r1->BitAtLSB(7);
        r1->Set( r1->value() >> 1);
        r1->SetBitLSB(7, false);

        CPU->FLAGS->SetZeroFlag(r1->value() == 0x0);
        CPU->FLAGS->SetSubtractFlag(false);
        CPU->FLAGS->SetHalfCarryFlag(false);
        CPU->FLAGS->SetCarryFlag(bit_0);
    }

    void Opcode::RlcA_HL()
    {
        std::shared_ptr<register8_t> tmp = std::shared_ptr<register8_t>(new register8_t(Ram::Instance()->ReadByte(CPU->HL->value()), "HL Byte"));
        RlcA(tmp);
        Ram::Instance()->WriteByte(CPU->HL->value(), tmp->value());
    }

    void Opcode::RrcA_HL()
    {
        std::shared_ptr<register8_t> tmp = std::shared_ptr<register8_t>(new register8_t(Ram::Instance()->ReadByte(CPU->HL->value()), "HL Byte"));
        RrcA(tmp);
        Ram::Instance()->WriteByte(CPU->HL->value(), tmp->value());
    }

    void Opcode::Rla_HL()
    {
        std::shared_ptr<register8_t> tmp = std::shared_ptr<register8_t>(new register8_t(Ram::Instance()->ReadByte(CPU->HL->value()), "HL Byte"));
        Rla(tmp);
        Ram::Instance()->WriteByte(CPU->HL->value(), tmp->value());
    }

    void Opcode::RrA_HL()
    {
        std::shared_ptr<register8_t> tmp = std::shared_ptr<register8_t>(new register8_t(Ram::Instance()->ReadByte(CPU->HL->value()), "HL Byte"));
        RrA(tmp);
        Ram::Instance()->WriteByte(CPU->HL->value(), tmp->value());
    }

    void Opcode::Sla_HL()
    {
        std::shared_ptr<register8_t> tmp = std::shared_ptr<register8_t>(new register8_t(Ram::Instance()->ReadByte(CPU->HL->value()), "HL Byte"));
        Sla(tmp);
        Ram::Instance()->WriteByte(CPU->HL->value(), tmp->value());
    }

    void Opcode::Sra_HL()
    {
        std::shared_ptr<register8_t> tmp = std::shared_ptr<register8_t>(new register8_t(Ram::Instance()->ReadByte(CPU->HL->value()), "HL Byte"));
        Sra(tmp);
        Ram::Instance()->WriteByte(CPU->HL->value(), tmp->value());
    }

    void Opcode::Srl_HL()
    {
        std::shared_ptr<register8_t> tmp = std::shared_ptr<register8_t>(new register8_t(Ram::Instance()->ReadByte(CPU->HL->value()), "HL Byte"));
        Srl(tmp);
        Ram::Instance()->WriteByte(CPU->HL->value(), tmp->value());
    }

    void Opcode::JpNN()
    {
       // std::cout << "Executing jpNN" << std::endl;
        uint16_t read = CPU->GetWordFromPC();
        CPU->PC->Set(read);
    }

    void Opcode::JpCCNN(std::function<bool()> bit)
    {
      //  std::cout << "bool is = " << bit() << std::endl;
        if (bit())
            JpNN();
        else
            uint16_t read = CPU->GetWordFromPC(); // always read the word no matter what

    }

    void Opcode::JpHL()
    {
        CPU->PC->Set(CPU->HL->value());
    }

    void Opcode::JrN()
    {
        BOOST_LOG_TRIVIAL(debug) << "doing JR n";
        int8_t read = static_cast<int8_t>(CPU->GetByteFromPC());
        CPU->PC->Set(CPU->PC->value() + read);
    }

    void Opcode::JrCCN(std::function<bool()> bit)
    {
        if (bit())
            JrN();
        else
            uint16_t read = CPU->GetByteFromPC();
    }

    void Opcode::CallNN()
    {
        uint16_t read = CPU->GetWordFromPC();
        Push(CPU->PC);
        CPU->PC->Set(read);
    }

    void Opcode::CallCCNN(std::function<bool()> bit)
    {
        if (bit())
            CallNN();
        else
            uint16_t read = CPU->GetWordFromPC();
    }

    void Opcode::Rst(uint8_t address)
    {
        Push(CPU->PC);
        CPU->PC->Set(address);
    }

    void Opcode::Ret()
    {
        BOOST_LOG_TRIVIAL(debug) << "Doing ret cc";
        uint16_t val = CPU->StackPop();
        CPU->PC->Set(val);
    }

    void Opcode::RetCC(std::function<bool()> bit)
    {
        if (bit())
            Ret();
    }

    void Opcode::RetI()
    {
        uint16_t read = CPU->StackPop();
        CPU->PC->Set(read);
    }

    void Opcode::BitBR(byte b, std::shared_ptr<register8_t> r1)
    {

        CPU->FLAGS->SetZeroFlag(r1->BitAtLSB(b) == 0);
        CPU->FLAGS->SetSubtractFlag(false);
        CPU->FLAGS->SetHalfCarryFlag(true);
    }

    void Opcode::BitBR_HL(byte b)
    {
        std::shared_ptr<register8_t> tmp = std::shared_ptr<register8_t>(new register8_t(Ram::Instance()->ReadByte(CPU->HL->value()), "HL Byte"));
        BitBR(b, tmp);
    }

    void Opcode::SetBR(byte b, std::shared_ptr<register8_t> r1)
    {
        r1->SetBitLSB(b);
    }

    void Opcode::SetBR_HL(byte b)
    {
        std::shared_ptr<register8_t> tmp = std::shared_ptr<register8_t>(new register8_t(Ram::Instance()->ReadByte(CPU->HL->value()), "HL Byte"));
        SetBR(b, tmp);
        Ram::Instance()->WriteByte(CPU->HL->value(), tmp->value());
    }

    void Opcode::ResBR(byte b, std::shared_ptr<register8_t> r1)
    {
        r1->ResetBitLSB(b);
    }

    void Opcode::ResBR_HL(byte b)
    {
        std::shared_ptr<register8_t> tmp = std::shared_ptr<register8_t>(new register8_t(Ram::Instance()->ReadByte(CPU->HL->value()), "HL Byte"));
        ResBR(b, tmp);
        Ram::Instance()->WriteByte(CPU->HL->value(), tmp->value());
    }

    std::shared_ptr<Opcode> Opcode::Instance()
    {
        static std::shared_ptr<Opcode> inst = std::make_shared<Opcode>(Opcode());
        return inst;
    }
}