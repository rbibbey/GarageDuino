/*
Arduino Garage Console v1.0
Original Author: Ryan Bibbey (mail@ryanbibbey.com)

User Interface Functions

NOTE: This module previously used the standard TFT library and was designed to use a SeedStudio TFT screen
*/

//#include <stdint.h>
//#include <TFT.h>

#include "SPI\SPI.h"
#include "Wire\Wire.h"
#include "Adafruit-GFX\Adafruit_GFX.h"
#include "Adafruit_ILI9341\Adafruit_ILI9341.h"

#define THEME_STANDARD
//#define THEME_INVERSE

#ifdef THEME_STANDARD
#define FG_COLOR 0xFFFF
#define BG_COLOR 0x0000
#endif

#ifdef THEME_INVERSE
#define FG_COLOR 0x0000
#define BG_COLOR 0xFFFF
#endif

int fgColor = FG_COLOR;
int bgColor = BG_COLOR;

bool inStandBy = false;

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

void initScreen()
{
	//Tft.init();
	tft.begin();

	//Tft.setDisplayDirect(DOWN2UP);
	tft.setRotation(3);
	tft.setTextColor(fgColor);
	tft.setTextSize(2);
	drawUIEx();
}

void setStandby(bool standby)
{
	if (standby && standby != inStandBy)
	{
		logInfo("Sending LCD standby command...");
		
		tft.writecommand(0x0007);
		tft.writedata(0x0131);

		//Tft.sendData(0x0131);
	}

	if (!standby && standby != inStandBy)
	{
		logInfo("Attempting to exit standby mode...");
		tft.writecommand(0x0007);
		tft.writedata(0x0131);

		//Tft.sendData(0x0133);
	}

	inStandBy = standby;
}

void drawUIEx()
{
	logInfo("Starting drawUIEx()...");
	tft.fillScreen(bgColor);
	//tft.fillRectangle(0,320,240,320,bgColor);

	drawButtons(false);
	updateTitle("GarageDuino");
	updateTemperature(0);

	logInfo("Leaving drawUIEx()...");
}

void updateTitle(char title[])
{
	logInfo("Updating user interface title...");
	tft.drawRect(0,0,320,25,fgColor);
	tft.setCursor(5, 5);

	tft.print(title);

	//Tft.fillRectangle(10,290,40,270,bgColor);
	//Tft.drawString(title,20,290,3,fgColor);
}

void updateTemperature(int temp)
{
	logInfo("Updating user interface temperature...");
	char buffer[20];
	char value[10];

	itoa(temp, value, 10);
	strcpy(buffer, "TEMP: ");

	if (temp > 0)
		strcat(buffer, value);
	else
		strcat(buffer, "---");

	if (USE_FAHRENHEIT)
		strcat(buffer, "F");
	else
		strcat(buffer, "C");

	//if (temp == 0)
	//{
		//Tft.drawString("TEMP: ",80,300,4,fgColor);
		//tft.setCursor(210, 5);
		//tft.print("TEMP: 000");
	//}

	//Tft.fillRectangle(70,150,40,140,bgColor);
	//Tft.drawString(buffer,80,130,4,fgColor);

	tft.setCursor(197, 5);
	tft.fillRect(256,5,59,14,bgColor);
	tft.print(buffer);
}

void drawButtons(boolean invert)
{
	logInfo("Drawing buttons...");
	drawLeftButton(invert);
	drawMiddleButton(invert);
	drawRightButton(invert);
}

void drawLeftButton(boolean invert)
{
	int c1 = FG_COLOR;
	int c2 = BG_COLOR;

	if (invert)
	{
		c1 = BG_COLOR;
		c2 = FG_COLOR;
	}

	//Left Button (Up/Down Arrow)
	//Tft.drawRectangle(140,220,80,80,c1);
	//Tft.fillRectangle(141,299,79,79,c2);

	//Tft.fillRectangle(165,270,10,20,c1);
	//Tft.fillRectangle(185,270,10,20,c1);

	tft.drawRoundRect(20,140,80,80,7,c1);
	tft.fillRoundRect(21,141,77,77,7,c2);

	tft.fillRect(50,165,20,10,c1);
	tft.fillRect(50,185,20,10,c1);

	for (int i = 0; i < 10; i++)
	{
		//bottom arrow
		tft.drawLine(45+(i*1.5),165-i,75-(i*1.5),165-i, c1);
		tft.drawLine(45+(i*1.5),195+i,75-(i*1.5),195+i, c1);
		//Tft.drawLine(165-i, 246+(i*1.5), 165-i, 276-(i*1.5),c1);
		//Tft.drawLine(195+i, 246+(i*1.5), 195+i, 276-(i*1.5),c1);
	}
}

