#include "OGLHandler.h"

#include "glad/glad.h"
#include "glfw3.h"

#include <iostream>


C_OGLHandler::C_OGLHandler() : m_WindowWidth(640), m_WindowHeight(480) {}


bool C_OGLHandler::init(GLFWwindow * window, bool mode_2d) const
{
	// Set the initial dimensions of the output window for openGL
	glViewport(0, 0, m_WindowWidth, m_WindowHeight);
	std::cout << "C_OGLHandler:: OpenGL viewport initialised with dimensions: " << m_WindowWidth << "x" << m_WindowHeight << std::endl;

	// Set the framebuffer size callback in glfw to update the above viewport
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	std::cout << "C_OGLHandler:: Registered framebufferSizeCallback with glfw" << std::endl;

	// Enable depth testing
	if (!mode_2d)
	{
		glEnable(GL_DEPTH_TEST);
		std::cout << "C_OGLHandler:: Enabled OpenGL depth testing" << std::endl;
	}
	else
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	// Set the "clear" color we'll overwrite previous frames with before drawing
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
	std::cout << "C_OGLHandler:: Set OpenGL clear colour to 1.0, 0.0, 1.0, 1.0" << std::endl;

	return true;
}


void C_OGLHandler::framebufferSizeCallback(GLFWwindow * window, int width, int height)
{
	// Update the viewport with the new size
	glViewport(0, 0, width, height);
}