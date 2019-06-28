#pragma once
#include <memory>
#include "FilePath.h"

class Texture
{
private:
	unsigned int _texture;
public:
	Texture(FilePath filePath);
	void use();
};