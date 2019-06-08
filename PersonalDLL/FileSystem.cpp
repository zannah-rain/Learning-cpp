#ifdef _WIN32
#    ifdef LIBRARY_EXPORTS
#        define LIBRARY_API __declspec(dllexport)
#    else
#        define LIBRARY_API __declspec(dllimport)
#    endif
#elif
#    define LIBRARY_API
#endif

#include <string>
#include <initializer_list>
#include "FileSystem.h"

#ifdef _WIN32
std::string const FileSystem::sc_PathSep = "\\";
#else
std::string const FileSystem::sc_PathSep = "/";
#endif

LIBRARY_API FileSystem::FileSystem()
{
	// Directory of the .exe and initial working directory
	exePath = getWorkingDirectory();
	wd = getWorkingDirectory();
}

LIBRARY_API std::string FileSystem::filePath(std::initializer_list<std::string> const path_parts)
{
	auto it = path_parts.begin();
	std::string full_path = *it;
	for (it = ++it; it != path_parts.end(); ++it)
	{
		if ((*it).back() != sc_PathSep.back())
		{
			full_path += sc_PathSep + *it;
		}
		else
		{
			full_path += *it;
		}
	}
	return full_path;
}

LIBRARY_API std::string FileSystem::wdPath(std::initializer_list<std::string> const path_parts)
{
	return wd + filePath(path_parts);
}

// Get the directory that the .exe file is in
LIBRARY_API std::string FileSystem::getWorkingDirectory()
{
	std::string basePath = "TODO";
		
	// SDL returns a pointer to the actual path
	// char * basePathPointer = SDL_GetBasePath();
		
	//if (basePathPointer == nullptr)
	//{
	//	// If it's nullptr then SDL couldn't do it
	//	basePath = "";
	//}
	//else
	//{
	//	basePath = basePathPointer;
	//}

	// Free up SDLs copy of it
	//SDL_free(basePathPointer);
	return basePath;
}