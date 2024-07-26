#ifndef GEOMETRY_POINT_H
#define GEOMETRY_POINT_H
#include <array>
#include <Vector.h>

template<std::size_t n>
struct Point
{
	Vector<n> r0;
};

#endif
