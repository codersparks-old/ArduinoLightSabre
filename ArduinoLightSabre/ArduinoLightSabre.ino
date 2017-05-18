/*
 Name:		ArduinoLightSabre.ino
 Created:	5/18/2017 7:30:04 PM
 Author:	codersparks
*/

#include "LightSaberSound.h"

#define SOUND_BUSY_PIN 13
#define SOUND_DATA_PIN 12
#define SOUND_RESET_PIN 11

ArduinoLightSaber::LightSaberSound soundBoard(SOUND_BUSY_PIN, SOUND_DATA_PIN, SOUND_RESET_PIN);

void setup() {

	Serial.begin(115200);
	while (!Serial); // Wait for the serial monitor to start
	
	soundBoard.resetModule();
	// If the board is not busy (i.e. playing a sound then we play the idle on repeat

	soundBoard.playSound(ArduinoLightSaber::LightSaberSounds::STARTUP, true);

	Serial.println("************ Setup complete!");

}


void loop() {
  
	soundBoard.playSound(ArduinoLightSaber::LightSaberSounds::IDLE, true);
}
