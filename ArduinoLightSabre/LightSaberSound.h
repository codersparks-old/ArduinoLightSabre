#pragma once

namespace ArduinoLightSaber {
enum LightSaberSounds {
	IDLE = 0,
	ON = 1,
	OFF = 2,
	SWING1 = 3,
	SWING2 = 4,
	SWING3 = 5,
	SWING4 = 6,
	SWING5 = 7,
	SWING6 = 8,
	SWING7 = 9,
	SWING8 = 10,
	STRIKE1 = 11,
	STRIKE2 = 12,
	STRIKE3 = 13,
	HIT1 = 14,
	HIT2 = 15,
	HIT3 = 16,
	HIT4 = 17,
	STARTUP = 18
};

const unsigned int MIN_SWING = 3;
const unsigned int MAX_SWING = 10;
const unsigned int MIN_STRIKE = 11;
const unsigned int MAX_STRIKE = 13;
const unsigned int MIN_HIT = 14;
const unsigned int MAX_HIT = 17;

/*
Class: LightSaberSound

This class is used to interact with the WT588D sound board

Obviously this requires the sound board to have been flashed with the correct sounds (that can be found in the Non_Visual_Studio_Files folder of the git project)

The constructor takes in 3 pin numbers to asign the following pins:
	busy: Allows the class to check if the WT588d module is busy
	data: The single serial line for data
	reset: Connected to the reset pin of the WT588d

Information for timings etc available from the manual here: https://www.hobbielektronika.hu/forum/getfile.php?id=200287
*/
class LightSaberSound
{
public:
	LightSaberSound(const unsigned int busyPin, const unsigned int dataPin, const unsigned int resetPin);
	~LightSaberSound();
	void playSound(unsigned int soundAddress);
	void playSound(unsigned int soundAddress, bool waitForEndPlayback);
	void resetModule();
	bool isBusy();

private:
	int _busyPin;
	int _dataPin;
	int _resetPin;
	const int BUSY_VALUE = 0; // Pin goes low if it is busy
};

} // Namespace ArduinoLightSaber

