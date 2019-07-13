#pragma once
#include <string>

#include "FilePath.h"

/**
 * A class to handle interactions with the OS filesystem
 */
class C_FileSystem
{
public:
	/**
	 * Constructor
	 *
	 * Just calculates where the program is being run from and stores it so it doesn't need to be run again.
	 */
	C_FileSystem();

	/**
	 * Starting from the m_WorkingDirectory, add additional bits of file paths
	 * 
	 * @param path_parts A list of extra strings to add to the path. Typically with one entry representing one folder / file.
	 * @return A C_FilePath with path_parts appended to the m_WorkingDirectory
	 */
	C_FilePath wdRelativePath(std::initializer_list<std::string> const path_parts) const;

	/**
	 * Starting from the m_ExeDirectory, add additional bits of file paths
	 * 
	 * @param path_parts A list of extra strings to add to the path. Typically with one entry representing one folder / file.
	 * @return A C_FilePath with path_parts appended to the m_ExeDirectory
	 */
	C_FilePath exeRelativePath(std::initializer_list<std::string> const path_parts) const;

	/**
	 * Just provides public read-only access to m_ExePath
	 */
	C_FilePath getExePath() const;

	/**
	 * Just provides public read-only access to m_ExeDirectory
	 */
	C_FilePath getExeDirectory() const;

private:
	C_FilePath calculateExecutablePath() const; /** Only meant to be used to initialise m_ExePath */

	// Paths which can't be changed by other classes
	C_FilePath m_ExePath; /** Will save the path to the executable when constructed */
	C_FilePath m_ExeDirectory; /** Will save the directory the executable is in when constructed (for easy relative paths) */

public:
	// Paths which can be changed by other classes
	C_FilePath m_WorkingDirectory; /** Unlike the privately saved m_ExeDirectory, m_WorkingDirectory might change over time */

	/**
	 * Path separator, depends on the OS
	 */
	static std::string const sc_PathSep;
};