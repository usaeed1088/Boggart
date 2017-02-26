#pragma once

#include <vector>
#include <list>

namespace Transport
{
	namespace Type
	{
		typedef std::uint8_t		Byte;
		typedef std::vector<Byte>	Bytes;

		typedef std::uint16_t		Id;
		typedef std::uint8_t		Sequence;

		typedef std::list<Bytes>	Queue;

		typedef std::size_t			Size;
	}
}