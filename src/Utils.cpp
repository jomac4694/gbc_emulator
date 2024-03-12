#include "Utils.h"

namespace gbc
{

namespace Utils
{

    uint64_t Time::NowMilli()
    {
        using namespace std::chrono;
        return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    }

    uint64_t Time::NowNano()
    {
        using namespace std::chrono;
        return duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();
    }

}
} 