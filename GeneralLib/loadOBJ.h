#include <vector>

#include "FilePath.h"

// Forward declarations
struct Vertex;

/**
* Load a .obj file
*
* @param path The file path of the .obj file
* @param outVertices The vector to write the vertices to
*
* @return Whether the operation was a success or not
*/
bool loadOBJ(FilePath path,	std::vector< Vertex > &outVertices);