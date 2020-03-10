#pragma once

#include <vector>

// Forward declarations
class C_Texture;
struct S_Vertex;

/**
*	A class to represent a static 3d model
*/
class C_Model
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
	* @param texture Pointer to the C_Texture to use when shading
	*/
	C_Model::C_Model(std::vector< S_Vertex > vertices,
					 unsigned short nPositions,
					 unsigned short nColours,
					 unsigned short nTextureCoords,
					 unsigned short nNormalCoords,
					 unsigned int VAO, 
					 unsigned int VBO, 
					 bool willChangeFrequently,
					 C_Texture * texture);

	/** Standard constructor
	* @param vertices S_Vertex data for the model
	* @param VAO Which VAO needs to be bound for this model
	* @param VBO Which VBO needs to be bound for this model
	* @param willChangeFrequently Whether it's expected that these values will need to be resent to the GPU regularly
	* @param texture Pointer to the C_Texture to use when shading
	*/
	C_Model::C_Model(std::vector< S_Vertex > vertices,
					 unsigned int VAO,
					 unsigned int VBO,
					 bool willChangeFrequently,
					 C_Texture * texture);

	/** Minimal constructor
	* @param vertices S_Vertex data for the model
	* @param willChangeFrequently Whether it's expected that these values will need to be resent to the GPU regularly
	* @param texture Pointer to the C_Texture to use when shading
	*/
	C_Model::C_Model(std::vector< S_Vertex > vertices,
					 bool willChangeFrequently,
					 C_Texture * texture);

	/**
	* Draw the model!
	*/
	void draw();

private:
	unsigned int m_VAO; /** Record which VAO & VBO we'll push the vertex data to the GPU with/under*/
	unsigned int m_VBO; /** Record which VAO & VBO we'll push the vertex data to the GPU with/under*/
	C_Texture * m_Texture; /** The texture object that the model uses */
	unsigned int m_NumVertices; /** Record how many vertices are sent to the GPU for draw calls*/

	unsigned short m_NumPositions; /** How many values in each vertex refer to position*/
	unsigned short m_NumColours; /** How many values in each vertex refer to colour*/
	unsigned short m_NumTextureCoords; /** How many values in each vertex refer to texture position*/
	unsigned short m_NumNormalCoords; /** How many values in each vertex refer to the nomal*/

	std::vector< S_Vertex > m_Vertices; /** The actual vertices for the model */

	/** Send the vertices to the VBO */
	void bufferData() const;

	bool m_WillChangeFrequently; /** Whether the VBO should be static or dynamic*/
};