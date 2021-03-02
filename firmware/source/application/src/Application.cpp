/********************************************************************************
 * Include 
 ********************************************************************************/

#include "Application.h"

/********************************************************************************
 * User variables
 ********************************************************************************/
Display TFT;
/********************************************************************************
 * Methods class 
 ********************************************************************************/
void Application::Init() {
    Clock::Init();
    Delay::Init();
    Led::Init();
    Button::Init();
    Buzzer::Init(1000);

    TFT.Init();
    TFT.Background(Color::GreenYellow);
    TFT.SetBrightness(80);
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