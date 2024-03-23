#ifndef MEMORY_H
#define MEMORY_H

#include <array>
#include "Register.h"
#include <memory>
namespace gbc
{

    // no _START or _END postfix means its a single byte
    namespace MemoryMap
    {
        const uint16_t OFFSET_RESTART_AND_INTERRUPT_VECTORS_START = 0x0000;
        const uint16_t OFFSET_RESTART_AND_INTERRUPT_VECTORS_END   = 0x00FF;
        const uint16_t OFFSET_CART_HEADER_START                   = 0x0100;
        const uint16_t OFFSET_CART_HEADER_END                     = 0x014F;
        const uint16_t OFFSET_CART_ROM_BANK0_START                = 0x0150;
        const uint16_t OFFSET_CART_ROM_BANK0_END                  = 0x3FFF;
        const uint16_t OFFSET_CART_ROM_BANKN_START                = 0x4000;
        const uint16_t OFFSET_CART_ROM_BANKN_END                  = 0x7FFF;
        const uint16_t OFFSET_CHARACTER_RAM_START                 = 0x8000;
        const uint16_t OFFSET_CHARACTER_RAM_END                   = 0x97FF;
        const uint16_t OFFSET_BG_MAP_DATA1_START                  = 0x9800;
        const uint16_t OFFSET_BG_MAP_DATA1_END                    = 0x9BFF;
        const uint16_t OFFSET_BG_MAP_DATA2_START                  = 0x9C00;
        const uint16_t OFFSET_BG_MAP_DATA2_END                    = 0x9FFF;
        const uint16_t OFFSET_CART_RAM_START                      = 0xA000;
        const uint16_t OFFSET_CART_RAM_END                        = 0xBFFF;
        const uint16_t OFFSET_INTERNAL_RAM_BANK0_START            = 0xC000;
        const uint16_t OFFSET_INTERNAL_RAM_BANK0_END              = 0xCFFF;
        const uint16_t OFFSET_INTERNAL_RAM_BANK1_7_START          = 0xD000;
        const uint16_t OFFSET_INTERNAL_RAM_BANK1_7_END            = 0xDFFF;
        const uint16_t OFFSET_ECHO_RAM_START                      = 0xE000;
        const uint16_t OFFSET_ECHO_RAM_END                        = 0xFDFF;
        const uint16_t OFFSET_OBJECT_ATTR_MEM_START               = 0xFE00;
        const uint16_t OFFSET_OBJECT_ATTR_MEM_END                 = 0xFE9F;
        const uint16_t OFFSET_UNUSABLE_MEMORY_START               = 0xFEA0;
        const uint16_t OFFSET_UNUSABLE_MEMORY_END                 = 0xFEFF;
        const uint16_t OFFSET_HARDWARE_IO_REGS_START              = 0xFF00;
        const uint16_t OFFSET_HARDWARE_IO_REGS_END                = 0xFF7F;
        const uint16_t OFFSET_ZERO_PAGE_START                     = 0xFF80;
        const uint16_t OFFSET_ZERO_PAGE_END                       = 0xFFFE;
        const uint16_t OFFSET_INTERRUPT_ENABLE                    = 0xFFFF;
    

    namespace Reserved
    {
        constexpr uint16_t RST_00                                 = 0x0000; // RST calls this address
        constexpr uint16_t RST_08                                 = 0x0008;
        constexpr uint16_t RST_10                                 = 0x0010;
        constexpr uint16_t RST_18                                 = 0x0018;
        constexpr uint16_t RST_20                                 = 0x0020;
        constexpr uint16_t RST_28                                 = 0x0028;
        constexpr uint16_t RST_30                                 = 0x0030;
        constexpr uint16_t RST_38                                 = 0x0038;
        constexpr uint16_t VB_INTERRUPT                           = 0x0040;               // vertical bank interrupt
        constexpr uint16_t LCDC_INTERRUPT                         = 0x0048;             // lcdc status interrupt
        constexpr uint16_t TIMER_INTERRUPT                        = 0x0050;            // timer overflow interrupt
        constexpr uint16_t SERIAL_TRANSFER_INTERRUPT              = 0x0058;  // serial transfer completion interrupt
        constexpr uint16_t HIGH_LOW_P10_P13_INTERRUPT             = 0x0060; // high to low of p10-p13 interrupt

    namespace CartHeader
    {
        constexpr uint16_t OFFSET_NOP_START                       = 0x0100;
        constexpr uint16_t OFFSET_NOP_END                         = 0x0103;
        constexpr uint16_t OFFSET_LOGO_START                      = 0x0104;
        constexpr uint16_t OFFSET_LOGO_END                        = 0x0133;
        constexpr uint16_t OFFSET_PROGRAM_TITLE_START             = 0x0134;
        constexpr uint16_t OFFSET_PROGRAM_TITLE_END               = 0x013E;
        constexpr uint16_t OFFSET_GAME_DESIGNATION_START          = 0x013F;
        constexpr uint16_t OFFSET_GAME_DESIGNATION_END            = 0x0142;
        constexpr uint16_t OFFSET_GB_COLOR_INDICATOR              = 0x0143;
        constexpr uint16_t OFFSET_LICENSEE_CODE_START             = 0x0144;
        constexpr uint16_t OFFSET_LICENSEE_CODE_END               = 0x0145;
        constexpr uint16_t OFFSET_SGB_INDICATOR                   = 0x0146;
        constexpr uint16_t OFFSET_CARTRIDGE_TYPE                  = 0x0147;
        constexpr uint16_t OFFSET_ROM_SIZE                        = 0x0148;
        constexpr uint16_t OFFSET_RAM_SIZE                        = 0x0149;
        constexpr uint16_t OFFSET_DESTINATION_CODE                = 0x014A;
        constexpr uint16_t OFFSET_OLD_LICENSEE_CODE               = 0x014B;
        constexpr uint16_t OFFSET_MASK_ROM_VERSION                = 0x014C;
        constexpr uint16_t OFFSET_COMPLEMENT_CHECK                = 0x014D;
        constexpr uint16_t OFFSET_CHECKSUM_START                  = 0x014E;
    }
    
    namespace Display
    {
        constexpr uint16_t OFFSET_SCROLL_X = 0xFF42;
        constexpr uint16_t OFFSET_SCROLL_Y = 0xFF43;
        constexpr uint16_t OFFSET_LCDC_Y_COORD = 0xFF44;
        constexpr uint16_t OFFSET_LY_COMPARE = 0xFF45;
        constexpr uint16_t OFFSET_WINDOW_Y = 0xFF4A;
        constexpr uint16_t OFFSET_WINDOW_X = 0xFF4B;
        constexpr uint16_t OFFSET_BGP_PALETTE_DATA = 0xFF47; // non-CGB only
        constexpr uint16_t OFFSET_OBJ_PALETTE0_DATA = 0xFF48; // non-CGB only
        constexpr uint16_t OFFSET_OBJ_PALETTE1_DATA = 0xFF48; // non-CGB only
        constexpr uint16_t OFFSET_DMA_TRANSFER = 0xFF46; // dma transfer and start address

    }

    }
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

        void LoadRom(const std::vector<byte>& rom_data);

        static std::shared_ptr<Ram> Instance();

        
    private:
        std::array<byte, 0xFFFF> mMemory;

    };

}

#endif