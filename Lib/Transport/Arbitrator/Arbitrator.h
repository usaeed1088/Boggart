#pragma once

#include "../TransportBase.h"

namespace Boggart
{
	namespace Transport
	{
		class Arbitrator : public TransportBase
		{
		public:
			Arbitrator(std::string id);
			~Arbitrator() override;

		private:
			bool OnOpen() override;

			bool OnClose() override;

			bool OnSend(const std::vector<unsigned char>& data) override;

			std::vector<unsigned char> OnReceive() override;
		};
	}
}