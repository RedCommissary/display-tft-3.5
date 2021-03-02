/********************************************************************************
 * class        Settings external button of keyboard                            *
 *                                                                              *
 * file         Button.h                                                       *
 * author       @RedCommissary                                                  *
 * date         12.02.2021                                                      *
 *                                                                              *
 ********************************************************************************/

#pragma once

/********************************************************************************
 * Include 
 ********************************************************************************/

#include "stm32f4xx.h"
#include "Gpio.h"

/********************************************************************************
 * Class Button
 * 
 * PH0  - DOWN
 * PH1  - UP
 * PC13 - RIGHT
 * PC14 - LEFT
 * PC15 - OK
 ********************************************************************************/
class Button {
    public:
        static void Init() {
            Gpio::Init<0,1>(GPIOH, Gpio::Mode::input);
            Gpio::Init<13,14,15>(GPIOC, Gpio::Mode::input);

            RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

            SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PH;  // Connect PH0 with EXTI
            EXTI->FTSR |= EXTI_FTSR_TR0;                   // Generation interrupt for falling
            EXTI->IMR  |= EXTI_IMR_MR0;                    // Enable interrupt line

            SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI1_PH;  // Connect PH1 with EXTI
            EXTI->FTSR |= EXTI_FTSR_TR1;                   // Generation interrupt for falling
            EXTI->IMR  |= EXTI_IMR_MR1;                    // Enable interrupt line

            SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;  // Connect PC13 with EXTI
            EXTI->FTSR |= EXTI_FTSR_TR13;                   // Generation interrupt for falling
            EXTI->IMR  |= EXTI_IMR_MR13;                    // Enable interrupt line

            SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI14_PC;  // Connect PC14 with EXTI
            EXTI->FTSR |= EXTI_FTSR_TR14;                   // Generation interrupt for falling
            EXTI->IMR  |= EXTI_IMR_MR14;                    // Enable interrupt line

            SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI15_PC;  // Connect PC15 with EXTI
            EXTI->FTSR |= EXTI_FTSR_TR15;                   // Generation interrupt for falling
            EXTI->IMR  |= EXTI_IMR_MR15;                    // Enable interrupt line

            NVIC_EnableIRQ(EXTI0_IRQn); 
            NVIC_EnableIRQ(EXTI1_IRQn); 
            NVIC_EnableIRQ(EXTI15_10_IRQn); 
        }

        static void ResetFlag() {
            EXTI->PR |= EXTI_PR_PR0;
            EXTI->PR |= EXTI_PR_PR1;
            EXTI->PR |= EXTI_PR_PR13;
            EXTI->PR |= EXTI_PR_PR14;
            EXTI->PR |= EXTI_PR_PR15;
        }
};