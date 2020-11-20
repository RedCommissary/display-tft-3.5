#include "ili9488.h"
extern SPI_HandleTypeDef hspi1;

void Reset_Active() {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
}

void Reset_Idle() {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
}

void DataDisplay() {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
}

void CommandDisplay() {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
}

void CS_Active() {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
}

void CS_Idle() {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
}

void TFT_Reset() {
    Reset_Active();
    HAL_Delay(10);
    Reset_Idle();   
}

void TFT_SendData (uint8_t data) {
	CS_Active();
    DataDisplay();
    HAL_SPI_Transmit(&hspi1, &data, 1, 5000);
	CS_Idle();
}

void TFT_WriteData (uint8_t* buffer, size_t buffer_size) {
	CS_Active();
    DataDisplay();

    while (buffer_size > 0) {
        uint16_t chunk_size = buffer_size > 32768 ? 32768 : buffer_size;
        HAL_SPI_Transmit(&hspi1, buffer, chunk_size, HAL_MAX_DELAY);
        buffer += chunk_size;
        buffer_size -= chunk_size;
    }

	CS_Idle();
}

void TFT_SendCommand (uint8_t command) {
	CS_Active();
    CommandDisplay();
    HAL_SPI_Transmit(&hspi1, &command, 1, 5000);
	CS_Idle();
}

void TFT_Init() {
    CS_Active();
    TFT_Reset();

    // Software reset
    TFT_SendCommand(ILI9488_SWRESET);
    HAL_Delay(1000);

    TFT_SendCommand(0xE0);
	TFT_SendData(0x00);
	TFT_SendData(0x03);
	TFT_SendData(0x09);
	TFT_SendData(0x08);
	TFT_SendData(0x16);
	TFT_SendData(0x0A);
	TFT_SendData(0x3F);
	TFT_SendData(0x78);
	TFT_SendData(0x4C);
	TFT_SendData(0x09);
	TFT_SendData(0x0A);
	TFT_SendData(0x08);
	TFT_SendData(0x16);
	TFT_SendData(0x1A);
	TFT_SendData(0x0F);

	TFT_SendCommand(0xE1);
	TFT_SendData(0x00);
	TFT_SendData(0x16);
	TFT_SendData(0x19);
	TFT_SendData(0x03);
	TFT_SendData(0x0F);
	TFT_SendData(0x05);
	TFT_SendData(0x32);
	TFT_SendData(0x45);
	TFT_SendData(0x46);
	TFT_SendData(0x04);
	TFT_SendData(0x0E);
	TFT_SendData(0x0D);
	TFT_SendData(0x35);
	TFT_SendData(0x37);
	TFT_SendData(0x0F);

	TFT_SendCommand(0xC0);      //Power Control 1
	TFT_SendData(0x17);    //Vreg1out
	TFT_SendData(0x15);    //Verg2out

	TFT_SendCommand(0xC1);      //Power Control 2
	TFT_SendData(0x41);    //VGH,VGL

	TFT_SendCommand(0xC5);      //Power Control 3
	TFT_SendData(0x00);
	TFT_SendData(0x12);    //Vcom
	TFT_SendData(0x80);

	TFT_SendCommand(0x36);      //Memory Access
	TFT_SendData(0xE8);

	TFT_SendCommand(0x3A);      // Interface Pixel Format
	TFT_SendData(0x66); 	  //18 bit

	TFT_SendCommand(0xB0);      // Interface Mode Control
	TFT_SendData(0x80);     			 //SDO NOT USE

	TFT_SendCommand(0xB1);      //Frame rate
	TFT_SendData(0xA0);    //60Hz

	TFT_SendCommand(0xB4);      //Display Inversion Control
	TFT_SendData(0x02);    //2-dot

	TFT_SendCommand(0xB6);      //Display Function Control  RGB/MCU Interface Control

	TFT_SendData(0x02);    //MCU
	TFT_SendData(0x02);    //Source,Gate scan dieection

	TFT_SendCommand(0xE9);      // Set Image Functio
	TFT_SendData(0x00);    // Disable 24 bit data

	TFT_SendCommand(0xF7);      // Adjust Control
	TFT_SendData(0xA9);
	TFT_SendData(0x51);
	TFT_SendData(0x2C);
	TFT_SendData(0x82);    // D7 stream, loose

    TFT_SendCommand(ILI9488_SLPOUT);    //Exit Sleep
    HAL_Delay(120);
    TFT_SendCommand(ILI9488_DISPON);    //Display on
	
	CS_Idle();
}

void SetAddrWindow (uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    TFT_SendCommand(ILI9488_CASET); // Column addr set
    TFT_SendData(x0 >> 8);
    TFT_SendData(x0 & 0xFF);     // XSTART
    TFT_SendData(x1 >> 8);
    TFT_SendData(x1 & 0xFF);     // XEND

    TFT_SendCommand(ILI9488_PASET); // Row addr set
    TFT_SendData(y0>>8);
    TFT_SendData(y0 &0xff);     // YSTART
    TFT_SendData(y1>>8);
    TFT_SendData(y1 &0xff);     // YEND

    TFT_SendCommand(ILI9488_RAMWR); // write to RAM
}

void Write16BitColor (uint16_t color) {
	uint8_t r = (color & 0xF800) >> 11;
	uint8_t g = (color & 0x07E0) >> 5;
	uint8_t b = color & 0x001F;

	r = (r * 255) / 31;
	g = (g * 255) / 63;
	b = (b * 255) / 31;

	TFT_SendData(r);
	TFT_SendData(g);
	TFT_SendData(b);
}

void DrawPixel (int16_t x, int16_t y, uint16_t color) {

	if((x < 0) ||(x >= 480) || (y < 0) || (y >= 320)) return;
	SetAddrWindow(x,y,x+1,y+1);
	Write16BitColor(color);
}

void DrawFastVLine (int16_t x, int16_t y, int16_t h, uint16_t color) {

	if((y+h-1) >= 480) {h = 480-y;}

	SetAddrWindow(x, y, x, y+h-1);

	while (h--) {
		Write16BitColor(color);
	}
}