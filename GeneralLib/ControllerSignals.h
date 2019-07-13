#pragma once

#include "glfw3.h"
#include "sigslot/signal.hpp"

/**
* All signals a single controller can send
*/
struct ControllerSignals
{
	signal0<> Connected;
	signal0<> Disconnected;
	signal0<> ButtonPressed[GLFW_GAMEPAD_BUTTON_LAST];
	signal0<> ButtonReleased[GLFW_GAMEPAD_BUTTON_LAST];
	signal1<float timeHeld> ButtonHeld[GLFW_GAMEPAD_BUTTON_LAST];
	
	signal2<float x, float y> LeftAxisHeld;
	signal2<float x, float y> RightAxisHeld;
	signal1<float amount> LeftTriggerHeld;
	signal1<float amount> RightTriggerHeld;
};
