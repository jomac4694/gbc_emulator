#include <SFML/Graphics.hpp>
#include <boost/log/trivial.hpp>
#include <fstream>
#include <iostream>
#include <Logger.h>
#include <ctime>
#include "boost/date_time/local_time/local_time.hpp"
#include "Opcode.h"
#include "Cpu.h"
//#include "Cpu.h"

using namespace gbc;
using namespace boost::posix_time;

std::vector<char> LoadRom(const std::string& file_path)
{

    std::ifstream infile(file_path, std::ios_base::binary);

    return std::vector<char>( std::istreambuf_iterator< char>(infile),
                            std::istreambuf_iterator< char>() );
}
/*
void shit()
{

      ptime now = microsec_clock::local_time();
    
    std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
    INIT_LOGGER(new std::ofstream ("test.txt", std::ios_base::ate|std::ios_base::app), true);
    LOG_STREAM << "testing the logger" << LOG_END;
    LOG_STREAM << now << " testing the logger agin" << LOG_END;
    register8_t reg((byte) 0xBA, "A"); 
    BOOST_LOG_TRIVIAL(debug) << "yoooo" << reg;
    reg.SetBit(7);
    BOOST_LOG_TRIVIAL(debug) << "yoooo again " << reg;
    register8_t regb(reg.GetBits(4, 7), "B");
    BOOST_LOG_TRIVIAL(debug) << "yoooo againnn " << regb;

    address16_t ins(0xABCD, "Do something");

    // format of 0xFNNA
    unsigned short expect = 0xC00A;
    unsigned short expect_mask = 0xF00F;
    unsigned short actual_ins = 0xCBBA;
    unsigned short ret = expect_mask & actual_ins;
    register16_t re(ret, "C");
    std::cout << (ret == expect) << std::endl;
    address16_t in(0xF00A, "OPCODE_INSTRUCTION");
  //  gbc::OpcodeCommand cmd = Opcode::opcode_map().at(0xF8);
  //  cmd.Execute(in);
    Cpu::Instance()->A.mValue = 0xAB;
    BOOST_LOG_TRIVIAL(debug) <<  Cpu::Instance()->A;
  //  cmd.Execute(in);
    std::cout << gbc::Utils::Time::NowNano() << std::endl;
    uint64_t tick_rate_nano = 1000000000/CPU_SPEED;
    std::cout << "tick_rate_nano = " << tick_rate_nano << std::endl;
    uint64_t cycles = 0;
    uint64_t next_tick_nano = 0;
    auto start = gbc::Utils::Time::NowNano();
    std::cout << "start= " << start << std::endl;
    while (cycles < CPU_SPEED)
    {
        //uint64_t now = Utils::Time::NowNano();
        if (gbc::Utils::Time::NowNano() >= next_tick_nano)
        {
            cycles++;
            next_tick_nano = gbc::Utils::Time::NowNano() + tick_rate_nano;
        }
    }
    auto end = gbc::Utils::Time::NowNano();
    std::cout << "end= " << (end - start) << std::endl;
}
*/

