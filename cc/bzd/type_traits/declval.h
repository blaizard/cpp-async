#pragma once

#include "bzd/type_traits/add_rvalue_reference.h"

namespace bzd::typeTraits {
template <class T>
AddRValueReference<T> declval();
} // namespace bzd::typeTraits
