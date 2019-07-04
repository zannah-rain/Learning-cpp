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
	void use() const;
	unsigned int ID() const;
};