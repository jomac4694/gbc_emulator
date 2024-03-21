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
	//initlog();
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
/*
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

BOOST_AUTO_TEST_CASE(test_register_shit)
{
	CPU->FLAGS->Set(0xAECD);
	CPU->AF->Set(0xABCD);
	//BOOST_LOG_TRIVIAL(debug) << cpu.FLAGS->value();
}
*/
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