/********************************************************************************
 * Include 
 ********************************************************************************/

#include "Pinout.h"

/********************************************************************************
 * Methods class
 ********************************************************************************/

void Pinout::Init() {
/******************************************
 * LED indicator
 ******************************************/
    Gpio::Init<4,5>(GPIOB, Gpio::Mode::output);

/******************************************
 * External button
 ******************************************/
    Gpio::Init<0,1>(GPIOH, Gpio::Mode::input);
    Gpio::Init<13,14,15>(GPIOC, Gpio::Mode::input);

/******************************************
 * PWM buzzer. TIM2 channel 3
 ******************************************/
    Gpio::Init<2>(GPIOA, Gpio::Mode::outputAF, Gpio::Type::PP, Gpio::Speed::medium, Gpio::Pupd::noPull, Gpio::AF::af1);

/******************************************
 * PWM for LED TFT display. TIM5 channel 4
 ******************************************/
    Gpio::Init<3>(GPIOA, Gpio::Mode::outputAF, Gpio::Type::PP, Gpio::Speed::medium, Gpio::Pupd::noPull, Gpio::AF::af2);

/******************************************
 * TFT display. SPI + IO
 ******************************************/
    Gpio::Init<5,6,7>(GPIOA, Gpio::Mode::outputAF, Gpio::Type::PP, Gpio::Speed::medium, Gpio::Pupd::noPull, Gpio::AF::af5);
    Gpio::Init<0,1>(GPIOB, Gpio::Mode::output);
    Gpio::Init<3,4>(GPIOA, Gpio::Mode::output);

    Gpio::Set<1>(GPIOB);

/******************************************
 * USART1
 ******************************************/
    Gpio::Init<6>(GPIOB, Gpio::Mode::outputAF, Gpio::Type::PP, Gpio::Speed::medium, Gpio::Pupd::noPull, Gpio::AF::af7);
    Gpio::Init<7>(GPIOB, Gpio::Mode::input, Gpio::Type::PP, Gpio::Speed::medium, Gpio::Pupd::pullUp, Gpio::AF::af7);
};