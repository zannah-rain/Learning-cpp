#include <iostream>
#include <fstream>

#include "glm/glm.hpp"

#include "FileSystem\wrapFILE.h"
#include "OpenGL\loadOBJ.h"
#include "OpenGL\Vertex.h"


bool loadOBJ(
	C_FilePath path,
	std::vector< S_Vertex > &outVertices)
{
	// Store the results in temporary variables
	// Don't want to modify anything until we've done checks
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	std::unique_ptr<FILE, S_FILEDeleter> file = make_fopen(path, "r");

	if (file == nullptr)
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
			// C_Texture coordinates only have x & y at the moment :)
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

	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		S_Vertex vertex;
		
		vertex.posX = temp_vertices[vertexIndices[i] - 1].x;
		vertex.posY = temp_vertices[vertexIndices[i] - 1].y;
		vertex.posZ = temp_vertices[vertexIndices[i] - 1].z;

		vertex.texX = temp_uvs[uvIndices[i] - 1].x;
		vertex.texY = temp_uvs[uvIndices[i] - 1].y;

		vertex.normX = temp_normals[vertexIndices[i] - 1].x;
		vertex.normY = temp_normals[vertexIndices[i] - 1].y;
		vertex.normZ = temp_normals[vertexIndices[i] - 1].z;

		outVertices.push_back(vertex);
	}

	std::cout << "loadOBJ:: Successfully loaded " << vertexIndices.size() << " vertices from .obj file at: " << path.toString() << std::endl;

	return true;
}
