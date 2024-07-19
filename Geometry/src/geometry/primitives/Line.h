#ifndef GEOMETRY_LINE_H
#define GEOMETRY_LINE_H
#include "Point.h"
#include "Vector.h"

template<std::size_t n>
struct Line
{
	Point<n> r0;
	Vector<n> a;
};

#endif
