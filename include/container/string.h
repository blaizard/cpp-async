#pragma once

#include <string.h>

#include "include/types.h"
#include "include/utility.h"
#include "include/container/span.h"
#include "include/container/string_view.h"
#include "include/type_traits/const_volatile.h"

namespace bzd
{
	namespace impl
	{
		template <class T, class Impl>
		class String : public Impl
		{
		protected:
			using Parent = Impl;
			using Impl::size_;
			using Impl::data_;

			using StringView = bzd::impl::StringView<T, bzd::Span<typename bzd::typeTraits::addConst<T>::type>>;

		public:
			template <class... Args>
			constexpr explicit String(const SizeType capacity, Args&&... args)
					: Impl(args...), capacity_(capacity)
			{
			}

			// Converter
			constexpr SizeType append(const StringView& str) noexcept { return append(str.data(), str.size()); }
			constexpr SizeType append(const T c) noexcept { return append(&c, 1); }
			constexpr SizeType append(const T* data, const SizeType n) noexcept
			{
				// Handles overflows
				const SizeType sizeLeft = capacity_ - size_ - 1;
				const SizeType actualN = (sizeLeft < n) ? sizeLeft : n;
				bzd::memcpy(&Parent::at(size_), data, actualN);
				size_ += actualN;
				Parent::at(size_) = '\0';

				return actualN;
			}

			template <class U>
			constexpr SizeType assign(const U& data) noexcept
			{
				clear();
				return append(data);
			}

			constexpr SizeType capacity() const noexcept
			{
				return capacity_ - 1;
			}

			constexpr void clear() noexcept
			{
				resize(0);
			}

			constexpr void resize(const SizeType n) noexcept
			{
				size_ = (n < capacity_ - 1) ? n : capacity_ - 1;
				Parent::at(size_) = '\0';
			}

			template <class U>
			constexpr String<T, Impl>& operator+=(const U& data) noexcept
			{
				append(data);
				return *this;
			}

			template <class U>
			constexpr String<T, Impl>& operator=(const U& data) noexcept
			{
				assign(data);
				return *this;
			}

		public:
			const SizeType capacity_;
		};
	}

	namespace interface
	{
		using String = impl::String<char, Span<char>>;
	}

	template <SizeType N>
	class String : public interface::String
	{
	public:
		constexpr String() : interface::String(N + 1, data_, 0) { data_[0] = '\0'; }
		constexpr String(const bzd::StringView& str) : String() { append(str); }

		template <class T>
		constexpr String<N>& operator=(const T& data) noexcept
		{
			assign(data);
			return *this;
		}

		// Copy assignment, has to be non-templated
		constexpr String<N>& operator=(const String<N>& data) noexcept
		{
			assign(data);
			return *this;
		}

	protected:
		interface::String::DataType data_[N + 1] = {}; // needed for constexpr
	};
}
