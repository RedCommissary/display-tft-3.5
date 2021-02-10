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
    Periphery::Clock::Init();
    Periphery::Button::Init();
    Periphery::Buzzer::Init(1000);
}

/********************************************************************************
 * Clock system
 ********************************************************************************/
void BSP::Periphery::Clock::Init() {
    RCC->CR |= RCC_CR_HSION;                                    // Enable system for internal clock
    while (!(RCC->CR & RCC_CR_HSIRDY));                         // Waiting flag about enable

    FLASH->ACR |= FLASH_ACR_LATENCY_3WS;                        // Latency for internal flash memory

    RCC->CFGR |= RCC_PLLCFGR_PLLM_4;                            // HSI divider 16
    RCC->CFGR |= RCC_PLLCFGR_PLLN_6 | RCC_PLLCFGR_PLLN_7;       // Mult x192

    RCC->CR |= RCC_CR_PLLON;                                    // Enable PLL system
    while((RCC->CR & RCC_CR_PLLRDY) == 0){}                     // Waiting flag about enable
    RCC->CFGR |= RCC_CFGR_SW_PLL;                               // Select source SYSCLK = PLL
    while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_1) {}      // Waiting flag about enable
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
 * Buzzer
 * PA2 - TIM2 channel 3
 ********************************************************************************/
void BSP::Periphery::Buzzer::Init (uint16_t frequence) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;     
    TIM2->PSC = 42-1;
    TIM2->ARR = frequence;
    TIM2->CCR3 = 0;
    TIM2->CCER |= TIM_CCER_CC3E;
    TIM2->BDTR |= TIM_BDTR_MOE;
    TIM2->CCMR2 = TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1;
    TIM2->CR1  |= TIM_CR1_CEN;
}

void BSP::Periphery::Buzzer::SetDuty (uint16_t duty) {
    TIM2->CCR3 = duty;
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