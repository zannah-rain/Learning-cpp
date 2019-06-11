#pragma once
#include <string>
#include "FilePath.h"

class FileSystem
{
private:
	// Paths which can't be changed by other classes
	FilePath exePath;
	FilePath exeDirectory;
	
	FilePath calculateExecutablePath(); // Only meant to be used to initialise exePath

public:
	// Paths which can be changed by other classes
	FilePath workingDirectory;

	FileSystem();

	// Path separator on Windows vs other OSs
	static std::string const sc_PathSep;

	FilePath wdRelativePath(std::initializer_list<std::string> const path_parts);
	FilePath exeRelativePath(std::initializer_list<std::string> const path_parts);

	FilePath getExePath();
	FilePath getExeDirectory();
};