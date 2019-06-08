#ifdef _WIN32
#    ifdef LIBRARY_EXPORTS
#        define LIBRARY_API __declspec(dllexport)
#    else
#        define LIBRARY_API __declspec(dllimport)
#    endif
#elif
#    define LIBRARY_API
#endif

#pragma once
#include <string>
#include <vector>

class FilePath
{
private:

#ifdef _WIN32
	// Linux doesn't use drive qualifiers
	std::string m_Drive;
#endif

	std::vector<std::string> m_Folders;
	std::string m_File;
	void addPathPart(std::string);

public:

	LIBRARY_API FilePath(std::initializer_list<std::string> const pathParts);
	LIBRARY_API FilePath(std::string const path);
	LIBRARY_API std::string to_string();
};

