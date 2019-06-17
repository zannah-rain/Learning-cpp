#include "SDL.h"
#undef main

#include <memory>
#include <string>
#include <iostream>
#include "FileSystem.h"
#include "Logger.h"
#include "Quit.h"

int main(int argc, char* argv[])
{
	Logger logger;
	FileSystem fileSystem;
	SDL_Event event;

	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	
	logger.log("Program started");

	// Initialise SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		logger.log({ "SDL_Init Error: " , SDL_GetError() });
		return 1;
	}
	else
	{
		logger.log("SDL initialised");
	}
	
	logger.log("Initial working directory: " + fileSystem.workingDirectory.toString());
	logger.log("Executable directory: " + fileSystem.getExeDirectory().toString());
	fileSystem.workingDirectory--; // Set workingDirectory to the project folder, we aren't going to look for files in /bin/ very often
	logger.log("New working directory: " + fileSystem.workingDirectory.toString());

	// Open a window

	// We're going to store the pointer to the window in a unique_ptr
	// We need to tell it the class of the thing it points to and the class of the destructor
	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> win(SDL_CreateWindow("Hello World!", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN), &SDL_DestroyWindow);
	if (win == nullptr) 
	{
		logger.log({ "SDL_CreateWindow Error: " , SDL_GetError() });
		Quit();
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
		logger.log({ "SDL_CreateRenderer Error: ", SDL_GetError() });
		Quit();
		return 4;
	}
	else
	{
		logger.log("Renderer created!");
	}

	// Load a .bmp
	FilePath imagePath = fileSystem.wdRelativePath({ "resources", "roguelikeSheet_magenta.bmp" });
	logger.log("imagePath: " + imagePath.toString());
	std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> bmp(SDL_LoadBMP(imagePath.toString().c_str()), &SDL_FreeSurface);
	if (bmp == nullptr) {
		logger.log({ "SDL_LoadBMP Error: ", SDL_GetError() });
		Quit();
		return 1;
	}

	// Convert it to a texture
	std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> tex(SDL_CreateTextureFromSurface(ren.get(), bmp.get()), &SDL_DestroyTexture);
	bmp.reset();
	if (tex == nullptr) {
		logger.log({ "SDL_CreateTextureFromSurface Error: " , SDL_GetError() });
		Quit();
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

	// Game loop
	bool quit = false;
	while (!quit)
	{
		// Handle key presses
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:
				logger.log("Key press");
				switch (event.key.keysym.sym)
				{
				case SDLK_q:
					break;
				case SDLK_LEFT:
					break;
				}
				break;
			case SDL_KEYUP:
				logger.log("Key release");
				break;
			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
					break;
				case SDL_BUTTON_RIGHT:
					break;
				case SDL_BUTTON_MIDDLE:
					break;
				}
				break;
			case SDL_QUIT:
				quit = true;
				break;
			}
		}
	}

	// Cleanup before closing
	Quit();
	return 0;
}