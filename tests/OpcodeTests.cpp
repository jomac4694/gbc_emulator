#include <boost/test/unit_test.hpp>
#include "Cpu.h"
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "Memory.h"
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#define CPU gbc::Cpu::Instance()
using namespace gbc;

void initlog()
{
			boost::log::core::get()->set_filter
    (
        boost::log::trivial::severity >= boost::log::trivial::error
    );
}
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
	initlog();
   // gbc::Ram::Instance()->ClearMem();
   // std::cout << a.second.get<std::string>("name") << std::endl;
   // std::cout << a.second.get<unsigned short>("initial.pc") << std::endl;
    CPU->PC->Set(a.second.get<unsigned short>("initial.pc"));
    CPU->SP->Set(a.second.get<unsigned short>("initial.sp"));
    CPU->A->Set(a.second.get<unsigned char>("initial.a"));
    CPU->B->Set(a.second.get<unsigned short>("initial.b"));
    CPU->C->Set(a.second.get<unsigned short>("initial.c"));
    CPU->D->Set(a.second.get<unsigned short>("initial.d"));
    CPU->E->Set(a.second.get<unsigned short>("initial.e"));
    CPU->FLAGS->Set(a.second.get<unsigned char>("initial.f"));
    CPU->H->Set(a.second.get<unsigned short>("initial.h"));
    CPU->L->Set(a.second.get<unsigned short>("initial.l"));
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
    //std::cout << a.second.get<std::string>("name") << std::endl;

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
    }
}

void CheckFinalState(const Expected& e, const boost::property_tree::ptree::value_type& a)
{
    BOOST_CHECK_EQUAL(CPU->PC->value() , e.pc.value());
    BOOST_CHECK_EQUAL(CPU->SP->value() , e.sp.value());
    BOOST_CHECK_EQUAL(CPU->A->value() , e.a.value());
    BOOST_CHECK_EQUAL(CPU->B->value() , e.b.value());
    BOOST_CHECK_EQUAL(CPU->C->value() , e.c.value());
    BOOST_CHECK_EQUAL(CPU->D->value() , e.d.value());
    BOOST_CHECK_EQUAL(CPU->E->value() , e.e.value());
    BOOST_CHECK_EQUAL(CPU->FLAGS->value() , e.f.value());
    BOOST_CHECK_EQUAL(CPU->H->value() , e.h.value());
    BOOST_CHECK_EQUAL(CPU->L->value() , e.l.value());
	auto k = a.second.get_child("final.ram");
    for (auto& x : k)
    {
        uint16_t addr = std::stoi(x.second.front().second.data());
        uint8_t val = std::stoi(x.second.back().second.data());
		BOOST_LOG_TRIVIAL(debug) << "checking address " << addr << std::endl;
		BOOST_CHECK_EQUAL(e.memory[addr], gbc::Ram::Instance()->ReadByte(addr));
    }
}

