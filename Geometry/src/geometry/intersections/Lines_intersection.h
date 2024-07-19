#ifndef GEOMETRY_LINES_INTERSECTION_H
#define GEOMETRY_LINES_INTERSECTION_H
#include <optional>
#include "geometry/primitives/Line.h"
#include "geometry/intersections/Intersection.h"
#include "geometry/primitives/Vector.h"

template<std::size_t n>
std::optional<Intersection> lines_intersection(const Line<n>& l1, const Line<n>& l2);

#endif
