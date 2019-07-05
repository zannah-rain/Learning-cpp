#pragma once

#include "glfw3.h"


class Controllers
{
public:
	Controllers();

	void step();

	void logEvents();

	bool mJoystickPresent[GLFW_JOYSTICK_LAST];
	bool mJoystickIsGamepad[GLFW_JOYSTICK_LAST];

private:
	GLFWgamepadstate mPreviousState[GLFW_JOYSTICK_LAST];
	GLFWgamepadstate mCurrentState[GLFW_JOYSTICK_LAST];
};