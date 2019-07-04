#pragma once
#include <string>
#include <vector>

/**
 * A class to hold a file path and provide relevant methods which would be a pain to program for strings
 */
class FilePath
{
public:
	FilePath(); /** Initialise a blank FilePath */
	FilePath(std::initializer_list<std::string> const pathParts); /** Initialise a FilePath from a list of strings. Calls addPathPart on each part! */
	FilePath(std::string const path); /** Initialise from a single string. Scans the string for the OSs path separator char to automatically guess parts */

	// Operator overloads
	/**
	 * Override the += operator to append the rhs FilePath to the lhs FilePath
	 *
	 * @param rhs A relative FilePath to add to lhs
	 * @return A reference to the lhs FilePath after it has has rhs appended to it
	 */
	FilePath& operator+= (const FilePath& rhs);

	/**
	 * Override the + operator to append the rhs FilePath to the lhs FilePath
	 *
	 * @param rhs A relative FilePath to add to lhs
	 * @return A FilePath with rhs appended to lhs
	 */
	FilePath operator+ (const FilePath& rhs) const;

	/**
	 * Override the == operator to compare the rhs FilePath to the lhs FilePath
	 *
	 * @param rhs A FilePath to compare with lhs
	 * @return true if both FilePaths resolve to the same string
	 */
	bool operator== (const FilePath& rhs) const;

	/**
	 * Override the != operator to compare the rhs FilePath to the lhs FilePath
	 *
	 * @param rhs A FilePath to compare with lhs
	 * @return false if both FilePaths resolve to the same string
	 */
	bool operator!= (const FilePath& rhs) const;

	/**
	 * Decrements a FilePath, removes the rightmost file / folder
	 *
	 * @return A FilePath& with one less file / folder
	 */
	FilePath& operator--(); //prefix decrement operator

	/**
	 * Decrements a FilePath, removes the rightmost file / folder
	 *
	 * @return A FilePath& with one less file / folder
	 */
	FilePath operator--(int); //postfix decrement operator

	// Conversion
	/**
	 * Convert a FilePath to a string
	 *
	 * @param dirOnly If true, will not append the file name (if any) to the string, and only return the path to the enclosing directory
	 * @return A std::string representing the given FilePath on the current OS
	 */
	std::string toString(bool dirOnly = false) const;

	// Attributes
	/**
	 * Just provides read only access to m_isRelative
	 * @return true if it represents a relative path, false for an absolute path
	 */
	bool isRelative() const;

	/**
	 * Check if the FilePath represents a file
	 * @return true if it contains a file, false for just a directory or an empty FilePath
	 */
	bool isFile() const;

	/**
	 * Check if the FilePath represents a directory
	 * @return true if it does NOT contain a file, false for a file or an empty FilePath
	 */
	bool isDirectory() const;

	/**
	 * Check the relevant size of the FilePath
	 * @return the number of folders + file
	 */
	unsigned int size() const;

	/**
	 * Check whether the FilePath is empty or not
	 * @return true if it contains no folders nor filename
	 */
	bool empty() const;

private:
	void addPathPart(std::string pathPart);
	// In windows we can guess this based on whether the drive is there or not
	// In Linux we need it as its own member, based on whether the original path begins with a /
	bool m_isRelative = true; /** Whether it's an absolute or relative filepath */

	std::vector<std::string> m_Folders; /** One entry per folder or drive, in descending order */
	std::string m_File; /** The file name + type (if any) */

	/**
	* Append a string to the current FilePath, detecting if it's a folder or file
	* 
	* @param pathPart A single std::string to add
	*/	
};

