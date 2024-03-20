#include <boost/test/unit_test.hpp>
#include "Cpu.h"
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "Memory.h"

#define CPU gbc::Cpu::Instance()
using namespace gbc;

struct Expected
{
    Expected()
    {

    }
    register8_t a;
    register8_t b;
    register8_t c;
    register8_t d;
    register8_t e;
    register8_t f;
    register8_t h;
    register8_t l;
    address16_t pc;
    address16_t sp;
    std::array<uint16_t, 0xFFFF> memory = {};
};

void SetInitialParams(boost::property_tree::ptree::value_type& a)
{
    gbc::Ram::Instance()->ClearMem();
    std::cout << a.second.get<std::string>("name") << std::endl;
    std::cout << a.second.get<unsigned short>("initial.pc") << std::endl;
    CPU->PC.Set(a.second.get<unsigned short>("initial.pc"));
    CPU->SP.Set(a.second.get<unsigned short>("initial.sp"));
    CPU->A.Set(a.second.get<unsigned char>("initial.a"));
    CPU->B.Set(a.second.get<unsigned short>("initial.b"));
    CPU->C.Set(a.second.get<unsigned short>("initial.c"));
    CPU->D.Set(a.second.get<unsigned short>("initial.d"));
    CPU->E.Set(a.second.get<unsigned short>("initial.e"));
    CPU->FLAGS.Set(a.second.get<unsigned short>("initial.f"));
    CPU->H.Set(a.second.get<unsigned short>("initial.h"));
    CPU->L.Set(a.second.get<unsigned short>("initial.l"));
    auto e = a.second.get_child("initial.ram");
    for (auto& x : e)
    {
        uint16_t addr = std::stoi(x.second.front().second.data());
        uint8_t val = std::stoi(x.second.back().second.data());
        gbc::Ram::Instance()->WriteByte(addr, val);
    }
    //  std::cout << "ram=" << e << std::endl;

}

void SetExpectedParams(boost::property_tree::ptree::value_type& a, Expected& e)
{
    std::cout << a.second.get<std::string>("name") << std::endl;
    std::cout << a.second.get<unsigned short>("final.pc") << std::endl;
    e.pc.Set(a.second.get<unsigned short>("final.pc"));
    e.sp.Set(a.second.get<unsigned short>("final.sp"));
    e.a.Set(a.second.get<unsigned char>("final.a"));
    e.b.Set(a.second.get<unsigned char>("final.b"));
    e.c.Set(a.second.get<unsigned char>("final.c"));
    e.d.Set(a.second.get<unsigned char>("final.d"));
    e.e.Set(a.second.get<unsigned char>("final.e"));
    e.f.Set(a.second.get<unsigned char>("final.f"));
    e.h.Set(a.second.get<unsigned char>("final.h"));
    e.l.Set(a.second.get<unsigned char>("final.l"));
    auto k = a.second.get_child("final.ram");
    for (auto& x : k)
    {
        uint16_t addr = std::stoi(x.second.front().second.data());
        uint8_t val = std::stoi(x.second.back().second.data());
        e.memory[addr] = val;
      //  for (auto& l : x.second)
       // {
        //    std::cout << "oogabooga=" << l.second.data() << std::endl;
        //}
    }
}

void CheckFinalState(const Expected& e)
{
    BOOST_CHECK_EQUAL(CPU->PC.value() , e.pc.value());
    BOOST_CHECK_EQUAL(CPU->SP.value() , e.sp.value());
    BOOST_CHECK_EQUAL(CPU->A.value() , e.a.value());
    BOOST_CHECK_EQUAL(CPU->B.value() , e.b.value());
    BOOST_CHECK_EQUAL(CPU->C.value() , e.c.value());
    BOOST_CHECK_EQUAL(CPU->D.value() , e.d.value());
    BOOST_CHECK_EQUAL(CPU->E.value() , e.e.value());
    BOOST_CHECK_EQUAL(CPU->FLAGS.value() , e.f.value());
    BOOST_CHECK_EQUAL(CPU->H.value() , e.h.value());
    BOOST_CHECK_EQUAL(CPU->L.value() , e.l.value());
    for (int i = 0; i < 0xFFFF; i++)
        BOOST_CHECK_EQUAL(gbc::Ram::Instance()->ReadByte(i) , e.memory[i]);
}
/*
BOOST_AUTO_TEST_CASE(cpu_instruction_7B)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("/Users/josephmcilvaine/gbc_emulator/tests/v1/7b.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
        CheckFinalState(e);
	}
}

BOOST_AUTO_TEST_CASE(cpu_instruction_78)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("/Users/josephmcilvaine/gbc_emulator/tests/v1/78.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
         CheckFinalState(e);
	}
}

BOOST_AUTO_TEST_CASE(cpu_instruction_79)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("/Users/josephmcilvaine/gbc_emulator/tests/v1/79.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
         CheckFinalState(e);
	}
}

BOOST_AUTO_TEST_CASE(cpu_instruction_87)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("/Users/josephmcilvaine/gbc_emulator/tests/v1/87.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
         CheckFinalState(e);
	}
}

BOOST_AUTO_TEST_CASE(cpu_instruction_97)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("/Users/josephmcilvaine/gbc_emulator/tests/v1/97.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
         CheckFinalState(e);
	}
}

BOOST_AUTO_TEST_CASE(cpu_instruction_8F)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("/Users/josephmcilvaine/gbc_emulator/tests/v1/8f.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
         CheckFinalState(e);
	}
}

BOOST_AUTO_TEST_CASE(cpu_instruction_9F)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("/Users/josephmcilvaine/gbc_emulator/tests/v1/9f.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
         CheckFinalState(e);
	}
}

BOOST_AUTO_TEST_CASE(cpu_instruction_A7)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("/Users/josephmcilvaine/gbc_emulator/tests/v1/a7.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
        CheckFinalState(e);
	}
}

BOOST_AUTO_TEST_CASE(cpu_instruction_B7)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("/Users/josephmcilvaine/gbc_emulator/tests/v1/b7.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
         CheckFinalState(e);
	}
}

BOOST_AUTO_TEST_CASE(cpu_instruction_CB40)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("/Users/josephmcilvaine/gbc_emulator/tests/v1/cb 40.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
        CheckFinalState(e);
	}
}

BOOST_AUTO_TEST_CASE(cpu_instruction_CB10)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("/Users/josephmcilvaine/gbc_emulator/tests/v1/cb 10.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
        CheckFinalState(e);
	}
}
*/
BOOST_AUTO_TEST_CASE(cpu_instruction_CB00)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("/mnt/c/Users/Joe Mcilvaine/gbc_emulator/tests/v1/cb 00.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
        CheckFinalState(e);
	}
}

