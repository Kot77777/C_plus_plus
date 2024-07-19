#include "Point_in_triangle.h"

template<std::size_t n>
bool point_in_triangle(const Point<n>& point, const Triangle<n>& triangle)
{
	const Vector<n> d1 = triangle.b - triangle.a;
	const Vector<n> d2 = triangle.c - triangle.a;

	const Vector<n> r = point - triangle.a;

	const float det = det(d1, d2);
	const float det1 = det(r, d2);
	const float det2 = det(d1, r);

	const float x1 = det1 / det;
	const float x2 = det2 / det;

	return x1 >= 0 && x2 >= 0 && (x1 + x2) <= 1;
}
