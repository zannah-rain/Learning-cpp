

/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "stb_image.h"

// Instantiate static variables
std::map<std::string, C_Texture2D>    ResourceManager::Textures;
std::map<std::string, C_Shader>       ResourceManager::Shaders;


C_Shader ResourceManager::LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, std::string name)
{
	Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile);
	return Shaders[name];
}

C_Shader ResourceManager::GetShader(std::string name)
{
	return Shaders[name];
}

C_Texture2D ResourceManager::LoadTexture(const GLchar *file, GLboolean alpha, std::string name)
{
	Textures[name] = loadTextureFromFile(file, alpha);
	return Textures[name];
}

C_Texture2D ResourceManager::GetTexture(std::string name)
{
	return Textures[name];
}

void ResourceManager::Clear()
{
	// (Properly) delete all shaders	
	for (auto iter : Shaders)
		glDeleteProgram(iter.second.m_ID);
	// (Properly) delete all textures
	for (auto iter : Textures)
		glDeleteTextures(1, &iter.second.ID);
}

C_Shader ResourceManager::loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile)
{
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	try
	{
		// Open files
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();
		// close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();
		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}
	const GLchar *vShaderCode = vertexCode.c_str();
	std::cout << "Vertex shader code loaded with " << strlen(vShaderCode) << " characters" << std::endl;
	const GLchar *fShaderCode = fragmentCode.c_str();
	std::cout << "Fragment shader code loaded with " << strlen(fShaderCode) << " characters" << std::endl;
	// 2. Now create shader object from source code
	C_Shader shader;
	shader.compile(vShaderCode, fShaderCode);
	return shader;
}

C_Texture2D ResourceManager::loadTextureFromFile(const GLchar *file, GLboolean alpha)
{
	// Create Texture object
	C_Texture2D texture;
	if (alpha)
	{
		texture.Internal_Format = GL_RGBA;
		texture.Image_Format = GL_RGBA;
	}
	else 
	{
		texture.Internal_Format = GL_RGB;
		texture.Image_Format = GL_RGB;
	}
	// Load image
	int width, height;
	unsigned char* image = stbi_load(file, &width, &height, 0, texture.Image_Format == GL_RGBA ? 4 : 3);
	std::cout << "Image loaded from " << file << std::endl;
	// Now generate texture
	texture.Generate(width, height, image);
	// And finally free image data
	stbi_image_free(image);
	return texture;
}

