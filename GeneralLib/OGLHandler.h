#pragma once

// Forward declarations
struct GLFWwindow;

/**
* A class to handle global / very general openGL settings
*/
class OGLHandler
{
public:
	/**
	* Default Constructor
	* Just initialises member variables to reasonable defaults
	*/
	OGLHandler();

	/**
	* Perform basic open GL initialisation steps.
	* 
	* Sets viewport size to windowWidth, windowHeight.
	* Adds a callback to glfw to update said width & height when the window size changes.
	* Enables depth testing.
	* Sets the clear colour.
	*/
	bool init(GLFWwindow * window) const;

	/** 
	* A callback function to keep the openGL viewport size synced with the window size
	* 
	* @param window A pointer to the relevant glfw window
	* @param width How wide the window now is
	* @param height How tall the window now is
	*/
	static void framebufferSizeCallback(GLFWwindow * window, int width, int height);

	unsigned int windowWidth; /** The window width that openGL is currently set up to use*/
	unsigned int windowHeight; /** The window height that openGL is currently set up to use*/
};