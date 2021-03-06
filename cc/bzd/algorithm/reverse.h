#pragma once

#include "bzd/utility/swap.h"

namespace bzd::algorithm {
template <class BidirIt>
constexpr void reverse(BidirIt first, BidirIt last)
{
	while ((first != last) && (first != --last))
	{
		bzd::swap(*first++, *last);
	}
}
} // namespace bzd::algorithm
