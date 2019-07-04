#pragma once

#include <memory>

// Forward declarations
class FilePath;


/**
* Encapsulates CPU & GPU operations for a single texture object
*/
class Texture
{
public:
	/**
	* Construct a Texture object from a file
	* Loads the file & pushes it to the GPU
	* 
	* @param filePath The file path to the physical resource to use as a texture
	*/
	Texture(FilePath filePath);

	/**
	* Bind this texture in openGL
	*/
	void use() const;

	/**
	* Accessor for _texture
	*/
	unsigned int ID() const;

private:
	unsigned int _texture; /** The openGL ID for the texture*/
};