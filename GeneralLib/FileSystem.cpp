#include <string>
#include <initializer_list>
#include "FileSystem.h"
#include "whereami.h"

#ifdef _WIN32
std::string const C_FileSystem::sc_PathSep = "\\";
#else
std::string const C_FileSystem::sc_PathSep = "/";
#endif


C_FileSystem::C_FileSystem()
{
	// Directory of the .exe and initial working directory
	m_ExePath = calculateExecutablePath();
	m_ExeDirectory = C_FilePath(m_ExePath.toString(true));

	m_WorkingDirectory = m_ExeDirectory;
}


C_FilePath C_FileSystem::wdRelativePath(std::initializer_list<std::string> const path_parts) const
{
	return m_WorkingDirectory + C_FilePath(path_parts);
}


C_FilePath C_FileSystem::exeRelativePath(std::initializer_list<std::string> const path_parts) const
{
	return m_ExeDirectory + C_FilePath(path_parts);
}


C_FilePath C_FileSystem::calculateExecutablePath() const
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

	C_FilePath x = pathString;

	return x;
}


C_FilePath C_FileSystem::getExePath() const
{
	return m_ExePath;
}


C_FilePath C_FileSystem::getExeDirectory() const
{
	return m_ExeDirectory;
}