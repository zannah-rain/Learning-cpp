#pragma once
#include "Texture.h"

/**
*	A class to represent a static 3d model
*/
class Model
{
private:
	unsigned int _VAO; /** Record which VAO & VBO we'll push the vertex data to the GPU with/under*/
	unsigned int _VBO; /** Record which VAO & VBO we'll push the vertex data to the GPU with/under*/
	Texture * _texture; /** The texture object that the model uses */
	unsigned int nVertices; /** Record how many vertices are sent to the GPU for draw calls*/
public:
	Model(
		std::vector<float> vertices, 
		unsigned short nPositions, /** How many entries in vertices are positional*/
		unsigned short nColours, /** How many entries in vertices are colours*/
		unsigned short nTextureCoords, /** How many entries in vertices are texturecoords*/
		unsigned short nNormalCoords, /** How many entries in the vertices are normals */
		unsigned int VAO, 
		unsigned int VBO, 
		bool willChangeFrequently,
		Texture * texture
	);

	void bufferData(
		std::vector<float> vertices,
		bool willChangeFrequently,
		unsigned short nPositions,
		unsigned short nColours,
		unsigned short nTextureCoords,
		unsigned short nNormalCoords);

	void draw();
};