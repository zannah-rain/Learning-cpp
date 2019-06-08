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

class FileSystem 
{
public:
	LIBRARY_API FileSystem();

	// Path separator on Windows vs other OSs
	static std::string const sc_PathSep;

	std::string wd;
	std::string exePath;
	LIBRARY_API std::string filePath(std::initializer_list<std::string> const path_parts);
	LIBRARY_API std::string wdPath(std::initializer_list<std::string> const path_parts);
	LIBRARY_API std::string getWorkingDirectory();
};