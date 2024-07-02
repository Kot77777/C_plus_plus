#include "Segments_intersection.h"

std::optional<Intersection> segments_intersection(const Segment& s1, const Segment& s2)
{
	const Line l1{s1.A, s1.B - s1.A};
	const Line l2{s2.A, s2.B - s2.A};

	const auto intersection = lines_intersection(l1, l2);

	if (intersection.has_value() &&
	    intersection->t1 >= 0 && intersection->t1 <= 1 &&
	    intersection->t2 >= 0 && intersection->t2 <= 2)
	{
		return intersection;
	}

	return {};
}
