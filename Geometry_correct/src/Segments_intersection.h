#ifndef GEOMETRY_SEGMENTS_INTERSECTION_H
#define GEOMETRY_SEGMENTS_INTERSECTION_H
#include "Lines_intersection.h"
#include "Segment.h"

std::optional<Intersection> segments_intersection(const Segment& s1, const Segment& s2);

#endif

