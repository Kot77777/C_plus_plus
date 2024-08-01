#ifndef GEOMETRY_POINT_IN_TRIANGLE_H
#define GEOMETRY_POINT_IN_TRIANGLE_H
#include "geometry/primitives/Triangle.h"
#include "geometry/primitives/Vector.h"

template <std::size_t N>
bool point_in_triangle(const Point<N>& point, const Triangle<N>& triangle);

template <>
bool point_in_triangle<2>(const Point<2>& point, const Triangle<2>& triangle)
{
	const Vector<2> d1 = triangle.b.r0 - triangle.a.r0;
	const Vector<2> d2 = triangle.c.r0 - triangle.a.r0;

	const Vector<2> r = point.r0 - triangle.a.r0;

	const float det = determinant(d1, d2);
	const float det1 = determinant(r, d2);
	const float det2 = determinant(d1, r);

	const float x1 = det1 / det;
	const float x2 = det2 / det;

	return x1 >= 0 && x2 >= 0 && (x1 + x2) <= 1;
}

#endif
