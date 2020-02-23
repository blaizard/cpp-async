#pragma once

#include "bzd/type_traits/add_pointer.h"
#include "bzd/type_traits/conditional.h"
#include "bzd/type_traits/is_array.h"
#include "bzd/type_traits/is_function.h"
#include "bzd/type_traits/remove_cv.h"
#include "bzd/type_traits/remove_extent.h"
#include "bzd/type_traits/remove_reference.h"

namespace bzd {
template <class T>
struct decay
{
private:
	typedef typename bzd::typeTraits::removeReference<T>::type U;

public:
	typedef bzd::typeTraits::Conditional<
		bzd::typeTraits::isArray<U>,
		typename bzd::typeTraits::removeExtent<U>::type*,
		bzd::typeTraits::Conditional<bzd::typeTraits::isFunction<U>, bzd::typeTraits::AddPointer<U>, bzd::typeTraits::RemoveCV<U>>>
		type;
};
} // namespace bzd
