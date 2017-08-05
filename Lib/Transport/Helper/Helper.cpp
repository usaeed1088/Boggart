#include "Helper.h"

#include "../Definition/Definition.h"

namespace Boggart
{
	namespace Transport
	{
		Helper::Helper()
		{

		}

		std::vector<unsigned char> Helper::Wrap(const std::vector<unsigned char>& data)
		{
			std::vector<unsigned char> wrapped;
			std::vector<unsigned char> escaped = Escape(data);

			wrapped.push_back(Definition::SOP);
			wrapped.insert(wrapped.end(), escaped.begin(), escaped.end());
			wrapped.push_back(Definition::EOP);

			return wrapped;
		}

		std::vector<unsigned char> Helper::Unwrap(const std::vector<unsigned char>& data)
		{
			if (data[0] != Definition::SOP || data[data.size() - 1] != Definition::EOP)
			{
				return std::vector<unsigned char>();
			}

			std::vector<unsigned char> unwrapped(data.begin() + 1, data.end() - 1);
			std::vector<unsigned char> unescaped = Unescape(unwrapped);
			return unescaped;
		}

		std::vector<unsigned char> Helper::Escape(const std::vector<unsigned char>& data)
		{
			std::vector<unsigned char> escaped;

			for (std::uint32_t i = 0; i < data.size(); i++)
			{
				if (data[i] == Definition::SOP || data[i] == Definition::EOP || data[i] == Definition::EscapeCharacter)
				{
					escaped.push_back(Definition::EscapeCharacter);
					escaped.push_back(data[i] & 0x0F);
					escaped.push_back(data[i] & 0xF0);
				}
				else
				{
					escaped.push_back(data[i]);
				}
			}

			return escaped;
		}

		std::vector<unsigned char> Helper::Unescape(const std::vector<unsigned char>& data)
		{
			std::vector<unsigned char> unescaped;

			for (std::uint32_t i = 0; i < data.size(); i++)
			{
				if (data[i] == Definition::EscapeCharacter)
				{
					std::uint8_t c = (data[i + 2]) | (data[i + 1]);
					unescaped.push_back(c);
					i += 2;
				}
				else
				{
					unescaped.push_back(data[i]);
				}
			}

			return unescaped;
		}
	}
}