#ifndef PPU_H
#define PPU_H
#include <array>
#include "Register.h"

// this probably going to be a temporary monolith of all the ppu functionality
namespace gbc
{
// Dimnensions of a Tile
constexpr static uint16_t TILE_WIDTH = 8;
constexpr static uint16_t TILE_HEIGHT = 8;

// Dimensions of GB Display Layer (Background and Window)
constexpr static uint16_t DISPLAY_LAYER_WIDTH = 256;
constexpr static uint16_t DISPLAY_LAYER_HEIGHT = 256;

// Dimensions of a Sprite/Obj
constexpr static uint16_t SPRITE_WIDTH = 8;
constexpr static uint16_t SPRITE_HEIGHT = 8;

constexpr static uint16_t MAX_SPRITES = 40;

// Dimensions of a Tall Sprite/Obj
constexpr static uint16_t TALL_SPRITE_WIDTH = 8;
constexpr static uint16_t TALL_SPRITE_HEIGHT = 16;

// Dimensions of GB Viewport (display the user actually sees)
constexpr static uint16_t VPORT_WIDTH = 160;
constexpr static uint16_t VPORT_HEIGHT = 144;

// Buffer sizes
constexpr static uint16_t TILE_BUFFER_SIZE = TILE_WIDTH * TILE_HEIGHT;
constexpr static uint16_t DISPLAY_LAYER_SIZE = DISPLAY_LAYER_WIDTH * DISPLAY_LAYER_HEIGHT;
constexpr static uint16_t SPRITE_BUFFER_SIZE = SPRITE_WIDTH * SPRITE_HEIGHT;
constexpr static uint16_t TALL_SPRITE_BUFFER_SIZE = TALL_SPRITE_WIDTH * TALL_SPRITE_HEIGHT;
constexpr static uint16_t DISPLAY_SIZE = VPORT_WIDTH * VPORT_HEIGHT;


// flat buffers for pixel maps
typedef std::array<byte, TILE_BUFFER_SIZE> TileDataBuffer;
typedef std::array<byte, DISPLAY_LAYER_SIZE> DisplayLayerBuffer;
typedef std::array<byte, SPRITE_BUFFER_SIZE> SpriteBuffer;
typedef std::array<byte, TALL_SPRITE_BUFFER_SIZE> TallSpriteBuffer;



uint16_t CoordsAsIndex(int x, int y, int row_width, int row_height)
{
  if (x > row_width)
    std::runtime_error("X exceeds row width");
  else if (y > row_height)
    std::runtime_error("Y exceeds row height");

  return y * row_width + x;
}

uint16_t TileDataI(int x, int y)
{
  return CoordsAsIndex(x, y, TILE_WIDTH, TILE_HEIGHT);
}

uint16_t SpriteDataI(int x, int y, bool tall_sprite = false)
{
  return CoordsAsIndex(x, y, SPRITE_WIDTH, tall_sprite ? TALL_SPRITE_HEIGHT : SPRITE_HEIGHT);
}

uint16_t BgMapI(int x, int y)
{
  return CoordsAsIndex(x, y, DISPLAY_LAYER_WIDTH, DISPLAY_LAYER_HEIGHT);
}

uint16_t VPortI(int x, int y)
{
  return CoordsAsIndex(x, y, VPORT_WIDTH, VPORT_HEIGHT);
}

struct Sprite
{
    uint8_t x_pos;
    uint8_t y_pos;
    uint8_t tile_index;
    uint8_t flags;
};

std::vector<byte> ReadTileLine(byte y)
{
    std::vector<byte> ret;
    for (int i = 0; i < 32; i++)
    {
      uint8_t tile_num = gbc::Ram::Instance()->ReadByte(0x9800 + ((y / 8) * 32) + i);

      uint16_t tile_data_start = 0x8000 + (16*tile_num) + ((y%8)*2);
      register8_t byte1 = gbc::Ram::Instance()->ReadByte(tile_data_start);
      register8_t byte2 = gbc::Ram::Instance()->ReadByte(tile_data_start + 1);
      for (int j = 0; j < 8; j++)
      {
        uint8_t lsb = byte1.BitAtMSB(i);
        uint8_t msb = byte2.BitAtMSB(i);
        // std::cout << "placing pixel of shade " << (int) ((second_bit << 1) | first_bit) << std::endl;
        ret.push_back((msb << 1) | lsb);
      }
    }
    return ret;
}
void DrawBgScanline()
{
    // scanline == 100 = y
    // start_y = y + scroll_y
    // start_x = 0 + scroll_x;
    // 
    // get tile data at y

}
std::vector<Sprite> ReadSprites()
{
    std::vector<Sprite> ret;

    for (uint16_t i = MemoryMap::OFFSET_OBJECT_ATTR_MEM_START; i < MAX_SPRITES; i+=4)
    {
        auto sprite_data = gbc::Ram::Instance()->ReadBytesAt(i, 4);
        Sprite sprite;
        sprite.y_pos = sprite_data[0];
        sprite.x_pos = sprite_data[1];
        sprite.tile_index = sprite_data[2];
        sprite.flags = sprite_data[3];
        ret.push_back(sprite);
    }
    return ret;
}


// there are 1024 tiles, 32 in each row. 
void DrawTileAt(int tile_num, DisplayLayerBuffer& pixel_buff, const TileDataBuffer& tile_buff) // 1024 tiles
{
  // start_offset + (y * ROW_WIDTH + x)
  // tile 2 would start at x = 8 and y = 0
  // tile 33 would start at x = 0 y = 8
  int tiles_per_row = DISPLAY_LAYER_WIDTH/8;
  int start_x = (tile_num % tiles_per_row) * 8;
  int start_y = (tile_num / tiles_per_row) * 8;
  // std::cout << "starting tile " << tile_num << std::endl;
  // std::cout << "start_x = " << start_x << std::endl;
  // std::cout << "start_y = " << start_y << std::endl;


  int tile_y = 0;
  int tile_x = 0;
  for (int y = start_y; y < (start_y + TILE_HEIGHT); y++)
  {

    for (int x = start_x; x < start_x + TILE_WIDTH; x++)
    {
      // std::cout << "tile_x = " << tile_x << std::endl;
      // std::cout << "tile_y = " << tile_y << std::endl;
      // std::cout << "x = " << x << std::endl;
      // std::cout << "y = " << y << std::endl;
      // std::cout << "updating pixel at " << (y * ROW_WIDTH + x) << " to val " << (int) tile_buff[tile_y * 8 + tile_x] << std::endl;
      pixel_buff[BgMapI(x, y)] = tile_buff[TileDataI(tile_x, tile_y)];
      tile_x++;
    }
    tile_y++;
    tile_x = 0;
  }
}


void DrawSpriteAt(int x, int y, DisplayLayerBuffer& pixel_buff, const SpriteBuffer& sprite_buffer) // 1024 tiles
{
  // start_offset + (y * ROW_WIDTH + x)
  // tile 2 would start at x = 8 and y = 0
  // tile 33 would start at x = 0 y = 8
  int start_x = x;
  int start_y = y;
  // std::cout << "start_x = " << start_x << std::endl;
  // std::cout << "start_y = " << start_y << std::endl;


  int sprite_y = 0;
  int sprite_x = 0;
  for (int y = start_y; y < (start_y + SPRITE_HEIGHT); y++)
  {

    for (int x = start_x; x < start_x + SPRITE_WIDTH; x++)
    {
      // std::cout << "tile_x = " << tile_x << std::endl;
      // std::cout << "tile_y = " << tile_y << std::endl;
      // std::cout << "x = " << x << std::endl;
      // std::cout << "y = " << y << std::endl;
      // std::cout << "updating pixel at " << (y * ROW_WIDTH + x) << std::endl;
      pixel_buff[BgMapIndex(x, y)] = sprite_buffer[SpriteDataI(sprite_x, sprite_y)];
      sprite_x++;
    }
    sprite_y++;
    sprite_x = 0;
  }
}

// Draw a ssprite at the specified coordinates in the given displayer layer buffer (probably the Window or Background)
void DrawTallSpriteAt(int x, int y, DisplayLayerBuffer& pixel_buff, const TallSpriteBuffer& sprite_buffer) // 1024 tiles
{
  // start_offset + (y * ROW_WIDTH + x)
  // tile 2 would start at x = 8 and y = 0
  // tile 33 would start at x = 0 y = 8
  int start_x = x;
  int start_y = y;
  // std::cout << "start_x = " << start_x << std::endl;
  // std::cout << "start_y = " << start_y << std::endl;


  int sprite_y = 0;
  int sprite_x = 0;
  for (int y = start_y; y < (start_y + TALL_SPRITE_HEIGHT); y++)
  {

    for (int x = start_x; x < start_x + TALL_SPRITE_WIDTH; x++)
    {
      // std::cout << "tile_x = " << tile_x << std::endl;
      // std::cout << "tile_y = " << tile_y << std::endl;
      // std::cout << "x = " << x << std::endl;
      // std::cout << "y = " << y << std::endl;
      // std::cout << "updating pixel at " << (y * ROW_WIDTH + x) << std::endl;
      pixel_buff[BgMapIndex(x, y)] = sprite_buffer[SpriteDataI(sprite_x, sprite_y)];
      sprite_x++;
    }
    sprite_y++;
    sprite_x = 0;
  }
}

}
#endif