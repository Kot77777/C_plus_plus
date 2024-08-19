#include "gtest/gtest.h"
#include "metaproga/contain.h"

TEST(CONTAIN, CREATE_CONTAIN)
{
	   ASSERT_EQ((contain<Pack<int, double, char, long int, unsigned>, long int>()), true);
}
