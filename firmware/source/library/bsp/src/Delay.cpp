/********************************************************************************
 * Include 
 ********************************************************************************/

#include "Delay.h"

/********************************************************************************
 * Used variable
 ********************************************************************************/

volatile uint32_t Delay::delayCounter = 0;

/********************************************************************************
 * Methods for delay class
 ********************************************************************************/
void Delay::Init() {
    SysTick->LOAD = 84000000UL/1000 - 1;    // Set 1 tick = 1 ms
	SysTick->VAL = 84000000UL/1000 - 1;     // Set value
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk  | SysTick_CTRL_ENABLE_Msk;
}

void Delay::Set (uint32_t milliseconds) {
    delayCounter = milliseconds;
	while (delayCounter != 0);
}

void sSysTick::handler() {
    Delay::delayCounter--;
}