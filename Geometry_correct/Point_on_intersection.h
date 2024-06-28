#ifndef GEOMETRY_POINT_ON_INTERSECTION_H
#define GEOMETRY_POINT_ON_INTERSECTION_H
#include "Line.h"
#include "Vector.h"
#include "Determinant.h"

Vector operator-(const Point& a,
		 const Point& b);
		 
Point point_on_intersection(const Line& l1,
			    const Line& l2);

#endif

