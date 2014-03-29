/*
Arduino Garage Console v1.0
Original Author: Ryan Bibbey (mail@ryanbibbey.com)

Temperature Sensor Functions
*/

const float magicVoltageValue = 0.004882814;  //Used to turn an analogRead value to actual voltage
const int deltaMax = 5;                        //Used to filter out variations in readings greater than this value

int lastTempValueC = 0;
int lastTempValueF = 0;

void GetLatestReading()
{
	if (TEMP_ENABLED)
	{
		logInfo("Requesting temperature from analog sensor...");

		int readValue = analogRead(TEMP_PIN);
		float voltage = readValue * magicVoltageValue;
		int tempC = (voltage - 0.5) * 100.0;
		int tempF = tempC * (9.0/5.0) + 32;

		if (lastTempValueC == 0 || abs(lastTempValueC - tempC) < deltaMax)
			lastTempValueC = tempC;

		if (lastTempValueF == 0 || abs(lastTempValueF - tempF) < deltaMax)
			lastTempValueF = tempF;

		logInfo("Temperature readings updated...");
	}
}

int GetTemperatureF()
{
	GetLatestReading();
	return lastTempValueF;
}

int GetTemperatureC()
{
	GetLatestReading();
	return lastTempValueC;
}
