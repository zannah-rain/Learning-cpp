#pragma once

#include <memory>

// Forward declarations
class FilePath;

class Texture
{
private:
	unsigned int _texture;
public:
	Texture(FilePath filePath);
	void use();
	unsigned int ID();
};