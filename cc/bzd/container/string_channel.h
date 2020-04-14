#pragma once

#include "bzd/container/string.h"
#include "bzd/container/string_view.h"
#include "bzd/core/channel.h"

namespace bzd {
namespace impl {
class StringChannel : public bzd::OChannel
{
public:
	constexpr StringChannel(bzd::interface::String& str) : string_(str) {}

	bzd::Expected<SizeType> write(const bzd::StringView& data) noexcept
	{
		return write({reinterpret_cast<const UInt8Type*>(data.data()), data.size()});
	}

	bzd::Expected<SizeType> write(const bzd::Span<const UInt8Type>& data) noexcept override
	{
		return string_.append(reinterpret_cast<const char*>(data.data()), data.size());
	}

	constexpr const bzd::interface::String& str() const noexcept { return string_; }

	constexpr bzd::interface::String& str() noexcept { return string_; }

protected:
	bzd::interface::String& string_;
};
} // namespace impl

namespace interface {
using StringChannel = bzd::impl::StringChannel;
}

template <SizeType N>
class StringChannel : public bzd::interface::StringChannel
{
public:
	constexpr StringChannel() : bzd::interface::StringChannel(container_), container_() {}

private:
	bzd::String<N> container_;
};
} // namespace bzd