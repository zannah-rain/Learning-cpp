#include <fstream>
#include <sstream>
#include <iostream>

#include "shader.h"
#include "FileSystem/FileSystem.h"

#include "glm/gtc/type_ptr.hpp"


C_Shader::C_Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	compile(vertexPath, fragmentPath);
}


C_Shader::C_Shader()
{

}


void C_Shader::compile(const GLchar* vShaderCode, const GLchar* fShaderCode)
{
	unsigned int vertex, fragment;

	// vertex C_Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, nullptr);
	glCompileShader(vertex);
	// print compile errors if any
	checkCompileErrors(vertex, "VERTEX");

	// similiar for Fragment C_Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, nullptr);
	glCompileShader(fragment);
	// print compile errors if any
	checkCompileErrors(fragment, "FRAGMENT");

	// shader Program
	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertex);
	glAttachShader(m_ID, fragment);
	glLinkProgram(m_ID);
	// print linking errors if any
	checkCompileErrors(m_ID, "PROGRAM");

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
	// TODO Learn whether shader needs to be the one that's currently in use for setting uniforms to work
	// If so, the shader class should track the current shader program, and call glUseProgram before glUniform1i if needed
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


void C_Shader::SetVector2f(const GLchar *name, GLfloat x, GLfloat y)
{
	glUniform2f(glGetUniformLocation(m_ID, name), x, y);
}


void C_Shader::SetVector2f(const GLchar *name, const glm::vec2 &value)
{
	glUniform2f(glGetUniformLocation(m_ID, name), value.x, value.y);
}


void C_Shader::SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z)
{
	glUniform3f(glGetUniformLocation(m_ID, name), x, y, z);
}


void C_Shader::SetVector3f(const GLchar *name, const glm::vec3 &value)
{
	glUniform3f(glGetUniformLocation(m_ID, name), value.x, value.y, value.z);
}


void C_Shader::SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	glUniform4f(glGetUniformLocation(m_ID, name), x, y, z, w);
}


void C_Shader::SetVector4f(const GLchar *name, const glm::vec4 &value)
{
	glUniform4f(glGetUniformLocation(m_ID, name), value.x, value.y, value.z, value.w);
}


void C_Shader::SetMatrix4(const GLchar *name, const glm::mat4 &matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(m_ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}


void C_Shader::checkCompileErrors(GLuint object, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
	else
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
}