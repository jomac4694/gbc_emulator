#include "DisplayBuffer.h"

namespace gbc
{
    uint16_t CoordsAsIndex(uint32_t x, uint32_t y, uint32_t row_width, uint32_t row_height)
    {
    if (x > row_width)
        std::runtime_error("X exceeds row width");
    else if (y > row_height)
        std::runtime_error("Y exceeds row height");

    return y * row_width + x;
    }

    DisplayBuffer::DisplayBuffer(uint32_t width, uint32_t height) :
        mWidth(width),
        mHeight(height),
        buffer(width*height, 0x0)
    {

    }

    void DisplayBuffer::SetPixel(uint32_t x, uint32_t y, byte pixel)
    {
        buffer[CoordsAsIndex(x, y, mWidth, mHeight)] = pixel;
    }

    byte DisplayBuffer::GetPixel(uint32_t x, uint32_t y) const
    {
        return buffer[CoordsAsIndex(x, y, mWidth, mHeight)];
    }

    void DisplayBuffer::Clear()
    {
        for (int i = 0; i < mHeight*mWidth; i++)
            buffer[i] = 0x0;
    }

}