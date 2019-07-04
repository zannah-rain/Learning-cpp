#pragma once
#include <string>

#include "FilePath.h"

/**
 * A class to handle interactions with the OS filesystem
 */
class FileSystem
{
private:
	// Paths which can't be changed by other classes
	FilePath exePath; /** Will save the path to the executable when constructed */
	FilePath exeDirectory; /** Will save the directory the executable is in when constructed (for easy relative paths) */
	
	FilePath calculateExecutablePath(); /** Only meant to be used to initialise exePath */

public:
	// Paths which can be changed by other classes
	FilePath workingDirectory; /** Unlike the privately saved exeDirectory, workingDirectory might change over time */


	/**
	 * Constructor
	 *
	 * Just calculates where the program is being run from and stores it so it doesn't need to be run again.
	 */
	FileSystem();

	/**
	 * Path separator, depends on the OS
	 */
	static std::string const sc_PathSep;

	/**
	 * Starting from the workingDirectory, add additional bits of file paths
	 * 
	 * @param path_parts A list of extra strings to add to the path. Typically with one entry representing one folder / file.
	 * @return A FilePath with path_parts appended to the workingDirectory
	 */
	FilePath wdRelativePath(std::initializer_list<std::string> const path_parts) const;

	/**
	 * Starting from the exeDirectory, add additional bits of file paths
	 * 
	 * @param path_parts A list of extra strings to add to the path. Typically with one entry representing one folder / file.
	 * @return A FilePath with path_parts appended to the exeDirectory
	 */
	FilePath exeRelativePath(std::initializer_list<std::string> const path_parts) const;

	/**
	 * Just provides public read-only access to exePath
	 */
	FilePath getExePath() const;

	/**
	 * Just provides public read-only access to exeDirectory
	 */
	FilePath getExeDirectory() const;
};