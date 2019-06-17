#include "SDL.h"
#undef main

#include <memory>
#include <string>
#include <iostream>
#include "Logger.h"
#include "FileSystem.h"

int main(int argc, char* argv[])
{
	Logger logger;
	FileSystem fileSystem;
	
	logger.log("Program started");

	// Initialise SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	else
	{
		logger.log("SDL initialised");
	}

	// Check we've calculated the workingDirectory properly
	if (fileSystem.workingDirectory.empty())
	{
		std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
		std::cerr << fileSystem.workingDirectory.toString() << std::endl;
		return 2;
	}
	else 
	{
		logger.log("Initial working directory: " + fileSystem.workingDirectory.toString());
		logger.log("Executable directory: " + fileSystem.getExeDirectory().toString());
		fileSystem.workingDirectory--; // Set workingDirectory to the project folder, we aren't going to look for files in /bin/ very often
		logger.log("New working directory: " + fileSystem.workingDirectory.toString());
	}

	// Open a window

	// We're going to store the pointer to the window in a unique_ptr
	// We need to tell it the class of the thing it points to and the class of the destructor
	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> win(SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN), &SDL_DestroyWindow);
	if (win == nullptr) 
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 3;
	}
	else
	{
		logger.log("Window created!");
	}

	// Create a renderer
	std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> ren(SDL_CreateRenderer(win.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC), &SDL_DestroyRenderer);
	if (ren == nullptr) 
	{
		//SDL_DestroyWindow(win.get());
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 4;
	}
	else
	{
		logger.log("Renderer created!");
	}

	// Load a .bmp
	FilePath imagePath = fileSystem.wdRelativePath({ "resources", "roguelikeSheet_magenta.bmp" });
	std::cout << imagePath.toString() << std::endl;
	std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> bmp(SDL_LoadBMP(imagePath.toString().c_str()), &SDL_FreeSurface);
	if (bmp == nullptr) {
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	// Convert it to a texture
	std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> tex(SDL_CreateTextureFromSurface(ren.get(), bmp.get()), &SDL_DestroyTexture);
	bmp.reset();
	if (tex == nullptr) {
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
	
	//A sleepy rendering loop, wait for 3 seconds and render and present the screen each time
	for (int i = 0; i < 3; ++i) {
		//First clear the renderer
		SDL_RenderClear(ren.get());
		//Draw the texture
		SDL_RenderCopy(ren.get(), tex.get(), NULL, NULL);
		//Update the screen
		SDL_RenderPresent(ren.get());
		//Take a quick break after all that hard work
		SDL_Delay(1000);
	}

	// Cleanup before closing
	//SDL_DestroyWindow(win.get());
	logger.log("Window destroyed.");
	SDL_Quit();
	logger.log("SDL quit.");
	return 0;
}