void drawMiddleButton(boolean invert)
{
	int c1 = FG_COLOR;
	int c2 = BG_COLOR;

	if (invert)
	{
		c1 = BG_COLOR;
		c2 = FG_COLOR;
	}

	//Middle Button (Lock)
	//Tft.drawRectangle(140,120,80,80,c1);
	//Tft.fillRectangle(141,199,79,79,c2);
	//Tft.fillRectangle(165,180,40,40,c1);
	//Tft.fillRectangle(165,177,5,34,c2);
	//Tft.drawCircle(170,160,19,c1);
	//Tft.drawCircle(170,161,19,c1);
	//Tft.drawCircle(170,160,18,c1);
	//Tft.drawCircle(170,161,18,c1);
	//Tft.drawCircle(170,160,17,c1);
	//Tft.drawCircle(170,161,17,c1);

	//Tft.fillCircle(180, 161, 5, c2);
	//Tft.fillRectangle(185,162,8,4,c2);

	//Button Outline
	tft.drawRoundRect(120,140,80,80,7,c1);
	tft.fillRoundRect(121,141,77,77,7,c2);

	//Lock Symbol
	tft.fillCircle(160,165,18, c1);
	tft.fillCircle(160,166,18, c1);
	tft.fillCircle(160,165,17, c1);
	tft.fillCircle(160,166,17, c1);
	tft.fillCircle(160,165,16, c1);
	tft.fillCircle(160,166,16, c1);
	tft.fillCircle(160,165,15, c2);

	tft.fillRect(140,165,40,40,c1);
	tft.fillRect(155,170,10,30,c2);
	tft.fillCircle(160,177,9, c2);
}

void drawRightButton(boolean invert)
{
	int c1 = FG_COLOR;
	int c2 = BG_COLOR;

	if (invert)
	{
		c1 = BG_COLOR;
		c2 = FG_COLOR;
	}
	//Right button (Light Bulb)
/*	Tft.drawRectangle(140,20,80,80,c1);
	Tft.fillRectangle(141,99,79,79,c2);
	Tft.fillCircle(170, 61, 19, c1);

	Tft.fillCircle(171, 61, 19, c1);
	Tft.fillCircle(172, 61, 18, c1);
	Tft.fillCircle(173, 61, 18, c1);
	Tft.fillCircle(174, 61, 17, c1);
	Tft.fillCircle(175, 61, 16, c1);
	Tft.fillCircle(176, 61, 15, c1);
	Tft.fillCircle(177, 61, 14, c1);
	Tft.fillCircle(178, 61, 13, c1);
	Tft.fillCircle(179, 61, 13, c1);
	Tft.fillCircle(180, 61, 12, c1);
	Tft.fillCircle(181, 61, 12, c1);
	Tft.fillCircle(182, 61, 12, c1);
	Tft.fillCircle(183, 61, 11, c1);
	Tft.fillCircle(184, 61, 11, c1);
	Tft.fillCircle(185, 61, 11, c1);
	Tft.fillCircle(186, 61, 10, c1);
	Tft.fillCircle(187, 61, 10, c1);
	Tft.fillCircle(188, 61, 10, c1);
	Tft.fillCircle(189, 61, 10, c1);
	Tft.fillCircle(190, 61, 10, c1);
	Tft.fillCircle(191, 61, 10, c1);
	Tft.fillCircle(192, 61, 10, c1);
	Tft.fillCircle(193, 61, 10, c1);
	Tft.fillCircle(194, 61, 10, c1);
	Tft.fillCircle(195, 61, 10, c1);

	Tft.drawLine(190,81,192,40,c2);    
	Tft.drawLine(194,81,196,40,c2);    
	Tft.drawLine(198,81,200,40,c2);  */  
	
	//Button Outline
	tft.drawRoundRect(220,140,80,80,7,c1);
	tft.fillRoundRect(221,141,77,77,7,c2);

	tft.fillCircle(260, 170, 19, c1);
	tft.fillCircle(260, 172, 18, c1);
	tft.fillCircle(260, 173, 18, c1);
	tft.fillCircle(260, 174, 17, c1);
	tft.fillCircle(260, 175, 16, c1);
	tft.fillCircle(260, 176, 15, c1);
	tft.fillCircle(260, 177, 14, c1);
	tft.fillCircle(260, 178, 13, c1);
	tft.fillCircle(260, 179, 13, c1);
	tft.fillCircle(260, 180, 12, c1);
	tft.fillCircle(260, 181, 12, c1);
	tft.fillCircle(260, 182, 12, c1);
	tft.fillCircle(260, 183, 11, c1);
	tft.fillCircle(260, 184, 11, c1);
	tft.fillCircle(260, 185, 11, c1);
	tft.fillCircle(260, 186, 10, c1);
	tft.fillCircle(260, 187, 10, c1);
	tft.fillCircle(260, 188, 10, c1);
	tft.fillCircle(260, 189, 10, c1);
	tft.fillCircle(260, 190, 10, c1);
	tft.fillCircle(260, 191, 10, c1);
	tft.fillCircle(260, 192, 10, c1);
	tft.fillCircle(260, 193, 10, c1);
	tft.fillCircle(260, 194, 10, c1);
	tft.fillCircle(260, 195, 10, c1);

	tft.drawLine(250, 190, 270, 190, c2);
	tft.drawLine(250, 192, 270, 192, c2);
	tft.drawLine(250, 194, 270, 194, c2);
	tft.drawLine(250, 196, 270, 196, c2);
}
