#include <vector>

#include "FilePath.h"

// Forward declarations
struct S_Vertex;

/**
* Load a .obj file
*
* @param path The file path of the .obj file
* @param outVertices The vector to write the vertices to
*
* @return Whether the operation was a success or not
*/
bool loadOBJ(C_FilePath path, std::vector< S_Vertex > &outVertices);