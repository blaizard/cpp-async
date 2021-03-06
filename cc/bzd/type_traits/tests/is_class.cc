#include "bzd/type_traits/is_class.h"

#include "cc_test/test.h"

struct A
{
};

class B
{
};

enum class C
{
};

TEST(TypeTraits, isClass)
{
	{
		const bool result = bzd::typeTraits::isClass<int>;
		EXPECT_FALSE(result);
	}
	{
		const bool result = bzd::typeTraits::isClass<A>;
		EXPECT_TRUE(result);
	}
	{
		const bool result = bzd::typeTraits::isClass<B>;
		EXPECT_TRUE(result);
	}
	{
		const bool result = bzd::typeTraits::isClass<C>;
		EXPECT_FALSE(result);
	}
}
