#ifndef GEOMETRY_POINT_IN_TRIANGLE_H
#define GEOMETRY_POINT_IN_TRIANGLE_H
#include "geometry/primitives/Triangle.h"
#include "geometry/operations/Determinant.h"

Vector operator-(const Point& point1, const Point& point2);

bool point_in_triangle(const Point& point, const Triangle& triangle);

#endif
