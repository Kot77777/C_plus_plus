#ifndef GEOMETRY_POINT_H
#define GEOMETRY_POINT_H
#include <array>

template<std::size_t n>
struct Point
{
	std::array<double, n> data_;
};

#endif
