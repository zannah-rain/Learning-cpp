#include <memory>

// glad & glfw need loading in this specific order
#include "glad/glad.h"
#include "glfw3.h"

#include "Controller.h"
#include "ECS\World.h"
#include "FileSystem\FileSystem.h"
#include "OpenGL\loadOBJ.h"
#include "Logger.h"
#include "OpenGL\Model.cpp"
#include "OpenGL\OGLHandler.h"
#include "OpenGL\Shader.h"
#include "OpenGL\Texture.h"
#include "OpenGL\Camera.h"
#include "OpenGL\Vertex.h"

#include <iostream>

// glm stuff
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

// ECS stuff
#include "Systems/C_MomentumSystem.h"
#include "Components/S_PositionComponent.h"
#include "Components/S_RotationComponent.h"
#include "Components/S_ModelComponent.h"
#include "Components/S_MomentumComponent.h"

// A callback function we'll use for changing the openGL viewport size
void framebuffer_size_callback(GLFWwindow * window, int height, int width);

// A function to handle inputs
void processInput(GLFWwindow * window, C_Camera * camera, float deltaTime);

int main(int argc, char* argv[])
{
	C_Logger logger;
	C_FileSystem fileSystem;
	C_Camera camera;
	C_OGLHandler oglHandler;
	
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

	C_Controller controller(0, 0.1f, 0.1f, logger);

	// Creating the window
	std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> window(glfwCreateWindow(oglHandler.m_WindowWidth, oglHandler.m_WindowHeight, "LearnOpenGL", NULL, NULL), &glfwDestroyWindow);
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

	std::vector< S_Vertex > cubeVertices;

	loadOBJ(fileSystem.wdRelativePath({ "resources", "cube.obj" }), cubeVertices);

	// Set up and apply our shader (only one so doesn't need to be in the render loop)
	C_Shader shader(fileSystem.wdRelativePath({ "resources", "3dVertexShader.glsl" }).toString().c_str(), 
				    fileSystem.wdRelativePath({ "resources", "3dFragmentShader.glsl" }).toString().c_str());
	shader.use();

	C_Texture tex(fileSystem.wdRelativePath({ "resources", "roguelikeSheet_magenta.bmp" }));

	C_Model cubeModel(cubeVertices, false, &tex);

	// View matrix
	// Transforms everything relative to the camera position & rotation
	glm::mat4 view;

	// Projection matrix
	// Applies perspective!
	glm::mat4 projection;
	// 3D
	//projection = glm::perspective(glm::radians(45.0f), (float)oglHandler.m_WindowWidth / (float)oglHandler.m_WindowHeight, 0.1f, 100.0f);
	// 2D
	projection = glm::ortho(0.0f, 1920.0f, 1080.0f, 0.0f, -1.0f, 1.0f);

	// Send the transformation matrix to the GPU
	unsigned int modelLoc = glGetUniformLocation(shader.m_ID, "model");
	unsigned int viewLoc = glGetUniformLocation(shader.m_ID, "view");
	unsigned int projectionLoc = glGetUniformLocation(shader.m_ID, "projection");


	C_World ECS;
	ECS.addSystem< C_MomentumSystem >(ECS, modelLoc);

	{
		unsigned int cubeID = ECS.newEntity();

		ECS.addComponent< S_PositionComponent >(cubeID, S_PositionComponent());
		ECS.addComponent< S_RotationComponent >(cubeID, S_RotationComponent());
		ECS.addComponent< S_ModelComponent >(cubeID, S_ModelComponent(&cubeModel));
		ECS.addComponent< S_MomentumComponent >(cubeID, S_MomentumComponent(glm::vec3(0.0f, 0.0f, -0.1f), glm::vec3(0.1f, 0.1f, 0.2f), 0.0f));
	}	

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

		controller.step(deltaTime); // Handle changes in controller state

		ECS.step(deltaTime);

		// We have one buffer for drawing to and one to send to the screen
		glfwSwapBuffers(window.get());
		
		// Poll events
		glfwPollEvents();
	}

	// Cleanup before closing
	glfwTerminate();
	return 0;
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