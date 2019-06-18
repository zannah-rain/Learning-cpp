#include <memory>
#include <string>
#include <iostream>
#include "FileSystem.h"
#include "Logger.h"

int main(int argc, char* argv[])
{
	Logger logger;
	FileSystem fileSystem;
	
	logger.log("Program started");
	
	logger.log("Initial working directory: " + fileSystem.workingDirectory.toString());
	logger.log("Executable directory: " + fileSystem.getExeDirectory().toString());
	fileSystem.workingDirectory--; // Set workingDirectory to the project folder, we aren't going to look for files in /bin/ very often
	logger.log("New working directory: " + fileSystem.workingDirectory.toString());

	// Cleanup before closing
	return 0;
}
