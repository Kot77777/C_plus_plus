#ifndef GEOMETRY_LINES_INTERSECTION_H
#define GEOMETRY_LINES_INTERSECTION_H
#include <optional>
#include "Line.h"
#include "Intersection.h"
#include "Determinant.h"

std::optional<Intersection> lines_intersection(const Line& l1, const Line& l2);

#endif
