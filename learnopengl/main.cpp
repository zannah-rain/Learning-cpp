#include <memory>
#include "FileSystem.h"
#include "Logger.h"
// GLAD MUST BE INCLUDED BEFORE glfw
#include "glad/glad.h"
#include "glfw3.h"
#include "vertexShaderExample.h"

// A callback function we'll use for changing the openGL viewport size
void framebuffer_size_callback(GLFWwindow * window, int height, int width);

// A function to handle inputs
void processInput(GLFWwindow * window);

int main(int argc, char* argv[])
{
	Logger logger;
	FileSystem fileSystem;

	unsigned int cWindowWidth = 640;
	unsigned int cWindowHeight = 480;
	
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
	std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> window(glfwCreateWindow(cWindowWidth, cWindowHeight, "LearnOpenGL", NULL, NULL), &glfwDestroyWindow);
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

	// Set the initial dimensions of the output window for openGL
	glViewport(0, 0, cWindowWidth, cWindowHeight);

	glfwSetFramebufferSizeCallback(window.get(), framebuffer_size_callback);

	// Set the "clear" color we'll overwrite previous frames with before drawing
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	// Create a Vertex Array Object to store a bunch of configurations
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO); // Assign vertex options to this array

	// Create our Vertex Buffer Object, to pass vertices to the GPU
	unsigned int VBO;
	glGenBuffers(1, &VBO); // Creates a bunch of buffers
	
	// Bind the Vertex Buffer Object before passing vertices!
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Specify that VBO should be an array buffer (for vertices)
	// Define vertices of two triangles in the CPU!
	float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f   // bottom left
	};
	// Send them to the GPU!
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Tell openGL how to translate our values to its own stuff
	glVertexAttribPointer(
		0, // Which vertex attribute we want to configure, we used location = 0 in the shader
		3, // The size of the vertex attribute, we used vec3 in the shader
		GL_FLOAT, // The type of the data
		GL_FALSE, // Do we want the data to be normalized
		3 * sizeof(float), // The distance between each set of vertex attributes
		(void*)0 // The offset of where the position data begins in the buffer
	);
	glEnableVertexAttribArray(0);

	// Create our vertex shader & compile it
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER); // Create it
	char * rgbaVertexShaderSource =
		#include "rgbaVertexShader.h"
	;
	glShaderSource(vertexShader, 1, &rgbaVertexShaderSource, NULL); //See vertexShaderExample.h
	glCompileShader(vertexShader);

	// Check if compilation was successful
	{
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			logger.log("ERROR::SHADER::VERTEX::COMPILATION_FAILED");
			logger.log(infoLog);
			glfwTerminate();
			return 3;
		}
	}

	// Create our fragment shader & compile it too!
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	char * rgbaFragmentShaderSource =
		#include "rgbaFragmentShader.h"
	;
	glShaderSource(fragmentShader, 1, &rgbaFragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Create our shader program, which links all our shaders together
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	// Link it to the shaders we've made
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram); // Make the program!

	// Check the program was creates successfully
	{
		int success;
		char infoLog[512];
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

		if (!success)
		{
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			logger.log("ERROR::PROGRAM::LINKING_FAILED");
			logger.log(infoLog);
			glfwTerminate();
			return 4;
		}
	}

	// Once the shaders have been linked in to a program, we no longer need them
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Render loop
	while (!glfwWindowShouldClose(window.get()))
	{
		// Process inputs since last frame
		processInput(window.get());

		// Render stuff
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		// We have one buffer for drawing to and one to send to the screen
		glfwSwapBuffers(window.get());
		glfwPollEvents();
	}

	// Cleanup before closing
	glfwTerminate();
	return 0;
}

// Create a callback function to keep the openGL viewport size synced with
// the window size
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// Handle inputs
void processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}