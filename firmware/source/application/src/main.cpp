#include "stm32f4xx.h"
#include "Gpio.h"

int main() {
    Gpio::Init<4,5>(GPIOB, Gpio::Mode::output);
    Gpio::Set<4,5>(GPIOB);
    while(1){}
}