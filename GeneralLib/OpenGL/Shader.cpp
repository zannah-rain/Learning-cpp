#include <fstream>
#include <sstream>
#include <iostream>

#include "shader.h"

#include "glm/gtc/type_ptr.hpp"


C_Shader::C_Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();


	// 2. compile shaders
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	// vertex C_Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, nullptr);
	glCompileShader(vertex);
	// print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	// similiar for Fragment C_Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, nullptr);
	glCompileShader(fragment);
	// print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	};


	// shader Program
	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertex);
	glAttachShader(m_ID, fragment);
	glLinkProgram(m_ID);
	// print linking errors if any
	glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_ID, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}


void C_Shader::use() const
{
	glUseProgram(m_ID);
}


void C_Shader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
}


void C_Shader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}


void C_Shader::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}


void C_Shader::SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader)
{
	glUniform2f(glGetUniformLocation(m_ID, name), x, y);
}


void C_Shader::SetVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader)
{
	glUniform2f(glGetUniformLocation(m_ID, name), value.x, value.y);
}


void C_Shader::SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader)
{
	glUniform3f(glGetUniformLocation(m_ID, name), x, y, z);
}


void C_Shader::SetVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader)
{
	glUniform3f(glGetUniformLocation(m_ID, name), value.x, value.y, value.z);
}


void C_Shader::SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader)
{
	glUniform4f(glGetUniformLocation(m_ID, name), x, y, z, w);
}


void C_Shader::SetVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader)
{
	glUniform4f(glGetUniformLocation(m_ID, name), value.x, value.y, value.z, value.w);
}


void C_Shader::SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader)
{
	glUniformMatrix4fv(glGetUniformLocation(m_ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}