#include "gtest/gtest.h"
#include "geometry/primitives/Matrix.h"

TEST(VECTOR, CREATE_VECTOR)
{
	std::array<std::array<double, 3>, 1> matrix1 = {{{1, 2, 3}}};
	Matrix<1, 3> matrix_1{matrix1};
	
	std::array<std::array<double, 3>, 3> matrix2 = {{{3, 2, 5}, {7, 8, 6}, {11, 3, 6}}};
	Matrix<3, 3> matrix_2{matrix2};
	
	Vector v1 = matrix1;
	
	ASSERT_EQ(determinant<3>(matrix_2), -197);
	ASSERT_EQ(v1(0, 1), 2);
}
