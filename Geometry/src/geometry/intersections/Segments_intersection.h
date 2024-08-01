#ifndef GEOMETRY_SEGMENTS_INTERSECTION_H
#define GEOMETRY_SEGMENTS_INTERSECTION_H
#include "geometry/intersections/Lines_intersection.h"
#include "geometry/primitives/Segment.h"

template <std::size_t N>
std::optional<Intersection> segments_intersection(const Segment<N>& s1, const Segment<N>& s2);

template <>
std::optional<Intersection> segments_intersection<2>(const Segment<2>& s1, const Segment<2>& s2)
{
	const Line<2> l1{s1.A, s1.B - s1.A};
	const Line<2> l2{s2.A, s2.B - s2.A};

	const auto intersection = lines_intersection(l1, l2);

	if (intersection.has_value() &&
	    intersection->t1 >= 0 && intersection->t1 <= 1 &&
	    intersection->t2 >= 0 && intersection->t2 <= 2)
	{
		return intersection;
	}

	return {};
}

#endif

