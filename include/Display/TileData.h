#ifndef TILEDATA_H
#define TILEDATA_H
#include "Register.h"

namespace gbc
{



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