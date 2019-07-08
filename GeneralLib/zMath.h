#pragma once

namespace zMath
{
	/*
	* Return the absolute value of an object
	* 
	* @param x When x is positive it is returned as is, else it is * -1
	*/
	template< class T >
	T abs(T x);

	template float abs(float x);
}