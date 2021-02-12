/********************************************************************************
 * class        Settings PWM for buzzer                                         *
 *                                                                              *
 * file         Buzzer.h                                                        *
 * author       @RedCommissary                                                  *
 * date         13.02.2021                                                      *
 *                                                                              *
 ********************************************************************************/

#pragma once

/********************************************************************************
 * Include 
 ********************************************************************************/

#include "Pinout.h"

/********************************************************************************
 * Class Buzzer
 ********************************************************************************/
class Buzzer {
    public:
        static void Init (uint16_t frequence) {
            RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;     
            TIM2->PSC = 42-1;
            TIM2->ARR = frequence;
            TIM2->CCR3 = 0;
            TIM2->CCER |= TIM_CCER_CC3E;
            TIM2->BDTR |= TIM_BDTR_MOE;
            TIM2->CCMR2 = TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1;
            TIM2->CR1  |= TIM_CR1_CEN;
        }

        static void SetDuty (uint16_t duty) {
            TIM2->CCR3 = duty;
        }
};