#include <vector>

#include "FilePath.h"
#include "glm/glm.hpp"

/**
* Load a .obj file
*
* @param path The file path of the .obj file
* @param out_vertices The vector to write all the vertex data to (interleaved)
*
* @return Whether the operation was a success or not
*/
std::vector<float> loadOBJ(FilePath path);

/**
* Load a .obj file
*
* @param path The file path of the .obj file
* @param out_vertices The vector to write the vertices to
* @param out_uvs The vector to write the uvs to
* @param out_normals The vector to write the normals to
*
* @return Whether the operation was a success or not
*/
bool loadOBJ(
	FilePath path,
	std::vector<glm::vec3> &out_vertices,
	std::vector<glm::vec2> &out_uvs,
	std::vector<glm::vec3> &out_normals
);