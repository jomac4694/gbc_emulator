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
#include "DisplayBuffer.h"

using namespace gbc;
using namespace boost::posix_time;

static const byte PIXEL_SCALE = 3;
static std::unique_ptr<sf::RenderWindow> window;
static sf::Sprite sprite;

static sf::Image frame; // represents the entire current frame

void initlog()
{
	boost::log::core::get()->set_filter
    (
        boost::log::trivial::severity >= boost::log::trivial::error
    );
}


static std::vector<byte> LoadRom(const std::string& file_path)
{

    std::ifstream infile(file_path, std::ios_base::binary);
    auto vec = std::vector<char>( std::istreambuf_iterator< char>(infile),
                            std::istreambuf_iterator< char>() );
    std::vector<byte> ret;
    for (int i = 0; i < vec.size(); i++)
        ret.push_back(static_cast<byte>(vec[i]));
    return ret;
}
    // this is really just a 32x32 area in memory where the "TileNumber" for each tile is stored
    // The tile number is effectively an index into the Tile Data Map (the tile data map contains color info for each pixel in the 8x8 tile)
    // Ultimately the tile data is used to render the tiles for both the background and window grids




static sf::Color ColorFromPixel(byte pixel)
{
    sf::Color c;
    if (pixel == 0x00)
    {
      c = sf::Color(255, 255, 255);
    }
    else if (pixel == 0x01)
    {
      c = sf::Color(169, 169, 169);
    }
    else if (pixel == 0x02)
    {
        c = sf::Color(84, 84, 84);
    }
    else if (pixel == 0x03)
    {
      c = sf::Color(0, 0, 0);
    }
    else
    {
      c = sf::Color(0, 0, 0);
    }
    return c;
}

// thanks to github for this, did not know how to scale the pixels
static void SetLargePixel(uint16_t x, uint16_t y, sf::Color pixel)
{
  for (int img_y = 0; img_y < PIXEL_SCALE; img_y++)
  {
    for (int img_x = 0; img_x < PIXEL_SCALE; img_x++)
    {
      frame.setPixel(x * PIXEL_SCALE + img_x, y * PIXEL_SCALE + img_y, pixel);
    }
  } 
}

static void SetPixelsLCD(const DisplayBuffer& buff)
{
  for (int y = 0; y < LCD_HEIGHT; y++)
  {
      for (int x = 0; x < LCD_WIDTH; x++)
      {
        SetLargePixel(x, y, ColorFromPixel(buff.GetPixel(x, y)));
      }
  }
}

static void EventLoop()
{
    for (auto event = sf::Event{}; window->pollEvent(event);)
    {
        if (event.type == sf::Event::Closed)
        {
            window->close();
        }
    }  
}
static void Draw(const DisplayBuffer& buff)
{
  //  std::cout << "doing the real draw" << std::endl;
    sf::Texture texture; 
    EventLoop();
    window->clear(sf::Color::White);
    SetPixelsLCD(buff);
    texture.loadFromImage(frame);
    sprite.setTexture(texture, true);
    window->draw(sprite);
    window->display();
}

int main()
{
 // initlog();
  auto vec = LoadRom("../src/roms/dmg-acid2.gb");
  gbc::Ram::Instance()->LoadRom(vec);
  gbc::Ram::Instance()->WriteByte(0xFF00, 0xFF);
  std::cout << vec.size() << std::endl;
  Ppu p;
  
  window = std::make_unique<sf::RenderWindow>(sf::VideoMode( LCD_WIDTH * PIXEL_SCALE, LCD_HEIGHT *PIXEL_SCALE), "Jomac Gameboy", sf::Style::Titlebar | sf::Style::Close );
  frame.create( LCD_WIDTH * PIXEL_SCALE, LCD_HEIGHT * PIXEL_SCALE);
  window->setFramerateLimit(60);
  window->display();

  p.RegisterDrawCallback(Draw);

  int fired = 0;
//  while (fired < 100000)
 // {
 //   gbc::Cpu::Instance()->Execute();
 //   fired++;
 // }
  while (true)
  {
  //  std::cout << "fired: " << fired << std::endl;
    if (!window->isOpen())
    {
      p.DumpBufferDebug();
      break;
  }
    else
    {
      auto cycles = gbc::Cpu::Instance()->Execute();
      p.Tick(cycles);
    }
  }

}