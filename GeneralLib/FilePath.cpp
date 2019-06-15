#include <assert.h>
#include <cstddef>
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
	for (char i : path)
	{
		if (i == FileSystem::sc_PathSep[0])
		{
			if (!currentSection.empty())
			{
				addPathPart(currentSection);
				currentSection = "";
			}
		}
		else
		{
			currentSection += i;
		}
	}
	if (!currentSection.empty())
	{
		addPathPart(currentSection);
		currentSection = "";
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

	for (auto & Folder : m_Folders)
	{
		full_path += Folder + FileSystem::sc_PathSep;
	}

	if (!dirOnly)
	{
		full_path += m_File;
	}

	return full_path;
}

bool FilePath::isDirectory()
{
	return m_File.empty() && !m_Folders.empty();
}

bool FilePath::isFile()
{
	return !m_File.empty();
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

	for (const auto & Folder : rhs.m_Folders)
	{
		result.m_Folders.push_back(Folder);
	}

	result.m_File = rhs.m_File;

	return result;
}

unsigned int FilePath::size()
{
	return m_Folders.size() + !m_File.empty();
}