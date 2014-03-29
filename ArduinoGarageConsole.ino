/*
Arduino Garage Console v1.0
Original Author: Ryan Bibbey (mail@ryanbibbey.com)

This is where the Arduino program's setup and main loop live
*/


#define DEBUG true
#define LOG_LEVEL 3          //1 = ERROR, 2 = DEBUG, 3 = INFO    
#define RELAY_ENABLED false
#define TEMP_ENABLED false
#define USE_FAHRENHEIT true
#define LCD_ENABLED true
//#define LCD_TIMEOUT 30000
#define TOUCH_ENABLED true

#define TEMP_PIN A4
#define RELAY_PIN A5

const long LCD_TIMEOUT = 30000;

int loopCount = 0;
int lastTemp = 0;
long lastTouch = 0;
long buttonPressed = 0;
long buttonHoldTime = 1000;

void setup()
{
	if (DEBUG)
		initSerialLogger();

	logInfo("Initializing...");

	if (RELAY_ENABLED)
		pinMode(RELAY_PIN, OUTPUT);

	if (LCD_ENABLED)
	{
		pinMode(0, OUTPUT);
		initScreen();
	}
}

void loop()
{
	logInfo("Executing main loop...");
	int currentTemp = 0;

	if (TEMP_ENABLED)
	{
		if (USE_FAHRENHEIT)
			currentTemp = GetTemperatureF();
		else
			currentTemp = GetTemperatureC();

		char message[50] = "Current temperature reading: ";
		char value[10];

		itoa(currentTemp, value, 10);
		strcat(message, value);

		logInfo(message);
		updateTemperature(currentTemp);
	}

	if (RELAY_ENABLED && loopCount % 10 == 0)
	{
		trigger(500);
		loopCount = 0;
	}

	if (LCD_ENABLED)
	{
		if (DEBUG)
		{
			if (lastTemp == 0) { lastTemp = 67; }

			currentTemp = lastTemp;

			if (currentTemp < 79)
				currentTemp++;
		}

		if (currentTemp != lastTemp && abs(currentTemp-lastTemp) < 5)		//Only display changes if difference between temp reads is less than a 5 degree swing
		{
			lastTemp = currentTemp;

			char message[50] = "Updating LCD temperature reading: ";
			char value[10];

			itoa(currentTemp, value, 10);
			strcat(message, value);

			logInfo(message);
			updateTemperature(currentTemp);
		}
	}

	if (TOUCH_ENABLED)
	{
		getPoint();

		int x = mapX();
		int y = mapY();
		char zReading[20];
		char zMessage[100];

		itoa(getZ(), zReading, 10);
		strcpy(zMessage, "Last Z Reading = ");
		strcat(zMessage, zReading);
		logInfo(zMessage);

		if (pressDetected)
		{
			logInfo("Screen press detected...");
			lastTouch = millis();

			if (x >= 130 && x <= 230)
			{
				//touch received in range of buttons

				// if y between 20-100, then right button
				// if y between 120-200 the middle button
				// if y between 220-300 then left button
				if (y > 10 && y < 110)
				{
					buttonPressed = millis();
					drawRightButton(true);
					logInfo("Right button pressed...");
				}

				if (y > 110 && y < 210)
				{
					buttonPressed = millis();
					drawMiddleButton(true);
					logInfo("Middle button pressed...");
				}

				if (y > 210 && y < 310)
				{
					buttonPressed = millis();
					drawLeftButton(true);
					logInfo("Left button pressed...");
				}
			}
		}

		if (buttonPressed > 0 && millis() > buttonPressed + buttonHoldTime)
		{
			buttonPressed = 0;
			drawButtons(false);
		}

		char touchString[50];
		char value[20];
		strcpy(touchString, "Last Touch = ");
		ltoa(lastTouch, value, 10);
		strcat(touchString, value);
		logInfo(touchString);

		//if (lastTouch > 0 && millis() > LCD_TIMEOUT)
		//{
		//	logInfo("Requesting standby...");
		//	setStandby(true);
		//}
		//else
		//	setStandby(false);
	}

	loopCount++;
	delay(100);
}
