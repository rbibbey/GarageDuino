/*
Arduino Garage Console v1.0
Original Author: Ryan Bibbey (mail@ryanbibbey.com)

Relay Control Functions
*/


void trigger(int period)
{
	if (RELAY_ENABLED)
	{
		logInfo("Relay trigger requested...");
		digitalWrite(RELAY_PIN, HIGH);
		delay(period);
		digitalWrite(RELAY_PIN, LOW);

		logInfo("Relay triggered...");
	}
}
