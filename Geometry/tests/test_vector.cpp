#include "gtest/gtest.h"
#include "geometry/primitives/Matrix.h"

TEST(VECTOR, CREATE_VECTOR)
{
	std::array<std::array<double, 3>, 1> matrix1 = {{{1, 2, 3}}};
	//Matrix<1, 3> matrix_1{matrix1};
	Vector<3> vec{matrix1};
	std::cout << vec.x() << std::endl;
	
	std::array<std::array<double, 3>, 3> matrix2 = {{{3, 2, 5}, {7, 8, 6}, {11, 3, 6}}};
	Matrix<3, 3> matrix_2{matrix2};
	
	ASSERT_EQ(determinant<3>(matrix_2), -197);
}
