#ifndef UTILS_H
#define UTILS_H

#include <chrono>

namespace gbc
{
typedef unsigned char byte;
namespace Utils
{
namespace Time
{
    uint64_t NowMilli()
    {
        using namespace std::chrono;
        return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    }

    uint64_t NowNano()
    {
        using namespace std::chrono;
        return duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();
    }

}

}
} 
#endif