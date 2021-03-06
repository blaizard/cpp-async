#include "bzd/utility/format/integral.h"

namespace bzd::format {

void toString(bzd::OChannel& stream, const bzd::StringView& data)
{
	stream.write(data.asBytes());
}

void toString(bzd::OChannel& stream, const char c)
{
	stream.write(bzd::StringView{&c, 1}.asBytes());
}
} // namespace bzd::format
