#include <SFML/Graphics.hpp>
#include <boost/log/trivial.hpp>
#include <fstream>
#include <iostream>
#include <Logger.h>
#include <ctime>
#include "boost/date_time/local_time/local_time.hpp"
#include "Opcode.h"
#include "Cpu.h"
#include "Memory.h"
#include <SFML/Graphics.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
//#include "Cpu.h"

using namespace gbc;
using namespace boost::posix_time;

static const int ROW_WIDTH = 256;

void initlog()
{
	boost::log::core::get()->set_filter
    (
        boost::log::trivial::severity >= boost::log::trivial::error
    );
}
uint16_t CoordsAsIndex(int x, int y, int row_width, int row_height)
{
  if (x > row_width)
    std::runtime_error("X exceeds row width");
  else if (y > row_height)
    std::runtime_error("Y exceeds row height");

  return y * row_width + x;
}

uint16_t TileDataIndex(int x, int y)
{
  return CoordsAsIndex(x, y, 8, 8);
}

uint16_t SpriteDataIndex(int x, int y, bool tall_sprite)
{
  return CoordsAsIndex(x, y, 8, tall_sprite ? 16 : 8);
}

uint16_t BgMapIndex(int x, int y)
{
  return CoordsAsIndex(x, y, ROW_WIDTH, ROW_WIDTH);
}

uint16_t ViewPortIndex(int x, int y)
{
  return CoordsAsIndex(x, y, 160, 144);
}

std::vector<byte> LoadRom(const std::string& file_path)
{

    std::ifstream infile(file_path, std::ios_base::binary);
    auto vec = std::vector<char>( std::istreambuf_iterator< char>(infile),
                            std::istreambuf_iterator< char>() );
    std::vector<byte> ret;
    for (int i = 0; i < vec.size(); i++)
        ret.push_back(static_cast<byte>(vec[i]));
    return ret;
}
/*
void shit()
{

      ptime now = microsec_clock::local_time();
    
    std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
    INIT_LOGGER(new std::ofstream ("test.txt", std::ios_base::ate|std::ios_base::app), true);
    LOG_STREAM << "testing the logger" << LOG_END;
    LOG_STREAM << now << " testing the logger agin" << LOG_END;
    register8_t reg((byte) 0xBA, "A"); 
    BOOST_LOG_TRIVIAL(debug) << "yoooo" << reg;
    reg.SetBit(7);
    BOOST_LOG_TRIVIAL(debug) << "yoooo again " << reg;
    register8_t regb(reg.GetBits(4, 7), "B");
    BOOST_LOG_TRIVIAL(debug) << "yoooo againnn " << regb;

    address16_t ins(0xABCD, "Do something");

    // format of 0xFNNA
    unsigned short expect = 0xC00A;
    unsigned short expect_mask = 0xF00F;
    unsigned short actual_ins = 0xCBBA;
    unsigned short ret = expect_mask & actual_ins;
    register16_t re(ret, "C");
    // std::cout << (ret == expect) << std::endl;
    address16_t in(0xF00A, "OPCODE_INSTRUCTION");
  //  gbc::OpcodeCommand cmd = Opcode::opcode_map().at(0xF8);
  //  cmd.Execute(in);
    Cpu::Instance()->A.mValue = 0xAB;
    BOOST_LOG_TRIVIAL(debug) <<  Cpu::Instance()->A;
  //  cmd.Execute(in);
    // std::cout << gbc::Utils::Time::NowNano() << std::endl;
    uint64_t tick_rate_nano = 1000000000/CPU_SPEED;
    // std::cout << "tick_rate_nano = " << tick_rate_nano << std::endl;
    uint64_t cycles = 0;
    uint64_t next_tick_nano = 0;
    auto start = gbc::Utils::Time::NowNano();
    // std::cout << "start= " << start << std::endl;
    while (cycles < CPU_SPEED)
    {
        //uint64_t now = Utils::Time::NowNano();
        if (gbc::Utils::Time::NowNano() >= next_tick_nano)
        {
            cycles++;
            next_tick_nano = gbc::Utils::Time::NowNano() + tick_rate_nano;
        }
    }
    auto end = gbc::Utils::Time::NowNano();
    // std::cout << "end= " << (end - start) << std::endl;
}
*/
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

            // start_offset + (y * ROW_WIDTH + x)
            

        }
        byte GetTileNumberAt(byte offset); // just start_offset + offset

    };

    struct DisplayLayerBuffer
    {

    };

    void UpdateBuffers()
    {
        // maybe a basic loop will look like...
        // for all tiles (32x32)
        // get Tile Number from BackgroundMap
        // Get tile_data[tile_number] 
        // draw the tile into the buffer?? idrk
    }

    // there are 2 methods for this but just for now lets use "8000" method


    struct TileData
    {

        TileData(std::array<byte, 16> buffer) 
            : mBuffer(buffer)
        {

        }

        std::array<byte, 16> mBuffer;

        // this should return a 8x8 64 byte pixel map, where each represents a pixel/color in a tile
        std::array<byte, 64> AsPixelMap()
        {
            std::array<byte, 64> ret;
            for (int i = 0; i < mBuffer.size(); i+=2)
            {
                register8_t first = mBuffer[i];
                register8_t second = mBuffer[i + 1];
                for (int j = 0; j < 8; j++)
                {
                    uint8_t first_bit = first.BitAtMSB(i);
                    uint8_t second_bit = second.BitAtMSB(i);
                    // std::cout << "placing pixel of shade " << (int) ((second_bit << 1) | first_bit) << std::endl;
                    ret[TileDataIndex(j, i/2)] = ((second_bit << 1) | first_bit);
                }

            }
            return ret;
        }
    };



