#include "Ppu.h"
#include "Cpu.h"
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
    void PrintTile(const std::array<byte, 64> &buff)
    {
        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                std::cout << (int)buff[CoordsAsIndex(x, y, 8, 8)];
            }
            std::cout << std::endl;
        }
    }
    std::array<byte, 4> ReadSpriteBlock(byte sprite_num)
    {
        std::array<byte, 4> ret;
        uint16_t start_offset = 0xFE00 + (sprite_num * 4);

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
            for (int i = 0; i < mBuffer.size(); i += 2)
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
    void TwoBPP(const byte byte1, const byte byte2, std::vector<byte> &buff)
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

    Ppu::Ppu() : mLcdControl(Ram::Instance()->ReadBytePtr(0xFF40)),
                 mLcdStatus(Ram::Instance()->ReadBytePtr(0xFF41)),
                 mSx(Ram::Instance()->ReadBytePtr(0xFF43)),
                 mSy(Ram::Instance()->ReadBytePtr(0xFF42)),
                 mWx(Ram::Instance()->ReadBytePtr(0xFF4B)),
                 mWy(Ram::Instance()->ReadBytePtr(0xFF4A)),
                 mLy(Ram::Instance()->ReadBytePtr(0xFF44)),
                 mLyc(Ram::Instance()->ReadBytePtr(0xFF45)),
                 mLcdBuffer(DisplayBuffer(LCD_WIDTH, LCD_HEIGHT))
    {
    }

    int Ppu::GetModeCycles()
    {
        int cycles = 0;
        switch (mCurrMode)
        {
        case PpuMode::H_BLANK:
            cycles = 188;
            break;
        case PpuMode::V_BLANK:
            cycles = 456;
            break;
        case PpuMode::OAM_SCAN:
            cycles = 80;
            break;
        case PpuMode::DRAW:
            cycles = 188;
            break;
        }  
        return cycles;
    }
    // the main Ppu loop
    void Ppu::Tick(int cycles)
    {
        mCycles += (cycles*3);
        // Update all the status bit we will need for rendering
        LcdControlUpdate();
        // update the status reg too
        register8_t lcd_status = register8_t(*mLcdStatus, "LCD Status");
        if (mCycles >= GetModeCycles())
        {
        switch (mCurrMode)
        {
        case PpuMode::H_BLANK:
            ModeHBlank(lcd_status);
            break;
        case PpuMode::V_BLANK:
            ModeVBlank();
            break;
        case PpuMode::OAM_SCAN:
            ModeOAMScan(lcd_status);
            break;
        case PpuMode::DRAW:
            ModeDraw();
            mCurrMode = PpuMode::H_BLANK;
            break;
        }
        *mLy = mCurrentScanline;
            if (*mLy == *mLyc && !lcd_status.BitAtLSB(2) )
            {
                std::cout << "setting coincidence thing with y " << (int) mCurrentScanline << std::endl;
                lcd_status.SetBitLSB(2);
                Cpu::Instance()->SetIF(true);
                Cpu::Instance()->mCoinInt = true;
            }
            else
            {
                lcd_status.ResetBitLSB(2);
            }
        lcd_status.ResetBitLSB(0);
        lcd_status.ResetBitLSB(0);
        lcd_status.Set(lcd_status.value() | static_cast<byte>(mCurrMode));
        *mLcdStatus = lcd_status.value();

        BOOST_LOG_TRIVIAL(debug) << "Scanline: " << (int) mCurrentScanline;
        BOOST_LOG_TRIVIAL(debug) << "WindowEnabled: " << (int) mWindowEnable;
        if (mWindowEnable)
            std::cout << "Window is enabled" << std::endl;
        mCycles = 0;
        }
    }

    void Ppu::RegisterDrawCallback(std::function<void(const DisplayBuffer &)> func)
    {
        mDrawCallback = func;
    }

    void Ppu::ModeOAMScan(register8_t& lcd_status)
    {
        Cpu::Instance()->mVblankInt = false;

          //  if (mWindowEnable)
           // {
            //    std::cout << "drawing window" << std::endl;
             //   ReadWindowTileLine(mCurrentScanline);
           // }
            mCurrMode = PpuMode::DRAW;
    }

    void Ppu::ModeHBlank(register8_t& lcd_status)
    {
        mCurrentScanline++;
        if (mCurrentScanline < 144)
        {
            mCurrMode = PpuMode::OAM_SCAN;

        }
        else
        {
            Cpu::Instance()->mVblankInt = true;
            Cpu::Instance()->SetIF(true);
            mCurrMode = PpuMode::V_BLANK;
        }

    }

    void Ppu::ModeDraw()
    {
          ReadBgTileLine(mCurrentScanline);
    }

    void Ppu::ModeVBlank()
    {
        if (mCurrentScanline == 153)
        {
            //Cpu::Instance()->mVblankInt = true;
            //Cpu::Instance()->SetIF(true);
            mCurrentScanline++;
        }
        else if (mCurrentScanline < 154)
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
                register8_t flags = sprite_block[3];
                auto tile_block = ReadTileDataBlock(tile_num);
                TileData td(tile_block);
                auto as_map = td.AsPixelMap();

                DrawSpriteAt(x_pos, y_pos, as_map, flags);
            }

            mDrawCallback(mLcdBuffer);
            mCurrentScanline = 0;
            mFramesRendered++;
            mCurrMode = PpuMode::OAM_SCAN;
            mWindowLinesDrawn = 0;
        }
    }

    // Read a single scan line of tile data from Bg window and copy to the LCD buffer
    void Ppu::ReadBgTileLine(const byte y)
    {

        std::vector<byte> line_buffer;
        std::vector<byte> window_buff;
        byte bg_y = (y + *mSy) % DISPLAY_LAYER_HEIGHT;
        
        if ( mBgWindowEnable  )
        {
        //    std::cout << "drawing background " << std::endl;
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
            //      PrintTile(p.AsPixelMap());     
            uint16_t tile_data_start = 0;
            if (!mTileDataSelect)
            {
                tile_data_start = mTileDataSelectOffset + (BYTES_PER_TILE * static_cast<int8_t>(tile_num)) + ((bg_y % TILE_WIDTH) * 2);
            }   
            else
            {
                tile_data_start = mTileDataSelectOffset + (BYTES_PER_TILE * tile_num) + ((bg_y % TILE_WIDTH) * 2);
            }                                                       
            address16_t d = tile_data_start;
            //   std::cout << "getting tile data from addr " << d << std::endl;
            byte byte1 = gbc::Ram::Instance()->ReadByte(tile_data_start);
            //   std::cout << "byte1: " << byte1 << std::endl;

            byte byte2 = gbc::Ram::Instance()->ReadByte(tile_data_start + 1);
            //   std::cout << "byte2: " << byte2 << std::endl;
            TwoBPP(byte1, byte2, line_buffer);
            // now populate the LCD buffer
            byte bg_x = 0 + *mSx;
            for (int i = 0; i < LCD_WIDTH; i++)
            {
                mLcdBuffer.SetPixel(i, y, line_buffer[bg_x % DISPLAY_LAYER_WIDTH]);
                bg_x++;
            }

        }
        
        }
        
        else
        {
            for (int i = 0; i < DISPLAY_LAYER_WIDTH + 1; i++)
            {
                line_buffer.push_back(0x0);
            }
        }

        if ( y >= *mWy && mWindowEnable && *mWx <= 166)
        {
            std::cout << "drawing window" << std::endl;
            std::cout << "y= " << (int) y << std::endl;
            std::cout << "mWy= " << (int) *mWy << std::endl;
           // if (y >= 110)
           //     *mWy = 96;
            for (int i = 0; i < BG_TILES_PER_ROW; i++)
            {

                address16_t addr = (mWindowBgMapOffset + (mWindowLinesDrawn / TILE_WIDTH) * BG_TILES_PER_ROW + i);
                     std::cout << "getting tile num from addr " << addr << std::endl;
                uint8_t tile_num = gbc::Ram::Instance()->ReadByte(addr.value());
                //     std::cout << "got tile num " << (int) tile_num << std::endl;
                //  auto til = ReadTileDataBlock(tile_num);
                //      TileData p(til);
                //      PrintTile(p.AsPixelMap());      
                 uint16_t tile_data_start = 0;                           
                if (!mTileDataSelect)
                {
                      tile_data_start = mTileDataSelectOffset + (BYTES_PER_TILE * static_cast<int8_t>(tile_num)) + (((y - *mWy) % TILE_WIDTH) * 2);
                }
                else
                {
                     tile_data_start = mTileDataSelectOffset + (BYTES_PER_TILE * tile_num) + (((y - *mWy) % TILE_WIDTH) * 2);
                }
               
                address16_t d = tile_data_start;
                //   std::cout << "getting tile data from addr " << d << std::endl;
                byte byte1 = gbc::Ram::Instance()->ReadByte(tile_data_start);
                //   std::cout << "byte1: " << byte1 << std::endl;

                byte byte2 = gbc::Ram::Instance()->ReadByte(tile_data_start + 1);
                //   std::cout << "byte2: " << byte2 << std::endl;
                TwoBPP(byte1, byte2, window_buff);
            }
        
           //     for (auto& a : window_buff)
           //     {
           //         std::cout << (int) a;
           //     }
           //     std::cout << std::endl;
                byte win_x = 0;
                for (int i = *mWx - 7; i < LCD_WIDTH; i++)
                {
                    mLcdBuffer.SetPixel(i, y, window_buff[win_x]);
                    win_x++;
                }
                        mWindowLinesDrawn++;
                }

    }

    void Ppu::LcdControlUpdate()
    {
        register8_t lcd_control = register8_t(*mLcdControl, "LCD Control");
        register8_t wy = register8_t(*mWy, "W Y");
        register8_t wx = register8_t(*mWx, "W X");
        register8_t sy = register8_t(*mSy, "S Y");
        register8_t sx = register8_t(*mSx, "S X");
     //   std::cout << "LcdControlUpdate " << lcd_control << std::endl;
     //    std::cout << "LcdControlUpdate " << wy << std::endl;
     //    std::cout << "LcdControlUpdate " << wx << std::endl;
     //    std::cout << "LcdControlUpdate " << sy << std::endl;
     //    std::cout << "LcdControlUpdate " << sx << std::endl;

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
        mTileDataSelectOffset = mTileDataSelect ? 0x8000 : 0x9000;
    }

    void Ppu::DumpBufferDebug()
    {

        for (int y = 0; y < LCD_HEIGHT; y++)
        {
            for (int x = 0; x < LCD_WIDTH; x++)
            {
                std::cout << (int)mLcdBuffer.GetPixel(x, y);
            }
            std::cout << std::endl;
        }
        std::cout << "FramesRendered: " << mFramesRendered << std::endl;
    }

    void Ppu::DrawSpriteAt(int x, int y, SpriteBuffer &sprite_buffer, const register8_t& flags) // 1024 tiles
    {

        int start_x = x;
        int start_y = y;

        int sprite_y = 0;
        int sprite_x = 0;
    
        // janky Y flip
        if (flags.BitAtLSB(6))
        {
            for (int x = 0; x < SPRITE_WIDTH; x++)
            {
                for (int y = 0; y < SPRITE_HEIGHT/2; y++)
                {
                    uint8_t tmp = sprite_buffer[CoordsAsIndex(x, y, 8, 8)];
                    sprite_buffer[CoordsAsIndex(x, y, 8, 8)] = sprite_buffer[CoordsAsIndex(x, SPRITE_HEIGHT - y - 1, 8, 8)];
                    sprite_buffer[CoordsAsIndex(x, SPRITE_HEIGHT - y - 1, 8, 8)]  = tmp;
                }
            }
        }

        // janky X flip
        if (flags.BitAtLSB(5))
        {
            for (int y = 0; y < SPRITE_WIDTH; y++)
            {
                for (int x = 0; x < SPRITE_HEIGHT/2; x++)
                {
                    uint8_t tmp = sprite_buffer[CoordsAsIndex(x, y, 8, 8)];
                    sprite_buffer[CoordsAsIndex(x, y, 8, 8)] = sprite_buffer[CoordsAsIndex(SPRITE_WIDTH - x - 1, y, 8, 8)];
                    sprite_buffer[CoordsAsIndex(SPRITE_WIDTH - x - 1, y, 8, 8)]  = tmp;
                }
            }
        }
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
