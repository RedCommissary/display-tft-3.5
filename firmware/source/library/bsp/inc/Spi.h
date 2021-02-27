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
            RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

            SPI1->CR1 |= SPI_CR1_BR_0 | SPI_CR1_BR_1;   // Baud rate = Fpclk/16
            SPI1->CR1 &= ~SPI_CR1_DFF;                  // 8 bit data
            SPI1->CR1 &= ~SPI_CR1_BIDIMODE;             // 2-line data mode
            SPI1->CR1 &= ~SPI_CR1_CPOL;                 // Polarity cls signal CPOL = 0;
            SPI1->CR1 &= ~SPI_CR1_CPHA;                 // Phase cls signal    CPHA = 0;
            SPI1->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI;     // Software slave management & Internal slave select
            SPI1->CR1 &= ~SPI_CR1_LSBFIRST;             // MSB will be first
            SPI1->CR1 |= SPI_CR1_MSTR;                  // Mode Master
            SPI1->CR1 |= SPI_CR1_SPE;                   // Enable SPI1
        }

        static void ChipSelect (bool status) {
            if (status) {Gpio::Reset<1>(GPIOB);}
            if (status) {Gpio::Set<1>(GPIOB);}
        }

        static void SendByte (uint8_t data) {
            while(!(SPI1->SR & SPI_SR_TXE));
            ChipSelect(true);
            SPI1->DR = data;
            ChipSelect(false);
        }

        static void SendArray (uint8_t *buffer, uint16_t size) {
            ChipSelect(true);

            uint16_t txDataNeed = size;
            uint8_t *txDataPointer = buffer;
            uint16_t txDataCounter = 0;

            for (; txDataCounter < txDataNeed; txDataCounter++) {
                while(!(SPI1->SR & SPI_SR_TXE));
                SPI1->DR = *txDataPointer;
                txDataPointer++;
            }
            ChipSelect(false);
        }
};