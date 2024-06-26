#include "Determinant.h"

double determinant(const double a11,
	           const double a21,
		   const double a12,
		   const double a22)
{
	return a11 * a22 - a12 * a21;
}
