#pragma once

#include "include/container/string_view.h"
#include "include/system.h"

namespace bzd
{
	namespace assert
	{
		constexpr void isTrue(const bool condition)
		{
			if (!condition)
			{
				bzd::panic();
			}
		}

		constexpr void isTrue(const bool condition, const bzd::StringView& message)
		{
			if (!condition)
			{
				getOut().write(message);
				bzd::panic();
			}
		}
	}
}
