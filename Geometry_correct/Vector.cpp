#include "Vector.h"

Vector operator-(const Point& a, const Point& b)
{
	return {b.x - a.x, b.y - a.y};
}
