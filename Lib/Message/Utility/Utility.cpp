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

		void Utility::EncodeVector(const std::vector<unsigned char>& vector, std::vector<unsigned char>& data)
		{
			std::uint8_t size = static_cast<std::uint8_t>(vector.size());

			data.push_back(size);
			data.insert(data.end(), vector.begin(), vector.end());
		}

		void Utility::DecodeVector(std::vector<unsigned char>& vector, std::vector<unsigned char>& data)
		{
			std::uint8_t size = data[0];

			vector.insert(vector.end(), data.begin() + 1, data.begin() + 1 + size);
			data.erase(data.begin(), data.begin() + 1 + size);
		}
	}
}