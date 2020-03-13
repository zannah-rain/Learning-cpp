// TODO Get Cmake to link the SOIL static library

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
#include "OpenGL\Camera.h"
#include "OpenGL\Vertex.h"

#include "ResourceManager.h"

#include <iostream>

// glm stuff
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

// ECS stuff
#include "Systems/C_SpriteSystem.h"
#include "Components/S_PositionComponent.h"
#include "Components/S_RotationComponent.h"
#include "Components/S_ModelComponent.h"
#include "Components/S_SpriteComponent.h"

#include "OpenGL/SpriteRenderer.h"

// A callback function we'll use for changing the openGL viewport size
void framebuffer_size_callback(GLFWwindow * window, int height, int width);

// A function to handle inputs
void processInput(GLFWwindow * window, C_Camera * camera, float deltaTime);

int main(int argc, char* argv[])
{
	C_Logger logger;
	C_FileSystem fileSystem;
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

	oglHandler.init(window.get(), true); // Initialise global openGL stuff

	// Projection matrix
	glm::mat4 projection;
	projection = glm::ortho(0.0f, 640.0f, 480.0f, 0.0f, -1.0f, 1.0f);

	// Set up and apply our shader (only one so doesn't need to be in the render loop)
	ResourceManager::LoadShader(
		fileSystem.wdRelativePath({ "resources", "2dVertexShader.glsl" }).toString().c_str(),
		fileSystem.wdRelativePath({ "resources", "2dFragmentShader.glsl" }).toString().c_str(),
		"2DShader");

	ResourceManager::GetShader("2DShader").use();
	ResourceManager::GetShader("2DShader").setInt("image", 0);
	ResourceManager::GetShader("2DShader").SetMatrix4("projection", projection);
	
	ResourceManager::LoadTexture(fileSystem.wdRelativePath({ "resources", "roguelikeSheet_magenta.bmp" }).toString().c_str(), true, "roguelike_test");
	ResourceManager::LoadTexture(fileSystem.wdRelativePath({ "resources", "sprites", "PNG", "Default size", "Environment", "medievalEnvironment_01.png" }).toString().c_str(), true, "tree");
	
	C_SpriteRenderer spriteRenderer(ResourceManager::GetShader("2DShader"));

	// Set up ECS
	C_World ECS;
	ECS.addSystem< C_SpriteSystem >(ECS, &spriteRenderer);

	{
		unsigned int treeID = ECS.newEntity();

		ECS.addComponent< S_PositionComponent >(treeID, S_PositionComponent());
		ECS.addComponent< S_RotationComponent >(treeID, S_RotationComponent());
		ECS.addComponent< S_SpriteComponent >(treeID, S_SpriteComponent("tree"));
	}

	// Render loop
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	while (!glfwWindowShouldClose(window.get()))
	{
		// Update deltaTime
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Render stuff
		glClear(GL_COLOR_BUFFER_BIT); // Add  | GL_DEPTH_BUFFER_BIT for 3d

		controller.step(deltaTime); // Handle changes in controller state

		ECS.step(deltaTime);

		ResourceManager::GetShader("2DShader").use();

		//spriteRenderer.DrawSprite(ResourceManager::GetTexture("tree"), glm::vec2(-200, -200), glm::vec2(100.0f, 100.0f), 0.0f, glm::vec3(1.0f));
		spriteRenderer.DrawSprite(ResourceManager::GetTexture("tree"), glm::vec2(200, 200), glm::vec2(100.0f, 100.0f), 0.0f, glm::vec3(1.0f));
		//spriteRenderer.DrawSprite(ResourceManager::GetTexture("tree"), glm::vec2(-200, 200), glm::vec2(100.0f, 100.0f), 0.0f, glm::vec3(1.0f));
		//spriteRenderer.DrawSprite(ResourceManager::GetTexture("tree"), glm::vec2(200, -200), glm::vec2(100.0f, 100.0f), 0.0f, glm::vec3(1.0f));

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