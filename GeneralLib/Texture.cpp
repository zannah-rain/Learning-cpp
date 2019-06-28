#include <iostream>

#include "include/stb_image.h"
#include "Texture.h"
#include "glad/glad.h"

Texture::Texture(FilePath filePath)
{
	int width, height, nrChannels;
	std::unique_ptr<unsigned char, decltype(&stbi_image_free)> data(stbi_load(filePath.toString().c_str(), &width, &height, &nrChannels, 0), &stbi_image_free);

	if (data)
	{
		// Generate the texture
		glGenTextures(1, &_texture);
		// Bind it so we can write to it
		glBindTexture(GL_TEXTURE_2D, _texture);

		// Set the texture wrapping / filtering options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGB,
			width,
			height,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			data.get());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
}

void Texture::use()
{
	glBindTexture(GL_TEXTURE_2D, _texture);
}