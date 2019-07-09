#pragma once
#include <string>
#include <vector>

/**
 * A class to hold a file path and provide relevant methods which would be a pain to program for strings
 */
class C_FilePath
{
public:
	C_FilePath(); /** Initialise a blank C_FilePath */
	C_FilePath(std::initializer_list<std::string> const pathParts); /** Initialise a C_FilePath from a list of strings. Calls addPathPart on each part! */
	C_FilePath(std::string const path); /** Initialise from a single string. Scans the string for the OSs path separator char to automatically guess parts */

	// Operator overloads
	/**
	 * Override the += operator to append the rhs C_FilePath to the lhs C_FilePath
	 *
	 * @param rhs A relative C_FilePath to add to lhs
	 * @return A reference to the lhs C_FilePath after it has has rhs appended to it
	 */
	C_FilePath& operator+= (const C_FilePath& rhs);

	/**
	 * Override the + operator to append the rhs C_FilePath to the lhs C_FilePath
	 *
	 * @param rhs A relative C_FilePath to add to lhs
	 * @return A C_FilePath with rhs appended to lhs
	 */
	C_FilePath operator+ (const C_FilePath& rhs) const;

	/**
	 * Override the == operator to compare the rhs C_FilePath to the lhs C_FilePath
	 *
	 * @param rhs A C_FilePath to compare with lhs
	 * @return true if both FilePaths resolve to the same string
	 */
	bool operator== (const C_FilePath& rhs) const;

	/**
	 * Override the != operator to compare the rhs C_FilePath to the lhs C_FilePath
	 *
	 * @param rhs A C_FilePath to compare with lhs
	 * @return false if both FilePaths resolve to the same string
	 */
	bool operator!= (const C_FilePath& rhs) const;

	/**
	 * Decrements a C_FilePath, removes the rightmost file / folder
	 *
	 * @return A C_FilePath& with one less file / folder
	 */
	C_FilePath& operator--(); //prefix decrement operator

	/**
	 * Decrements a C_FilePath, removes the rightmost file / folder
	 *
	 * @return A C_FilePath& with one less file / folder
	 */
	C_FilePath operator--(int); //postfix decrement operator

	// Conversion
	/**
	 * Convert a C_FilePath to a string
	 *
	 * @param dirOnly If true, will not append the file name (if any) to the string, and only return the path to the enclosing directory
	 * @return A std::string representing the given C_FilePath on the current OS
	 */
	std::string toString(bool dirOnly = false) const;

	// Attributes
	/**
	 * Just provides read only access to m_IsRelative
	 * @return true if it represents a relative path, false for an absolute path
	 */
	bool isRelative() const;

	/**
	 * Check if the C_FilePath represents a file
	 * @return true if it contains a file, false for just a directory or an empty C_FilePath
	 */
	bool isFile() const;

	/**
	 * Check if the C_FilePath represents a directory
	 * @return true if it does NOT contain a file, false for a file or an empty C_FilePath
	 */
	bool isDirectory() const;

	/**
	 * Check the relevant size of the C_FilePath
	 * @return the number of folders + file
	 */
	unsigned int size() const;

	/**
	 * Check whether the C_FilePath is empty or not
	 * @return true if it contains no folders nor filename
	 */
	bool empty() const;

private:
	/**
	* Append a string to the current C_FilePath, detecting if it's a folder or file
	*
	* @param pathPart A single std::string to add
	*/
	void addPathPart(std::string pathPart);

	// In windows we can guess this based on whether the drive is there or not
	// In Linux we need it as its own member, based on whether the original path begins with a /
	bool m_IsRelative = true; /** Whether it's an absolute or relative filepath */

	std::vector<std::string> m_Folders; /** One entry per folder or drive, in descending order */
	std::string m_File; /** The file name + type (if any) */
};

