#ifndef GEOMETRY_LINES_INTERSECTION_H
#define GEOMETRY_LINES_INTERSECTION_H
#include <optional>
#include "geometry/primitives/Line.h"
#include "geometry/intersections/Intersection.h"

template <std::size_t N>
std::optional<Intersection> lines_intersection(const Line<N>& l1, const Line<N>& l2);

template <>
inline std::optional<Intersection> lines_intersection<2>(const Line<2>& l1, const Line<2>& l2)
{
	const double det_ = -determinant({l1.a, l2.a});
	if (det_ == 0)
	{
		return {};
	}

	const Vector<2> dr = l2.r0.r0 - l1.r0.r0;
	
	const double det1_ = -determinant({dr, l2.a});
	const double det2_ = determinant({l1.a, dr});
	return Intersection{det1_ / det_, det2_ / det_};
}

#endif
