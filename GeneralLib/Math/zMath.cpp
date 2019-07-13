#include "zMath.h"

template< class T >
T zMath::abs(T x)
{
	if (x >= 0)
	{
		return x;
	}
	else
	{
		return -x;
	}
}