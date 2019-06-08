#ifdef _WIN32
#    ifdef LIBRARY_EXPORTS
#        define LIBRARY_API __declspec(dllexport)
#    else
#        define LIBRARY_API __declspec(dllimport)
#    endif
#elif
#    define LIBRARY_API
#endif

#include <assert.h>
#include "FilePath.h"
#include "FileSystem.h"
#include <string>


void FilePath::addPathPart(std::string pathPart)
{
	// Strings are classified in this order:
	// If it ends in ":", it is assumed to be a drive
	// If it contains a ".", it is assumed to be a file
	// Otherwise, it's assumed to be a folder

	
#ifdef _WIN32
	// Drive id's are on Windows but not on Linux
	// Drives end in a : character
	if (pathPart.back() == ':') 
	{
		// We're only expecting to be "adding" more data to our FilePath
		// If it turns out we're overwriting something, error
		assert(m_Drive.size() == 0);

		m_Drive = pathPart;
		return;
	}
#endif

	if (pathPart.find(".") != std::string::npos)
	{
		// We're only expecting to be "adding" more data to our FilePath
		// If it turns out we're overwriting something, error
		assert(m_File.size() == 0);

		m_File = pathPart;
		return;
	}

	m_Folders.push_back(pathPart);
	return;
}

LIBRARY_API FilePath::FilePath(std::initializer_list<std::string> const pathParts)
{
	for (auto it = pathParts.begin(); it != pathParts.end(); ++it)
	{
		addPathPart(*it);
	}
}

LIBRARY_API FilePath::FilePath(const std::string path)
{
	std::string currentSection = "";
	for (int i = 0; i != path.size(); ++i)
	{
		if (path[i] == FileSystem::sc_PathSep[0])
		{
			if (currentSection != "")
			{
				addPathPart(currentSection);
				currentSection = "";
			}
		}
	}
}

LIBRARY_API std::string FilePath::to_string()
{
	std::string full_path = m_Drive;

	for (auto it = m_Folders.begin(); it != m_Folders.end(); ++it)
	{
		full_path += FileSystem::sc_PathSep + *it;
	}

	full_path += FileSystem::sc_PathSep + m_File;
	return full_path;
}