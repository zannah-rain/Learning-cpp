#pragma once

#include "glfw3.h"


class Controllers
{
public:
	Controllers();

	void logEvents();

	bool mJoystickPresent[GLFW_JOYSTICK_LAST];
	bool mJoystickIsGamepad[GLFW_JOYSTICK_LAST];
};