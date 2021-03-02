/********************************************************************************
 * Include 
 ********************************************************************************/

#include "Display.h"

/********************************************************************************
 * Methods class 
 ********************************************************************************/
void Display::Init() {
    ILI9488::Init();
    Backlight::Init();
}

void Display::SetBrightness(uint16_t level){
    Backlight::SetBrightness(level);
}

void Display::BacklightDisable(){
    Backlight::Disable();
}

void Display::DrawPixel(uint16_t x, uint16_t y, uint16_t color){
    ILI9488::DrawPixel(x, y, color);
}

void Display::DrawLine (uint16_t xStart, uint16_t yStart, uint16_t length, uint16_t color){
    ILI9488::DrawLine(xStart, yStart, length, color);
}

void Display::DrawFill (uint16_t xStart, uint16_t yStart, uint16_t xEnd, uint16_t yEnd, uint16_t color){
    ILI9488::DrawFill(xStart, yStart, xEnd, yEnd, color);
}

void Display::Background (uint16_t color){
    ILI9488::DrawFill(0, 0, width, height, color);
}