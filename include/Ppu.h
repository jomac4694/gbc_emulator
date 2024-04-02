#ifndef PPU_H
#define PPU_H
#include <array>
#include "Register.h"
#include "DisplayBuffer.h"
#include "Memory.h"
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
constexpr static uint16_t LCD_WIDTH = 160;
constexpr static uint16_t LCD_HEIGHT = 144;

// Buffer sizes
constexpr static uint16_t TILE_BUFFER_SIZE = TILE_WIDTH * TILE_HEIGHT;
constexpr static uint32_t DISPLAY_LAYER_SIZE = DISPLAY_LAYER_WIDTH * DISPLAY_LAYER_HEIGHT;
constexpr static uint16_t SPRITE_BUFFER_SIZE = SPRITE_WIDTH * SPRITE_HEIGHT;
constexpr static uint16_t TALL_SPRITE_BUFFER_SIZE = TALL_SPRITE_WIDTH * TALL_SPRITE_HEIGHT;
constexpr static uint16_t LCD_DISPLAY_SIZE = LCD_WIDTH * LCD_HEIGHT;

constexpr static uint16_t BG_TILES_PER_ROW = 32;
constexpr static uint16_t LCD_TILES_PER_ROW = 20;
constexpr static uint16_t LCD_TILES_PER_COL = 18;
constexpr static uint16_t BYTES_PER_TILE = 16;
    typedef std::array<byte, SPRITE_BUFFER_SIZE> SpriteBuffer;

struct Sprite
{
    uint8_t x_pos;
    uint8_t y_pos;
    uint8_t tile_index;
    uint8_t flags;
};
  enum PpuMode
  {
    H_BLANK,
    V_BLANK,
    OAM_SCAN,
    DRAW
  };

  class Ppu
  {
    public:
      void DumpBufferDebug();
      Ppu();
      // perform a single ppu tick
      void Tick(int cycles);
      void RegisterDrawCallback(std::function<void(const DisplayBuffer&)> func);
      int mFramesRendered{0};
    private:
      void ReadBgTileLine(const byte y);
      
      void ReadWindowTileLine(const byte y);

      // do mode stuff functions
      void ModeOAMScan(register8_t& lcd_status);
      void ModeHBlank(register8_t& lcd_status);
      void ModeDraw();
      void ModeVBlank(register8_t& lcd_status);

      // Read and draw the sprite at sprite_index
      void DrawSprite(uint16_t sprite_index); 

      void LcdControlUpdate();

      byte* mLcdStatus; // I think the ppu controls this
      byte* mLcdControl; // I think the cpu controls this
      byte* mLyc;
      byte* mLy;

      byte* mSx;
      byte* mSy;

      byte* mWx;
      byte* mWy;

      byte mCurrentScanline{0};

      PpuMode mCurrMode{PpuMode::OAM_SCAN};

      // the main LCD display buffer (160x144 pixels 20x18 tiles)
      DisplayBuffer mLcdBuffer;

      // Status bits, i dont think all are needed
      bool mLcdEnabled{false};
      bool mWindowMapSelect{false};
      bool mWindowEnable{false};
      bool mTileDataSelect{false};
      bool mBgTileMapSelect{false};
      bool mSpriteSizeFlag{false};
      bool mSpriteEnable{false};
      bool mBgWindowEnable{false};

      // offsets
      uint16_t mWindowBgMapOffset;
      uint16_t mBgTileMapOffset;
      uint16_t mTileDataSelectOffset;

      // should draw the current frame to the actual GUI
      std::function<void(const DisplayBuffer&)> mDrawCallback;
      void DrawSpriteAt(int x, int y,  SpriteBuffer& sprite_buffer, const register8_t& flags);

      int GetModeCycles();
      int mCycles{0};
      
      int mWindowLinesDrawn{0};

      void ScanSprites();
      std::vector<Sprite> mSpriteLineBuffer;

  };

}
#endif