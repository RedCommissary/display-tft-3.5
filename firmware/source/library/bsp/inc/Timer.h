/********************************************************************************
 * class        Settings timers for periphery                                   *
 *                                                                              *
 * file         Timer.h                                                         *
 * author       @RedCommissary                                                  *
 * date         02.03.2021                                                      *
 *                                                                              *
 ********************************************************************************/

#pragma once

/********************************************************************************
 * Include 
 ********************************************************************************/

#include "Gpio.h"

/********************************************************************************
 * Class Timer
 ********************************************************************************/
class Timer {
    public:
        static void InitTimer2 (uint16_t frequence) {
            Gpio::Init<2>(GPIOA, Gpio::Mode::outputAF, Gpio::Type::PP, Gpio::Speed::medium, Gpio::Pupd::noPull, Gpio::AF::af1);
            RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; 
            TIM2->PSC = 42-1;
            TIM2->ARR = frequence;
            TIM2->CCR3 = 0;
            TIM2->CCER |= TIM_CCER_CC3E;
            TIM2->BDTR |= TIM_BDTR_MOE;
            TIM2->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1;
            TIM2->CR1  |= TIM_CR1_CEN;
        }

        static void InitTimer5 (uint16_t frequence) {
            Gpio::Init<3>(GPIOA, Gpio::Mode::outputAF, Gpio::Type::PP, Gpio::Speed::medium, Gpio::Pupd::noPull, Gpio::AF::af2);
            RCC->APB1ENR |= RCC_APB1ENR_TIM5EN; 
            TIM5->PSC = 42-1;
            TIM5->ARR = frequence;
            TIM5->CCR3 = 0;
            TIM5->CCER |= TIM_CCER_CC4E;
            TIM5->BDTR |= TIM_BDTR_MOE;
            TIM5->CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1;
            TIM5->CR1  |= TIM_CR1_CEN;
        }

        static void SetTimer2 (uint16_t duty) {
            TIM2->CCR3 = duty;
        }

        static void SetTimer5 (uint16_t duty) {
            TIM5->CCR4 = duty;
        }
};