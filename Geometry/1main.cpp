#include <iostream>
#include "geometry/intersections/Lines_intersection.h"
#include "geometry/intersections/Segments_intersection.h"

int main()
{
	const Point<2> r0_1{2, 2};
	const Vector<2> a1{4, 4};

	const Point<2> r0_2{1, 1};
	const Vector<2> a2{2, 1};

	const Line<2> l1{r0_1, a1};
	const Line<2> l2{r0_2, a2};

	const Segment<2> s1{{1, 1}, {4, 4}};
	const Segment<2> s2{{0, 0}, {5, 0}};

	const auto O = lines_intersection(l1, l2);

	std::cout << "Точка пересечения: " << O->t1 << " " << O->t2 << std::endl;

	const auto s = segments_intersection(s1, s2);
	std::cout << s->t1 << " " << s->t2 << std::endl;
}
