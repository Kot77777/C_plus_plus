#include <iostream>
#include "geometry/intersections/Lines_intersection.h"
#include "geometry/intersections/Segments_intersection.h"

int main()
{
	const Point r0_1{2, 2};
	const Vector a1{4, 4};

	const Point r0_2{1, 1};
	const Vector a2{2, 1};

	const Line l1{r0_1, a1};
	const Line l2{r0_2, a2};

	const Segment s1{{1, 1}, {4, 4}};
	const Segment s2{{0, 0}, {5, 0}};

	const auto O = lines_intersection(l1, l2);

	std::cout << "Точка пересечения: " << O->t1 << " " << O->t2 << std::endl;

	const auto s = segments_intersection(s1, s2);
	std::cout << s->t1 << " " << s->t2 << std::endl;
}
