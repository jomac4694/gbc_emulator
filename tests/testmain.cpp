#include "Cpu.h"
#include <cassert>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "Memory.h"
#define CPU gbc::Cpu::Instance()
using namespace gbc;

struct Expected
{
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
    std::array<uint16_t, 0xFFFF> memory;
};

void SetInitialParams(boost::property_tree::ptree::value_type& a)
{
    std::cout << a.second.get<std::string>("name") << std::endl;
    std::cout << a.second.get<unsigned short>("initial.pc") << std::endl;
    CPU->PC.Set(a.second.get<unsigned short>("initial.pc"));
    CPU->SP.Set(a.second.get<unsigned short>("initial.sp"));
    CPU->A.Set(a.second.get<unsigned char>("initial.a"));
    CPU->B.Set(a.second.get<unsigned short>("initial.b"));
    CPU->C.Set(a.second.get<unsigned short>("initial.c"));
    CPU->D.Set(a.second.get<unsigned short>("initial.d"));
    CPU->E.Set(a.second.get<unsigned short>("initial.e"));
    CPU->F.Set(a.second.get<unsigned short>("initial.f"));
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
int main(int argc, char *argv[])
{
    try
    {
        std::string ss = "/Users/josephmcilvaine/gbc_emulator/tests/v1/7f.json";
        // send your JSON above to the parser below, but populate ss first


        boost::property_tree::ptree pt;
        boost::property_tree::read_json(ss, pt);

        for (auto& a : pt)
        {
            Expected e;
        
            SetInitialParams(a);
            SetExpectedParams(a, e);


        }

        return EXIT_SUCCESS;
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return EXIT_FAILURE;
}
