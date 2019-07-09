#pragma once

#include "sigslot/signal.hpp"
#include "glfw3.h"

#include "Logger.h"

/**
* A class describing a single controller and its events
*/
class C_Controller
{
public:
	/**
	* Create a C_Controller and tell it to watch the glfw controller slot inputID
	* 
	* @param inputID Which controller to watch (0-16 currently)
	*/
	C_Controller(unsigned int inputID, 
			     float axisSensitivity, 
			     float triggerSensitivity, 
			     C_Logger logger);

	/**
	* Update the state of the controller & send any relevant signals
	* 
	* @param deltaTime How much time has passed since the last update
	*/
	void step(float deltaTime);

	/**
	* Check if this controller is connected & useable
	*
	* @return If the controller is connected & is useable as a gamepad
	*/
	bool isValid();

	// SIGNALS!! Sent when:
	sigslot::signal<> SIG_Connected; /** the controller is plugged in OR when "step" is first called if it's already plugged in*/
	sigslot::signal<> SIG_Disconnected; /** the controller is unplugged OR when "step" is first called if it's already unplugged*/
	sigslot::signal<> SIG_ButtonPressed[GLFW_GAMEPAD_BUTTON_LAST + 1]; /** the button has been pressed since the last step (and wasn't before)*/

	// Should send how long it is held
	sigslot::signal<float> SIG_ButtonReleased[GLFW_GAMEPAD_BUTTON_LAST + 1]; /** the button has been released since the last step*/
	sigslot::signal<float> SIG_ButtonHeld[GLFW_GAMEPAD_BUTTON_LAST + 1]; /** the button is currently down*/

	// Sends the X & Y value for the axis
	sigslot::signal<float, float> SIG_LeftAxisHeld; /** the left axis moves further from 0,0 than m_AxisSensitivity in either direction*/
	sigslot::signal<float, float> SIG_RightAxisHeld; /** the right axis moves further from 0,0 than m_AxisSensitivity in either direction*/

	// Sends the amount the axis is depressed
	sigslot::signal<float> SIG_LeftTriggerHeld; /** the left trigger moves further from -1 (min) than m_TriggerSensitivity*/
	sigslot::signal<float> SIG_RightTriggerHeld; /** the right trigger moves further from -1 (min) than m_TriggerSensitivity*/

	float m_AxisSensitivity; /** The minimum amount (in either dimension) an axis must be moved before registering as an event*/
	float m_TriggerSensitivity; /** The minimum amount a trigger must be depressed before registering as an event*/

	C_Logger m_Logger; /** The C_Logger controlling how messages are handled from this object*/


private:
	// Signal logging functions
	/**
	* Log signals sent by C_Controller.SIG_Connected
	*
	* This function should not be called directly
	*/
	void logConnected() const;

	/**
	* Log signals sent by C_Controller.SIG_Disconnected
	*
	* This function should not be called directly
	*/
	void logDisconnected() const;

	/**
	* Log signals sent by C_Controller.SIG_ButtonPressed
	*
	* This function should not be called directly
	*/
	void logButtonPressed() const;

	/**
	* Log signals sent by C_Controller.SIG_ButtonReleased
	*
	* This function should not be called directly
	*
	* @param timeHeld See C_Controller.SIG_ButtonReleased
	*/
	void logButtonReleased(float timeHeld) const;

	/**
	* Log signals sent by C_Controller.SIG_ButtonHeld
	*
	* This function should not be called directly
	*
	* @param timeHeld See C_Controller.SIG_ButtonHeld
	*/
	void logButtonHeld(float timeHeld) const;

	/**
	* Log signals sent by C_Controller.SIG_LeftAxisHeld
	*
	* This function should not be called directly
	*
	* @param x See C_Controller.SIG_LeftAxisHeld
	* @param y See C_Controller.SIG_LeftAxisHeld
	*/
	void logLeftAxisHeld(float x, float y) const;

	/**
	* Log signals sent by C_Controller.SIG_RightAxisHeld
	*
	* This function should not be called directly
	*
	* @param x See C_Controller.SIG_RightAxisHeld
	* @param y See C_Controller.SIG_RightAxisHeld
	*/
	void logRightAxisHeld(float x, float y) const;

	/**
	* Log signals sent by C_Controller.SIG_LeftTriggerHeld
	*
	* This function should not be called directly
	*
	* @param amountDepressed See C_Controller.SIG_LeftTriggerHeld
	*/
	void logLeftTriggerHeld(float amountDepressed) const;

	/**
	* Log signals sent by C_Controller.SIG_RightTriggerHeld
	*
	* This function should not be called directly
	*
	* @param amountDepressed See C_Controller.SIG_RightTriggerHeld
	*/
	void logRightTriggerHeld(float amountDepressed) const;

	// These two variables need to be stored so that the controller state can be compared
	// from frame to frame (call of step to call of step actually)
	GLFWgamepadstate m_CurrentState; /** The GLFWgamepadstate from the last step call*/
	bool m_JoystickValid; /** Whether the controller was is plugged in a gamepad last step*/

	float m_ButtonHeldTime[GLFW_GAMEPAD_BUTTON_LAST + 1]; /** How long each button has been held for*/

	unsigned int m_InputID; /** Which GLFW input this controller corresponds to*/
};