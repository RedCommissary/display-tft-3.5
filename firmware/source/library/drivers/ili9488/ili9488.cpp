/********************************************************************************
 * Include 
 ********************************************************************************/

#include "ili9488.h"

/********************************************************************************
 * Method TFT ILI9488
 * 
 * Use - SPI1 (Master)
 * PB0 - Command or data
 * PA4 - Reset
 ********************************************************************************/
void ILI9488::InitPort() {
    Gpio::Init<0>(GPIOB, Gpio::Mode::output, Gpio::Type::PP);
    Gpio::Init<3,4>(GPIOA, Gpio::Mode::output, Gpio::Type::PP);
}

void ILI9488::LedEnable (bool status) {
    if (status) {Gpio::Set<3>(GPIOA);}
    if (!status) {Gpio::Reset<3>(GPIOA);}
}

void ILI9488::Reset() {
    Gpio::Reset<4>(GPIOA);
    Delay::Set(10);
    Gpio::Set<4>(GPIOA);
}

void ILI9488::SetMode (Mode mode) {
    if (mode == Mode::Data) {Gpio::Set<0>(GPIOB);}
    if (mode == Mode::Command) {Gpio::Reset<0>(GPIOB);}
}

void ILI9488::SendCommand (uint8_t command) {
    SetMode(Mode::Command);
    Spi::SendByte(command);
}

void ILI9488::SendData (uint8_t data) {
    SetMode(Mode::Data);
    Spi::SendByte(data);
}

void ILI9488::SendDataBuffer (uint8_t* buffer, uint16_t size) {
    SetMode(Mode::Data);
    Spi::SendArray(buffer, size);
}

void ILI9488::Init() {
    InitPort();
    Reset();

    SendCommand(Command::SWRESET);
    Delay::Set(1000);

    SendCommand(Command::GMCTRP1);
    SendData(0x00);
    SendData(0x03);
    SendData(0x09);
    SendData(0x08);
    SendData(0x16);
    SendData(0x0A);
    SendData(0x3F);
    SendData(0x78);
    SendData(0x4C);
    SendData(0x09);
    SendData(0x0A);
    SendData(0x08);
    SendData(0x16);
    SendData(0x1A);
    SendData(0x0F);

    SendCommand(Command::GMCTRN1);
    SendData(0x00);
    SendData(0x16);
    SendData(0x19);
    SendData(0x03);
    SendData(0x0F);
    SendData(0x05);
    SendData(0x32);
    SendData(0x45);
    SendData(0x46);
    SendData(0x04);
    SendData(0x0E);
    SendData(0x0D);
    SendData(0x35);
    SendData(0x37);
    SendData(0x0F);

    SendCommand(Command::PWCTR1);
    SendData(0x17);
    SendData(0x15);

    SendCommand(Command::PWCTR2);
    SendData(0x41);

    SendCommand(Command::VMCTR1);
    SendData(0x00);
    SendData(0x12);
    SendData(0x80);

    SendCommand(Command::MADCTL);
    SendData(0xE8);

    SendCommand(Command::PIXFMT);
    SendData(0x66);

    SendCommand(Command::INTFMODE);
    SendData(0x80);

    SendCommand(Command::FRMCTR1);
    SendData(0xA0);

    SendCommand(Command::INVCTR);   
    SendData(0x02);

    SendCommand(Command::DFUNCTR); 
    SendData(0x02);
    SendData(0x02);

    SendCommand(Command::IMGFUNC); 
    SendData(0x00);

    SendCommand(Command::ADJCTRL); 
    SendData(0xA9);
    SendData(0x51);
    SendData(0x2C);
    SendData(0x82);

    SendCommand(Command::SLPOUT);
    Delay::Set(120);
    SendCommand(Command::DISPON);
}

void ILI9488::SetAddressWindow (uint16_t xStart, uint16_t yStart, uint16_t xEnd, uint16_t yEnd) {
    SendCommand(Command::CASET);    // Column address set
    SendData(xStart >> 8);
    SendData(xStart & 0xFF);
    SendData(xEnd >> 8);
    SendData(xEnd & 0xFF);

    SendCommand(Command::PASET);    // Row address set
    SendData(yStart >> 8);
    SendData(yStart & 0xFF);
    SendData(yEnd >> 8);
    SendData(yEnd & 0xFF);

    SendCommand(Command::RAMWR);    // Write to RAM   
}

void ILI9488::WriteColor (uint16_t color) {
    uint16_t bufferColor = static_cast<uint16_t>(color);
	uint8_t red = (bufferColor & 0xF800) >> 11;
	uint8_t green = (bufferColor & 0x07E0) >> 5;
	uint8_t blue = bufferColor & 0x001F;

	red = (red * 255) / 31;
	green = (green * 255) / 63;
	blue = (blue * 255) / 31;

    SendData(red);
    SendData(green);
    SendData(blue);
}

void ILI9488::DrawPixel (uint16_t x, uint16_t y, uint16_t color) {
    if((x < 0) ||(x >= 480) || (y < 0) || (y >= 320)) return;
	SetAddressWindow (x, y, x + 1, y + 1);
	WriteColor(color);
}

void ILI9488::DrawLine (uint16_t xStart, uint16_t yStart, uint16_t length, uint16_t color) {
    if((yStart + length - 1) >= 480) {length = 480 - yStart;}
	SetAddressWindow(xStart, yStart, xStart, yStart + length - 1);
	while (length--) {
		WriteColor(color);
    }
}

void ILI9488::DrawFill (uint16_t xStart, uint16_t yStart, uint16_t xEnd, uint16_t yEnd, uint16_t color) {
	uint16_t i,j;
	SetAddressWindow(xStart ,yStart, xEnd, yEnd);      
	for (i = yStart; i <= yEnd; i++) {													   	 	
		for(j = xStart; j <= xEnd; j++) {WriteColor(color);}
	} 
}