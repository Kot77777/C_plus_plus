#include "Point_on_intersection.h"

Vector operator-(const Point& a,
		 const Point& b)
{
	return{a.x - b.x, a.y - b.y};
}

Point point_on_intersection(const Line& l1,
			    const Line& l2)
{
	const Vector e1 = l1.b - l1.a;
	const Vector e2 = l2.b - l2.a;

	const double b1 = l1.a.x * e1.y - l1.a.y * e1.x;
	const double b2 = l2.a.x * e2.y - l2.a.y * e2.x;
	
	const Vector b{b1, b2};
	const Vector d1{e1.y, e2.y};
	const Vector d2{-e1.x, -e2.x};

	const double det = determinant(d1, d2);
	const double det1 = determinant(b, d2);
	const double det2 = determinant(d1, b);

	const double x = det1 / det;
	const double y = det2 / det;

	return {x, y};
}
