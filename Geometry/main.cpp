#include <iostream>
#include "Geometry.hpp"

int main()
{
	Point A, B, C, O;
	std::cout << "Введите координаты вершин треугольника" << std::endl;
	std::cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y;
	std::cout << "Введите координаты эксперементальной точки" << std::endl;
	std::cin >> O.x >> O.y;

	std::cout << Geometry(O, A, B, C) << std::endl;
}
