#include <iostream>
#include "Geometry.hpp"

int main()
{
	Point A, B, C, O;
	
	std::cout << "Введите координаты вершин треугольника" << std::endl;
	std::cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y;
	
	std::cout << "Введите координаты эксперементальной точки" << std::endl;
	std::cin >> O.x >> O.y;
	
	if (Geometry(O, A, B, C))
	{
		std::cout << "Точка принадлежит треугольнику" << std::endl;
	}
	
	else
	{
		std::cout << "Точка НЕ принадлежит треугольнику" << std::endl;
	}
}
