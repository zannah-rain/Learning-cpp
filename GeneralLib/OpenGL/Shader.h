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
	* @param vertexPath The file path for the vertex shader source
	* @param fragmentPath The file path for the fragment shader source
	*/
	C_Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

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
	void    SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
	void    SetVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);
	void    SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
	void    SetVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
	void    SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
	void    SetVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);
	void    SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);

	unsigned int m_ID; /** The program m_ID */
};