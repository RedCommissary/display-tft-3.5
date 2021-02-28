/********************************************************************************
 * class        Low level driver for TFT with ILI9488 controller                *
 *                                                                              *
 * file         ili9488.h                                                       *
 * author       @RedCommissary                                                  *
 * date         12.02.2021                                                      *
 *                                                                              *
 ********************************************************************************/

#pragma once

/********************************************************************************
 * Include 
 ********************************************************************************/

#include "Delay.h"
#include "Spi.h"

/********************************************************************************
 * Class TFT ILI9488
 ********************************************************************************/
class TFT {
    public:
        enum class Color:int {
            Black = 0x0000,
            Navy = 0x000F,
            DarkGreen = 0x03E0,
            DarkCyan = 0x03EF,
            Maroon = 0x7800,
            Purple = 0x780F,
            Olive = 0x7BE0,
            LightGrey = 0xC618,
            DarkGrey = 0x7BEF,
            Blue = 0x001F,
            Green = 0x07E0,
            Cyan = 0x07FF,
            Red = 0xF800,
            Magenta = 0xF81F,
            Yellow = 0xFFE0,
            White = 0xFFFF,
            Oragne = 0xFD20,
            GreenYellow = 0xAFE5,
            Pink = 0xF81F
        };
        enum class Mode {
            Data, Command
        };
        enum class Command:int {
            NOP = 0x00,
            SWRESET = 0x01,
            RDDID = 0x04,
            RDDST = 0x09,
            SLPIN = 0x10,
            SLPOUT = 0x11,
            PTLON = 0x12,
            NORON = 0x13,
            RDMODE = 0x0A,
            RDMADCTL = 0x0B,
            RDPIXFMT = 0x0C,
            RDIMGFMT = 0x0D,
            RDSELFDIAG = 0x0F,
            INVOFF = 0x20,
            INVON = 0x21,
            GAMMASET = 0x26,
            DISPOFF = 0x28,
            DISPON = 0x29,
            CASET = 0x2A,
            PASET = 0x2B,
            RAMWR = 0x2C,
            RAMRD = 0x2E,
            PTLAR = 0x30,
            MADCTL = 0x36,
            PIXFMT = 0x3A,
            INTFMODE = 0xB0,
            FRMCTR1 = 0xB1,
            FRMCTR2 = 0xB2,
            FRMCTR3 = 0xB3,
            INVCTR = 0xB4,
            DFUNCTR = 0xB6,
            PWCTR1 = 0xC0,
            PWCTR2 = 0xC1,
            PWCTR3 = 0xC2,
            PWCTR4 = 0xC3,
            PWCTR5 = 0xC4,
            VMCTR1 = 0xC5,
            VMCTR2 = 0xC7,
            RDID1 = 0xDA,
            RDID2 = 0xDB,
            RDID3 = 0xDC,
            RDID4 = 0xDD,
            GMCTRP1 = 0xE0,
            GMCTRN1 = 0xE1,
            IMGFUNC = 0xE9,
            ADJCTRL = 0xF7
        };  
         
    public:
        static void Init();
        static void Reset();
        static void LedEnable (bool status);
        static void SetMode (Mode mode);
        static void SendData (uint8_t data);
        static void SendDataBuffer (uint8_t* buffer, uint16_t size);
        static void SendCommand(uint8_t command);
        static void inline SendCommand(TFT::Command command) {
            SendCommand(static_cast<uint8_t>(command));
        }
        static void SetAddressWindow (uint16_t xStart, uint16_t yStart, uint16_t xEnd, uint16_t yEnd);
        static void WriteColor (Color color);
        static void DrawPixel (uint16_t x, uint16_t y, Color color);
        static void DrawLine (uint16_t xStart, uint16_t yStart, uint16_t length, Color color);
        static void DrawFill (uint16_t xStart, uint16_t yStart, uint16_t xEnd, uint16_t yEnd, Color color);
 
};