#include <iostream>
#include "Geometry.h"

int main()
{
	const Point point{2, 2};
	
	const Point a{1, 1};
	const Point b{1, 5};
	const Point c{4, 1};
	
	const Triangle triangle{a, b, c};

	std::cout << point_in_triangle(point, triangle) << std::endl;
}
