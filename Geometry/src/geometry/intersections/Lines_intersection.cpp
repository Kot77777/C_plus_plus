#include "Lines_intersection.h"

template<std::size_t n>
std::optional<Intersection> lines_intersection(const Line<n>& l1, const Line<n>& l2)
{
	const double det_ = -det({l1.a, l2.a});
	if (det_ == 0)
	{
		return {};
	}

	const Vector dr = l2.r0 - l1.r0;
	const double det1_ = -det({dr, l2.a});
	const double det2_ = det({l1.a, dr});
	return Intersection{det1_ / det_, det2_ / det_};
}
