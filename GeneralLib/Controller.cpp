#include "Controller.h"

#include <iostream>
#include <string>

#include "zMath.h"


C_Controller::C_Controller(unsigned int inputID, 
					   float axisSensitivity, 
					   float triggerSensitivity,
					   C_Logger logger) :
	m_InputID(inputID),
	m_AxisSensitivity(axisSensitivity),
	m_TriggerSensitivity(triggerSensitivity),
	m_Logger(logger),
	m_JoystickValid(false)
{
	// Sets m_CurrentState AND m_JoystickValid
	m_JoystickValid = glfwGetGamepadState(inputID, &m_CurrentState);

	// Initialise m_ButtonHeldTime
	for (size_t i = 0; i <= GLFW_GAMEPAD_BUTTON_LAST; i++)
	{
		m_ButtonHeldTime[i] = 0;
	}


	// Connect signals to internal logger
	SIG_Connected.connect(&C_Controller::logConnected, this);
	SIG_Disconnected.connect(&C_Controller::logDisconnected, this);

	for (size_t i = 0; i <= GLFW_GAMEPAD_BUTTON_LAST; i++)
	{
		SIG_ButtonPressed[i].connect(&C_Controller::logButtonPressed, this);
		SIG_ButtonReleased[i].connect(&C_Controller::logButtonReleased, this);
		SIG_ButtonHeld[i].connect(&C_Controller::logButtonHeld, this);
	}

	SIG_LeftAxisHeld.connect(&C_Controller::logLeftAxisHeld, this);
	SIG_RightAxisHeld.connect(&C_Controller::logRightAxisHeld, this);
	SIG_LeftTriggerHeld.connect(&C_Controller::logLeftTriggerHeld, this);
	SIG_RightTriggerHeld.connect(&C_Controller::logRightTriggerHeld, this);
}


void C_Controller::step(float deltaTime)
{
	// Set previous state before updating current state
	GLFWgamepadstate mPreviousState = m_CurrentState;

	// Sets current state and returns whether the controller is connected & a gamepad
	bool mJoystickPreviouslyValid = m_JoystickValid;
	m_JoystickValid = glfwGetGamepadState(m_InputID, &m_CurrentState);

	if (!m_JoystickValid)
	{
		// Check if we need to send a disconnection event
		if (mJoystickPreviouslyValid)
		{
			SIG_Disconnected();
		}
		return;
	}

	// Check if we need to send a connection event
	if (!mJoystickPreviouslyValid)
	{
		SIG_Connected();
		return; // Other comparisons with previous state don't really make sense if we've just connected it
	}

	// Send button signals
	for (size_t i = 0; i <= GLFW_GAMEPAD_BUTTON_LAST; i++)
	{
		if (m_CurrentState.buttons[i])
		{
			// Update how long the buttons been held for
			m_ButtonHeldTime[i] += deltaTime;

			// Send SIG_ButtonHeld signal
			SIG_ButtonHeld[i](m_ButtonHeldTime[i]);

			// See if we should send SIG_ButtonPressed
			if (!mPreviousState.buttons[i])
			{
				SIG_ButtonPressed[i]();
			}
		}
		else
		{
			// See if the button has just been released
			if (mPreviousState.buttons[i])
			{
				SIG_ButtonReleased[i](m_ButtonHeldTime[i]);
				m_ButtonHeldTime[i] = 0;
			}
		}
	}

	// Send axis signals
	if (zMath::abs(m_CurrentState.axes[GLFW_GAMEPAD_AXIS_LEFT_X]) > m_AxisSensitivity ||
		zMath::abs(m_CurrentState.axes[GLFW_GAMEPAD_AXIS_LEFT_Y]) > m_AxisSensitivity)
	{
		SIG_LeftAxisHeld(m_CurrentState.axes[GLFW_GAMEPAD_AXIS_LEFT_X], m_CurrentState.axes[GLFW_GAMEPAD_AXIS_LEFT_Y]);
	}

	// Send axis signals
	if (zMath::abs(m_CurrentState.axes[GLFW_GAMEPAD_AXIS_RIGHT_X]) > m_AxisSensitivity ||
		zMath::abs(m_CurrentState.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y]) > m_AxisSensitivity)
	{
		SIG_RightAxisHeld(m_CurrentState.axes[GLFW_GAMEPAD_AXIS_RIGHT_X], m_CurrentState.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y]);
	}

	// Send trigger signals
	if (m_CurrentState.axes[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER] > -1 + m_TriggerSensitivity)
	{
		SIG_LeftTriggerHeld(m_CurrentState.axes[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER]);
	}
	if (m_CurrentState.axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER] > -1 + m_TriggerSensitivity)
	{
		SIG_RightTriggerHeld(m_CurrentState.axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER]);
	}
}


bool C_Controller::isValid()
{
	return glfwJoystickIsGamepad(m_InputID);
}


void C_Controller::logConnected() const
{
	m_Logger.log("Controller connected");
}


void C_Controller::logDisconnected() const
{
	m_Logger.log("Controller disconnected");
}


void C_Controller::logButtonPressed() const
{
	m_Logger.log("Button pressed");
}


void C_Controller::logButtonReleased(float timeHeld) const
{
	m_Logger.log("Button released: " + std::to_string(timeHeld));
}


void C_Controller::logButtonHeld(float timeHeld) const
{
	m_Logger.log("Button held: " + std::to_string(timeHeld));
}


void C_Controller::logLeftAxisHeld(float x, float y) const
{
	m_Logger.log("Left axis held: " + std::to_string(x) + ", " + std::to_string(y));
}


void C_Controller::logRightAxisHeld(float x, float y) const
{
	m_Logger.log("Right axis held: " + std::to_string(x) + ", " + std::to_string(y));
}


void C_Controller::logLeftTriggerHeld(float amountDepressed) const
{
	m_Logger.log("Left trigger held: " + std::to_string(amountDepressed));
}


void C_Controller::logRightTriggerHeld(float amountDepressed) const
{
	m_Logger.log("Right trigger held: " + std::to_string(amountDepressed));
}
