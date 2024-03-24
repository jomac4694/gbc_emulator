#ifndef TILEDATA_H
#define TILEDATA_H
#include "Register.h"
#include "Memory.h"

namespace gbc
{

    // this is really just a 32x32 area in memory where the "TileNumber" for each tile is stored
    // The tile number is effectively an index into the Tile Data Map (the tile data map contains color info for each pixel in the 8x8 tile)
    // Ultimately the tile data is used to render the tiles for both the background and window grids
    struct BackgroundMap
    {
        BackgroundMap();
        int ROW_WIDTH = 32;
        byte GetTileNumberAt(byte x, byte y)
        {
            // 1, 0
            // need to get 32

            // start_offset + x * ROW_WIDTH + y
            

        }
        byte GetTileNumberAt(byte offset); // just start_offset + offset

    }

    struct DisplayLayerBuffer
    {

    }

    void UpdateBuffers()
    {
        // maybe a basic loop will look like...
        // for all tiles (32x32)
        // get Tile Number from BackgroundMap
        // Get tile_data[tile_number] 
        // draw the tile into the buffer?? idrk
    }

    // there are 2 methods for this but just for now lets use "8000" method
    std::array<byte, 16> ReadTileDataBlock(byte tile_number)
    {
        std::array<byte, 16> ret;
        uint16_t start_offset = gbc::MemoryMap::OFFSET_CHARACTER_RAM_START + (tile_number * 16);

        for (uint16_t i = start_offset; i < start_offset + 16; i++)
        {
            ret[i] = gbc::Ram::Instance()->ReadByte(i);
        }
        return ret;
    }

    struct TileData
    {

        TileData(std::array<byte, 16> buffer) 
            : mBuffer(buffer)
        {

        }

        std::array<byte, 16> mBuffer;

        // this should return a 64 byte pixel map, where each represents a pixel/color in a tile
        std::vector<uint8_t> AsPixelMap()
        {
            std::vector<uint8_t> ret;
            for (int i = 0; i < mBuffer.size(); i+=2)
            {
                register8_t first = mBuffer[i];
                register8_t second = mBuffer[i + 1];
                for (int i = 0; i < 8; i++)
                {
                    uint8_t first_bit = first.BitAtMSB(i);
                    uint8_t second_bit = second.BitAtMSB(i);
                    ret.push_back((second_bit << 1) | first_bit);s
                }

            }
        }
    }

    struct Tile
    {
        static const uint8_t TILE_WIDTH = 8;
        static const uint8_t TILE_HEIGHT = 8;
        byte color1;
        byte color2;
        byte color3;
        byte color4;
        
    };
}

#endif