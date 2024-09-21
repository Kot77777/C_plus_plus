#include "gtest/gtest.h"
#include "metaproga/Pack.h"
#include "metaproga/unique.h"

TEST(CONTAIN, CREATE_CONTAIN)
{
	ASSERT_EQ((is_same_v<unique<Pack<>, Pack<>>, Pack<>>), 1);
	ASSERT_EQ((is_same_v<unique<Pack<int>, Pack<>>, Pack<int>>), 1);
	ASSERT_EQ((is_same_v<unique<Pack<int, char, int>, Pack<>>, Pack<int, char>>), 1);
	ASSERT_EQ((is_same_v<unique<Pack<int, char, char, unsigned, int, double>, Pack<>>, Pack<int, char, unsigned, double>>), 1);
	ASSERT_EQ((is_same_v<unique<Pack<int, char, int, int, double>, Pack<>>, Pack<int, char, double>>), 1);
	ASSERT_EQ((is_same_v<unique<Pack<int, char, int>, Pack<>>, Pack<int, char>>), 1);
}