void DrawBuffer(std::array <byte, ROW_WIDTH*ROW_WIDTH>& buff)
{
  for (int y = 0; y < ROW_WIDTH; y++)
  {
    for (int x = 0; x < ROW_WIDTH; x++)
    { 
        byte c = buff[y * ROW_WIDTH + x];
        if (c == '.')
        {
          // std::cout << c;
        }
        else if ( c == 0x01)
        {
            // std::cout << '$';
        }
        else if ( c == 0x02)
        {
            // std::cout << '#';
        }
        else if ( c == 0x03)
        {
            // std::cout << '@';
        }
        else if ( c == 0x00)
        {
            // std::cout << '.';
        }
        else
        {
          // std::cout << (int) buff[y * ROW_WIDTH + x];
        }
    }
   // // std::cout << "this draw" << std::endl;
    // std::cout << std::endl;
  }
}

// there are 1024 tiles, 32 in each row. 
void DrawTileAt(int tile_num, std::array <byte, ROW_WIDTH*ROW_WIDTH>& pixel_buff, std::array <byte, 64>& tile_buff) // 1024 tiles
{
  // start_offset + (y * ROW_WIDTH + x)
  // tile 2 would start at x = 8 and y = 0
  // tile 33 would start at x = 0 y = 8
  int tiles_per_row = ROW_WIDTH/8;
  int start_x = (tile_num % tiles_per_row) * 8;
  int start_y = (tile_num / tiles_per_row) * 8;
  // std::cout << "starting tile " << tile_num << std::endl;
  // std::cout << "start_x = " << start_x << std::endl;
  // std::cout << "start_y = " << start_y << std::endl;


  int tile_y = 0;
  int tile_x = 0;
  for (int y = start_y; y < (start_y + 8); y++)
  {

    for (int x = start_x; x < start_x + 8; x++)
    {
      // std::cout << "tile_x = " << tile_x << std::endl;
      // std::cout << "tile_y = " << tile_y << std::endl;
      // std::cout << "x = " << x << std::endl;
      // std::cout << "y = " << y << std::endl;
      // std::cout << "updating pixel at " << (y * ROW_WIDTH + x) << " to val " << (int) tile_buff[tile_y * 8 + tile_x] << std::endl;
      pixel_buff[y * ROW_WIDTH + x] = tile_buff[tile_y * 8 + tile_x];
      tile_x++;
    }
    tile_y++;
    tile_x = 0;
  }
}


void DrawSpriteAt(int x, int y, std::array <byte, ROW_WIDTH*ROW_WIDTH>& pixel_buff, std::array <byte, 64>& sprite_buffer) // 1024 tiles
{
  // start_offset + (y * ROW_WIDTH + x)
  // tile 2 would start at x = 8 and y = 0
  // tile 33 would start at x = 0 y = 8
  int tiles_per_row = ROW_WIDTH/8;
  int start_x = x;
  int start_y = y;
  // std::cout << "start_x = " << start_x << std::endl;
  // std::cout << "start_y = " << start_y << std::endl;


  int tile_y = 0;
  int tile_x = 0;
  for (int y = start_y; y < (start_y + 8); y++)
  {

    for (int x = start_x; x < start_x + 8; x++)
    {
      // std::cout << "tile_x = " << tile_x << std::endl;
      // std::cout << "tile_y = " << tile_y << std::endl;
      // std::cout << "x = " << x << std::endl;
      // std::cout << "y = " << y << std::endl;
      // std::cout << "updating pixel at " << (y * ROW_WIDTH + x) << std::endl;
      pixel_buff[BgMapIndex(x, y)] = sprite_buffer[TileDataIndex(tile_x, tile_y)];
      tile_x++;
    }
    tile_y++;
    tile_x = 0;
  }
}

