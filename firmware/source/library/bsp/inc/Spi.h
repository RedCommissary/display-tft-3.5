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

            SPI1->CR1 = 0;
            SPI1->CR1 |= SPI_CR1_MSTR;                  // Mode Master 
            SPI1->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI;     // Software slave management & Internal slave select
            SPI1->CR1 |= SPI_CR1_SPE;                   // Enable SPI1
        }

        static void ChipSelectActive (bool status) {
            if (status)
                Gpio::Reset<1>(GPIOB);
                else
                Gpio::Set<1>(GPIOB);
        }

        static void SendByte (uint8_t data) {
            ChipSelectActive(true);
            while(!(SPI1->SR & SPI_SR_TXE));
            SPI1->DR = data;
            while(!(SPI1->SR & SPI_SR_RXNE));
            while(SPI1->SR & SPI_SR_BSY);
            ChipSelectActive(false);
        }

        static void SendArray (uint8_t *buffer, uint16_t size) {
            ChipSelectActive(true);

            uint16_t txDataNeed = size;
            uint8_t *txDataPointer = buffer;
            uint16_t txDataCounter = 0;

            for (; txDataCounter < txDataNeed; txDataCounter++) {
                while(!(SPI1->SR & SPI_SR_TXE));
                SPI1->DR = *txDataPointer;
                while(!(SPI1->SR & SPI_SR_RXNE));
                txDataPointer++;
            }
            while(SPI1->SR & SPI_SR_BSY);
            ChipSelectActive(false);
        }
};