#pragma once

#include "bzd/type_traits/false_type.h"
#include "bzd/type_traits/true_type.h"

namespace bzd::typeTraits::impl {
template <class T>
struct IsVolatile : FalseType
{
};
template <class T>
struct IsVolatile<volatile T> : TrueType
{
};
} // namespace bzd::typeTraits::impl

namespace bzd::typeTraits {
template <class T>
using IsVolatile = typename impl::IsVolatile<T>;

template <class T>
constexpr bool isVolatile = IsVolatile<T>::value;

} // namespace bzd::typeTraits
