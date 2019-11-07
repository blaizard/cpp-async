#include "gtest/gtest.h"

#include "include/type_traits/const_volatile.h"
#include "include/type_traits/utils.h"

TEST(TypeTraits, removeCV)
{
	{
		typedef bzd::typeTraits::removeCV<const int>::type type;
		const bool result = bzd::typeTraits::isSame<int, type>::value;
		EXPECT_TRUE(result);
	}

	{
		typedef bzd::typeTraits::removeCV<volatile int>::type type;
		const bool result = bzd::typeTraits::isSame<int, type>::value;
		EXPECT_TRUE(result);
	}

	{
		typedef bzd::typeTraits::removeCV<const volatile int>::type type;
		const bool result = bzd::typeTraits::isSame<int, type>::value;
		EXPECT_TRUE(result);
	}

	{
		typedef bzd::typeTraits::removeCV<const volatile int*>::type type;
		const bool result = bzd::typeTraits::isSame<const volatile int*, type>::value;
		EXPECT_TRUE(result);
	}

	{
		typedef bzd::typeTraits::removeCV<int* const volatile>::type type;
		const bool result = bzd::typeTraits::isSame<int*, type>::value;
		EXPECT_TRUE(result);
	}
}