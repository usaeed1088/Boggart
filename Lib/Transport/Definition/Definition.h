#pragma once

#include <cstdint>

namespace Boggart
{
	namespace Transport
	{
		class Definition
		{
		private:
			Definition();

		public:
			static const std::uint8_t SOP;
			static const std::uint8_t EOP;
			static const std::uint8_t EscapeCharacter;
		};
	}
}