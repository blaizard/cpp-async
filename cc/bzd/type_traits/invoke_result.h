#pragma once

#include "bzd/container/reference_wrapper.h"
#include "bzd/type_traits/decay.h"
#include "bzd/type_traits/declval.h"
#include "bzd/type_traits/enable_if.h"
#include "bzd/type_traits/false_type.h"
#include "bzd/type_traits/is_base_of.h"
#include "bzd/type_traits/is_function.h"
#include "bzd/type_traits/true_type.h"
#include "bzd/utility/forward.h"

namespace bzd::typeTraits::impl {
template <class T>
struct IsReferenceWrapper : bzd::typeTraits::FalseType
{
};
template <class U>
struct IsReferenceWrapper<bzd::ReferenceWrapper<U>> : bzd::typeTraits::TrueType
{
};

template <class T>
struct InvokeImpl
{
	template <class F, class... Args>
	static auto call(F&& f, Args&&... args) -> decltype(bzd::forward<F>(f)(bzd::forward<Args>(args)...));
};

template <class B, class MT>
struct InvokeImpl<MT B::*>
{
	template <class T,
			  class Td = typename bzd::typeTraits::Decay<T>,
			  class = typename bzd::typeTraits::EnableIf<typeTraits::isBaseOf<B, Td>>>
	static auto get(T&& t) -> T&&;

	template <class T,
			  class Td = typename bzd::typeTraits::Decay<T>,
			  class = typename bzd::typeTraits::EnableIf<IsReferenceWrapper<Td>::value>>
	static auto get(T&& t) -> decltype(t.get());

	template <class T,
			  class Td = typename bzd::typeTraits::Decay<T>,
			  class = typename bzd::typeTraits::EnableIf<!typeTraits::isBaseOf<B, Td>>,
			  class = typename bzd::typeTraits::EnableIf<!IsReferenceWrapper<Td>::value>>
	static auto get(T&& t) -> decltype(*bzd::forward<T>(t));

	template <class T, class... Args, class MT1, class = typename bzd::typeTraits::EnableIf<bzd::typeTraits::isFunction<MT1>>>
	static auto call(MT1 B::*pmf, T&& t, Args&&... args)
		-> decltype((InvokeImpl::get(bzd::forward<T>(t)).*pmf)(bzd::forward<Args>(args)...));

	template <class T>
	static auto call(MT B::*pmd, T&& t) -> decltype(InvokeImpl::get(bzd::forward<T>(t)).*pmd);
};

template <class F, class... Args, class Fd = typename bzd::typeTraits::Decay<F>>
auto Invoke(F&& f, Args&&... args) -> decltype(InvokeImpl<Fd>::call(bzd::forward<F>(f), bzd::forward<Args>(args)...));

template <typename AlwaysVoid, typename, typename...>
struct InvokeResult
{
};
template <typename F, typename... Args>
struct InvokeResult<decltype(void(Invoke(bzd::typeTraits::declval<F>(), bzd::typeTraits::declval<Args>()...))), F, Args...>
{
	using Type = decltype(Invoke(bzd::typeTraits::declval<F>(), bzd::typeTraits::declval<Args>()...));
};
} // namespace bzd::typeTraits::impl

namespace bzd::typeTraits {
template <class F, class... ArgTypes>
using InvokeResult = typename impl::InvokeResult<void, F, ArgTypes...>::Type;
}
