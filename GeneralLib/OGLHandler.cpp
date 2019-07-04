#include "OGLHandler.h"

#include "glad/glad.h"
#include "glfw3.h"

OGLHandler::OGLHandler() : windowWidth(640), windowHeight(480) {}

bool OGLHandler::init(GLFWwindow * window)
{
	// Set the initial dimensions of the output window for openGL
	glViewport(0, 0, windowWidth, windowHeight);

	// Set the framebuffer size callback in glfw to update the above viewport
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);

	// Set the "clear" color we'll overwrite previous frames with before drawing
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	return true;
}

void OGLHandler::framebufferSizeCallback(GLFWwindow * window, int width, int height)
{
	// Update the viewport with the new size
	glViewport(0, 0, width, height);
}