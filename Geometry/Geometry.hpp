#ifndef GEOMETRY_H
#define GEOMETRY_H

struct Point
{
	double x;
	double y;
};


double value_of_function_in_point(const Point &O, const Point &A, const Point &B);
bool Geometry(const Point &O, const Point &A, const Point &B, const Point &C);

#endif

