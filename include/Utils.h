#ifndef UTILS_H
#define UTILS_H

#include <chrono>

namespace gbc
{
typedef unsigned char byte;

namespace Utils
{

struct Time
{
    Time()
    {

    }

    static uint64_t NowMilli();

    static uint64_t NowNano();

};

}
} 
#endif