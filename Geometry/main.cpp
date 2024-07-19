#include <iostream>
#include "Geometry.h"

int main()
{
	const Point<2> point{2, 2};
	
	const Point<2> a{1, 1};
	const Point<2> b{1, 5};
	const Point<2> c{4, 1};
	
	const Triangle<2> triangle{a, b, c};

	std::cout << point_in_triangle(point, triangle) << std::endl;
}
