#include <memory>
#include "FileSystem/FileSystem.h"
#include "Logger.h"
// GLAD MUST BE INCLUDED BEFORE glfw
#include "glad/glad.h"
#include "glfw3.h"
#include "OpenGL/Shader.h"
#include "OpenGL/Texture.h"
#include "OpenGL/Camera.h"

#include <iostream>

// glm stuff
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

// A callback function we'll use for changing the openGL viewport size
void framebuffer_size_callback(GLFWwindow * window, int height, int width);

// A function to handle inputs
void processInput(GLFWwindow * window, C_Camera * camera, float deltaTime);

int main(int argc, char* argv[])
{
	C_Logger logger;
	C_FileSystem fileSystem;
	C_Camera camera;

	unsigned int cWindowWidth = 640;
	unsigned int cWindowHeight = 480;

	glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
	
	logger.log("Program started");
	
	logger.log("Initial working directory: " + fileSystem.m_WorkingDirectory.toString());
	logger.log("Executable directory: " + fileSystem.getExeDirectory().toString());
	fileSystem.m_WorkingDirectory--; // Set workingDirectory to the project folder, we aren't going to look for files in /bin/ very often
	logger.log("New working directory: " + fileSystem.m_WorkingDirectory.toString());

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
		// positions			// colours			// texture coords
		-0.5f, -0.5f, -0.5f,  	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  	1.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  	1.0f, 1.0f, 1.0f,	1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  	1.0f, 1.0f, 1.0f,	1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  	0.0f, 1.0f, 1.0f,	0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  	1.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  	1.0f, 1.0f, 1.0f,	1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  	1.0f, 1.0f, 1.0f,	1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  	0.0f, 1.0f, 1.0f,	0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  	1.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  	1.0f, 1.0f, 1.0f,	1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  	0.0f, 1.0f, 1.0f,	0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  	0.0f, 1.0f, 1.0f,	0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  	1.0f, 0.0f, 0.0f,	1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  	1.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  	1.0f, 1.0f, 1.0f,	1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  	0.0f, 1.0f, 1.0f,	0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  	0.0f, 1.0f, 1.0f,	0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  	1.0f, 0.0f, 0.0f,	1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  	0.0f, 1.0f, 1.0f,	0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  	1.0f, 1.0f, 1.0f,	1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  	1.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  	1.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  	0.0f, 1.0f, 1.0f,	0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  	0.0f, 1.0f, 1.0f,	0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  	1.0f, 1.0f, 1.0f,	1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  	1.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  	1.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  	0.0f, 1.0f, 1.0f,	0.0f, 1.0f
	};
	// Send them to the GPU!
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Tell openGL how to translate our positional values to its own stuff
	glVertexAttribPointer(
		0, // Which vertex attribute we want to configure, we used location = 0 in the shader
		3, // The size of the vertex attribute, we used vec3 in the shader
		GL_FLOAT, // The type of the data
		GL_FALSE, // Do we want the data to be normalized
		8 * sizeof(float), // The distance between each set of vertex attributes
		(void*)0 // The offset of where the position data begins in the buffer
	);
	glEnableVertexAttribArray(0); // Enable position attribute

	// Tell openGL how to translate our colour to its own stuff
	glVertexAttribPointer(
		1, // Which vertex attribute we want to configure, we used location = 0 in the shader
		3, // The size of the vertex attribute, we used vec3 in the shader
		GL_FLOAT, // The type of the data
		GL_FALSE, // Do we want the data to be normalized
		8 * sizeof(float), // The distance between each set of vertex attributes
		(void*)(3*sizeof(float)) // The offset of where the position data begins in the buffer
	);
	glEnableVertexAttribArray(1); // Enable color attribute

	// Notify openGL the format that the texture coords are in
	glVertexAttribPointer(
		2, // Which vertex attribute we want to configure, we used location = 0 in the shader
		2, // The size of the vertex attribute, we used vec3 in the shader
		GL_FLOAT, // The type of the data
		GL_FALSE, // Do we want the data to be normalized
		8 * sizeof(float), // The distance between each set of vertex attributes
		(void*)(6 * sizeof(float)) // The offset of where the position data begins in the buffer
	);
	glEnableVertexAttribArray(2); // Enable color attribute

	C_Shader shader(fileSystem.wdRelativePath({ "resources", "3dVertexShader.glsl" }).toString().c_str(), 
				  fileSystem.wdRelativePath({ "resources", "3dFragmentShader.glsl" }).toString().c_str());

	C_Texture tex(fileSystem.wdRelativePath({ "resources", "roguelikeSheet_magenta.bmp"}));

	// The matrices to transform stuff to the 2d screen :)
	// model matrix goes from model coords to world coords
	glm::mat4 model = glm::mat4(1.0f); // The model matrix
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	// View matrix
	// Transforms everything relative to the camera position & rotation
	glm::mat4 view = glm::mat4(1.0f);
	// note that we're translating the scene in the reverse direction of where we want to move
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	// Projection matrix
	// Applies perspective!
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), (float)cWindowWidth / (float)cWindowHeight, 0.1f, 100.0f);

	// Send the transformation matrix to the GPU
	unsigned int modelLoc = glGetUniformLocation(shader.m_ID, "model");
	unsigned int viewLoc = glGetUniformLocation(shader.m_ID, "view");
	unsigned int projectionLoc = glGetUniformLocation(shader.m_ID, "projection");

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);

	// MOAR CUBES
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	// Render loop
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	while (!glfwWindowShouldClose(window.get()))
	{
		// Update deltaTime
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Process inputs since last frame
		processInput(window.get(), &camera, deltaTime);

		// Render stuff
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();
		tex.use();

		// Create the view matrix from the camera
		view = camera.view();
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

			// Rotate tha cube
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
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
void processInput(GLFWwindow * window, C_Camera * camera, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	float cameraSpeed = 1.0f; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		camera->move(cameraSpeed * camera->m_Up * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		camera->move(-cameraSpeed * camera->m_Up * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		camera->move(cameraSpeed * camera->m_Right * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		camera->move(-cameraSpeed * camera->m_Right * deltaTime);
}