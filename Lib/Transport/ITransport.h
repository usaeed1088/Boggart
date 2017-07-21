#pragma once

#include <vector>

namespace Boggart
{
	namespace Transport
	{
		class ITransport
		{
		public:
			virtual ~ITransport() {}

			virtual bool Send(const std::vector<unsigned char>& data) = 0;

			virtual std::vector<unsigned char> Receive() = 0;

		protected:
			virtual bool Open() = 0;

			virtual bool Close() = 0;
		};
	}
}