#pragma once

#include <vector>
#include <string>

namespace Boggart
{
	namespace Message
	{
		class Utility
		{
		private:
			Utility();

		public:
			static void EncodeString(const std::string& string, std::vector<unsigned char>& data);
			static void DecodeString(std::string& string, std::vector<unsigned char>& data);
		};
	}
}