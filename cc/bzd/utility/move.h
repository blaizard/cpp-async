#pragma once

#include "bzd/type_traits/remove_reference.h"

namespace bzd {
template <class T>
constexpr bzd::typeTraits::RemoveReference<T>&& move(T&& arg)
{
	return static_cast<bzd::typeTraits::RemoveReference<T>&&>(arg);
}
} // namespace bzd
