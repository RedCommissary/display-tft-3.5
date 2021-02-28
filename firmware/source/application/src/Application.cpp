/********************************************************************************
 * Include 
 ********************************************************************************/

#include "Application.h"

/********************************************************************************
 * User variables
 ********************************************************************************/

/********************************************************************************
 * Methods class 
 ********************************************************************************/
void Application::Init() {
    TFT::Init();
    TFT::LedEnable(true);
    TFT::DrawFill(0, 0, 480, 320, TFT::Color::Purple);
}

/********************************************************************************
 * Interrupt
 ********************************************************************************/

/**************************************
 * Logic for button
 *************************************/
void sExti::line0Handler() {
    Button::ResetFlag();
    Led::Green(Led::Status::toggle);  
}

void sExti::line1Handler() {
    Button::ResetFlag();
    Led::Yellow(Led::Status::toggle);        
}

void sExti::line10Handler() {
    if (EXTI->PR & EXTI_PR_PR13) {
        Button::ResetFlag();
        Led::Yellow(Led::Status::toggle);
    }
    if (EXTI->PR & EXTI_PR_PR14) {
        Button::ResetFlag();
        Led::Yellow(Led::Status::toggle);
    }
    if (EXTI->PR & EXTI_PR_PR15) {
        Button::ResetFlag();
        Led::Yellow(Led::Status::toggle);
    }        
}