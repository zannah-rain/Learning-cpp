#pragma once

#include "glad/glad.h"

#include <string>


class Shader
{
public:
	unsigned int ID; /** The program ID */

	/**
	* Constructor reads and builds the shader
	* 
	* @param vertexPath The file path for the vertex shader source
	* @param fragmentPath The file path for the fragment shader source
	*/
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	void use(); /** use/activate the shader */

	/**
	* Utility uniform functions
	*
	* @param name The name of the bool uniform to set
	* @param value The value to set it to
	*/
	void setBool(const std::string &name, bool value) const;

	/**
	* Utility uniform functions
	*
	* @param name The name of the bool uniform to set
	* @param value The value to set it to
	*/
	void setInt(const std::string &name, int value) const;

	/**
	* Utility uniform functions
	*
	* @param name The name of the bool uniform to set
	* @param value The value to set it to
	*/
	void setFloat(const std::string &name, float value) const;
};