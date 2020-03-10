#include "Vertex.h"
#include "glad/glad.h"


std::vector< float > S_Vertex::toFloats(std::vector< S_Vertex > vertices)
{
	std::vector< float > outVector;

	for (size_t i = 0; i < vertices.size(); i++)
	{
		// Position, Colour, C_Texture, Normal
		outVector.push_back(vertices[i].posX);
		outVector.push_back(vertices[i].posY);
		outVector.push_back(vertices[i].posZ);

		outVector.push_back(vertices[i].r);
		outVector.push_back(vertices[i].g);
		outVector.push_back(vertices[i].b);
		outVector.push_back(vertices[i].a);

		outVector.push_back(vertices[i].texX);
		outVector.push_back(vertices[i].texY);

		outVector.push_back(vertices[i].normX);
		outVector.push_back(vertices[i].normY);
		outVector.push_back(vertices[i].normZ);
	}

	return outVector;
}


void S_Vertex::configureVAO(std::size_t VAO)
{
	// VAO STUFF
	// Bind the VAO (Metadata about how to interpret the raw vertex data)
	glBindVertexArray(VAO);

	unsigned short currentOffset = 0;
	if (sc_NumPositions > 0)
	{
		glVertexAttribPointer(
			0, // Which vertex attribute we want to configure, we used location = 0 in the shader
			sc_NumPositions, // The size of the vertex attribute, we used vec3 in the shader
			GL_FLOAT, // The type of the data
			GL_FALSE, // Do we want the data to be normalized
			(sc_NumPositions + sc_NumColours + sc_NumTextureCoords + sc_NumNormalCoords) * sizeof(float), // The distance between each set of vertex attributes
			(void*)(currentOffset * sizeof(float)) // The offset of where the position data begins in the buffer
		);
		currentOffset += sc_NumPositions;
		glEnableVertexAttribArray(0);
	}
	if (sc_NumColours > 0)
	{
		glVertexAttribPointer(
			1, // Which vertex attribute we want to configure, we used location = 1 in the shader
			sc_NumColours, // The size of the vertex attribute, we used vec3 in the shader
			GL_FLOAT, // The type of the data
			GL_FALSE, // Do we want the data to be normalized
			(sc_NumPositions + sc_NumColours + sc_NumTextureCoords + sc_NumNormalCoords) * sizeof(float), // The distance between each set of vertex attributes
			(void*)(currentOffset * sizeof(float)) // The offset of where the position data begins in the buffer
		);
		currentOffset += sc_NumColours;
		glEnableVertexAttribArray(1);
	}
	if (sc_NumTextureCoords > 0)
	{
		glVertexAttribPointer(
			2, // Which vertex attribute we want to configure, we used location = 1 in the shader
			sc_NumTextureCoords, // The size of the vertex attribute, we used vec3 in the shader
			GL_FLOAT, // The type of the data
			GL_FALSE, // Do we want the data to be normalized
			(sc_NumPositions + sc_NumColours + sc_NumTextureCoords + sc_NumNormalCoords) * sizeof(float), // The distance between each set of vertex attributes
			(void*)(currentOffset * sizeof(float)) // The offset of where the position data begins in the buffer
		);
		currentOffset += sc_NumTextureCoords;
		glEnableVertexAttribArray(2);
	}
	if (sc_NumNormalCoords > 0)
	{
		glVertexAttribPointer(
			3, // Which vertex attribute we want to configure, we used location = 1 in the shader
			sc_NumNormalCoords, // The size of the vertex attribute, we used vec3 in the shader
			GL_FLOAT, // The type of the data
			GL_FALSE, // Do we want the data to be normalized
			(sc_NumPositions + sc_NumColours + sc_NumTextureCoords + sc_NumNormalCoords) * sizeof(float), // The distance between each set of vertex attributes
			(void*)(currentOffset * sizeof(float)) // The offset of where the position data begins in the buffer
		);
		currentOffset += sc_NumNormalCoords;
		glEnableVertexAttribArray(3);
	}

	glBindVertexArray(0);
}