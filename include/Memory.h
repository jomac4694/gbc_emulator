#ifndef MEMORY_H
#define MEMORY_H

#include <array>
#include "Register.h"
#include <memory>
namespace gbc
{

    namespace Reserved
    {
        constexpr uint16_t RST_00 = 0x0000; // RST calls this address
        constexpr uint16_t RST_08 = 0x0008;
        constexpr uint16_t RST_10 = 0x0010;
        constexpr uint16_t RST_18 = 0x0018;
        constexpr uint16_t RST_20 = 0x0020;
        constexpr uint16_t RST_28 = 0x0028;
        constexpr uint16_t RST_30 = 0x0030;
        constexpr uint16_t RST_38 = 0x0038;
        constexpr uint16_t VB_INTERRUPT = 0x0040;               // vertical bank interrupt
        constexpr uint16_t LCDC_INTERRUPT = 0x0048;             // lcdc status interrupt
        constexpr uint16_t TIMER_INTERRUPT = 0x0050;            // timer overflow interrupt
        constexpr uint16_t SERIAL_TRANSFER_INTERRUPT = 0x0058;  // serial transfer completion interrupt
        constexpr uint16_t HIGH_LOW_P10_P13_INTERRUPT = 0x0060; // high to low of p10-p13 interrupt
        constexpr uint16_t CARTRIDGE_START = 0x0100;
        constexpr uint16_t LOGO_START = 0x0104;
        constexpr uint16_t PROGRAM_TITLE = 0x0134;
        constexpr uint16_t GB_COLOR_INDICATOR = 0x0143;
        constexpr uint16_t ASCII_HEX_DIG_HIGH = 0x0144;
        constexpr uint16_t ASCII_HEX_DIG_LOW = 0x0145;
        constexpr uint16_t SGB_INDICATOR = 0x0146;
        constexpr uint16_t CARTRIDGE_TYPE = 0x0147;
        constexpr uint16_t ROM_SIZE = 0x0148;
        constexpr uint16_t RAM_SIZE = 0x0149;
        constexpr uint16_t DESTINATION_CODE = 0x014A;
        constexpr uint16_t LICENSEE_CODE = 0x014B;
        constexpr uint16_t MASK_ROM_VERSION = 0x014C;
        constexpr uint16_t COMPLEMENT_CHECK = 0x014D;
        constexpr uint16_t CHECKSUM = 0x014E;

    }
    //  std::vector<byte> tendo_logo =
    //{ 0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D,
    // 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99,
    // 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E};

    struct Ram
    {

    public:
        Ram();
        std::array<byte, 0xFFFF> GetMemory();

        byte ReadByte(uint16_t address);

        // Handles increments
        byte ReadByte(address16_t address);

        uint16_t ReadWord(address16_t address);

        void WriteByte(uint16_t address, register8_t val);

        void WriteByte(address16_t address, register8_t val);

        void WriteWord(address16_t address, register16_t value);

        uint16_t ReadWordStack(address16_t address);

        void WriteWordStack(address16_t address, register16_t value);

        void ClearMem();

        static std::shared_ptr<Ram> Instance();

        
    private:
        std::array<byte, 0xFFFF> mMemory;

    };

}

#endif