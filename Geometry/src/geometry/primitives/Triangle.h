#ifndef GEOMERTY_TRIANGLE_H
#define GEOMERTY_TRIANGLE_H
#include "Point.h"

template<std::size_t n>
struct Triangle
{
	Point<n> a;
	Point<n> b;
	Point<n> c;
};

#endif
