#include "LightSaberSound.h"
#include <Arduino.h>



ArduinoLightSaber::LightSaberSound::LightSaberSound(unsigned int busyPin, unsigned int dataPin, unsigned int resetPin) 
	: _busyPin(busyPin),
	_dataPin(dataPin),
	_resetPin(resetPin)
{
	pinMode(_dataPin, OUTPUT);
	pinMode(_resetPin, OUTPUT);

	digitalWrite(_resetPin, HIGH);
	pinMode(_busyPin, INPUT_PULLUP);
}


ArduinoLightSaber::LightSaberSound::~LightSaberSound()
{
}

void ArduinoLightSaber::LightSaberSound::playSound(unsigned int soundAddress) const {
	this->playSound(soundAddress, false);
}

void ArduinoLightSaber::LightSaberSound::playSound(unsigned int soundAddress, bool waitForEndPlayback) const
{

	// Some logging to write out to monitor
	if (Serial) {
		Serial.print("Playing sound: ");
		Serial.println(soundAddress);
	}

	// Wait for the board to be ready (i.e. not busy)
//	while (this->isBusy());

	digitalWrite(_dataPin, LOW);	// We need to ensure that the chip is woken up from sleep mode
	delay(5);

	for (int i = 0; i < 8; i++) {

		if (bitRead(soundAddress, i)) { // Read each bit of the sound to be played

			digitalWrite(_dataPin, 1);
			delayMicroseconds(400);
			digitalWrite(_dataPin, 0); // 2:1 high/low indicates high
			delayMicroseconds(200);
		}
		else {
			digitalWrite(_dataPin, 1);
			delayMicroseconds(200);
			digitalWrite(_dataPin, 0);
			delayMicroseconds(400);
		}
	}

	digitalWrite(_dataPin, 1);

	if (waitForEndPlayback) {
		delay( 100); // We delay to allow the busy signal to register (documentation status 2ms)

		while (this->isBusy()) {
			// Do nothing other than log message (if Serial has been set)
			if (Serial) {
				Serial.println("Soundboard reporting busy");
			}
		}

		if (Serial) {
			Serial.println("Soundboard no longer reporting busy");
		}
	}
	//delay(1000);
	
}

void ArduinoLightSaber::LightSaberSound::resetModule() const
{
	digitalWrite(_resetPin, LOW);
	delay(5);
	digitalWrite(_resetPin, HIGH);
	delay(18);
}

bool ArduinoLightSaber::LightSaberSound::isBusy() const
{
	int busyVal = digitalRead(_busyPin);

	if (Serial) {
		Serial.print("Busy value: ");
		Serial.println(busyVal);
	}

	if (busyVal == BUSY_VALUE) {
		return true;
	}
	else {
		return false;
	}
}
