#pragma once

#include <vector>
#include <memory>
#include <string>

namespace Boggart
{
	class DependencyInjection;

	namespace Transport
	{
		class ITransport : std::enable_shared_from_this<ITransport>
		{
		public:
			virtual ~ITransport() {}

			virtual bool Open() = 0;

			virtual bool Close() = 0;

			virtual std::string Id() = 0;

			virtual bool Send(const std::vector<unsigned char>& data) = 0;

			virtual std::vector<unsigned char> Receive() = 0;
		};

		typedef std::shared_ptr<ITransport> ITransportPtr;
	}
}