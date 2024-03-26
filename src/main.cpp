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
#include "Ppu.h"
//#include "Cpu.h"

using namespace gbc;
using namespace boost::posix_time;

static const int ROW_WIDTH = 256;

// buffers for pixel maps
typedef std::array<byte, 64> TileDataBuffer;
typedef std::array<byte, 256*256> DisplayLayerBuffer;
typedef std::array<byte, 64> SpriteBuffer;
typedef std::array<byte, 128> TallSpriteBuffer;


void initlog()
{
	boost::log::core::get()->set_filter
    (
        boost::log::trivial::severity >= boost::log::trivial::error
    );
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



void DrawBuffer(std::array <byte, ROW_WIDTH*ROW_WIDTH>& buff)
{
  for (int y = 0; y < ROW_WIDTH; y++)
  {
    for (int x = 0; x < ROW_WIDTH; x++)
    { 
        byte c = buff[y * ROW_WIDTH + x];
        if (c == '0')
        {
           std::cout << c;
        }
        else if ( c == 0x01)
        {
             std::cout << '$';
        }
        else if ( c == 0x02)
        {
             std::cout << '#';
        }
        else if ( c == 0x03)
        {
             std::cout << '@';
        }
        else if ( c == 0x00)
        {
             std::cout << '.';
        }
        else
        {
           std::cout << (int) buff[y * ROW_WIDTH + x];
        }
    }
   // // std::cout << "this draw" << std::endl;
     std::cout << std::endl;
  }
}

std::array <byte, ROW_WIDTH*ROW_WIDTH> BuffFromLines()
{
  std::array <byte, ROW_WIDTH*ROW_WIDTH> ret;
  int f = 0;
  for (int i = 0; i < 256; i++)
  {
    auto tile_line = ReadTileLine(i);
    for (auto& t : tile_line)
    {
      ret[f] = t;
      f++;
    }
  }
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
    DrawSpriteAt(x_pos, y_pos,ret, as_map);
  }
  return ret;
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
      vp_buff[VPortI(vp_x, vp_y)] = background[((sy * ROW_WIDTH) % ROW_WIDTH) + (sx % ROW_WIDTH)];
      sx++;
    }
    sx = sx_copy;
    sy++;
  }
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

void DumpMem()
{
  for (uint16_t i = 0x8000; i < 0x8FFF; i++)
  {
    register8_t t = gbc::Ram::Instance()->ReadByte(i);
    std::cout << t.Hex() << " ";
    if ((i - 0x8000) % 32 == 0)
      std::cout << std::endl;
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
  pixel_buffer[i] = '0';
}
  
  
  auto vec = LoadRom("../src/roms/dmg-acid2.gb");

  gbc::Ram::Instance()->LoadRom(vec);
  gbc::Ram::Instance()->WriteByte(0xFF00, 0xFF);
  std::cout << vec.size() << std::endl;
  int i = 0;
  /*
  while (i < 10000)
  {
    gbc::Cpu::Instance()->Execute();
    i++;
    register8_t lcdc1 = register8_t(*d_regs.ly_comp, "LCDC Status");
    BOOST_LOG_TRIVIAL(debug) << lcdc1;
    lcdc1 = register8_t(gbc::Ram::Instance()->ReadByte(0xFF42), "Scroll Y");
    BOOST_LOG_TRIVIAL(debug) << lcdc1;
    lcdc1 = register8_t(gbc::Ram::Instance()->ReadByte(0xFF43), "Scroll X");
    BOOST_LOG_TRIVIAL(debug) << lcdc1;
    lcdc1 = register8_t(*d_regs.ly, "LCDC Y Coord");
    BOOST_LOG_TRIVIAL(debug) << lcdc1;
    lcdc1 = register8_t(gbc::Ram::Instance()->ReadByte(0xFF4A), "Window Y");
    BOOST_LOG_TRIVIAL(debug) << lcdc1;
    lcdc1 = register8_t(gbc::Ram::Instance()->ReadByte(0xFF4B), "Window X");
    BOOST_LOG_TRIVIAL(debug) << lcdc1;
    lcdc1 = register8_t(*d_regs.sx, "LCDC control");
    BOOST_LOG_TRIVIAL(debug) << lcdc1;


  }
*/




   while (i < 1000000)
   {
   // std::cout << "executed: " << i << std::endl;
    gbc::Cpu::Instance()->Execute();
    //UpdateBgBuffer(pixel_buffer);
    i++;

   }
    // UpdateBgBuffer(pixel_buffer);
 // DrawBuffer(pixel_buffer);
    std::cout << "showing line" << std::endl;
    auto a = ReadTileLine(18);
    for (auto& b : a)
      std::cout << (int) b;
    std::cout << std::endl;
     a = ReadTileLine(19);
    for (auto& b : a)
      std::cout << (int) b;
    std::cout << std::endl;
     a = ReadTileLine(20);
    for (auto& b : a)
      std::cout << (int) b;
    std::cout << std::endl;
     a = ReadTileLine(21);
    for (auto& b : a)
      std::cout << (int) b;
    std::cout << std::endl;
    int PIXEL_SCALE = 3;
    auto window = sf::RenderWindow{ { ROW_WIDTH*PIXEL_SCALE, ROW_WIDTH *PIXEL_SCALE}, "Jomac Gameboy" };
    window.setFramerateLimit(30);
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Sprite spr;
    sf::Image img;
    img.create( ROW_WIDTH*PIXEL_SCALE,ROW_WIDTH *PIXEL_SCALE);
    int executed = 0;
    int draws = 0;

    pixel_buffer = BuffFromLines();
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
        if (executed % 50000 == 0)
        {
        for (int i = 0; i < ROW_WIDTH; i++)
        {
            for (int j = 0; j < ROW_WIDTH; j++)
            {

                    byte shade = pixel_buffer[BgMapI(j, i)];
                    sf::Color c;
                    if (shade == 0x00)
                    {
                      c = sf::Color(255, 255, 255);
                    }
                    else if (shade == 0x01)
                    {
                     c = sf::Color(169, 169, 169);
                    }
                    else if (shade == 0x02)
                    {
                        c = sf::Color(84, 84, 84);
                    }
                    else if (shade == 0x03)
                    {
                      c = sf::Color(0, 0, 0);
                    }
                    else
                    {
                      c = sf::Color(0, 0, 0);
                    }

                    for (int m = 0; m < PIXEL_SCALE; m++)
                    {
                    for (int n = 0; n < PIXEL_SCALE; n++)
                    {
                      img.setPixel(j * PIXEL_SCALE + n, i * PIXEL_SCALE + m, c);
                    }
                    }

                  //  window.draw(shape);

            }
        }
        }
        texture.loadFromImage(img);
        sprite.setTexture(texture, true);
        window.draw(sprite);
        
        window.display();
        executed++;
    }
    
    
}