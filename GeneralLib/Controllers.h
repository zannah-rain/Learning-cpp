#pragma once

#include "ControllerSignals.h"
#include "glfw3.h"


class Controllers
{
public:
	Controllers(unsigned int maxPlayers);

	void step();

	void logEvents();

	bool mJoystickPresent[GLFW_JOYSTICK_LAST];
	bool mJoystickIsGamepad[GLFW_JOYSTICK_LAST];

private:
	GLFWgamepadstate mPreviousState[GLFW_JOYSTICK_LAST];
	GLFWgamepadstate mCurrentState[GLFW_JOYSTICK_LAST];

	ControllerSignals mControllerSignals[GLFW_JOYSTICK_LAST];

	unsigned int nMaxPlayers;
};