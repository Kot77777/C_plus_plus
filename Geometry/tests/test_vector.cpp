#include "gtest/gtest.h"
#include "geometry/primitives/Vector.h"

TEST(VECTOR, CREATE_VECTOR)
{
	Vector<2> v1 = {{1, 2}};
	ASSERT_EQ(v1[0], 2);
}
