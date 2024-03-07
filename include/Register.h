#ifndef REGISTER_H
#define REGISTER_H
#include "Utils.h"
#include <iostream>
#include <boost/log/trivial.hpp>

namespace gbc
{

template<class T>
class Register 
{
    public:
        T mValue;

        Register(T val) : mValue(val)
        {

        }

        Register(T val, std::string name) : mValue(val), mName(name)
        {

        }
        std::string name() const { return mName;};
        
        T value() const { return mValue; };

        byte bits() const { return sizeof(T)*8;}

        // Get bit at i starting from the LSB
        bool BitAtLSB(byte i) const {return mValue >> i & 0x1;}; //  right-to-left

        // Get bit at i starting from the MSB
        bool BitAtMSB(byte i) const {return mValue >> ((bits() - 1) - i) & 0x1;} // left-to-right

        // Get bits from start to end inclusive
        T GetBits(byte start, byte end)
        {
            T ret = 0;
            for (int i = start; i <= end; i++)
            {
                ret |= BitAtMSB(i);
                if (i != end)
                    ret = ret << 1;
            }
            return ret;
        }

        // Set bit at i starting from MSB
        void SetBit(byte i)
        {
            if (BitAtMSB(i))
                return;
            else
            {
                BOOST_LOG_TRIVIAL(debug) << "Set bit " << (int) i << " in Register " << mName;
                mValue = mValue | (0x0000000000000001 << (bits() - i - 1));
            }
        }

        // Reset bit at i starting from MSB
        void ResetBit(byte i)
        {
            if (!BitAtMSB(i))
                return;
            else
            {
                BOOST_LOG_TRIVIAL(debug) << "Reset bit " << (int) i << " in Register " << mName;
                mValue = mValue ^ (0x0000000000000001 << (bits() - i - 1)); 
            }

        }

        // Get High bits for the given type (ex. int is 32 bits so take high 32/2 = 16 bits)
        T High()
        {
            int half = bits() / 2;
            T ret = mValue >> half;
            return ret;
        }

        // Get Lower bits for the given type (ex. int is 32 bits so take lower 32/2 = 16 bits)
        T Low()
        {
            int half = bits() / 2;
            T ret = mValue & ((T) 0xFFFFFFFFFFFFFFFF >> half);
            return ret;
        }

        // Get the Nth nibble (4 bits), 0-indexed
        byte NibbleN(byte n)
        {
            byte start = n*4;
            if (start + 3 > bits())
            {
                BOOST_LOG_TRIVIAL(debug) << "Nibble " << n << " is greater than the number bits";
                return 0;
            }
            return GetBits(start, start + 3);

        }

        // get nibbles (4 bits) start-end, inclusive
        T GetNibbles(byte start, byte end)
        {
            return GetBits(start*4, (end*4 + 3));
        }

        inline friend std::ostream &operator << (std::ostream &out, const Register<T>& reg)
        {
            out << "Register " << reg.name() << " = ";
            for (int i = 0; i < reg.bits() ; i++)
                out << (uint64_t) reg.BitAtMSB(i) << " ";
            return out;
        }

        template<typename U>
        void operator=(const Register<U>& rhs)
        {
            mValue = static_cast<T>(rhs.mValue);
        }

        template<typename U>
        void operator=(const U& rhs)
        {
            mValue = static_cast<T>(rhs);
        }

        Register<T> operator++(int)
        {
            Register<T> temp = *this;
            mValue++;
            return temp;
        }

        Register<T> operator--(int)
        {
            Register<T> temp = *this;
            mValue--;
            return temp;
        }

        Register<T>& operator--()
        {
            mValue--;
            return *this;
        }

    protected:
        std::string mName;
};


// Specialization for flag register
struct flag_register_t : Register<byte>
{
    flag_register_t(byte val, std::string name) : Register(val, name)
    {

    } 

    void SetZeroFlag(bool bit) { bit ? SetBit(0) : ResetBit(0); }
    bool ZeroFlag() { return BitAtMSB(0); }

    void SetSubtractFlag(bool bit) { bit ? SetBit(1) : ResetBit(1); }
    bool SubtractFlag() { return BitAtMSB(1); }

    void SetHalfCarryFlag(bool bit) { bit ? SetBit(2) : ResetBit(2); }
    bool HalfCarryFlag() { return BitAtMSB(2); }

    void SetCarryFlag(bool bit) { bit ? SetBit(3) : ResetBit(3); }
    bool CarryFlag() { return BitAtMSB(3); }

    
};

typedef Register<byte> register8_t;
typedef Register<uint16_t> register16_t;
typedef Register<uint32_t> register32_t;
typedef Register<uint16_t> address16_t;

}
#endif