static const int VP_WIDTH = 160;
static const int VP_HEIGHT = 144;

void DrawViewPort(std::array <byte, VP_WIDTH*VP_HEIGHT>& buff)
{
  for (int y = 0; y < VP_HEIGHT; y++)
  {
    for (int x = 0; x < VP_WIDTH; x++)
    {
        // std::cout << buff[ViewPortIndex(x, y)];
    }
    // std::cout << std::endl;
  }
}

void UpdateViewPort(int sx, int sy, std::array <byte, ROW_WIDTH*ROW_WIDTH>& background,std::array <byte, VP_WIDTH*VP_HEIGHT>& vp_buff)
{

  int sx_copy = sx;
  for (int vp_y = 0; vp_y < VP_HEIGHT; vp_y++)
  {
    for (int vp_x = 0; vp_x < VP_WIDTH; vp_x++)
    {
      //// std::cout << " doing update vierwport" << std::endl;
      vp_buff[ViewPortIndex(vp_x, vp_y)] = background[((sy * ROW_WIDTH) % ROW_WIDTH) + (sx % ROW_WIDTH)];
      sx++;
    }
    sx = sx_copy;
    sy++;
  }
}
    std::array<byte, 16> ReadTileDataBlock(byte tile_number)
    {
        std::array<byte, 16> ret;
        uint16_t start_offset = 0x8000 + (tile_number * 16);

        for (uint16_t i = start_offset; i < start_offset + 16; i++)
        {
            register16_t tmp = i;
            // std::cout << "attempting to read at " << tmp << std::endl;
            ret[i - start_offset] = gbc::Ram::Instance()->ReadByte(i);
            // std::cout << "getting here " << std::endl;
        }
        return ret;
    }

    std::array<byte, 4> ReadSpriteBlock(byte sprite_num)
    {
        std::array<byte, 4> ret;
        uint16_t start_offset =  0xFE00 + (sprite_num * 4);

        for (uint16_t i = start_offset; i < start_offset + 4; i++)
        {
            register16_t tmp = i;
            // std::cout << "attempting to read at " << tmp << std::endl;
            ret[i - start_offset] = gbc::Ram::Instance()->ReadByte(i);
            // std::cout << "getting here " << std::endl;
        }
        return ret;
    }

