#pragma once

#include "LightSasberStates.h"

namespace ArduinoLightSaber {
	class LightSaber
	{
	public:
		LightSaber(unsigned int soundBusyPin, unsigned int soundDataPin, unsigned int soundResetPin);
		~LightSaber();
		void ExecuteState(LightSaberState state);
	private:
		LightSaberSound sound;
	};

} // Namespace

