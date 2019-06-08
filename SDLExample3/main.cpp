#include "SDL.h"
#include <string>
#include <iostream>
#include "Logger.h"
#include "FileSystem.h"

int main(int argc, char* argv[])
{
	Logger logger;
	
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

	FileSystem fileSystem;

	// Check we've calculated the wd properly
	if (fileSystem.wd.empty())
	{
		std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
		std::cerr << fileSystem.getWorkingDirectory() << std::endl;
		return 2;
	}
	else 
	{
		std::string logMessage = ".exe directory: " + fileSystem.wd;
		logger.log(logMessage);
	}

	// Open a window
	SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
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
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr) 
	{
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 4;
	}
	else
	{
		logger.log("Renderer created!");
	}

	// Load a .bmp
	std::string imagePath = fileSystem.wdPath({ "Lesson1", "hello.bmp" });
	std::cout << imagePath << std::endl;
//	SDL_Surface *bmp = SDL_LoadBMP(imagePath.c_str());
//	if (bmp == nullptr) {
//		SDL_DestroyRenderer(ren);
//		SDL_DestroyWindow(win);
//		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
//		SDL_Quit();
//		return 1;
//	}

	// Cleanup before closing
	SDL_DestroyWindow(win);
	logger.log("Window destroyed.");
	SDL_Quit();
	logger.log("SDL quit.");
	return 0;
}