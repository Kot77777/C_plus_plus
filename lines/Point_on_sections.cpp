#include "Point_on_sections.h"

bool point_on_sections(const Line& l1,
		       const Line& l2)
{
	const Point O = point_on_intersection(l1, l2);

	const Vector OA = l1.a - O;
	const Vector OB = l1.b - O;

	const Vector OC = l2.a - O;
	const Vector OD = l2.b - O;

	const double scalar_product1 = scalar_product(OA, OB);
	const double scalar_product2 = scalar_product(OC, OD);

	return (scalar_product1 < 0) && (scalar_product2 < 0);
}
