#include "gtest/gtest.h"
#include "geometry/primitives/Vector.h"

TEST(VECTOR, CREATE_VECTOR)
{
	Vector<2> v1 = {{1, 2}};
	Vector<2> v2 = {{1, 2}};
	std::array<Vector<2>, 2> matrix = {v1, v2};
	
	Vector<2> v1_ = {{2, 2}};
	Vector<2> v2_ = {{1, 2}};
	std::array<Vector<2>, 2> matrix_ = {v1_, v2_};
	
	ASSERT_EQ(determinant(matrix), 0);
	ASSERT_EQ(determinant(matrix_), 1);
}
