#include "Vertex.h"


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
