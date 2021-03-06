#include "bzd/utility/ratio.h"

#include "cc_test/test.h"

TEST(Ratio, Base)
{
	using MyRatio = bzd::Ratio<42, 34>;
	EXPECT_EQ(MyRatio::num, 42);
	EXPECT_EQ(MyRatio::den, 34);

	using MyRatioNum = bzd::Ratio<14>;
	EXPECT_EQ(MyRatioNum::num, 14);
	EXPECT_EQ(MyRatioNum::den, 1);
}