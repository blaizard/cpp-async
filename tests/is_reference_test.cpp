#include "gtest/gtest.h"
#include "bzd/type_traits/is_reference.h"

TEST(TypeTraits, isReference)
{
    {
        auto result = bzd::typeTraits::isReference<int>::value;
        EXPECT_EQ(result, false);
    }
    {
        auto result = bzd::typeTraits::isReference<int&>::value;
        EXPECT_EQ(result, true);
    }
    {
        auto result = bzd::typeTraits::isReference<int&&>::value;
        EXPECT_EQ(result, true);
    }
}