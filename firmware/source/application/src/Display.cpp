/********************************************************************************
 * Include 
 ********************************************************************************/

#include "Display.h"

/********************************************************************************
 * Methods class 
 ********************************************************************************/
void Display::Init() {
    ILI9488::Init();
}

void Display::SetBrightness(uint16_t level){
    ILI9488::SetBrightness(level);
}

void Display::DrawPixel(uint16_t x, uint16_t y, uint16_t color){
    ILI9488::DrawPixel(x, y, color);
}

void Display::DrawLine(uint16_t xStart, uint16_t yStart, uint16_t length, uint16_t color){
    ILI9488::DrawLine(xStart, yStart, length, color);
}

void Display::DrawFill(uint16_t xStart, uint16_t yStart, uint16_t xEnd, uint16_t yEnd, uint16_t color){
    ILI9488::DrawFill(xStart, yStart, xEnd, yEnd, color);
}

void Display::Background (uint16_t color){
    ILI9488::DrawFill(0, 0, width, height, color);
}

uint32_t Display::DrawChar(uint32_t xPosition, uint32_t yPosition, char symbol, const typeFont &font, uint16_t colorText, uint16_t colorBackground){
	uint16_t width = (font.chars + symbol - 32)->image->widthChar;
	uint16_t height = (font.chars + symbol - 32)->image->heightChar;
    const uint8_t* chars = font.chars[symbol - 32].image->buffChar;

    volatile uint16_t i = 0;
    for (uint32_t line = 0; line < height; line++) {
        for (uint32_t pixel = 0; pixel < width; pixel++) {
            uint16_t color = (chars[i++] == 0x00) ? colorText : colorBackground;
            DrawPixel(xPosition+pixel, yPosition+line, color);
        }
    }

    return (xPosition + width);
}

void Display::DrawString(uint32_t xPosition, uint32_t yPosition, char *str, const typeFont &font, uint16_t colorText, uint16_t colorBackground){

    while(*str){
		xPosition = DrawChar(xPosition, yPosition, *str++, font, colorText, colorBackground);
    }
}

// drawString(10, 10, "14.268.140", &SevenSegment_low, YELLOW);
//        return xPos+width;

/*    
    uint16_t width = 5;
    uint16_t height = 10;

    bool buffer[height * width] = {
        1, 1, 1, 1, 1,
        1, 1, 0, 1, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 1, 0, 1, 1,
        1, 1, 1, 1, 1
    }; 

    uint16_t xStart = 100;
    uint16_t yStart = 100; 

    uint16_t colorPixel = Color::Red;
    uint16_t colorBackground = Color::White;       

    volatile uint16_t counter = 0;

    for (uint16_t line = 0; line < height; line++) {
        for (uint16_t pixel = 0; pixel < width; pixel++) {
                if (buffer[counter]) {
                    DrawPixel(xStart+pixel, yStart+line, colorPixel);
                } else {
                    DrawPixel(xStart+pixel, yStart+line, colorBackground);
                } 
                counter++;
        }
    }
*/