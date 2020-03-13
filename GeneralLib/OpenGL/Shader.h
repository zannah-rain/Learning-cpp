#pragma once

#include <string>

#include "glad/glad.h"

#include "glm/glm.hpp"


class C_Shader
{
public:
	/**
	* Constructor reads and builds the shader
	* 
	* @param vertexShaderCode The source code for the vertex shader
	* @param fragmentShaderCode The source code for the fragment shader
	*/
	C_Shader(const GLchar* vertexShaderCode, const GLchar* fragmentShaderCode);

	/**
	* Alternatively, instantiate an empty shader for future compilation
	*/
	C_Shader();

	/**
	* Compile the shader
	* 
	* @param vertexShaderCode The source code for the vertex shader
	* @param fragmentShaderCode The source code for the fragment shader
	*/
	void compile(const GLchar* vertexShaderCode, const GLchar* fragmentShaderCode);

	void use() const; /** use/activate the shader */

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

	/**
	* More utility functions around setting uniforms in the shader
	*/
	void    SetVector2f(const GLchar *name, GLfloat x, GLfloat y);
	void    SetVector2f(const GLchar *name, const glm::vec2 &value);
	void    SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z);
	void    SetVector3f(const GLchar *name, const glm::vec3 &value);
	void    SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void    SetVector4f(const GLchar *name, const glm::vec4 &value);
	void    SetMatrix4(const GLchar *name, const glm::mat4 &matrix);

	unsigned int m_ID; /** The program m_ID */

private:
	// Checks if compilation or linking failed and if so, print the error logs
	void    checkCompileErrors(GLuint object, std::string type);
};