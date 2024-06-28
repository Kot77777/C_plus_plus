#include "Geometry.h"

Vector operator-(const Point& point1, const Point& point2)
{
	return {point1.x - point2.x, point1.y - point2.y};
}

bool point_in_triangle(const Point& point, const Triangle& triangle)
{
	const Vector d1 = triangle.b - triangle.a;
	const Vector d2 = triangle.c - triangle.a;

	const Vector r = point - triangle.a;

	const float det = determinant(d1, d2);
	const float det1 = determinant(r, d2);
	const float det2 = determinant(d1, r);

	const float x1 = det1 / det;
	const float x2 = det2 / det;

	return x1 >= 0 && x2 >= 0 && (x1 + x2) <= 1;
}
