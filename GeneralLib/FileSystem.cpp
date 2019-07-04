#include <string>
#include <initializer_list>
#include "FileSystem.h"
#include "whereami.h"

#ifdef _WIN32
std::string const FileSystem::sc_PathSep = "\\";
#else
std::string const FileSystem::sc_PathSep = "/";
#endif


FileSystem::FileSystem()
{
	// Directory of the .exe and initial working directory
	exePath = calculateExecutablePath();
	exeDirectory = FilePath(exePath.toString(true));

	workingDirectory = exeDirectory;
}


FilePath FileSystem::wdRelativePath(std::initializer_list<std::string> const path_parts) const
{
	return workingDirectory + FilePath(path_parts);
}


FilePath FileSystem::exeRelativePath(std::initializer_list<std::string> const path_parts) const
{
	return exeDirectory + FilePath(path_parts);
}


FilePath FileSystem::calculateExecutablePath() const
{
	char* path = nullptr;
	int length, dirname_length;
	std::string pathString;

	// Figure out how long the path is going to be in chars, so we can allocate it ahead of time
	length = wai_getExecutablePath(nullptr, 0, &dirname_length);
	if (length > 0)
	{
		// Allocate the right amount of memory (returns pointer to the first bit)
		path = (char*)malloc(length + 1); //TODO: Make smart pointer alternative
		if (!path) // If memory allocation failed
		{
			std::abort();
		}
		wai_getExecutablePath(path, length, &dirname_length);
		path[length] = '\0'; // Add null terminating character to signify the end of the char array
		pathString = path;
		free(path);
	}

	FilePath x = pathString;

	return x;
}


FilePath FileSystem::getExePath() const
{
	return exePath;
}


FilePath FileSystem::getExeDirectory() const
{
	return exeDirectory;
}