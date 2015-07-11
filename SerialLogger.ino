/*
Arduino Garage Console v1.0
Original Author: Ryan Bibbey (mail@ryanbibbey.com)

Serial Logger Helper Functions
*/

#include "MemoryFree\MemoryFree.h"

void initSerialLogger()
{
	Serial.begin(115200);
}

void logError(String message)
{
	if (DEBUG && LOG_LEVEL >= 1)
	{
		Serial.print("ERROR: ");
		Serial.println(message);    
	}
}

void logError(const char message[], int value)
{
	char touchString[50];
	char valueString[20];

	strcpy(touchString, message);
	itoa(lastTouch, valueString, 10);
	strcat(touchString, valueString);
	logInfo(touchString);
}

void logDebug(String message)
{
	if (DEBUG && LOG_LEVEL >= 2)
	{
		Serial.print("DEBUG: ");
		Serial.println(message);
		Serial.print("DEBUG: ");
		Serial.print("Free Memory = ");
		Serial.println(freeMemory());
	}
}

void logInfo(String message)
{
	if (DEBUG && LOG_LEVEL >= 3)
	{
		Serial.print("INFO: ");
		Serial.println(message);
	}
}
