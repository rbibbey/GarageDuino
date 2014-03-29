/*
Arduino Garage Console v1.0
Original Author: Ryan Bibbey (mail@ryanbibbey.com)

User Interface Functions
*/

#include <stdint.h>
#include <TFT.h>

#define THEME_BLACK_WHITE
//#define THEME_WHITE_BLACK

#ifdef THEME_BLACK_WHITE
#define FG_COLOR BLACK
#define BG_COLOR WHITE
#endif

#ifdef THEME_WHITE_BLACK
#define FG_COLOR BLACK
#define BG_COLOR WHITE
#endif

int fgColor = FG_COLOR;
int bgColor = BG_COLOR;

bool inStandBy = false;

void initScreen()
{
	Tft.init();

	Tft.setDisplayDirect(DOWN2UP);

	drawUIEx();
}

void setStandby(bool standby)
{
	if (standby && standby != inStandBy)
	{
		logInfo("Sending LCD standby command...");
		Tft.sendCommand(0x0007);
		Tft.sendData(0x0131);
	}

	if (!standby && standby != inStandBy)
	{
		logInfo("Attempting to exit standby mode...");
		Tft.sendCommand(0x0007);
		Tft.sendData(0x0133);
	}

	inStandBy = standby;
}

void drawUIEx()
{
	logInfo("Starting drawUIEx()...");
	Tft.fillRectangle(0,320,240,320,bgColor);

	drawButtons(false);
	updateTitle("GarageDuino");
	updateTemperature(0);

	logInfo("Leaving drawUIEx()...");
}

void updateTitle(char title[])
{
	logInfo("Updating user interface title...");
	Tft.fillRectangle(10,290,40,270,bgColor);
	Tft.drawString(title,20,290,3,fgColor);
}

void updateTemperature(int temp)
{
	logInfo("Updating user interface temperature...");
	char buffer[20];
	char value[10];

	itoa(temp, value, 10);

	if (temp > 0)
		strcpy(buffer, value);
	else
		strcpy(buffer, "--");

	if (USE_FAHRENHEIT)
		strcat(buffer, "F");
	else
		strcat(buffer, "C");

	if (temp == 0)
		Tft.drawString("TEMP: ",80,300,4,fgColor);

	Tft.fillRectangle(70,150,40,140,bgColor);
	Tft.drawString(buffer,80,130,4,fgColor);
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
	Tft.drawRectangle(140,220,80,80,c1);
	Tft.fillRectangle(141,299,79,79,c2);

	Tft.fillRectangle(165,270,10,20,c1);
	Tft.fillRectangle(185,270,10,20,c1);

	for (int i = 0; i < 10; i++)
	{
		//bottom arrow
		Tft.drawLine(165-i, 246+(i*1.5), 165-i, 276-(i*1.5),c1);
		Tft.drawLine(195+i, 246+(i*1.5), 195+i, 276-(i*1.5),c1);
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
	Tft.drawRectangle(140,120,80,80,c1);
	Tft.fillRectangle(141,199,79,79,c2);
	Tft.fillRectangle(165,180,40,40,c1);
	Tft.fillRectangle(165,177,5,34,c2);
	Tft.drawCircle(170,160,19,c1);
	Tft.drawCircle(170,161,19,c1);
	Tft.drawCircle(170,160,18,c1);
	Tft.drawCircle(170,161,18,c1);
	Tft.drawCircle(170,160,17,c1);
	Tft.drawCircle(170,161,17,c1);

	Tft.fillCircle(180, 161, 5, c2);
	Tft.fillRectangle(185,162,8,4,c2);
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
	Tft.drawRectangle(140,20,80,80,c1);
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
	Tft.drawLine(198,81,200,40,c2);    
}
