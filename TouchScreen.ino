/*
Arduino Garage Console v1.0
Original Author: Ryan Bibbey (mail@ryanbibbey.com)

Touch Screen Functions
*/

#include "Adafruit_STMPE610\Adafruit_STMPE610.h"

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) // mega
#define YP A2   // must be an analog pin, use "An" notation!
#define XM A1   // must be an analog pin, use "An" notation!
#define YM 54   // can be a digital pin, this is A0
#define XP 57   // can be a digital pin, this is A3 

#elif defined(__AVR_ATmega32U4__) // leonardo
#define YP A2   // must be an analog pin, use "An" notation!
#define XM A1   // must be an analog pin, use "An" notation!
#define YM 18   // can be a digital pin, this is A0
#define XP 21   // can be a digital pin, this is A3 

#else //168, 328, something else
#define YP A2   // must be an analog pin, use "An" notation!
#define XM A1   // must be an analog pin, use "An" notation!
#define YM 14   // can be a digital pin, this is A0
#define XP 17   // can be a digital pin, this is A3 

#endif

//Measured ADC values for (0,0) and (210-1,320-1)
//TS_MINX corresponds to ADC value when X = 0
//TS_MINY corresponds to ADC value when Y = 0
//TS_MAXX corresponds to ADC value when X = 240 -1
//TS_MAXY corresponds to ADC value when Y = 320 -1

#define TS_MINX 150
#define TS_MAXX 3800
#define TS_MINY 130
#define TS_MAXY 4000

Adafruit_STMPE610 tch = Adafruit_STMPE610(STMPE_CS);
//TouchScreen tch = TouchScreen(XP, YP, XM, YM, 360);
TS_Point point;
long pointTime;

void initTouch()
{
	if (!tch.begin())
		logInfo("Error initializing the touch screen!");
}

void getPoint()
{
	point = tch.getPoint();
	pointTime = millis();
}

bool pressDetected()
{
	return !tch.bufferEmpty();
}

int getZ()
{
	return point.z;
}

int mapX()
{
	return map(point.x, TS_MINX, TS_MAXX, 0, 240);
}

int mapY()
{
	return map(point.y, TS_MINY, TS_MAXY, 0, 320);
}
