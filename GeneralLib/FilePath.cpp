#include <assert.h>
#include "FilePath.h"
#include "FileSystem.h"
#include <exception>
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
		m_isRelative = false;
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

FilePath::FilePath()
{

}

FilePath::FilePath(std::initializer_list<std::string> const pathParts)
{
	for (const auto & pathPart : pathParts)
	{
		addPathPart(pathPart);
	}
}

FilePath::FilePath(const std::string path)
{
	std::string currentSection = "";
	for (int i = 0; i != path.size(); ++i)
	{
		if (path[i] == FileSystem::sc_PathSep[0])
		{
			if (!currentSection.empty())
			{
				addPathPart(currentSection);
				currentSection = "";
			}
		}
		else
		{
			currentSection += path[i];
		}
	}
}

std::string FilePath::toString(bool dirOnly)
{
	std::string full_path;
#ifdef _WIN32
	if (m_isRelative)
	{
		full_path += FileSystem::sc_PathSep;
	}
#elif
	if (!m_isRelative)
	{
		full_path += FileSystem::sc_PathSep;
	}
#endif

	for (auto it = m_Folders.begin(); it != m_Folders.end(); ++it)
	{
		full_path += *it + FileSystem::sc_PathSep;
	}

	if (!dirOnly)
	{
		full_path += m_File;
	}
	return full_path;
}

bool FilePath::isDirectory()
{
	return m_File.empty();
}

bool FilePath::isFile()
{
	return !isDirectory();
}

bool FilePath::isRelative()
{
	return m_isRelative;
}

bool FilePath::empty()
{
	return m_Folders.empty() && m_File.empty();
}

// Operator overloads
FilePath FilePath::operator+ (const FilePath& rhs)
{
	if (!rhs.m_isRelative)
	{
		throw std::invalid_argument("Concatenation only defined for relative path rhs.");
	}
	if (!this->m_File.empty())
	{
		throw std::invalid_argument("Attempted to lengthen a FilePath which already has a file in it.");
	}
	if (this->m_isRelative && !rhs.m_isRelative)
	{
		throw std::invalid_argument("Attempted to concatenate a static path with a relative one.");
	}

	FilePath result = *this;

	for (auto it = rhs.m_Folders.cbegin(); it <= rhs.m_Folders.cend(); it++)
	{
		result.m_Folders.push_back(*it);
	}

	result.m_File = rhs.m_File;

	return result;
}

unsigned int FilePath::size()
{
	return m_Folders.size() + !m_File.empty();
}