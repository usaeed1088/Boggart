#pragma once

#include <cstdint>
#include <functional>

namespace Boggart
{
	namespace Timer
	{
		typedef std::int16_t				Id_t;
		typedef std::uint16_t				Span_t;
		typedef std::uint64_t				TimePoint_t;
		typedef std::function<void(void)>	Callback_t;
	}
}