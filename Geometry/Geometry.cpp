#include <iostream>
#include "Geometry.hpp"

double value_of_function_in_point(
				 const Point &O,
				 const Point &A,
				 const Point &B
				 )
{
	return ((O.x - A.x)*(B.y - A.y) - (O.y - A.y)*(B.x - A.x));
}

bool Geometry(
	     const Point &O,
	     const Point &A,
	     const Point &B,
	     const Point &C
	     )
{
	double AB_C = value_of_function_in_point(C, A, B);
	double AB_O = value_of_function_in_point(O, A, B);
	
	double AC_B = value_of_function_in_point(B, A, C);
	double AC_O = value_of_function_in_point(O, A, C);
	
	double BC_A = value_of_function_in_point(A, B, C);
	double BC_O = value_of_function_in_point(O, B, C);

	if ((AB_C * AB_O >= 0) && (AC_B * AC_O >= 0) && (BC_A * BC_O >= 0))
	{
		return true;
	}
		
	else
	{
		return false;
	}
}

