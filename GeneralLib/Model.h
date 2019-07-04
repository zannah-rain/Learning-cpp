#pragma once

#include <vector>

// Forward declarations
class Texture;
struct Vertex;

/**
*	A class to represent a static 3d model
*/
class Model
{
public:
	/** Explicit constructor 
	* @param vertices Raw vertex data
	* @param nPositions How many entries in vertices are positional
	* @param nColours How many entries in vertices are colours
	* @param nTextureCoords How many entries in vertices are texturecoords
	* @param nNormalCoords How many entries in the vertices are normals
	* @param VAO Which VAO needs to be bound for this model
	* @param VBO Which VBO needs to be bound for this model
	* @param willChangeFrequently Whether it's expected that these values will need to be resent to the GPU regularly
	* @param texture Pointer to the Texture to use when shading
	*/
	Model(std::vector< float > vertices, 
		  unsigned short nPositions,
		  unsigned short nColours,
		  unsigned short nTextureCoords,
		  unsigned short nNormalCoords,
		  unsigned int VAO, 
		  unsigned int VBO, 
		  bool willChangeFrequently,
		  Texture * texture);

	/** Standard constructor
	* @param vertices Vertex data for the model
	* @param VAO Which VAO needs to be bound for this model
	* @param VBO Which VBO needs to be bound for this model
	* @param willChangeFrequently Whether it's expected that these values will need to be resent to the GPU regularly
	* @param texture Pointer to the Texture to use when shading
	*/
	Model::Model(
		std::vector< Vertex > vertices,
		unsigned int VAO,
		unsigned int VBO,
		bool willChangeFrequently,
		Texture * texture);

	/** Send the 
	* @param vertices Vertex data for the model
	* @param VAO Which VAO needs to be bound for this model
	* @param VBO Which VBO needs to be bound for this model
	* @param willChangeFrequently Whether it's expected that these values will need to be resent to the GPU regularly
	* @param texture Pointer to the Texture to use when shading
	*/
	void bufferData(std::vector< float > vertices) const;

	/**
	* Draw the model!
	*/
	void draw();

private:
	unsigned int mVAO; /** Record which VAO & VBO we'll push the vertex data to the GPU with/under*/
	unsigned int mVBO; /** Record which VAO & VBO we'll push the vertex data to the GPU with/under*/
	Texture * mTexture; /** The texture object that the model uses */
	unsigned int mNVertices; /** Record how many vertices are sent to the GPU for draw calls*/

	unsigned short mNPositions; /** How many values in each vertex refer to position*/
	unsigned short mNColours; /** How many values in each vertex refer to colour*/
	unsigned short mNTextureCoords; /** How many values in each vertex refer to texture position*/
	unsigned short mNNormalCoords; /** How many values in each vertex refer to the nomal*/

	bool mWillChangeFrequently; /** Whether the VBO should be static or dynamic*/
};