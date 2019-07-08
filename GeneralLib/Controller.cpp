#include "Controller.h"

#include <iostream>
#include <string>

#include "zMath.h"


Controller::Controller(unsigned int inputID, 
					   float axisSensitivity, 
					   float triggerSensitivity,
					   Logger logger) :
	mInputID(inputID),
	mAxisSensitivity(axisSensitivity),
	mTriggerSensitivity(triggerSensitivity),
	m_Logger(logger),
	mJoystickValid(false)
{
	// Sets mCurrentState AND mJoystickValid
	mJoystickValid = glfwGetGamepadState(inputID, &mCurrentState);

	// Initialise mButtonHeldTime
	for (size_t i = 0; i <= GLFW_GAMEPAD_BUTTON_LAST; i++)
	{
		mButtonHeldTime[i] = 0;
	}


	// Connect signals to internal logger
	Connected.connect(&Controller::logConnected, this);
	Disconnected.connect(&Controller::logDisconnected, this);

	for (size_t i = 0; i <= GLFW_GAMEPAD_BUTTON_LAST; i++)
	{
		ButtonPressed[i].connect(&Controller::logButtonPressed, this);
		ButtonReleased[i].connect(&Controller::logButtonReleased, this);
		ButtonHeld[i].connect(&Controller::logButtonHeld, this);
	}

	LeftAxisHeld.connect(&Controller::logLeftAxisHeld, this);
	RightAxisHeld.connect(&Controller::logRightAxisHeld, this);
	LeftTriggerHeld.connect(&Controller::logLeftTriggerHeld, this);
	RightTriggerHeld.connect(&Controller::logRightTriggerHeld, this);
}


void Controller::step(float deltaTime)
{
	// Set previous state before updating current state
	GLFWgamepadstate mPreviousState = mCurrentState;

	// Sets current state and returns whether the controller is connected & a gamepad
	bool mJoystickPreviouslyValid = mJoystickValid;
	mJoystickValid = glfwGetGamepadState(mInputID, &mCurrentState);

	if (!mJoystickValid)
	{
		// Check if we need to send a disconnection event
		if (mJoystickPreviouslyValid)
		{
			Disconnected();
		}
		return;
	}

	// Check if we need to send a connection event
	if (!mJoystickPreviouslyValid)
	{
		Connected();
		return; // Other comparisons with previous state don't really make sense if we've just connected it
	}

	// Send button signals
	for (size_t i = 0; i <= GLFW_GAMEPAD_BUTTON_LAST; i++)
	{
		if (mCurrentState.buttons[i])
		{
			// Update how long the buttons been held for
			mButtonHeldTime[i] += deltaTime;

			// Send ButtonHeld signal
			ButtonHeld[i](mButtonHeldTime[i]);

			// See if we should send ButtonPressed
			if (!mPreviousState.buttons[i])
			{
				ButtonPressed[i]();
			}
		}
		else
		{
			// See if the button has just been released
			if (mPreviousState.buttons[i])
			{
				ButtonReleased[i](mButtonHeldTime[i]);
				mButtonHeldTime[i] = 0;
			}
		}
	}

	// Send axis signals
	if (zMath::abs(mCurrentState.axes[GLFW_GAMEPAD_AXIS_LEFT_X]) > mAxisSensitivity ||
		zMath::abs(mCurrentState.axes[GLFW_GAMEPAD_AXIS_LEFT_Y]) > mAxisSensitivity)
	{
		LeftAxisHeld(mCurrentState.axes[GLFW_GAMEPAD_AXIS_LEFT_X], mCurrentState.axes[GLFW_GAMEPAD_AXIS_LEFT_Y]);
	}

	// Send axis signals
	if (zMath::abs(mCurrentState.axes[GLFW_GAMEPAD_AXIS_RIGHT_X]) > mAxisSensitivity ||
		zMath::abs(mCurrentState.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y]) > mAxisSensitivity)
	{
		RightAxisHeld(mCurrentState.axes[GLFW_GAMEPAD_AXIS_RIGHT_X], mCurrentState.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y]);
	}

	// Send trigger signals
	if (mCurrentState.axes[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER] > -1 + mTriggerSensitivity)
	{
		LeftTriggerHeld(mCurrentState.axes[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER]);
	}
	if (mCurrentState.axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER] > -1 + mTriggerSensitivity)
	{
		RightTriggerHeld(mCurrentState.axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER]);
	}
}


bool Controller::isValid()
{
	return glfwJoystickIsGamepad(mInputID);
}


void Controller::logConnected() const
{
	m_Logger.log("Controller connected");
}


void Controller::logDisconnected() const
{
	m_Logger.log("Controller disconnected");
}


void Controller::logButtonPressed() const
{
	m_Logger.log("Button pressed");
}


void Controller::logButtonReleased(float timeHeld) const
{
	m_Logger.log("Button released: " + std::to_string(timeHeld));
}


void Controller::logButtonHeld(float timeHeld) const
{
	m_Logger.log("Button held: " + std::to_string(timeHeld));
}


void Controller::logLeftAxisHeld(float x, float y) const
{
	m_Logger.log("Left axis held: " + std::to_string(x) + ", " + std::to_string(y));
}


void Controller::logRightAxisHeld(float x, float y) const
{
	m_Logger.log("Right axis held: " + std::to_string(x) + ", " + std::to_string(y));
}


void Controller::logLeftTriggerHeld(float amountDepressed) const
{
	m_Logger.log("Left trigger held: " + std::to_string(amountDepressed));
}


void Controller::logRightTriggerHeld(float amountDepressed) const
{
	m_Logger.log("Right trigger held: " + std::to_string(amountDepressed));
}
