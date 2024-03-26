#include "Ppu.h"

namespace gbc
{

  std::array<byte, 16> ReadTileDataBlock(byte tile_number)
{
    std::array<byte, 16> ret;
    uint16_t start_offset = 0x8000 + (tile_number * 16);
  address16_t d = start_offset;
//  std::cout << "getting tile data from addr in read tiledatablock " << d << std::endl;
    for (uint16_t i = start_offset; i < start_offset + 16; i++)
    {
        register16_t tmp = i;
        register8_t tmpers = gbc::Ram::Instance()->ReadByte(i);
        // std::cout << "attempting to read at " << tmp << std::endl;
        ret[i - start_offset] = tmpers.value();
       // std::cout << "added byte: " << tmpers << std::endl;
    }
    return ret;
}
void PrintTile(const std::array<byte, 64>& buff)
{
  for (int y = 0; y < 8; y++)
  {
    for (int x = 0; x < 8; x++)
    {
      std::cout << (int) buff[CoordsAsIndex(x, y, 8, 8)];
    }
    std::cout << std::endl;
  }
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
        int k = 0;
        for (int i = 0; i < mBuffer.size(); i+=2)
        {
            register8_t first = mBuffer[i];
            register8_t second = mBuffer[i + 1];
            for (int j = 0; j < 8; j++)
            {
                uint8_t first_bit = first.BitAtMSB(j);
                uint8_t second_bit = second.BitAtMSB(j);
                // std::cout << "placing pixel of shade " << (int) ((second_bit << 1) | first_bit) << std::endl;
                ret[k] = ((second_bit << 1) | first_bit);
                k++;
            }

        }
        return ret;
    }
};
    // push back 2BPP representation of 2 bytes into provided buffer
    void TwoBPP(const byte byte1, const byte byte2, std::vector<byte>& buff )
    {
      register8_t reg_byte1 = byte1;
      register8_t reg_byte2 = byte2;
      for (int j = 0; j < 8; j++)
      {
        uint8_t lsb = reg_byte1.BitAtMSB(j);
        uint8_t msb = reg_byte2.BitAtMSB(j);
      //  std::cout << "pushing " << (int) msb << (int) lsb << std::endl;
      //  std::cout << "placing pixel of shade " << (int) ((msb << 1) | lsb) << std::endl;
        buff.push_back(((msb << 1) | lsb));
      }  
    }

    Ppu::Ppu() :
        mLcdControl(Ram::Instance()->ReadBytePtr(0xFF40)),
        mSx(Ram::Instance()->ReadBytePtr(0xFF43)),
        mSy(Ram::Instance()->ReadBytePtr(0xFF42)),
        mWx(Ram::Instance()->ReadBytePtr(0xFF4A)),
        mWy(Ram::Instance()->ReadBytePtr(0xFF4B)),
        mLcdBuffer(DisplayBuffer(LCD_WIDTH, LCD_HEIGHT))
    {

    }

    // the main Ppu loop
    void Ppu::Tick()
    {
        // Update all the status bit we will need for rendering
        LcdControlUpdate();

        switch (mCurrMode)
        {
            case PpuMode::H_BLANK:
                break;
            case PpuMode::V_BLANK:
                ModeVBlank();
                break;
            case PpuMode::OAM_SCAN:
                ModeOAMScan();
                break;
            case PpuMode::DRAW:

                break;
        }

    }

    void Ppu::RegisterDrawCallback(std::function<void(const DisplayBuffer&)> func)
    {
        mDrawCallback = func;
    }

    void Ppu::ModeOAMScan()
    {
        if (mCurrentScanline < 144)
        {
            ReadBgTileLine(mCurrentScanline++);
        }
        else
        {
            mCurrMode = PpuMode::V_BLANK;
        }

    }

    void Ppu::ModeHBlank()
    {

    }

    void Ppu::ModeDraw()
    {

    }

    void Ppu::ModeVBlank()
    {
        if (mCurrentScanline < 154)
        {
            // just do nothing for now....
            mCurrentScanline++;
        }
        else
        {
           // std::cout << "doing draw" << std::endl;
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
                DrawSpriteAt(x_pos, y_pos, as_map);
            }
            mDrawCallback(mLcdBuffer);
            mCurrentScanline = 0;
            mCurrMode = PpuMode::OAM_SCAN;
        }
    }

    // Read a single scan line of tile data from Bg window and copy to the LCD buffer
    // should return a 256 byte vector
    void Ppu::ReadBgTileLine(const byte y)
    {

        std::vector<byte> line_buffer;
        
        byte bg_y = (y + *mSy) % DISPLAY_LAYER_HEIGHT;
        // I guess this will have 2 steps, first we need to actually pull data from line Y
        // then write the data to the LCD buffer appropriately 
        for (int i = 0; i < BG_TILES_PER_ROW; i++)
        {
        address16_t addr = (mBgTileMapOffset + ((bg_y / TILE_WIDTH) * BG_TILES_PER_ROW) + i);
   //     std::cout << "getting tile num from addr " << addr << std::endl;
        uint8_t tile_num = gbc::Ram::Instance()->ReadByte(addr.value());
   //     std::cout << "got tile num " << (int) tile_num << std::endl;
     //  auto til = ReadTileDataBlock(tile_num);
    //      TileData p(til);
    //      PrintTile(p.AsPixelMap());                                                                        // 2 bytes per single tile line
        uint16_t tile_data_start = mTileDataSelectOffset + (BYTES_PER_TILE * tile_num) + ((bg_y % TILE_WIDTH) * 2);
        address16_t d = tile_data_start;
    //   std::cout << "getting tile data from addr " << d << std::endl;
        byte byte1 = gbc::Ram::Instance()->ReadByte(tile_data_start);
    //   std::cout << "byte1: " << byte1 << std::endl;

        byte byte2 = gbc::Ram::Instance()->ReadByte(tile_data_start + 1);
    //   std::cout << "byte2: " << byte2 << std::endl;
        TwoBPP(byte1, byte2, line_buffer);
        

        }
      //  for (auto& a : line_buffer)
      //      std::cout << (int) a;
      //  std::cout << std::endl;
        // setup to populate the LCD buffer
        // now populate the LCD buffer?
        byte bg_x = 0 + *mSx;
        for (int i = 0; i < LCD_WIDTH; i++)
        {
            mLcdBuffer.SetPixel(i, y, line_buffer[bg_x % DISPLAY_LAYER_WIDTH]);
            bg_x++;
        }
    }

    void Ppu::LcdControlUpdate()
    {
        register8_t lcd_control = register8_t(*mLcdControl, "LCD Control");
        register8_t sy = register8_t(*mSy, "Scroll Y");
        register8_t sx = register8_t(*mSx, "Scroll X");
        //std::cout << "LcdControlUpdate " << lcd_control << std::endl;
        //std::cout << "LcdControlUpdate " << sx << std::endl;
        //std::cout << "LcdControlUpdate " << sy << std::endl;

        mLcdEnabled = lcd_control.BitAtLSB(7);
        mWindowMapSelect = lcd_control.BitAtLSB(6);
        mWindowEnable = lcd_control.BitAtLSB(5);
        mTileDataSelect = lcd_control.BitAtLSB(4);
        mBgTileMapSelect = lcd_control.BitAtLSB(3);
        mSpriteSizeFlag = lcd_control.BitAtLSB(2);
        mSpriteEnable = lcd_control.BitAtLSB(1);
        mBgWindowEnable = lcd_control.BitAtLSB(0);

        mWindowBgMapOffset = mWindowMapSelect ? 0x9C00 : 0x9800;
        mBgTileMapOffset = mBgTileMapSelect ? 0x9C00 : 0x9800;
        mTileDataSelectOffset = mTileDataSelect ? 0x8000 : 0x8800;
    }

    void Ppu::DumpBufferDebug()
    {

        for (int y = 0; y < LCD_HEIGHT; y++)
        {
            for (int x = 0; x < LCD_WIDTH; x++)
            {
                 std::cout << (int) mLcdBuffer.GetPixel(x, y);
            }
             std::cout << std::endl;
        }

    }

void Ppu::DrawSpriteAt(int x, int y, const SpriteBuffer& sprite_buffer) // 1024 tiles
{

  int start_x = x;
  int start_y = y;



  int sprite_y = 0;
  int sprite_x = 0;
  for (int y = start_y; y < (start_y + SPRITE_HEIGHT); y++)
  {
    for (int x = start_x; x < start_x + SPRITE_WIDTH; x++)
    {
      mLcdBuffer.SetPixel(x, y, sprite_buffer[CoordsAsIndex(sprite_x, sprite_y, 8, 8)]);
      sprite_x++;
    }
    sprite_y++;
    sprite_x = 0;
  }
}
}