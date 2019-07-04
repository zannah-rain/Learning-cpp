#pragma once

#include <vector>

/**
* Basic container for all data relating to a single vertex
*/
struct Vertex
{
	float posX; /** The x coordinate in model space*/
	float posY; /** The y coordinate in model space*/
	float posZ; /** The z coordinate in model space*/

	float r; /** Colours: red 0-1*/
	float g; /** Colours: green 0-1*/
	float b; /** Colours: blue 0-1*/
	float a; /** Colours: alpha 0-1*/

	float texX; /** The x coordinate in texture space*/
	float texY; /** The y coordinate in texture space*/

	float normX; /** The x coordinate of the normal vector*/
	float normY; /** The y coordinate of the normal vector*/
	float normZ; /** The z coordinate of the normal vector*/

	Vertex() : posX(0), posY(0), posZ(0), r(1), g(0), b(0), a(1), texX(0), texY(0), normX(0), normY(1), normZ(0) {};

	/**
	* Convert a vector of Vertex's to a vector of floats in the standard format:
	* position (3), colour (4), texture (2), normal (3)
	* 
	* @param vertices A vector of Vertex objects
	* @return A vector of floats, ready for passing to openGL
	*/
	static std::vector< float > toFloats(std::vector< Vertex > vertices);
};
