#include <assert.h>
#include <cstddef>
#include "FilePath.h"
#include "FileSystem.h"
#include <exception>
#include <string>


void C_FilePath::addPathPart(std::string pathPart)
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
		m_IsRelative = false;
	}
#endif

	if (pathPart.find(".") != std::string::npos)
	{
		// We're only expecting to be "adding" more data to our C_FilePath
		// If it turns out we're overwriting something, error
		assert(m_File.size() == 0);

		m_File = pathPart;
		return;
	}

	m_Folders.push_back(pathPart);
	return;
}


C_FilePath::C_FilePath()
{

}


C_FilePath::C_FilePath(std::initializer_list<std::string> const pathParts)
{
	for (const std::string & pathPart : pathParts)
	{
		addPathPart(pathPart);
	}
}


C_FilePath::C_FilePath(const std::string path)
{
	std::string currentSection = "";
	for (char i : path)
	{
		if (i == C_FileSystem::sc_PathSep[0])
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


std::string C_FilePath::toString(bool dirOnly) const
{
	std::string full_path;
#ifdef _WIN32
	if (m_IsRelative)
	{
		full_path += C_FileSystem::sc_PathSep;
	}
#elif
	if (!m_IsRelative)
	{
		full_path += C_FileSystem::sc_PathSep;
	}
#endif

	for (const std::string & Folder : m_Folders)
	{
		full_path += Folder + C_FileSystem::sc_PathSep;
	}

	if (!dirOnly)
	{
		full_path += m_File;
	}

	return full_path;
}


bool C_FilePath::isDirectory() const
{
	return m_File.empty() && !m_Folders.empty();
}


bool C_FilePath::isFile() const
{
	return !m_File.empty();
}


bool C_FilePath::isRelative() const
{
	return m_IsRelative;
}


bool C_FilePath::empty() const
{
	return m_Folders.empty() && m_File.empty();
}


// Operator overloads
C_FilePath& C_FilePath::operator+= (const C_FilePath& rhs)
{
	if (!rhs.m_IsRelative)
	{
		throw std::invalid_argument("Concatenation only defined for relative path rhs.");
	}
	if (!this->m_File.empty())
	{
		throw std::invalid_argument("Attempted to lengthen a C_FilePath which already has a file in it.");
	}
	if (this->m_IsRelative && !rhs.m_IsRelative)
	{
		throw std::invalid_argument("Attempted to concatenate a static path with a relative one.");
	}

	for (const std::string & Folder : rhs.m_Folders)
	{
		m_Folders.push_back(Folder);
	}

	m_File = rhs.m_File;

	return *this;
}


C_FilePath C_FilePath::operator+ (const C_FilePath& rhs) const
{
	C_FilePath result = *this;
	result += rhs;
	return result;
}


bool C_FilePath::operator==(const C_FilePath& rhs) const
{
	return toString() == rhs.toString();
}


bool C_FilePath::operator!=(const C_FilePath& rhs) const
{
	return !(*this == rhs);
}


C_FilePath& C_FilePath::operator--() //prefix operator
{
	assert(!empty()); // Can't decrement an already empty C_FilePath
	if (!m_File.empty())
	{
		m_File = "";
	}
	else if (!m_Folders.empty())
	{
		m_Folders.pop_back();
	}
	return *this;
}


C_FilePath C_FilePath::operator--(int) //postfix operator
{
	C_FilePath currentPath = *this; // Create a copy of the current C_FilePath
	--*this; // Decrement it in place
	return currentPath; // Return the original copy for use in the original expression
}


unsigned int C_FilePath::size() const
{
	return m_Folders.size() + !m_File.empty();
}