#include "bzd/container/variant.h"

#include "cc_test/test.h"

#include <iostream>

TEST(ContainerVariant, Constructor)
{
	bzd::Variant<int, bool, double> variant;
	bzd::Variant<int, bool, double> variantInt{static_cast<int>(45)};
	bzd::Variant<int, bool, double> variantBool{static_cast<bool>(true)};
	bzd::Variant<int, bool, double> variantDouble{static_cast<double>(5.4)};
}

TEST(ContainerVariant, ImplicitConstructor)
{
	bzd::Variant<void*, bool, double> variantExplicit(static_cast<double>(45.2));
	EXPECT_EQ(variantExplicit.index(), 2);
	bzd::Variant<void*, bool, double> variantImplicit(static_cast<float>(45.2));
	EXPECT_EQ(variantImplicit.index(), 1);
}

TEST(ContainerVariant, CopyConstructor)
{
	bzd::Variant<int, bool, double> variant1{static_cast<double>(3.1415)};
	EXPECT_NEAR(*variant1.get<double>(), 3.1415, 0.0001);
	bzd::Variant<int, bool, double> variant2{variant1};
	EXPECT_NEAR(*variant2.get<double>(), 3.1415, 0.0001);
}

TEST(ContainerVariant, Destructor)
{
	static int constructorA = 0;
	static int destructorA = 0;
	static int constructorB = 0;
	static int destructorB = 0;

	class TypeA
	{
	public:
		TypeA() { ++constructorA; }
		TypeA(const TypeA&) { ++constructorA; }
		~TypeA() { ++destructorA; }
	};

	class TypeB
	{
	public:
		TypeB() { ++constructorB; }
		TypeB(const TypeB&) { ++constructorB; }
		~TypeB() { ++destructorB; }
	};

	bzd::Variant<TypeA, TypeB> variant1;
	EXPECT_EQ(constructorA, 0);
	EXPECT_EQ(destructorA, 0);
	EXPECT_EQ(constructorB, 0);
	EXPECT_EQ(destructorB, 0);

	{
		TypeB b;
		bzd::Variant<TypeA, TypeB> variant(bzd::move(b));
		EXPECT_EQ(constructorA, 0);
		EXPECT_EQ(destructorA, 0);
		EXPECT_EQ(constructorB, 2);
		EXPECT_EQ(destructorB, 0);
	}
	EXPECT_EQ(destructorB, 2);

	{
		TypeA a;
		bzd::Variant<TypeA, TypeB> variant(bzd::move(a));
		EXPECT_EQ(constructorA, 2);
		EXPECT_EQ(destructorA, 0);
		EXPECT_EQ(constructorB, 2);
		EXPECT_EQ(destructorB, 2);
	}
	EXPECT_EQ(destructorA, 2);
}

TEST(ContainerVariant, Is)
{
	bzd::Variant<int, bool, double> variantBool(static_cast<bool>(true));
	EXPECT_TRUE(variantBool.is<bool>());
	EXPECT_FALSE(variantBool.is<int>());
	EXPECT_FALSE(variantBool.is<double>());
	EXPECT_FALSE(variantBool.is<char>());

	bzd::Variant<int, bool, double> variantEmpty;
	EXPECT_FALSE(variantEmpty.is<bool>());
}

TEST(ContainerVariant, Get)
{
	bzd::Variant<bool, int, double> variantInt(static_cast<int>(-12));

	auto retBool = variantInt.get<bool>();
	EXPECT_FALSE(retBool);

	auto retInt = variantInt.get<int>();
	EXPECT_TRUE(retInt);
	EXPECT_EQ(*retInt, -12);
	*retInt = 42;
	EXPECT_EQ(*(variantInt.get<int>()), 42);
}

TEST(ContainerVariant, Match)
{
	{
		bzd::Variant<int, bool, double> variant(static_cast<double>(5.6));
		double b = 0;
		variant.match([](const int) {}, [](const bool) {}, [&](const double a) { b = a; });
		EXPECT_NEAR(b, 5.6, 0.001);
	}
	{
		bzd::Variant<int, bool, double> variant(static_cast<int>(5));
		int b = 0;
		variant.match([&](const int a) { b = a; }, [](const bool) {}, [](const double) {});
		EXPECT_EQ(b, 5);
	}
	{
		bzd::Variant<int, bool, double> variant(static_cast<int>(5));
		bool isHandled = false;
		variant.match([&](auto&&) { isHandled = true; });
		EXPECT_TRUE(isHandled);
	}
}

TEST(ContainerVariant, Constexpr)
{
	constexpr bzd::VariantConstexpr<int, bool, double> variant;
	EXPECT_FALSE(variant.is<int>());
	EXPECT_FALSE(variant.is<bool>());
	EXPECT_FALSE(variant.is<double>());

	constexpr bzd::VariantConstexpr<int, bool, double> variantInt(static_cast<int>(45));
	EXPECT_TRUE(variantInt.is<int>());
	constexpr bzd::VariantConstexpr<int, bool, double> variantBool(static_cast<bool>(true));
	EXPECT_TRUE(variantBool.is<bool>());
	constexpr bzd::VariantConstexpr<int, bool, double> variantDouble(static_cast<double>(5.4));
	EXPECT_TRUE(variantDouble.is<double>());

	const auto ret = variantDouble.get<double>();
	EXPECT_TRUE(ret);
	EXPECT_NEAR(*ret, 5.4, 0.01);

	{
		constexpr bzd::VariantConstexpr<int, bool, double> variant(static_cast<double>(5.6));
		double b = 0;
		variant.match([](const int) {}, [](const bool) {}, [&](const double a) { b = a; });
		EXPECT_NEAR(b, 5.6, 0.001);
	}
}
