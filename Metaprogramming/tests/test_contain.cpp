#include "gtest/gtest.h"
#include "metaproga/contain.h"

TEST(CONTAIN, CREATE_CONTAIN)
{
	ASSERT_EQ((contain<Pack<int, double, char, long>, int>()), true);
	ASSERT_EQ((contain<Pack<int, double, char, long>, int*>()), false);
	ASSERT_EQ((contain<Pack<int, double, char, long, unsigned>, unsigned>()), true);
	ASSERT_EQ((contain<Pack<int, double, char>, long double>()), false);
	ASSERT_EQ((contain<Pack<>, int>()), false);
}
