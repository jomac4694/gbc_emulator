#ifndef DISPLAYBUFFER_H
#define DISPLAYBUFFER_H

#include "Register.h"
namespace gbc
{
uint16_t CoordsAsIndex(uint32_t x, uint32_t y, uint32_t row_width, uint32_t row_height);
class DisplayBuffer
{
    
    public:
        DisplayBuffer(uint32_t width, uint32_t height);
        void SetPixel(uint32_t x, uint32_t y, byte pixel);
        byte GetPixel(uint32_t x, uint32_t y) const;
        void Clear();

    private:
        uint32_t mHeight;
        uint32_t mWidth;
        std::vector<byte> buffer;
    
};
}
#endif