int main()
{
  
    register8_t reg(0x00, "A");
    BOOST_LOG_TRIVIAL(debug) << reg; 
    reg.SetBit(0);
    BOOST_LOG_TRIVIAL(debug) << reg; 
    reg.ResetBit(0);
    BOOST_LOG_TRIVIAL(debug) << reg; 
    reg.SetBit(2);
    BOOST_LOG_TRIVIAL(debug) << reg; 
    reg.ResetBit(2);
    BOOST_LOG_TRIVIAL(debug) << reg; 
    reg.SetBit(7);
    BOOST_LOG_TRIVIAL(debug) << reg; 
    reg.ResetBit(7);
    BOOST_LOG_TRIVIAL(debug) << reg; 
    reg.ResetBit(7);
    BOOST_LOG_TRIVIAL(debug) << reg; 

    flag_register_t freg(0x00, "Flag Register");
    freg.SetCarryFlag(true);
    BOOST_LOG_TRIVIAL(debug) << freg;

    register32_t reg32(0xABCDFFFF, "Reg 32");
    reg32.ResetBit(31);
    BOOST_LOG_TRIVIAL(debug) << reg32;
    register8_t regb(reg32.GetBits(8, 15), "reg b");
     BOOST_LOG_TRIVIAL(debug) << regb;

    register16_t high(reg32.High(), "high b");
    BOOST_LOG_TRIVIAL(debug) << high;

    register16_t low(reg32.Low(), "low b");
    BOOST_LOG_TRIVIAL(debug) << low;

    regb.mValue = high.High();

    BOOST_LOG_TRIVIAL(debug) << regb;
    BOOST_LOG_TRIVIAL(debug) << (int) regb.NibbleN(0);
    BOOST_LOG_TRIVIAL(debug) << (int) regb.NibbleN(1);
    BOOST_LOG_TRIVIAL(debug) << (int) regb.NibbleN(2);

    regb = 0xFF;
    BOOST_LOG_TRIVIAL(debug) << regb;

    register32_t tst = 0xABCFEF;
    BOOST_LOG_TRIVIAL(debug) << tst;

    register16_t regc = 0x0;
    regc++;
    regc++;
    BOOST_LOG_TRIVIAL(debug) << regc;
    regc--;
    BOOST_LOG_TRIVIAL(debug) << regc;

    Cpu cpu;
    Cpu::Instance()->B.mValue = 0xAB;
    BOOST_LOG_TRIVIAL(debug) << &(Cpu::Instance()->B);
     BOOST_LOG_TRIVIAL(debug) << Cpu::Instance()->B;
    cpu.Execute();
    //cpu.Execute();
    BOOST_LOG_TRIVIAL(debug) << Cpu::Instance()->A;
    Cpu::Instance()->B.mValue = 0xFF;
    cpu.Execute();
    BOOST_LOG_TRIVIAL(debug) << Cpu::Instance()->A;

    Cpu::Instance()->PC.mValue = 0xABCD;
    BOOST_LOG_TRIVIAL(debug) << Cpu::Instance()->PC;

    Cpu::Instance()->A.mValue = 0xA0;
    BOOST_LOG_TRIVIAL(debug) << Cpu::Instance()->A;

    Cpu::Instance()->B.mValue = 0x0B;
    BOOST_LOG_TRIVIAL(debug) << Cpu::Instance()->B;

    Cpu::Instance()->Execute();
    BOOST_LOG_TRIVIAL(debug) << Cpu::Instance()->A;

    reg.mValue = 0x0;
    BOOST_LOG_TRIVIAL(debug) << reg; 
    reg.SetBitLSB(0);
    BOOST_LOG_TRIVIAL(debug) << reg; 
    reg.ResetBitLSB(0);
    BOOST_LOG_TRIVIAL(debug) << reg; 
    reg.SetBitLSB(2);
    BOOST_LOG_TRIVIAL(debug) << reg; 
    reg.ResetBitLSB(2);
    BOOST_LOG_TRIVIAL(debug) << reg; 
    reg.SetBitLSB(7);
    BOOST_LOG_TRIVIAL(debug) << reg; 
    reg.ResetBitLSB(7);
    BOOST_LOG_TRIVIAL(debug) << reg; 
    reg.ResetBitLSB(7);
    BOOST_LOG_TRIVIAL(debug) << reg; 
    
    for (auto const& o : Opcode::Instance()->opcode_map)
    {
        auto e = o.second;
        address16_t t = 0xFFFF;
        e.Execute(t);
    }
/*
   Cpu::Instance()->FLAGS.SetCarryFlag(true);
   Cpu::Instance()->Execute();
      Cpu::Instance()->FLAGS.SetCarryFlag(false);
   Cpu::Instance()->Execute();
      Cpu::Instance()->FLAGS.SetCarryFlag(true);
   Cpu::Instance()->Execute();
      Cpu::Instance()->FLAGS.SetCarryFlag(false);
   Cpu::Instance()->Execute();
*/

    
    //Logger log;
    //log.setStream(&std::cout, false);
    //log << "fdfsf" << 5 << std::endl;

}