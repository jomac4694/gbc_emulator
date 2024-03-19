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
        return ret;
    }

    // Handles increments
    byte Ram::ReadByte(address16_t address)
    {
        byte ret = mMemory[address.value()];
        return ret;
    }

    uint16_t Ram::ReadWord(address16_t address)
    {
        uint16_t ret = ReadByte(address);
        address++;
        ret = ret << 8;
        uint16_t next = ReadByte(address);
        return ret | next;
    }

    void Ram::WriteByte(uint16_t address, register8_t val)
    {
        mMemory[address] = val.value();
    }

    void Ram::WriteByte(address16_t address, register8_t val)
    {
        mMemory[address.value()] = val.value();
    }

    void Ram::WriteWord(address16_t address, register16_t value)
    {
        WriteByte(address, register8_t(value.High()));
        address++;
        WriteByte(address, register8_t(value.Low()));
    }

    std::shared_ptr<Ram> Ram::Instance()
    {
        static std::shared_ptr<Ram> inst = std::make_shared<Ram>(Ram());
        return inst;
    }
}