#include "Lines_intersection.h"

std::optional<Intersection> lines_intersection(const Line& l1, const Line& l2)
{
	const double det = -determinant(l1.a, l2.a);
	if (det == 0)
	{
		return {};
	}

	const Vector dr = l2.r0 - l1.r0;
	const double det1 = -determinant(dr, l2.a);
	const double det2 = determinant(l1.a, dr);
	return Intersection{det1 / det, det2 / det};
}
