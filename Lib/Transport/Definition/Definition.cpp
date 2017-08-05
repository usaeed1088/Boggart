#include "Definition.h"

namespace Boggart
{
	namespace Transport
	{
		const std::uint8_t Definition::SOP('[');
		const std::uint8_t Definition::EOP(']');
		const std::uint8_t Definition::EscapeCharacter('\\');

		Definition::Definition()
		{

		}
	}
}