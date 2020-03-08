#pragma once

#include "bzd/container/span.h"
#include "bzd/container/expected.h"
#include "bzd/types.h"

namespace bzd {
namespace impl {

class IOChannelCommon
{
public:
	virtual bzd::Expected<void> connect() { return {}; }
	virtual bzd::Expected<void> disconnect(){ return {}; }
};

template <class T>
class OChannel : public IOChannelCommon
{
protected:
	OChannel() = default;

public:
	virtual bzd::Expected<SizeType> write(const Span<const T>& data) noexcept = 0;
	virtual bzd::Expected<SizeType> write(const T& data) noexcept { return write(Span<const T>(&data, 1)); }
};

template <class T>
class IChannel : public IOChannelCommon
{
protected:
	IChannel() = default;

public:
	virtual bzd::Expected<SizeType> read(Span<T>& data) noexcept = 0;
	virtual bzd::Expected<SizeType> read(T& data) noexcept
	{
		auto temp = Span<T>(&data, 1);
		return read(temp);
	}
};

template <class T>
class IOChannel
	: public IChannel<T>
	, public OChannel<T>
{
};
} // namespace impl

using OChannel = impl::OChannel<bzd::UInt8Type>;
using IChannel = impl::IChannel<bzd::UInt8Type>;
using IOChannel = impl::IOChannel<bzd::UInt8Type>;
} // namespace bzd