// very basic loop for updating background pixel buffer tiles
void UpdateBgBuffer(std::array <byte, ROW_WIDTH*ROW_WIDTH>& background)
{
  int ok = 0;
  // go through all 1024 tiles
  for (int i = 0; i < 32; i++)
  {
  for (int j = 0; j < 32; j++)
  {
    // std::cout << "looking for tile_num of tile " << i << std::endl;
    uint8_t tile_num = gbc::Ram::Instance()->ReadByte(BgMapIndex(j, i));
    // std::cout << "tile num is " << (int) tile_num << std::endl;
    auto block = ReadTileDataBlock(tile_num);
    // std::cout << "got a block " << std::endl;
    TileData td(block);
    auto blk = td.AsPixelMap();
    // std::cout << "trying to draw block " << std::endl;
    DrawTileAt(ok, background, blk);
    ok++;
  }
  }
  /*
  // do the same thing for sprites
  for (int i = 0; i < 40; i++)
  {
    auto sprite_block = ReadSpriteBlock(i);
    byte y_pos = sprite_block[0] - 16;
    byte x_pos = sprite_block[1] - 8;
    byte tile_num = sprite_block[2];
    byte flags = sprite_block[3];
    auto tile_block = ReadTileDataBlock(tile_num);
    TileData td(tile_block);
    auto as_map = td.AsPixelMap();
    DrawSpriteAt(x_pos, y_pos,background, as_map);
  }
  */
}
void UpdateBgBufferTest(std::array <byte, ROW_WIDTH*ROW_WIDTH>& background)
{
  // go through all 1024 tiles
  for (int i = 0; i < 192; i++)
  {
    //// std::cout << "looking for tile_num of tile " << i << std::endl;
  //  uint8_t tile_num = gbc::Ram::Instance()->ReadByte(0x9800 + i);
 //   // std::cout << "tile num is " << (int) tile_num << std::endl;
    auto block = ReadTileDataBlock(i);
    // std::cout << "got a block " << std::endl;
    TileData td(block);
    auto blk = td.AsPixelMap();
    // std::cout << "trying to draw block " << std::endl;
    DrawTileAt(i, background, blk);
  }
}
void test_stuffppu()
{
  // test drawing into a 256x256 buffer
// draw sprites or tiles
std::array <byte, ROW_WIDTH*ROW_WIDTH> pixel_buffer;
std::array <byte, 64> tile_buffer; // 8x8 tile = 64 pixels
std::array <byte, 64> sprite_buffer; // 8x8 tile = 64 pixels

std::array <byte, 64> tile_buffer2; // 8x8 tile = 64 pixels

std::array <byte, VP_WIDTH*VP_HEIGHT> vp_buffer;


for (int i = 0; i < pixel_buffer.size(); i++)
{
  pixel_buffer[i] = '.';
}

for (int i = 0; i < vp_buffer.size(); i++)
{
  vp_buffer[i] = '.';
}

for (int i = 0; i < tile_buffer.size(); i++)
{
  tile_buffer[i] = '@';
}

for (int i = 0; i < tile_buffer.size(); i++)
{
  sprite_buffer[i] = '$';
}

for (int i = 0; i < tile_buffer.size(); i++)
{
  tile_buffer2[i] = '#';
}


  for (int i = 0; i < 256; i++)
  {
    if (i % 2 == 0)
    {
      DrawTileAt(i, pixel_buffer, tile_buffer);
    }
    else
    {
      DrawTileAt(i, pixel_buffer, tile_buffer2);
    }
  }
  DrawBuffer(pixel_buffer);
  UpdateViewPort(101, 101, pixel_buffer, vp_buffer);
  DrawViewPort(vp_buffer);

}
int main()
{
initlog();
  std::array <byte, ROW_WIDTH*ROW_WIDTH> pixel_buffer;
  for (int i = 0; i < pixel_buffer.size(); i++)
{
  pixel_buffer[i] = '.';
}
  
  
  auto vec = LoadRom("../src/roms/single_ins.gb");

  gbc::Ram::Instance()->LoadRom(vec);
  // std::cout << vec.size() << std::endl;
  int i = 0;
  while (i < 10000000)
  {
    gbc::Cpu::Instance()->Execute();
    i++;
    register8_t lcdc1 = register8_t(gbc::Ram::Instance()->ReadByte(0xFF41), "LCDC Status");
    BOOST_LOG_TRIVIAL(debug) << lcdc1;
    lcdc1 = register8_t(gbc::Ram::Instance()->ReadByte(0xFF42), "Scroll Y");
    BOOST_LOG_TRIVIAL(debug) << lcdc1;
    lcdc1 = register8_t(gbc::Ram::Instance()->ReadByte(0xFF43), "Scroll X");
    BOOST_LOG_TRIVIAL(debug) << lcdc1;
    lcdc1 = register8_t(gbc::Ram::Instance()->ReadByte(0xFF44), "LCDC Y Coord");
    BOOST_LOG_TRIVIAL(debug) << lcdc1;
    lcdc1 = register8_t(gbc::Ram::Instance()->ReadByte(0xFF4A), "Window Y");
    BOOST_LOG_TRIVIAL(debug) << lcdc1;
    lcdc1 = register8_t(gbc::Ram::Instance()->ReadByte(0xFF4B), "Window X");
    BOOST_LOG_TRIVIAL(debug) << lcdc1;
    lcdc1 = register8_t(gbc::Ram::Instance()->ReadByte(0xFF40), "LCDC control");
    BOOST_LOG_TRIVIAL(debug) << lcdc1;


  }
  UpdateBgBuffer(pixel_buffer);
//  DrawBuffer(pixel_buffer);

    auto window = sf::RenderWindow{ { ROW_WIDTH + 20, ROW_WIDTH + 20}, "CMake SFML Project" };
    window.setFramerateLimit(30);
    sf::Sprite sprite;



    //while (cpu.mTickCount < 600)
   //     cpu.Decode(cpu.Fetch());

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
              //  PrintPixels(cpu);
                window.close();
            }
        }

        window.clear();
        
        for (int i = 0; i < ROW_WIDTH; i++)
        {
            for (int j = 0; j < ROW_WIDTH; j++)
            {
                    sf::CircleShape shape(1 * DISPLAY_SCALE);
                    byte shade = pixel_buffer[BgMapIndex(j, i)];
                    if (shade == 0x00)
                    {
                        shape.setFillColor(sf::Color(255, 255, 255));
                    }
                    else if (shade == 0x01)
                    {
                        shape.setFillColor(sf::Color(169, 169, 169));
                    }
                    else if (shade == 0x02)
                    {
                        shape.setFillColor(sf::Color(84, 84, 84));
                    }
                    else if (shade == 0x03)
                    {
                        shape.setFillColor(sf::Color(0, 0, 0));
                    }
                    shape.setPosition(j, i);
                    window.draw(shape);

            }
        }
        
        
        window.display();
    }
}