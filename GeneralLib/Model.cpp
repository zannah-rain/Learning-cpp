#include <vector>

#include "glad/glad.h"
#include "Model.h"
#include "Texture.h"
#include "Vertex.h"


Model::Model(
	std::vector< float > vertices,
	unsigned short nPositions,
	unsigned short nColours,
	unsigned short nTextureCoords,
	unsigned short nNormalCoords,
	unsigned int VAO,
	unsigned int VBO,
	bool willChangeFrequently,
	Texture * texture) :
	mVAO(VAO), mVBO(VBO), mTexture(texture), mNPositions(nPositions), 
	mNColours(nColours), mNTextureCoords(nTextureCoords), mNNormalCoords(nNormalCoords),
	mWillChangeFrequently(willChangeFrequently)
{
	// Send the vertices to the VBO
	bufferData(vertices);

	// Save how many vertices there are
	mNVertices = vertices.size() / (nPositions + nColours + nTextureCoords + nNormalCoords);
}


Model::Model(
	std::vector< Vertex > vertices,
	unsigned int VAO,
	unsigned int VBO,
	bool willChangeFrequently,
	Texture * texture) :
	mVAO(VAO), mVBO(VBO), mTexture(texture), mNPositions(3),
	mNColours(4), mNTextureCoords(2), mNNormalCoords(3),
	mWillChangeFrequently(willChangeFrequently)
{
	// Send the vertices to the VBO
	bufferData(Vertex::toFloats(vertices));

	mNVertices = vertices.size();
}


void Model::bufferData(std::vector < float > vertices) const
{
	// Bind the VAO
	glBindVertexArray(mVAO);
	// Bind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);

	if (mWillChangeFrequently)
	{
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_DYNAMIC_DRAW);
	}
	else
	{
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	}
	

	unsigned short currentOffset = 0;
	if (mNPositions > 0)
	{
		glVertexAttribPointer(
			0, // Which vertex attribute we want to configure, we used location = 0 in the shader
			mNPositions, // The size of the vertex attribute, we used vec3 in the shader
			GL_FLOAT, // The type of the data
			GL_FALSE, // Do we want the data to be normalized
			(mNPositions + mNColours + mNTextureCoords + mNNormalCoords) * sizeof(float), // The distance between each set of vertex attributes
			(void*)(currentOffset * sizeof(float)) // The offset of where the position data begins in the buffer
		);
		currentOffset += mNPositions;
		glEnableVertexAttribArray(0);
	}
	if (mNColours > 0)
	{
		glVertexAttribPointer(
			1, // Which vertex attribute we want to configure, we used location = 1 in the shader
			mNColours, // The size of the vertex attribute, we used vec3 in the shader
			GL_FLOAT, // The type of the data
			GL_FALSE, // Do we want the data to be normalized
			(mNPositions + mNColours + mNTextureCoords + mNNormalCoords) * sizeof(float), // The distance between each set of vertex attributes
			(void*)(currentOffset * sizeof(float)) // The offset of where the position data begins in the buffer
		);
		currentOffset += mNColours;
		glEnableVertexAttribArray(1);
	}
	if (mNTextureCoords > 0)
	{
		glVertexAttribPointer(
			2, // Which vertex attribute we want to configure, we used location = 1 in the shader
			mNTextureCoords, // The size of the vertex attribute, we used vec3 in the shader
			GL_FLOAT, // The type of the data
			GL_FALSE, // Do we want the data to be normalized
			(mNPositions + mNColours + mNTextureCoords + mNNormalCoords) * sizeof(float), // The distance between each set of vertex attributes
			(void*)(currentOffset * sizeof(float)) // The offset of where the position data begins in the buffer
		);
		currentOffset += mNTextureCoords;
		glEnableVertexAttribArray(2);
	}
	if (mNNormalCoords > 0)
	{
		glVertexAttribPointer(
			3, // Which vertex attribute we want to configure, we used location = 1 in the shader
			mNNormalCoords, // The size of the vertex attribute, we used vec3 in the shader
			GL_FLOAT, // The type of the data
			GL_FALSE, // Do we want the data to be normalized
			(mNPositions + mNColours + mNTextureCoords + mNNormalCoords) * sizeof(float), // The distance between each set of vertex attributes
			(void*)(currentOffset * sizeof(float)) // The offset of where the position data begins in the buffer
		);
		currentOffset += mNNormalCoords;
		glEnableVertexAttribArray(3);
	}

	glBindVertexArray(0);
}


void Model::draw()
{
	glDrawArrays(GL_TRIANGLES, 0, mNVertices);
}