#pragma once
#include <string>
#include <vector>

class FilePath
{
private:
	// In windows we can guess this based on whether the drive is there or not
	// In Linux we need it as its own member, based on whether the original path begins with a /
	bool m_isRelative = true;

	std::vector<std::string> m_Folders;
	std::string m_File;
	void addPathPart(std::string);

public:
	// Initialisers
	FilePath();
	FilePath(std::initializer_list<std::string> const pathParts);
	FilePath(std::string const path);

	// Operator overloads
	FilePath operator+ (const FilePath& rhs);

	// Conversion
	std::string toString(bool dirOnly = false);

	// Attributes
	bool isRelative();
	bool isFile();
	bool isDirectory();
	unsigned int size();
	bool empty();
};

