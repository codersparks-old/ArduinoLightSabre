#include "Arduino.h"
#include "LightSasberStates.h"

/*
Constructor that allows the LightSaberStateMachine to be initialised in the POWER_OFF State
*/
ArduinoLightSaber::LightSaberStateMachine::LightSaberStateMachine(const LightSaberSound & lightSaberSoundModule)
	: _lightSaberSoundModule(lightSaberSoundModule), _currentState(LightSaberState::POWER_OFF), _previousState(LightSaberState::POWER_OFF)
{
}

/*
Constructor that allows entry at any initial state
*/
ArduinoLightSaber::LightSaberStateMachine::LightSaberStateMachine(LightSaberState initialState, const LightSaberSound& lightSaberSoundModule)
	: _currentState(initialState), _lightSaberSoundModule(lightSaberSoundModule)
{		
}

void ArduinoLightSaber::LightSaberStateMachine::processEvent(LightSaberEvent lightSaberEvent)
{
	switch (lightSaberEvent) {
	case POWER_ON_EVENT:
		// We only react to this if we are in power off state
		switch (_currentState) {
		case POWER_OFF:
			_currentState = IDLE;
		}
	case POWER_OFF_EVENT:
		// Whatever happens we are going to stop the soundboard from playing and turn off
		_currentState = POWER_OFF;
		break;
	case SWING_EVENT:
		// We only change state on a swing event if the current state is IDLE
		switch (_currentState) {
		case IDLE:
			_currentState = SWING;
			break;
		default:
			// No - op / Change in state
			break;
		}
		break;
	case SHOCK_EVENT:
		// We act differently based on the currentState
		switch (_currentState) {
		case IDLE:
			_currentState = HIT;
			break;
		case SWING:
			_currentState = STRIKE;
			break;
		default:
			// No op / change is state
			break;
		}
		break;
	}
}

void ArduinoLightSaber::LightSaberStateMachine::runState()
{
	// We are going to capture the state in case there has been an interrupt that has changes state before the end of the function
	LightSaberState initialState = _currentState;


	// We are going to check if the state variable has changed from the begining of this loop
	if (_currentState == initialState) {}
}

