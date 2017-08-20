#include "Utility.h"

#include <cstdint>

namespace Boggart
{
	namespace Message
	{
		Utility::Utility()
		{

		}

		void Utility::EncodeString(const std::string& string, std::vector<unsigned char>& data)
		{
			std::uint8_t size = static_cast<std::uint8_t>(string.length());

			data.push_back(size);
			data.insert(data.end(), string.begin(), string.end());
		}

		void Utility::DecodeString(std::string& string, std::vector<unsigned char>& data)
		{
			std::uint8_t size = data[0];

			string.insert(string.end(), data.begin() + 1, data.begin() + 1 + size);
			data.erase(data.begin(), data.begin() + 1 + size);
		}
	}
}