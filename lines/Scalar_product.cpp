#include "Scalar_product.h"

double scalar_product(const Vector& r1,
		      const Vector& r2)
{
	return r1.x*r2.x + r1.y*r2.y;
}
