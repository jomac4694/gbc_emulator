#include "Memory.h"
#include "Utils.h"
#include "Cpu.h"

namespace gbc
{

    Ram::Ram()
    {
        for (int i = 0; i < mMemory.size(); i ++)
        {
            mMemory[i] = 0x00;
         }
    }

    std::vector<byte> Ram::ReadBytesAt(const uint16_t start_offset, uint16_t n)
    {
        std::vector<byte> ret;
        for (uint16_t i = start_offset; i < start_offset + n; i++)
        {
            ret.push_back(mMemory[i]);
        }

        return ret;
    }

   // Does not increment
    byte Ram::ReadByte(uint16_t address)
    {
        byte ret = mMemory[address];
      //  BOOST_LOG_TRIVIAL(debug) << "Read byte " << register8_t::Hex(ret) << " at " << address;
        return ret;
    }

    // Handles increments
    byte Ram::ReadByte(address16_t address)
    {
        byte ret = mMemory[address.value()];
      //  BOOST_LOG_TRIVIAL(debug) << "Read byte " << register8_t::Hex(ret) << " at " << address.Hex();
        return ret;
    }

    uint16_t Ram::ReadWord(address16_t address)
    {
        uint16_t low = ReadByte(address);
        address.Inc();
        uint16_t high = ReadByte(address);
        return (high << 8) | low;
    }

    void Ram::WriteByte(uint16_t address, register8_t val)
    {
        BOOST_LOG_TRIVIAL(debug) << "Setting address " << address << " to " << val;
        mMemory[address] = val.value();
    }

    void Ram::WriteByte(address16_t address, register8_t val)
    {   
        BOOST_LOG_TRIVIAL(debug) << "Setting address " << address.Hex() << " to " << val.Hex();
        mMemory[address.value()] = val.value();
    }

    void Ram::WriteWord(address16_t address, register16_t value)
    {
        BOOST_LOG_TRIVIAL(debug) << "Writing word " << value.Hex() << " to address " << address.Hex();
        WriteByte(address, register8_t(value.High()));
        address.Inc();
        WriteByte(address, register8_t(value.Low()));
    }

    void Ram::ClearMem()
    {
        for (int i = 0; i < mMemory.size(); i ++)
        {
            mMemory[i] = 0x00;
        }
    }

    uint16_t Ram::ReadWordStack(address16_t address)
    {
        uint16_t low = ReadByte(address);
        address.Inc();
        uint16_t high = ReadByte(address);
        return (high << 8) | low;
    }

    void Ram::WriteWordStack(address16_t address, register16_t value)
    {
        BOOST_LOG_TRIVIAL(debug) << "Writing word " << value.Hex() << " to Stack address " << address.Hex();
        address.Dec();
        WriteByte(address, register8_t(value.High()));
        address.Dec();
        WriteByte(address, register8_t(value.Low()));
    }

    uint8_t* Ram::ReadBytePtr(const uint16_t addr)
    {
        return &mMemory[addr];
    }


    void Ram::LoadRom(const std::vector<byte>& rom_data)
    {
        //std::memcpy(&mMemory[0], &rom_data[0], rom_data.size());
        for (int i = 0; i < rom_data.size(); i++)
            mMemory[i] = rom_data[i];
    }

    std::shared_ptr<Ram> Ram::Instance()
    {
        static std::shared_ptr<Ram> inst = std::make_shared<Ram>(Ram());
        return inst;
    }
}