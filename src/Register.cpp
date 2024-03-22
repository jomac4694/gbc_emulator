#include "Register.h"

        Register::Register() : mValue(0x0)
        {

        }

        Register::Register(T val) : mValue(val)
        {
            
        }

        Register::Register(T val, std::string name) : mValue(val), mName(name)
        {

        }

        virtual void Register::Set(T val)
        {
            BOOST_LOG_TRIVIAL(debug) << "Setting value in Register " << mName << " from " << Hex() << " to " << Hex<T>(val);
            mValue = val;
        }
        
        std::string Register::name() const { return mName;};
        
        T Register::value() const { return mValue; };

        byte Register::bits() const { return sizeof(T)*8;}

        // Get bit at i starting from the LSB
        bool Register::BitAtLSB(byte i) const {return mValue >> i & 0x1;}; //  right-to-left

        // Get bit at i starting from the MSB
        bool Register::BitAtMSB(byte i) const {return mValue >> ((bits() - 1) - i) & 0x1;} // left-to-right

        // Get bits from start to end inclusive
        T Register::GetBits(byte start, byte end)
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
        void Register::SetBit(byte i)
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
        void Register::ResetBit(byte i)
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
        void Register::SetBitLSB(byte i)
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

        void Register::SetBitLSB(byte i, bool bit)
        {
             bit ? SetBitLSB(i) : ResetBitLSB(i); 
        }

        // Reset bit at i starting from LSB
        void Register::ResetBitLSB(byte i)
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

        void Register::Dec()
        {
            Set(mValue - 1);
        }

        void Register::Inc()
        {
            Set(mValue + 1);
        }

        // Get High bits for the given type (ex. int is 32 bits so take high 32/2 = 16 bits)
        T Register::High()
        {
            int half = bits() / 2;
            T ret = mValue >> half;
            return ret;
        }

        // Get Lower bits for the given type (ex. int is 32 bits so take lower 32/2 = 16 bits)
        T Register::Low()
        {
            int half = bits() / 2;
            T ret = mValue & ((T) 0xFFFFFFFFFFFFFFFF >> half);
            return ret;
        }

        // Get the Nth nibble (4 bits), 0-indexed left-to-right
        byte Register::NibbleN(byte n)
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
        T Register::GetNibbles(byte start, byte end)
        {
            return GetBits(start*4, (end*4 + 3));
        }

        std::string Register::Hex() const
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
        static std::string Register::Hex(U value)
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