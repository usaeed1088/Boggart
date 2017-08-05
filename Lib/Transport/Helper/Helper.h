#pragma once

#include <vector>

namespace Boggart
{
	namespace Transport
	{
		class Helper
		{
		private:
			Helper();

		public:
			static std::vector<unsigned char> Wrap(const std::vector<unsigned char>& data);
			static std::vector<unsigned char> Unwrap(const std::vector<unsigned char>& data);

		private:
			static std::vector<unsigned char> Escape(const std::vector<unsigned char>& data);
			static std::vector<unsigned char> Unescape(const std::vector<unsigned char>& data);
		};
	}
}