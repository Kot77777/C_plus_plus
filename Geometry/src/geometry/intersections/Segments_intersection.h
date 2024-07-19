#ifndef GEOMETRY_SEGMENTS_INTERSECTION_H
#define GEOMETRY_SEGMENTS_INTERSECTION_H
#include "geometry/intersections/Lines_intersection.h"
#include "geometry/primitives/Segment.h"

template<std::size_t n>
std::optional<Intersection> segments_intersection(const Segment<n>& s1, const Segment<n>& s2);

#endif

