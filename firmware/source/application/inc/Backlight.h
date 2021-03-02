/********************************************************************************
 * class        Control of backlight for TFT display                            *
 *                                                                              *
 * file         Backlight.h                                                     *
 * author       @RedCommissary                                                  *
 * date         02.03.2021                                                      *
 *                                                                              *
 ********************************************************************************/

#pragma once

/********************************************************************************
 * Include 
 ********************************************************************************/

#include "Timer.h"

/********************************************************************************
 * Class Backlight
 * 
 * PA3  - TIM 5 channel 4
 ********************************************************************************/
class Backlight {
    public:
        static void Init() {
            Timer::InitTimer5(100);
        }
        static void SetBrightness (uint16_t level) {
            Timer::SetTimer5(level);
        }
        static void Disable() {
            Timer::SetTimer5(0);
        }
};