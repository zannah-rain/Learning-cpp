#pragma once

#include "glfw3.h"
#include "sigslot/signal.hpp"

/**
* All signals a single controller can send
*/
struct ControllerSignals
{
	sigslot::signal<> Connected;
	sigslot::signal<> Disconnected;
	sigslot::signal<> ButtonPressed[GLFW_GAMEPAD_BUTTON_LAST];
	sigslot::signal<> ButtonReleased[GLFW_GAMEPAD_BUTTON_LAST];

	// Should send how long it is held
	sigslot::signal<float> ButtonHeld[GLFW_GAMEPAD_BUTTON_LAST];
	
	// Sends the X & Y value for the axis
	sigslot::signal<float, float> LeftAxisHeld;
	sigslot::signal<float, float> RightAxisHeld;

	// Sends the amount the axis is depressed
	sigslot::signal<float> LeftTriggerHeld;
	sigslot::signal<float> RightTriggerHeld;
};
