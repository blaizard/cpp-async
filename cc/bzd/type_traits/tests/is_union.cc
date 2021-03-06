#include "bzd/type_traits/is_union.h"

#include "cc_test/test.h"

TEST(TypeTraits, isUnion)
{
	{
		const bool result = bzd::typeTraits::isUnion<int>;
		EXPECT_FALSE(result);
	}
	{
		struct Trivial
		{
			int val;
		};
		const bool result = bzd::typeTraits::isUnion<Trivial>;
		EXPECT_FALSE(result);
	}
	{
		union Ints {
			int in;
			long lo;
		};
		const bool result = bzd::typeTraits::isUnion<Ints>;
		EXPECT_TRUE(result);
	}
}
