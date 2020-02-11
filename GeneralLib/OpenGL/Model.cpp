#include <vector>

#include "glad/glad.h"
#include "Model.h"
#include "Texture.h"
#include "Vertex.h"


C_Model::C_Model(
	std::vector< float > vertices,
	unsigned short nPositions,
	unsigned short nColours,
	unsigned short nTextureCoords,
	unsigned short nNormalCoords,
	unsigned int VAO,
	unsigned int VBO,
	bool willChangeFrequently,
	C_Texture * texture) :
	m_VAO(VAO), 
	m_VBO(VBO), 
	m_Texture(texture), 
	m_NumPositions(nPositions), 
	m_NumColours(nColours), 
	m_NumTextureCoords(nTextureCoords), 
	m_NumNormalCoords(nNormalCoords),
	m_WillChangeFrequently(willChangeFrequently),
	m_NumVertices(vertices.size() / (nPositions + nColours + nTextureCoords + nNormalCoords))
{
	// Send the vertices to the VBO
	bufferData(vertices);
}


C_Model::C_Model(
	std::vector< S_Vertex > vertices,
	unsigned int VAO,
	unsigned int VBO,
	bool willChangeFrequently,
	C_Texture * texture) :
	m_VAO(VAO), 
	m_VBO(VBO), 
	m_Texture(texture), 
	m_NumPositions(3),
	m_NumColours(4), 
	m_NumTextureCoords(2), 
	m_NumNormalCoords(3),
	m_WillChangeFrequently(willChangeFrequently),
	m_NumVertices(vertices.size())
{
	// Send the vertices to the VBO
	bufferData(S_Vertex::toFloats(vertices));
}


C_Model::C_Model(
	std::vector< S_Vertex > vertices,
	bool willChangeFrequently,
	C_Texture * texture)
	: m_VAO(0)
	, m_VBO(0)
	, m_Texture(texture)
	, m_NumPositions(3)
	, m_NumColours(4)
	, m_NumTextureCoords(2)
	, m_NumNormalCoords(3)
	, m_WillChangeFrequently(willChangeFrequently)
	, m_NumVertices(vertices.size())
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	// Send the vertices to the VBO
	bufferData(S_Vertex::toFloats(vertices));
}


void C_Model::bufferData(std::vector < float > vertices) const
{
	// VBO STUFF
	// Bind the VBO (The raw vertex data)
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	if (m_WillChangeFrequently)
	{
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_DYNAMIC_DRAW);
	}
	else
	{
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	}
	
	// VAO STUFF
	// Bind the VAO (Metadata about how to interpret the raw vertex data)
	glBindVertexArray(m_VAO);

	unsigned short currentOffset = 0;
	if (m_NumPositions > 0)
	{
		glVertexAttribPointer(
			0, // Which vertex attribute we want to configure, we used location = 0 in the shader
			m_NumPositions, // The size of the vertex attribute, we used vec3 in the shader
			GL_FLOAT, // The type of the data
			GL_FALSE, // Do we want the data to be normalized
			(m_NumPositions + m_NumColours + m_NumTextureCoords + m_NumNormalCoords) * sizeof(float), // The distance between each set of vertex attributes
			(void*)(currentOffset * sizeof(float)) // The offset of where the position data begins in the buffer
		);
		currentOffset += m_NumPositions;
		glEnableVertexAttribArray(0);
	}
	if (m_NumColours > 0)
	{
		glVertexAttribPointer(
			1, // Which vertex attribute we want to configure, we used location = 1 in the shader
			m_NumColours, // The size of the vertex attribute, we used vec3 in the shader
			GL_FLOAT, // The type of the data
			GL_FALSE, // Do we want the data to be normalized
			(m_NumPositions + m_NumColours + m_NumTextureCoords + m_NumNormalCoords) * sizeof(float), // The distance between each set of vertex attributes
			(void*)(currentOffset * sizeof(float)) // The offset of where the position data begins in the buffer
		);
		currentOffset += m_NumColours;
		glEnableVertexAttribArray(1);
	}
	if (m_NumTextureCoords > 0)
	{
		glVertexAttribPointer(
			2, // Which vertex attribute we want to configure, we used location = 1 in the shader
			m_NumTextureCoords, // The size of the vertex attribute, we used vec3 in the shader
			GL_FLOAT, // The type of the data
			GL_FALSE, // Do we want the data to be normalized
			(m_NumPositions + m_NumColours + m_NumTextureCoords + m_NumNormalCoords) * sizeof(float), // The distance between each set of vertex attributes
			(void*)(currentOffset * sizeof(float)) // The offset of where the position data begins in the buffer
		);
		currentOffset += m_NumTextureCoords;
		glEnableVertexAttribArray(2);
	}
	if (m_NumNormalCoords > 0)
	{
		glVertexAttribPointer(
			3, // Which vertex attribute we want to configure, we used location = 1 in the shader
			m_NumNormalCoords, // The size of the vertex attribute, we used vec3 in the shader
			GL_FLOAT, // The type of the data
			GL_FALSE, // Do we want the data to be normalized
			(m_NumPositions + m_NumColours + m_NumTextureCoords + m_NumNormalCoords) * sizeof(float), // The distance between each set of vertex attributes
			(void*)(currentOffset * sizeof(float)) // The offset of where the position data begins in the buffer
		);
		currentOffset += m_NumNormalCoords;
		glEnableVertexAttribArray(3);
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void C_Model::draw()
{
	// Bind the VBO & VAO
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindVertexArray(m_VAO);

	glDrawArrays(GL_TRIANGLES, 0, m_NumVertices);

	// Reset the GL_ARRAY_BUFFER buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}