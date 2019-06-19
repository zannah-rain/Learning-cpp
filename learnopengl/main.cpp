#include <memory>
#include "FileSystem.h"
#include "Logger.h"
// GLAD MUST BE INCLUDED BEFORE glfw
#include <glad/glad.h>
#include "glfw3.h"

int main(int argc, char* argv[])
{
	Logger logger;
	FileSystem fileSystem;
	
	logger.log("Program started");
	
	logger.log("Initial working directory: " + fileSystem.workingDirectory.toString());
	logger.log("Executable directory: " + fileSystem.getExeDirectory().toString());
	fileSystem.workingDirectory--; // Set workingDirectory to the project folder, we aren't going to look for files in /bin/ very often
	logger.log("New working directory: " + fileSystem.workingDirectory.toString());

	// Init glfw
	if (!glfwInit()) {
		logger.log("GLFW couldn't initialize");
		return -1;
	}

	// Creating the window
	// std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> window(glfwCreateWindow(640, 480, "WINDOW_TITLE", NULL, NULL), &glfwDestroyWindow);
	GLFWwindow * window = glfwCreateWindow(640, 480, "BAL", NULL, NULL);
	if (window == NULL)
	{
		logger.log("Window couldn't be created by GLFW");
		return 1;
	}

	// Cleanup before closing
	return 0;
}
