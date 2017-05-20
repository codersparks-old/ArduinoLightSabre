#pragma once

#include "LightSaberSound.h"

namespace ArduinoLightSaber {

	enum LightSaberState {
		POWER_OFF,
		IDLE,
		SWING,
		STRIKE,
		HIT
	};

	enum LightSaberEvent {
		POWER_ON_EVENT,
		POWER_OFF_EVENT,
		SWING_EVENT,
		SHOCK_EVENT
	};

	

	class LightSaberStateMachine {
	public:
		LightSaberStateMachine(const LightSaberSound& lightSaberSoundModule);
		LightSaberStateMachine(LightSaberState initialState, const LightSaberSound& lightSaberSoundModule);
		void processEvent(LightSaberEvent lightSaberEvent);
		void runState();
	private:
		const LightSaberSound& _lightSaberSoundModule;
		LightSaberState _currentState;
		LightSaberState _previousState;
	};
}
