#ifndef GEOMETRY_VECTOR_H
#define GEOMETRY_VECTOR_H
#include "Point.h"

struct Vector 
{
	double x;
	double y;
};

Vector operator-(const Point& a, const Point& b);

#endif
