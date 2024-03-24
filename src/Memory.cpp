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
;        }
    }

   // Does not increment
    byte Ram::ReadByte(uint16_t address)
    {
        byte ret = mMemory[address];
        BOOST_LOG_TRIVIAL(debug) << "Read byte " << register8_t::Hex(ret) << " at " << address;
        return ret;
    }

    // Handles increments
    byte Ram::ReadByte(address16_t address)
    {
        byte ret = mMemory[address.value()];
        BOOST_LOG_TRIVIAL(debug) << "Read byte " << register8_t::Hex(ret) << " at " << address.Hex();
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
;       }
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

    void Ram::LoadRom(const std::vector<byte>& rom_data)
    {
        for (int i = 0; i < rom_data.size(); i++)
            mMemory[i] = rom_data[i];
        for (int i = 0x8000; i < 0xFFFF; i++)
        {
            register8_t val = mMemory[(i + 0x150) - 0x8000];
            register16_t addr = i;
            BOOST_LOG_TRIVIAL(debug) << " setting addr " << addr << " to " << val; 
            mMemory[i] = mMemory[(i + 0x150) - 0x8000];
        }
    }

    std::shared_ptr<Ram> Ram::Instance()
    {
        static std::shared_ptr<Ram> inst = std::make_shared<Ram>(Ram());
        return inst;
    }
}