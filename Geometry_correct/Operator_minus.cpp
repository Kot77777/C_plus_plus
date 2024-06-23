#include "Operator_minus.h"

Vector operator-(const Point& point1, const Point& point2)
{
	return {point1.x - point2.x, point1.y - point2.y};
}
