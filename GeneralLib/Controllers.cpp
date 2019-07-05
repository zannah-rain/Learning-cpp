#include "Controllers.h"

#include <iostream>


Controllers::Controllers()
{
	for (size_t i = 0; i <= GLFW_JOYSTICK_LAST; i++)
	{
		// Initialise our states
		glfwGetGamepadState(i, &mCurrentState[i]);
		mPreviousState[i] = mCurrentState[i];

		mJoystickPresent[i] = glfwJoystickPresent(i) == GLFW_TRUE;
		if (mJoystickPresent[i])
		{
			std::cout << "Joystick " << i << " present" << std::endl;
		}
		mJoystickIsGamepad[i] = glfwJoystickIsGamepad(i) == GLFW_TRUE;
		if (mJoystickIsGamepad[i])
		{
			std::cout << "Joystick " << i << " is gamepad!" << std::endl;
		}
		if ((!mJoystickIsGamepad[i]) && mJoystickPresent[i])
		{
			std::cout << "Joystick " << i << " is NOT a gamepad!" << std::endl;
		}
	}
}


void Controllers::step()
{
	for (size_t i = 0; i <= GLFW_JOYSTICK_LAST; i++)
	{
		mPreviousState[i] = mCurrentState[i];
		glfwGetGamepadState(i, &mCurrentState[i]);

		if (mCurrentState[i].buttons[GLFW_GAMEPAD_BUTTON_CROSS] != mPreviousState[i].buttons[GLFW_GAMEPAD_BUTTON_CROSS])
		{
			if (mCurrentState[i].buttons[GLFW_GAMEPAD_BUTTON_CROSS])
			{
				std::cout << "Joystick " << i << " button JUST pressed: EXS" << std::endl;
			}
			else
			{
				std::cout << "Joystick " << i << " button JUST released: EXS" << std::endl;
			}
		}
	}
}


void Controllers::logEvents()
{
	GLFWgamepadstate state;

	for (size_t i = 0; i <= GLFW_JOYSTICK_LAST; i++)
	{
		if (glfwGetGamepadState(i, &state))
		{
			if (state.buttons[GLFW_GAMEPAD_BUTTON_CROSS])
			{
				std::cout << "Joystick " << i << " button pressed: " << "EXS" << std::endl;
			}
			if (state.buttons[GLFW_GAMEPAD_BUTTON_CIRCLE])
			{
				std::cout << "Joystick " << i << " button pressed: " << "SURCLE" << std::endl;
			}
			if (state.buttons[GLFW_GAMEPAD_BUTTON_SQUARE])
			{
				std::cout << "Joystick " << i << " button pressed: " << "SCWARE" << std::endl;
			}
			if (state.buttons[GLFW_GAMEPAD_BUTTON_TRIANGLE])
			{
				std::cout << "Joystick " << i << " button pressed: " << "TWYANGL" << std::endl;
			}
			if (state.buttons[GLFW_GAMEPAD_BUTTON_LEFT_BUMPER])
			{
				std::cout << "Joystick " << i << " button pressed: " << "LEFT_BUMPER" << std::endl;
			}
			if (state.buttons[GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER])
			{
				std::cout << "Joystick " << i << " button pressed: " << "RIGHT_BUMPER" << std::endl;
			}
			if (state.buttons[GLFW_GAMEPAD_BUTTON_BACK])
			{
				std::cout << "Joystick " << i << " button pressed: " << "BACK" << std::endl;
			}
			if (state.buttons[GLFW_GAMEPAD_BUTTON_START])
			{
				std::cout << "Joystick " << i << " button pressed: " << "START" << std::endl;
			}
			if (state.buttons[GLFW_GAMEPAD_BUTTON_GUIDE])
			{
				std::cout << "Joystick " << i << " button pressed: " << "GUIDE" << std::endl;
			}
			if (state.buttons[GLFW_GAMEPAD_BUTTON_LEFT_THUMB])
			{
				std::cout << "Joystick " << i << " button pressed: " << "LEFT_THUMB" << std::endl;
			}
			if (state.buttons[GLFW_GAMEPAD_BUTTON_RIGHT_THUMB])
			{
				std::cout << "Joystick " << i << " button pressed: " << "RIGHT_THUMB" << std::endl;
			}
			if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_UP])
			{
				std::cout << "Joystick " << i << " button pressed: " << "DPAD_UP" << std::endl;
			}
			if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_RIGHT])
			{
				std::cout << "Joystick " << i << " button pressed: " << "DPAD_RIGHT" << std::endl;
			}
			if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_DOWN])
			{
				std::cout << "Joystick " << i << " button pressed: " << "DPAD_DOWN" << std::endl;
			}
			if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_LEFT])
			{
				std::cout << "Joystick " << i << " button pressed: " << "DPAD_LEFT" << std::endl;
			}
			if (abs(state.axes[GLFW_GAMEPAD_AXIS_LEFT_X]) >= 0.1f)
			{
				std::cout << "Joystick " << i << " axis value: " << "LEFT_X" << state.axes[GLFW_GAMEPAD_AXIS_LEFT_X] << std::endl;
			}
			if (abs(state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y]) >= 0.1f)
			{
				std::cout << "Joystick " << i << " axis value: " << "LEFT_Y" << state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] << std::endl;
			}
			if (abs(state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X]) >= 0.1f)
			{
				std::cout << "Joystick " << i << " axis value: " << "RIGHT_X" << state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X] << std::endl;
			}
			if (abs(state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y]) >= 0.1f)
			{
				std::cout << "Joystick " << i << " axis value: " << "RIGHT_Y" << state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y] << std::endl;
			}
			if (state.axes[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER] >= -0.9f)
			{
				std::cout << "Joystick " << i << " axis value: " << "LEFT_TRIGGER" << state.axes[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER] << std::endl;
			}
			if (state.axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER] >= -0.9f)
			{
				std::cout << "Joystick " << i << " axis value: " << "RIGHT_TRIGGER" << state.axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER] << std::endl;
			}

		}
	}
}