/********************************************************************************
 * class        Settings SPI for MCU                                            *
 *                                                                              *
 * file         Spi.h                                                           *
 * author       @RedCommissary                                                  *
 * date         13.02.2021                                                      *
 *                                                                              *
 ********************************************************************************/

#pragma once

/********************************************************************************
 * Include 
 ********************************************************************************/

#include "Gpio.h"

/********************************************************************************
 * Class SPI
 ********************************************************************************/
class Spi {
    public:
        static void Init() {

        }

        static void ChipSelect (bool status) {
            if (status) {Gpio::Reset<1>(GPIOB);}
            if (!status) {Gpio::Set<1>(GPIOB);}
        }

        static void SendByte (uint8_t data) {

        }

        static void SendArray (uint8_t* data, uint16_t size) {

        }
};