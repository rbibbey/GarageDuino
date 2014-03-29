/*
Arduino Garage Console v1.0
Original Author: Ryan Bibbey (mail@ryanbibbey.com)

Touch Screen Functions
*/

#include <stdint.h>
#include "TouchScreen.h"

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

#define TS_MINX 140
#define TS_MAXX 900
#define TS_MINY 120
#define TS_MAXY 940

TouchScreen tch = TouchScreen(XP, YP, XM, YM, 360);
Point point;
long pointTime;

void initTouch()
{

}

void getPoint()
{
	point = tch.getPoint();
	pointTime = millis();
}

bool pressDetected()
{
	return point.z > tch.pressureThreshhold;
}

int getZ()
{
	return point.z;
}

int mapX()
{
	return map(point.x, TS_MINX, TS_MAXX, 240, 0);
}

int mapY()
{
	return map(point.y, TS_MINY, TS_MAXY, 320, 0);
}
