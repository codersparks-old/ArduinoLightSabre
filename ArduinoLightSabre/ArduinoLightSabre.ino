/*
 Name:		ArduinoLightSabre.ino
 Created:	5/18/2017 7:30:04 PM
 Author:	codersparks
*/

#include <EnableInterrupt.h>
#include "LightSaberSound.h"

#define DEBOUNCE_TIME 200

#define SOUND_BUSY_PIN 13
#define SOUND_DATA_PIN 12
#define SOUND_RESET_PIN 11
#define INTERRUPT_POWER_PIN 10

ArduinoLightSaber::LightSaberSound soundBoard(SOUND_BUSY_PIN, SOUND_DATA_PIN, SOUND_RESET_PIN);

unsigned int last_interrupt_time = 0;

bool power = false;

void powerOnInterrupt() {
	// Do power off

	unsigned long interrupt_time = millis();

	if (interrupt_time - last_interrupt_time > DEBOUNCE_TIME) {

		Serial.println("Power On Interrupt fired");
		soundBoard.resetModule();
		delay(1000);
		soundBoard.playSound(ArduinoLightSaber::LightSaberSounds::OFF, true);
		power = false;
		registerPowerOffInterrupt();

		last_interrupt_time = interrupt_time;
	}

}

void powerOffInterrupt() {

	unsigned long interrupt_time = millis();

	if (interrupt_time - last_interrupt_time > DEBOUNCE_TIME) {

		Serial.println("Power Off Interrupt fired");
		soundBoard.resetModule();
		delay(1000);
		soundBoard.playSound(ArduinoLightSaber::LightSaberSounds::ON, true);
		power = true;
		registerPowerOnInterrupt();

		last_interrupt_time = interrupt_time;
	}
}

void registerPowerOffInterrupt() {
	enableInterrupt(INTERRUPT_POWER_PIN, powerOffInterrupt, CHANGE);
}

void registerPowerOnInterrupt() {
	enableInterrupt(INTERRUPT_POWER_PIN, powerOnInterrupt, CHANGE);
}

void setup() {

	Serial.begin(115200);
	while (!Serial); // Wait for the serial monitor to start

	pinMode(SOUND_DATA_PIN, OUTPUT);
	
	pinMode(SOUND_RESET_PIN, OUTPUT);
	digitalWrite(SOUND_RESET_PIN, HIGH);
	
	pinMode(SOUND_BUSY_PIN, INPUT_PULLUP);

	pinMode(INTERRUPT_POWER_PIN, INPUT_PULLUP);

	registerPowerOffInterrupt();
	
	soundBoard.resetModule();
	// If the board is not busy (i.e. playing a sound then we play the idle on repeat

	soundBoard.playSound(ArduinoLightSaber::LightSaberSounds::STARTUP, true);

	Serial.println("************ Setup complete!");

}


void loop() {
	if (power) {
		soundBoard.playSound(ArduinoLightSaber::LightSaberSounds::IDLE, true);
	}
}
