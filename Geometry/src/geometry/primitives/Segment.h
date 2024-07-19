#ifndef GEOMETRY_SEGMENT_H
#define GEOMETRY_SEGMENT_H
#include "Point.h"

template<std::size_t n>
struct Segment
{
	Point<n> A;
	Point<n> B;
};

#endif
