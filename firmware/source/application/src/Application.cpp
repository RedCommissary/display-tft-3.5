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
/*
    TFT::Init();
    TFT::DrawPixel(50, 50, 0xF800);
    TFT::DrawPixel(51, 50, 0xF800);
    TFT::DrawPixel(52, 50, 0xF800);
    TFT::DrawPixel(53, 50, 0xF800);
    TFT::DrawPixel(54, 50, 0xF800);
    TFT::DrawPixel(55, 50, 0xF800);
    TFT::DrawPixel(56, 50, 0xF800);
    TFT::DrawPixel(57, 50, 0xF800);
    TFT::DrawPixel(58, 50, 0xF800);
    TFT::DrawPixel(59, 50, 0xF800);
    TFT::DrawPixel(60, 50, 0xF800);
    TFT::DrawPixel(61, 50, 0xF800);
    TFT::DrawPixel(62, 50, 0xF800);
    TFT::DrawPixel(63, 50, 0xF800);
    TFT::DrawLine (100, 100, 200, 0xF800);
    TFT::DrawFill (0, 0, 40, 40, 0xF800);
    TFT::DrawPixel (120, 120, 0x07E0);
    TFT::DrawPixel (121, 120, 0x07E0);
    TFT::DrawPixel (122, 120, 0x07E0);
    TFT::DrawPixel (123, 120, 0x07E0);
    TFT::DrawPixel (124, 120, 0x07E0);
*/
    Gpio::Set<3>(GPIOA);    // Led TFT enable
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