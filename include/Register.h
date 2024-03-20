#ifndef REGISTER_H
#define REGISTER_H
#include "Utils.h"
#include <iostream>
#include <boost/log/trivial.hpp>
#include <iomanip>
#include <sstream>
#include <map>
namespace gbc
{

template<class T>
class Register 
{
    public:
        T mValue;

        Register() : mValue(0x0)
        {

        }
        Register(T val) : mValue(val)
        {
            
        }

        Register(T val, std::string name) : mValue(val), mName(name)
        {

        }

        void Set(T val)
        {
            BOOST_LOG_TRIVIAL(debug) << "Setting value in Register " << mName << " from " << Hex() << " to " << Hex<T>(val);
            mValue = val;
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
                BOOST_LOG_TRIVIAL(debug) << "Set bit " << ((mBitNameMap.find(i) == mBitNameMap.end()) ? std::to_string(i) : mBitNameMap[i]) << " in Register " << mName;
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

        // Set bit at i starting from LSB
        void SetBitLSB(byte i)
        {
            if (BitAtLSB(i))
            {
                BOOST_LOG_TRIVIAL(debug) << "NOT Setting bit " << ((mBitNameMap.find(i) == mBitNameMap.end()) ? std::to_string(i) : mBitNameMap[i]) << " in Register " << mName;
                return;
            }
            else
            {
                BOOST_LOG_TRIVIAL(debug) << "Set bit " << ((mBitNameMap.find(i) == mBitNameMap.end()) ? std::to_string(i) : mBitNameMap[i]) << " in Register " << mName;
                mValue = mValue | (0x0000000000000001 << i);
            }
        }

        void SetBitLSB(byte i, bool bit)
        {
             bit ? SetBitLSB(i) : ResetBitLSB(i); 
        }

        // Reset bit at i starting from LSB
        void ResetBitLSB(byte i)
        {
            if (!BitAtLSB(i))
            {
                BOOST_LOG_TRIVIAL(debug) << "NOT Resetting bit " << ((mBitNameMap.find(i) == mBitNameMap.end()) ? std::to_string(i) : mBitNameMap[i]) << " in Register " << mName;
                return;
            }
            else
            {
                BOOST_LOG_TRIVIAL(debug) << "Reset bit " << ((mBitNameMap.find(i) == mBitNameMap.end()) ? std::to_string(i) : mBitNameMap[i]) << " in Register " << mName;
                mValue = mValue ^ (0x0000000000000001 << i); 
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

        // Get the Nth nibble (4 bits), 0-indexed left-to-right
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

        std::string Hex() const
        {
            std::stringstream ss;
            ss << std::uppercase << std::hex << "0x";

            for (int i = sizeof(T) - 1; i >= 0; i--)
            {
                ss << std::setw(2) << std::setfill('0') << (int) ((mValue >> i*8) & 0xFF);
            }

            return ss.str();
        }

        template<typename U>
        static std::string Hex(U value)
        {
            std::stringstream ss;
            ss << std::uppercase << std::hex << "0x";

            for (int i = sizeof(U) - 1; i >= 0; i--)
            {
                ss << std::setw(2) << std::setfill('0') << (int) ((value >> i*8) & 0xFF);
            }

            return ss.str();
        }

        void AssignBitName(int32_t bit, const std::string& name)
        {
            if (bit > bits())
            {
                BOOST_LOG_TRIVIAL(debug) << "Failed to assign bit name to bit " << bit;
                BOOST_LOG_TRIVIAL(debug) << *this;
                return;
            }

            mBitNameMap.insert({bit, name});
        }
        
        inline friend std::ostream &operator << (std::ostream &out, const Register<T>& reg)
        {
            out << "Register " << reg.name() << " Binary: ";
            for (int i = 0; i < reg.bits() ; i++)
                out << (uint64_t) reg.BitAtMSB(i) << " ";
            out << "Hex: " << reg.Hex();
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
        std::map<int32_t, std::string> mBitNameMap;
};

typedef Register<byte> register8_t;
typedef Register<uint16_t> register16_t;
typedef Register<uint32_t> register32_t;
typedef Register<uint16_t> address16_t;

struct Register16
{
    public:

        Register16(register8_t* high, register8_t* low) :
            mHigh(high),
            mLow(low)
            {

            }
        void Set(uint16_t val)
        { 
            register16_t tmp(val);
            mHigh->Set(tmp.High());
            mLow->Set(tmp.Low());
        }

        uint16_t value()
        {
            return (mHigh->value() << 8) | mLow->value();
        }

    private:
        register8_t* mHigh;
        register8_t* mLow;
};


// Specialization for flag register
struct flag_register_t : Register<byte>
{
    flag_register_t(byte val, std::string name) : Register(val, name)
    {
        AssignBitName(7, "ZeroFlag");
        AssignBitName(6, "SubtractFlag");
        AssignBitName(5, "HalfCarryFlag");
        AssignBitName(4, "CarryFlag");
    } 

    void SetZeroFlag(bool bit) { bit ? SetBitLSB(7) : ResetBitLSB(7); }
    bool ZeroFlag() { return BitAtLSB(7); }

    void SetSubtractFlag(bool bit) { bit ? SetBitLSB(6) : ResetBitLSB(6); }
    bool SubtractFlag() { return BitAtLSB(6); }

    void SetHalfCarryFlag(bool bit) { bit ? SetBitLSB(5) : ResetBitLSB(5); }
    bool HalfCarryFlag() { return BitAtLSB(5); }

    void SetCarryFlag(bool bit) { bit ? SetBitLSB(4) : ResetBitLSB(4); }
    bool CarryFlag() { return BitAtLSB(4); }

    
};



}
#endif