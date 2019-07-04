#include <vector>

#include "glad/glad.h"
#include "Model.h"
#include "Texture.h"
#include "Vertex.h"

Model::Model(
	std::vector< float > vertices, /** Raw vertex data for the model*/
	unsigned short nPositions, /** How many entries in vertices are positional*/
	unsigned short nColours, /** How many entries in vertices are colours*/
	unsigned short nTextureCoords, /** How many entries in vertices are texturecoords*/
	unsigned short nNormalCoords, /** How many entries in the vertices are normals */
	unsigned int VAO, /** Which VAO to use*/
	unsigned int VBO, /** Which VBO to use*/
	bool willChangeFrequently,
	Texture * texture)
{
	// Save which VAO, VBO we're using for future use
	_VAO = VAO;
	_VBO = VBO;

	// Save the texture this model needs to be binded
	_texture = texture;

	// Send the vertices to the VBO
	bufferData(
		vertices, 
		willChangeFrequently,
		nPositions,
		nColours,
		nTextureCoords,
		nNormalCoords);

	// Save how many vertices there are
	nVertices = vertices.size() / (nPositions + nColours + nTextureCoords + nNormalCoords);
}

Model::Model(
	std::vector< Vertex > vertices, /** Vertex data for the model*/
	unsigned int VAO, /** Which VAO to use*/
	unsigned int VBO, /** Which VBO to use*/
	bool willChangeFrequently,
	Texture * texture)
{
	// Save which VAO, VBO we're using for future use
	_VAO = VAO;
	_VBO = VBO;

	// Save the texture this model needs to be binded
	_texture = texture;

	// Send the vertices to the VBO
	bufferData(
		Vertex::toFloats(vertices),
		willChangeFrequently,
		3,
		4,
		2,
		3);

	nVertices = vertices.size();
}

void Model::bufferData(
	std::vector<float> vertices, /** Vertex data for the model*/
	bool willChangeFrequently,
	unsigned short nPositions,
	unsigned short nColours,
	unsigned short nTextureCoords,
	unsigned short nNormalCoords) const
{
	// Bind the VAO
	glBindVertexArray(_VAO);
	// Bind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);

	if (willChangeFrequently)
	{
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_DYNAMIC_DRAW);
	}
	else
	{
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	}
	

	unsigned short currentOffset = 0;
	if (nPositions > 0)
	{
		glVertexAttribPointer(
			0, // Which vertex attribute we want to configure, we used location = 0 in the shader
			nPositions, // The size of the vertex attribute, we used vec3 in the shader
			GL_FLOAT, // The type of the data
			GL_FALSE, // Do we want the data to be normalized
			(nPositions + nColours + nTextureCoords + nNormalCoords) * sizeof(float), // The distance between each set of vertex attributes
			(void*)(currentOffset * sizeof(float)) // The offset of where the position data begins in the buffer
		);
		currentOffset += nPositions;
		glEnableVertexAttribArray(0);
	}
	if (nColours > 0)
	{
		glVertexAttribPointer(
			1, // Which vertex attribute we want to configure, we used location = 1 in the shader
			nColours, // The size of the vertex attribute, we used vec3 in the shader
			GL_FLOAT, // The type of the data
			GL_FALSE, // Do we want the data to be normalized
			(nPositions + nColours + nTextureCoords + nNormalCoords) * sizeof(float), // The distance between each set of vertex attributes
			(void*)(currentOffset * sizeof(float)) // The offset of where the position data begins in the buffer
		);
		currentOffset += nColours;
		glEnableVertexAttribArray(1);
	}
	if (nTextureCoords > 0)
	{
		glVertexAttribPointer(
			2, // Which vertex attribute we want to configure, we used location = 1 in the shader
			nTextureCoords, // The size of the vertex attribute, we used vec3 in the shader
			GL_FLOAT, // The type of the data
			GL_FALSE, // Do we want the data to be normalized
			(nPositions + nColours + nTextureCoords + nNormalCoords) * sizeof(float), // The distance between each set of vertex attributes
			(void*)(currentOffset * sizeof(float)) // The offset of where the position data begins in the buffer
		);
		currentOffset += nTextureCoords;
		glEnableVertexAttribArray(2);
	}
	if (nNormalCoords > 0)
	{
		glVertexAttribPointer(
			3, // Which vertex attribute we want to configure, we used location = 1 in the shader
			nNormalCoords, // The size of the vertex attribute, we used vec3 in the shader
			GL_FLOAT, // The type of the data
			GL_FALSE, // Do we want the data to be normalized
			(nPositions + nColours + nTextureCoords + nNormalCoords) * sizeof(float), // The distance between each set of vertex attributes
			(void*)(currentOffset * sizeof(float)) // The offset of where the position data begins in the buffer
		);
		currentOffset += nNormalCoords;
		glEnableVertexAttribArray(3);
	}

	glBindVertexArray(0);
}

void Model::draw()
{
	glDrawArrays(GL_TRIANGLES, 0, nVertices);
}