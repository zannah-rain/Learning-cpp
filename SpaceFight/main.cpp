#include <memory>

// glad & glfw need loading in this specific order
#include "glad/glad.h"
#include "glfw3.h"

#include "Controllers.h"
#include "FileSystem.h"
#include "loadOBJ.h"
#include "Logger.h"
#include "Model.cpp"
#include "OGLHandler.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Vertex.h"
#include "WorldObject.h"

#include <iostream>

// glm stuff
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"

// A callback function we'll use for changing the openGL viewport size
void framebuffer_size_callback(GLFWwindow * window, int height, int width);

// A function to handle inputs
void processInput(GLFWwindow * window, Camera * camera, float deltaTime);

int main(int argc, char* argv[])
{
	Logger logger;
	FileSystem fileSystem;
	Camera camera;
	OGLHandler oglHandler;
	
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

	Controllers controllers;

	// Creating the window
	std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> window(glfwCreateWindow(oglHandler.windowWidth, oglHandler.windowHeight, "LearnOpenGL", NULL, NULL), &glfwDestroyWindow);
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

	oglHandler.init(window.get()); // Initialise global openGL stuff

	// Create a Vertex Array Object to store a bunch of configurations
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	// Create our Vertex Buffer Object, to pass vertices to the GPU
	unsigned int VBO;
	glGenBuffers(1, &VBO); // Creates a bunch of buffers

	std::vector< Vertex > cubeVertices;

	loadOBJ(fileSystem.wdRelativePath({ "resources", "cube.obj" }), cubeVertices);

	for (const Vertex i : cubeVertices)
	{
		std::cout << " X: " << i.posX << " Y: " << i.posY << " Z: " << i.posZ << " R: " << i.r << " G: " << i.g << " B: " << i.b << " A: " << i.a << " texX: " << i.texX << " texY: " << i.texY << std::endl;
	}

	// Set up and apply our shader (only one so doesn't need to be in the render loop)
	Shader shader(fileSystem.wdRelativePath({ "resources", "3dVertexShader.glsl" }).toString().c_str(), 
				  fileSystem.wdRelativePath({ "resources", "3dFragmentShader.glsl" }).toString().c_str());
	shader.use();

	Texture tex(fileSystem.wdRelativePath({ "resources", "roguelikeSheet_magenta.bmp" }));

	Model cubeModel(cubeVertices, VAO, VBO, false, &tex);

	// View matrix
	// Transforms everything relative to the camera position & rotation
	glm::mat4 view;

	// Projection matrix
	// Applies perspective!
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), (float)oglHandler.windowWidth / (float)oglHandler.windowHeight, 0.1f, 100.0f);

	// Send the transformation matrix to the GPU
	unsigned int modelLoc = glGetUniformLocation(shader.ID, "model");
	unsigned int viewLoc = glGetUniformLocation(shader.ID, "view");
	unsigned int projectionLoc = glGetUniformLocation(shader.ID, "projection");

	std::vector< std::unique_ptr< WorldObject > > worldObjects;
	worldObjects.push_back(std::make_unique< WorldObject >(glm::vec3(0.0f, 0.0f, 0.0f), &cubeModel));

	// The projection matrix is constant so we can send it before the render loop
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

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

		// Create the view matrix from the camera
		view = camera.view();
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		glBindVertexArray(VAO);

		controllers.step(); // Handle changes in controller state

		glm::mat4 modelMatrix;
		for (std::unique_ptr< WorldObject > &i : worldObjects)
		{
			i->step(deltaTime);

			modelMatrix = i->getModelMatrix();

			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

			i->mpModel->draw();
		}

		// We have one buffer for drawing to and one to send to the screen
		glfwSwapBuffers(window.get());
		
		// Poll events
		glfwPollEvents();

		// Process controller inputs
		controllers.logEvents();
	}

	// Cleanup before closing
	glfwTerminate();
	return 0;
}

// Handle inputs
void processInput(GLFWwindow * window, Camera * camera, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	float cameraSpeed = 1.0f; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		camera->move(cameraSpeed * camera->up * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		camera->move(-cameraSpeed * camera->up * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		camera->move(cameraSpeed * camera->right * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		camera->move(-cameraSpeed * camera->right * deltaTime);
}