BOOST_AUTO_TEST_CASE(cpu_instruction_00)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/00.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_01)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/01.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_02)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/02.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_03)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/03.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_04)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/04.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_05)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/05.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_06)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/06.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_07)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/07.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_08)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/08.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_09)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/09.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_0A)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/0a.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_0B)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/0b.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_0C)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/0c.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_0D)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/0d.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_0E)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/0e.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_0F)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/0f.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_10)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/10.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_11)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/11.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_12)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/12.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_13)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/13.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_14)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/14.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_15)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/15.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_16)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/16.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_17)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/17.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_18)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/18.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_19)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/19.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_1A)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/1a.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_1B)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/1b.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_1C)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/1c.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_1D)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/1d.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_1E)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/1e.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_1F)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/1f.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_20)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/20.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_21)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/21.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_22)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/22.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_23)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/23.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_24)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/24.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_25)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/25.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_26)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/26.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_27)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/27.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_28)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/28.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_29)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/29.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_2A)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/2a.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_2B)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/2b.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_2C)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/2c.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_2D)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/2d.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_2E)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/2e.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_2F)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/2f.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_30)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/30.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_31)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/31.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_32)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/32.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_33)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/33.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_34)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/34.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_35)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/35.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_36)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/36.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_37)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/37.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_38)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/38.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_39)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/39.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_3A)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/3a.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_3B)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/3b.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_3C)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/3c.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_3D)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/3d.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_3E)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/3e.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_3F)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/3f.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_40)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/40.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_41)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/41.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_42)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/42.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_43)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/43.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_44)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/44.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_45)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/45.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_46)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/46.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_47)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/47.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_48)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/48.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_49)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/49.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_4A)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/4a.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_4B)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/4b.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_4C)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/4c.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_4D)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/4d.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_4E)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/4e.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_4F)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/4f.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_50)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/50.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_51)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/51.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_52)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/52.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_53)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/53.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_54)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/54.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_55)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/55.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_56)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/56.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_57)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/57.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_58)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/58.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_59)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/59.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_5A)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/5a.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_5B)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/5b.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_5C)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/5c.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_5D)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/5d.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_5E)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/5e.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_5F)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/5f.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_60)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/60.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_61)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/61.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_62)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/62.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_63)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/63.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_64)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/64.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_65)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/65.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_66)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/66.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_67)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/67.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_68)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/68.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_69)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/69.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_6A)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/6a.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_6B)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/6b.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_6C)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/6c.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_6D)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/6d.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_6E)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/6e.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_6F)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/6f.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_70)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/70.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_71)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/71.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_72)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/72.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_73)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/73.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_74)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/74.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_75)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/75.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_76)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/76.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_77)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/77.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_78)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/78.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_79)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/79.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_7A)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/7a.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_7B)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/7b.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_7C)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/7c.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_7D)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/7d.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_7E)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/7e.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_7F)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/7f.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_80)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/80.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_81)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/81.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_82)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/82.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_83)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/83.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_84)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/84.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_85)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/85.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_86)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/86.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_87)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/87.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_88)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/88.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_89)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/89.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_8A)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/8a.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_8B)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/8b.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_8C)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/8c.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_8D)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/8d.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_8E)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/8e.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_8F)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/8f.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_90)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/90.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_91)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/91.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_92)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/92.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_93)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/93.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_94)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/94.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_95)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/95.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_96)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/96.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_97)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/97.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_98)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/98.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_99)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/99.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_9A)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/9a.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_9B)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/9b.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_9C)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/9c.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_9D)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/9d.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_9E)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/9e.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_9F)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/9f.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_A0)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/a0.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_A1)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/a1.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_A2)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/a2.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_A3)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/a3.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_A4)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/a4.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_A5)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/a5.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_A6)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/a6.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_A7)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/a7.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_A8)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/a8.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_A9)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/a9.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_AA)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/aa.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_AB)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/ab.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_AC)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/ac.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_AD)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/ad.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_AE)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/ae.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_AF)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/af.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_B0)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/b0.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_B1)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/b1.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_B2)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/b2.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_B3)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/b3.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_B4)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/b4.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_B5)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/b5.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_B6)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/b6.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_B7)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/b7.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_B8)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/b8.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_B9)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/b9.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_BA)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/ba.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_BB)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/bb.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_BC)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/bc.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_BD)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/bd.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_BE)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/be.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_BF)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/bf.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_C0)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/c0.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_C1)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/c1.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_C2)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/c2.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_C3)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/c3.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_C4)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/c4.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_C5)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/c5.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_C6)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/c6.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_C7)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/c7.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_C8)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/c8.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_C9)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/c9.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CA)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/ca.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CC)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cc.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CD)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cd.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CE)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/ce.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CF)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cf.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_D0)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/d0.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_D1)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/d1.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_D2)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/d2.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_D4)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/d4.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_D5)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/d5.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_D6)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/d6.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_D7)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/d7.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_D8)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/d8.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_D9)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/d9.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_DA)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/da.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_DC)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/dc.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_DE)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/de.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_DF)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/df.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_E0)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/e0.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_E1)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/e1.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_E2)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/e2.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_E5)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/e5.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_E6)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/e6.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_E7)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/e7.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_E8)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/e8.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_E9)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/e9.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_EA)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/ea.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_EE)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/ee.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_EF)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/ef.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_F0)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/f0.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_F1)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/f1.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_F2)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/f2.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_F3)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/f3.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_F5)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/f5.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_F6)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/f6.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_F7)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/f7.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_F8)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/f8.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_F9)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/f9.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_FA)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/fa.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_FB)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/fb.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_FE)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/fe.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_FF)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/ff.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB00)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 00.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB01)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 01.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB02)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 02.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB03)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 03.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB04)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 04.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB05)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 05.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB06)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 06.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB07)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 07.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB08)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 08.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB09)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 09.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB0A)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 0a.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB0B)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 0b.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB0C)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 0c.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB0D)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 0d.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB0E)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 0e.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB0F)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 0f.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB10)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 10.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB11)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 11.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB12)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 12.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB13)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 13.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB14)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 14.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB15)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 15.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB16)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 16.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB17)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 17.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB18)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 18.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB19)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 19.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB1A)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 1a.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB1B)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 1b.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB1C)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 1c.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB1D)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 1d.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB1E)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 1e.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB1F)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 1f.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB20)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 20.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB21)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 21.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB22)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 22.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB23)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 23.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB24)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 24.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB25)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 25.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB26)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 26.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB27)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 27.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB28)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 28.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB29)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 29.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB2A)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 2a.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB2B)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 2b.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB2C)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 2c.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB2D)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 2d.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB2E)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 2e.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB2F)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 2f.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB30)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 30.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB31)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 31.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB32)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 32.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB33)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 33.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB34)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 34.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB35)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 35.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB36)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 36.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB37)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 37.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB38)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 38.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB39)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 39.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB3A)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 3a.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB3B)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 3b.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB3C)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 3c.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB3D)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 3d.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB3E)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 3e.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB3F)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 3f.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB40)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 40.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB41)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 41.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB42)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 42.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB43)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 43.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB44)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 44.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB45)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 45.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB46)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 46.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB47)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 47.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB48)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 48.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB49)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 49.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB4A)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 4a.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB4B)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 4b.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB4C)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 4c.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB4D)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 4d.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB4E)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 4e.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB4F)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 4f.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB50)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 50.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB51)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 51.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB52)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 52.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB53)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 53.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB54)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 54.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB55)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 55.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB56)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 56.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB57)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 57.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB58)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 58.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB59)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 59.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB5A)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 5a.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB5B)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 5b.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB5C)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 5c.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB5D)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 5d.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB5E)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 5e.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB5F)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 5f.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB60)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 60.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB61)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 61.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB62)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 62.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB63)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 63.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB64)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 64.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB65)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 65.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB66)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 66.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB67)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 67.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB68)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 68.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB69)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 69.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB6A)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 6a.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB6B)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 6b.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB6C)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 6c.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB6D)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 6d.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB6E)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 6e.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB6F)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 6f.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB70)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 70.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB71)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 71.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB72)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 72.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB73)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 73.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB74)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 74.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB75)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 75.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB76)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 76.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB77)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 77.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB78)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 78.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB79)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 79.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB7A)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 7a.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB7B)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 7b.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB7C)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 7c.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB7D)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 7d.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB7E)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 7e.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB7F)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 7f.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB80)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 80.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB81)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 81.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB82)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 82.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB83)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 83.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB84)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 84.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB85)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 85.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB86)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 86.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB87)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 87.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB88)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 88.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB89)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 89.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB8A)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 8a.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB8B)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 8b.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB8C)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 8c.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB8D)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 8d.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB8E)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 8e.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB8F)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 8f.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB90)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 90.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB91)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 91.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB92)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 92.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB93)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 93.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB94)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 94.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB95)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 95.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB96)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 96.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB97)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 97.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB98)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 98.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB99)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 99.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB9A)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 9a.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB9B)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 9b.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB9C)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 9c.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB9D)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 9d.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB9E)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 9e.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CB9F)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb 9f.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBA0)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb a0.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBA1)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb a1.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBA2)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb a2.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBA3)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb a3.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBA4)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb a4.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBA5)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb a5.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBA6)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb a6.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBA7)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb a7.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBA8)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb a8.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBA9)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb a9.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBAA)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb aa.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBAB)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb ab.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBAC)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb ac.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBAD)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb ad.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBAE)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb ae.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBAF)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb af.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBB0)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb b0.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBB1)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb b1.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBB2)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb b2.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBB3)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb b3.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBB4)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb b4.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBB5)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb b5.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBB6)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb b6.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBB7)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb b7.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBB8)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb b8.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBB9)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb b9.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBBA)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb ba.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBBB)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb bb.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBBC)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb bc.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBBD)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb bd.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBBE)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb be.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBBF)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb bf.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBC0)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb c0.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBC1)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb c1.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBC2)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb c2.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBC3)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb c3.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBC4)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb c4.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBC5)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb c5.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBC6)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb c6.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBC7)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb c7.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBC8)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb c8.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBC9)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb c9.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBCA)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb ca.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBCB)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb cb.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBCC)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb cc.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBCD)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb cd.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBCE)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb ce.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBCF)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb cf.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBD0)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb d0.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBD1)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb d1.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBD2)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb d2.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBD3)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb d3.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBD4)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb d4.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBD5)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb d5.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBD6)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb d6.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBD7)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb d7.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBD8)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb d8.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBD9)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb d9.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBDA)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb da.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBDB)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb db.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBDC)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb dc.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBDD)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb dd.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBDE)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb de.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBDF)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb df.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBE0)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb e0.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBE1)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb e1.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBE2)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb e2.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBE3)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb e3.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBE4)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb e4.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBE5)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb e5.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBE6)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb e6.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBE7)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb e7.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBE8)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb e8.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBE9)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb e9.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBEA)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb ea.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBEB)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb eb.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBEC)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb ec.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBED)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb ed.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBEE)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb ee.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBEF)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb ef.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBF0)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb f0.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBF1)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb f1.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBF2)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb f2.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBF3)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb f3.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBF4)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb f4.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBF5)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb f5.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBF6)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb f6.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBF7)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb f7.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBF8)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb f8.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBF9)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb f9.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBFA)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb fa.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBFB)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb fb.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBFC)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb fc.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBFD)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb fd.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBFE)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb fe.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}
BOOST_AUTO_TEST_CASE(cpu_instruction_CBFF)
{
	boost::property_tree::ptree pt;
	boost::property_tree::read_json("../tests/v1/cb ff.json", pt);
	for(auto& a : pt)
	{
		Expected e;
		SetInitialParams(a);
		SetExpectedParams(a, e);
		CPU->Execute();
		CheckFinalState(e, a);
	}
}

