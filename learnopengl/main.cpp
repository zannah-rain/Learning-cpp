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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Creating the window
	std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> window(glfwCreateWindow(640, 480, "LearnOpenGL", NULL, NULL), &glfwDestroyWindow);
	if (window == NULL)
	{
		logger.log("Window couldn't be created by GLFW");
		glfwTerminate();
		return 1;
	}

	// Set this window as our main context on the current thread
	glfwMakeContextCurrent(window.get());

	// Initialise GLAD before doing anything with openGL
	// GLAD manages function pointers for openGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		logger.log("Failed to initialize GLAD");
		glfwTerminate();
		return 2;
	}

	// Cleanup before closing
	glfwTerminate();
	return 0;
}
