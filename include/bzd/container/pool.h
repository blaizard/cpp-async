#pragma once

#include "bzd/types.h"
#include "bzd/utility/container_of.h"
#include "bzd/container/span.h"
#include "bzd/container/impl/single_linked_pool.h"

#include <iostream>

namespace bzd
{
	namespace impl
	{
		template <class T, class CapacityType = SizeType>
		class Pool : public SingleLinkedPool<T, CapacityType>
		{
		protected:
			using typename SingleLinkedPool<T, CapacityType>::Element;

		public:
			constexpr explicit Pool(const bzd::Span<Element> data) noexcept
					: SingleLinkedPool<T, CapacityType>(data)
			{
			}

			/**
			 * Release an element from the pool
			 */
			constexpr void release(T& container) noexcept
			{
				auto* item = containerOf(&container, &Element::container_);
				SingleLinkedPool<T, CapacityType>::release(*item);
			}

			/**
			 * Reserve an element from the free list (if any)
			 */
			constexpr T& reserve() noexcept
			{
				return SingleLinkedPool<T, CapacityType>::reserve().container_;
			}
		};
	}

	namespace interface
	{
		template <class T, class CapacityType = SizeType>
		using Pool = impl::Pool<T, CapacityType>;
	}

	/**
	 * A Pool is a fixed memory buffer containing fixed size elements that can be taken or released.
	 */
	template <class T, SizeType N, class CapacityType = SizeType>
	class Pool : public interface::Pool<T, CapacityType>
	{
	private:
		using typename interface::Pool<T, CapacityType>::Element;

	public:
		constexpr Pool()
				: interface::Pool<T, CapacityType>({data_, N})
		{
		}

	private:
		Element data_[N];
	};
}