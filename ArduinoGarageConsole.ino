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

#define STMPE_CS 8
#define TFT_DC 9
#define TFT_CS 10

const long LCD_TIMEOUT = 30000;

int loopCount = 0;
int lastTemp = 0;
long lastTouch = 0;
int lastButton = 0;			//0 = None; 1 = Left; 2 = Middle; 3 = Right;
long buttonPressed = 0;
long buttonHoldTime = 500;

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

	if (TOUCH_ENABLED)
	{
		initTouch();
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

			if (currentTemp < 102)
				currentTemp++;
			else
				currentTemp = 200;
		}

		if (currentTemp != lastTemp && abs(currentTemp-lastTemp) < 99)		//Only display changes if difference between temp reads is less than a 5 degree swing
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

		if (pressDetected() == true && lastButton == 0)
		{
			logInfo("Screen press detected...");
			lastTouch = millis();

			if (x >= 120 && x <= 200)
			{
				//touch received in range of buttons

				// if y between 20-100, then right button
				// if y between 120-200 the middle button
				// if y between 220-300 then left button
				if (y > 20 && y < 100)
				{
					buttonPressed = millis();
					lastButton = 3;
					drawRightButton(true);
					logInfo("Right button pressed...");
				}

				if (y > 120 && y < 200)
				{
					buttonPressed = millis();
					lastButton = 2;
					drawMiddleButton(true);
					logInfo("Middle button pressed...");
				}

				if (y > 220 && y < 300)
				{
					buttonPressed = millis();
					lastButton = 1;
					drawLeftButton(true);
					logInfo("Left button pressed...");
				}
			}
		}
		else
		{
			if (buttonPressed > 0 && millis() > buttonPressed + buttonHoldTime)
			{
				buttonPressed = 0;
				
				if (lastButton == 1) drawLeftButton(false);
				if (lastButton == 2) drawMiddleButton(false);
				if (lastButton == 3) drawRightButton(false);
				//drawButtons(false);

				lastButton = 0;
			}
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
	//delay(100);
}
