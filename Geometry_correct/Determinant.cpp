#include "Determinant.h"

float determinant(const Vector& a1, const Vector& a2)
{
	return a1.x * a2.y - a2.x * a1.y; 
}
