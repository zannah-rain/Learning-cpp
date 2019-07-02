#include "loadOBJ.h"

#include "wrapFILE.h"

#include <iostream>
#include <fstream>

// Just an interleaved version of the below
std::vector<float> loadOBJ(FilePath path)
{
	std::vector<float> outVertices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	if (!loadOBJ(path, temp_vertices, temp_uvs, temp_normals))
	{
		return outVertices;
	}

	for (size_t i = 0; i < temp_vertices.size(); i++)
	{
		float * tempVerticesArray = &(temp_vertices[i].x);
		float * tempUVArray = &temp_uvs[i].x;
		float * tempNormalsArray = &temp_normals[i].x;

		for (size_t j = 0; j < 3; j++)
		{
			outVertices.push_back(tempVerticesArray[j]);
		}
		for (size_t j = 0; j < 2; j++)
		{
			outVertices.push_back(tempUVArray[j]);
		}
		for (size_t j = 0; j < 3; j++)
		{
			outVertices.push_back(tempNormalsArray[j]);
		}
	}

	return outVertices;
}

bool loadOBJ(
	FilePath path,
	std::vector<glm::vec3> &out_vertices,
	std::vector<glm::vec2> &out_uvs,
	std::vector<glm::vec3> &out_normals)
{
	// Store the results in temporary variables
	// Don't want to modify anything until we've done checks
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	std::unique_ptr<FILE, FILEDeleter> file = make_fopen(path, "r");

	if (file == NULL)
	{
		std::cout << "Couldn't open: " << path.toString() << std::endl;
		return false;
	}

	while (true)
	{
		char lineHeader[128];

		// %s means we want to read until the first whitespace character
		int res = fscanf_s(file.get(), "%s", lineHeader, sizeof(lineHeader));

		// Stop looping when we reach the end of the file
		if (res == EOF)
		{
			break;
		}
		
		if (strcmp(lineHeader, "#") == 0)
		{
			// It's a comment line, do nothing!
		}
		else if (strcmp(lineHeader, "v") == 0) 
		{
			// When first word is "v", this line will describe the (x, y, z) for a vertex
			glm::vec3 vertex;
			// We want to read 3 numbers from this (x,y,z for the vertex)
			fscanf_s(file.get(), "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) 
		{
			// "vt" means it's a texture coordinate!
			glm::vec2 uv;
			// Texture coordinates only have x & y at the moment :)
			fscanf_s(file.get(), "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) 
		{
			// "vn" means it's a normal (x,y,z)
			glm::vec3 normal;
			fscanf_s(file.get(), "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			// "f" tells us how to glue together the stuff we've been reading so far
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf_s(file.get(), "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9)
			{
				std::cout << "File can't be read by our simple parser : Try exporting with other options" << std::endl;
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	// For each vertex of each triangle
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		// OBJ indexing starts at 1
		glm::vec3 vertex = temp_vertices[vertexIndices[i] - 1];
		out_vertices.push_back(vertex);
	}
	for (unsigned int i = 0; i < uvIndices.size(); i++) {
		// OBJ indexing starts at 1
		glm::vec2 uv = temp_uvs[uvIndices[i] - 1];
		out_uvs.push_back(uv);
	}
	for (unsigned int i = 0; i < normalIndices.size(); i++) {
		// OBJ indexing starts at 1
		glm::vec3 normal = temp_normals[normalIndices[i] - 1];
		out_normals.push_back(normal);
	}

	return true;
}
