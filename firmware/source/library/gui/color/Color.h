/********************************************************************************
 * class        Collection color for HMI panel solar charger NPPT-2420          *
 *                                                                              *
 * file         Color.h                                                         *
 * author       @RedCommissary                                                  *
 * date         01.03.2021                                                      *
 *                                                                              *
 ********************************************************************************/

#pragma once

/********************************************************************************
 * Include
 ********************************************************************************/

#include <stdint.h>

/********************************************************************************
 * Class with color
 ********************************************************************************/

class Color {
    public:
        static constexpr uint16_t Black = 0x0000;
        static constexpr uint16_t Navy = 0x000F;
        static constexpr uint16_t DarkGreen = 0x03E0;
        static constexpr uint16_t DarkCyan = 0x03EF;
        static constexpr uint16_t Maroon = 0x7800;
        static constexpr uint16_t Purple = 0x780F;
        static constexpr uint16_t Olive = 0x7BE0;
        static constexpr uint16_t LightGrey = 0xC618;
        static constexpr uint16_t DarkGrey = 0x7BEF;
        static constexpr uint16_t Blue = 0x001F;
        static constexpr uint16_t Green = 0x07E0;
        static constexpr uint16_t Cyan = 0x07FF;
        static constexpr uint16_t Red = 0xF800;
        static constexpr uint16_t Magenta = 0xF81F;
        static constexpr uint16_t Yellow = 0xFFE0;
        static constexpr uint16_t White = 0xFFFF;
        static constexpr uint16_t Oragne = 0xFD20;
        static constexpr uint16_t GreenYellow = 0xAFE5;
        static constexpr uint16_t Pink = 0xF81F;
};