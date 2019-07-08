#pragma once

#include "sigslot/signal.hpp"
#include "glfw3.h"

#include "Logger.h"

/**
* A class describing a single controller and its events
*/
class Controller
{
public:
	/**
	* Create a Controller and tell it to watch the glfw controller slot inputID
	* 
	* @param inputID Which controller to watch (0-16 currently)
	*/
	Controller(unsigned int inputID, 
			   float axisSensitivity, 
			   float triggerSensitivity, 
			   Logger logger);

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
	sigslot::signal<> Connected; /** the controller is plugged in OR when "step" is first called if it's already plugged in*/
	sigslot::signal<> Disconnected; /** the controller is unplugged OR when "step" is first called if it's already unplugged*/
	sigslot::signal<> ButtonPressed[GLFW_GAMEPAD_BUTTON_LAST + 1]; /** the button has been pressed since the last step (and wasn't before)*/

	// Should send how long it is held
	sigslot::signal<float> ButtonReleased[GLFW_GAMEPAD_BUTTON_LAST + 1]; /** the button has been released since the last step*/
	sigslot::signal<float> ButtonHeld[GLFW_GAMEPAD_BUTTON_LAST + 1]; /** the button is currently down*/

	// Sends the X & Y value for the axis
	sigslot::signal<float, float> LeftAxisHeld; /** the left axis moves further from 0,0 than mAxisSensitivity in either direction*/
	sigslot::signal<float, float> RightAxisHeld; /** the right axis moves further from 0,0 than mAxisSensitivity in either direction*/

	// Sends the amount the axis is depressed
	sigslot::signal<float> LeftTriggerHeld; /** the left trigger moves further from -1 (min) than mTriggerSensitivity*/
	sigslot::signal<float> RightTriggerHeld; /** the right trigger moves further from -1 (min) than mTriggerSensitivity*/

	float mAxisSensitivity; /** The minimum amount (in either dimension) an axis must be moved before registering as an event*/
	float mTriggerSensitivity; /** The minimum amount a trigger must be depressed before registering as an event*/

	Logger m_Logger; /** The Logger controlling how messages are handled from this object*/


private:
	// Signal logging functions
	/**
	* Log signals sent by Controller.Connected
	*
	* This function should not be called directly
	*/
	void logConnected() const;

	/**
	* Log signals sent by Controller.Disconnected
	*
	* This function should not be called directly
	*/
	void logDisconnected() const;

	/**
	* Log signals sent by Controller.ButtonPressed
	*
	* This function should not be called directly
	*/
	void logButtonPressed() const;

	/**
	* Log signals sent by Controller.ButtonReleased
	*
	* This function should not be called directly
	*
	* @param timeHeld See Controller.ButtonReleased
	*/
	void logButtonReleased(float timeHeld) const;

	/**
	* Log signals sent by Controller.ButtonHeld
	*
	* This function should not be called directly
	*
	* @param timeHeld See Controller.ButtonHeld
	*/
	void logButtonHeld(float timeHeld) const;

	/**
	* Log signals sent by Controller.LeftAxisHeld
	*
	* This function should not be called directly
	*
	* @param x See Controller.LeftAxisHeld
	* @param y See Controller.LeftAxisHeld
	*/
	void logLeftAxisHeld(float x, float y) const;

	/**
	* Log signals sent by Controller.RightAxisHeld
	*
	* This function should not be called directly
	*
	* @param x See Controller.RightAxisHeld
	* @param y See Controller.RightAxisHeld
	*/
	void logRightAxisHeld(float x, float y) const;

	/**
	* Log signals sent by Controller.LeftTriggerHeld
	*
	* This function should not be called directly
	*
	* @param amountDepressed See Controller.LeftTriggerHeld
	*/
	void logLeftTriggerHeld(float amountDepressed) const;

	/**
	* Log signals sent by Controller.RightTriggerHeld
	*
	* This function should not be called directly
	*
	* @param amountDepressed See Controller.RightTriggerHeld
	*/
	void logRightTriggerHeld(float amountDepressed) const;

	// These two variables need to be stored so that the controller state can be compared
	// from frame to frame (call of step to call of step actually)
	GLFWgamepadstate mCurrentState; /** The GLFWgamepadstate from the last step call*/
	bool mJoystickValid; /** Whether the controller was is plugged in a gamepad last step*/

	float mButtonHeldTime[GLFW_GAMEPAD_BUTTON_LAST + 1]; /** How long each button has been held for*/

	unsigned int mInputID; /** Which GLFW input this controller corresponds to*/
};