#include "Segments_intersection.h"

template<std::size_t n>
std::optional<Intersection> segments_intersection(const Segment<n>& s1, const Segment<n>& s2)
{
	const Line<n> l1{s1.A, s1.B - s1.A};
	const Line<n> l2{s2.A, s2.B - s2.A};

	const auto intersection = lines_intersection(l1, l2);

	if (intersection.has_value() &&
	    intersection->t1 >= 0 && intersection->t1 <= 1 &&
	    intersection->t2 >= 0 && intersection->t2 <= 2)
	{
		return intersection;
	}

	return {};
}
