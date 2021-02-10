/********************************************************************************
 * Include 
 ********************************************************************************/

#include "Periphery.h"

/********************************************************************************
 * Methods Periphery
 ********************************************************************************/

/******************************************
 * Global board init
 ******************************************/
void BSP::Periphery::Init() {
    Pinout::Init();
    Periphery::Button::Init();
}

/******************************************
 * LED control
 ******************************************/
void BSP::Periphery::Led::Yellow (Status status) {
    switch (status) {
    case Led::Status::on:
        Gpio::Set<4>(GPIOB);
        break;
    case Led::Status::off:
        Gpio::Reset<4>(GPIOB);
        break;
    case Led::Status::toggle:
        Gpio::Toggle<4>(GPIOB);
        break;
    default:
        Gpio::Reset<4>(GPIOB);
        break;
    }
}

void BSP::Periphery::Led::Green (Status status) {
    switch (status) {
    case Led::Status::on:
        Gpio::Set<5>(GPIOB);
        break;
    case Led::Status::off:
        Gpio::Reset<5>(GPIOB);
        break;
    case Led::Status::toggle:
        Gpio::Toggle<5>(GPIOB);
        break;
    default:
        Gpio::Reset<5>(GPIOB);
        break;
    }
}

/******************************************
 * Button settings
 * 
 * PH0  - DOWN
 * PH1  - UP
 * PC13 - RIGHT
 * PC14 - LEFT
 * PC15 - OK
 ******************************************/
void BSP::Periphery::Button::Init(){
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

void BSP::Periphery::Button::ResetFlag() {
    EXTI->PR |= EXTI_PR_PR0;
    EXTI->PR |= EXTI_PR_PR1;
    EXTI->PR |= EXTI_PR_PR13;
    EXTI->PR |= EXTI_PR_PR14;
    EXTI->PR |= EXTI_PR_PR15;
}

/********************************************************************************
 * Logic for button
 ********************************************************************************/
void sExti::line0Handler() {
    BSP::Periphery::Button::ResetFlag();
    BSP::Periphery::Led::Green(BSP::Periphery::Led::Status::toggle);        
}

void sExti::line1Handler() {
    BSP::Periphery::Button::ResetFlag();
    BSP::Periphery::Led::Green(BSP::Periphery::Led::Status::toggle);        
}

void sExti::line10Handler() {
    if (EXTI->PR & EXTI_PR_PR13) {
        BSP::Periphery::Button::ResetFlag();
        BSP::Periphery::Led::Green(BSP::Periphery::Led::Status::toggle);
    }
    if (EXTI->PR & EXTI_PR_PR14) {
        BSP::Periphery::Button::ResetFlag();
        BSP::Periphery::Led::Yellow(BSP::Periphery::Led::Status::toggle);
    }
    if (EXTI->PR & EXTI_PR_PR15) {
        BSP::Periphery::Button::ResetFlag();
        BSP::Periphery::Led::Yellow(BSP::Periphery::Led::Status::toggle);
    }        
}