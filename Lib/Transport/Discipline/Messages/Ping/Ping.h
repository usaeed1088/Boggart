#pragma once

#include <Message/MessageBase.h>

namespace Boggart
{
	namespace Transport
	{
		class Ping : public Message::MessageBase
		{
		private:
			static const std::string s_Type;

		public:
			static std::string TypeString();

		public:
			Ping();
			Ping(const std::vector<unsigned char> data);
			~Ping() override;

		private:
			std::vector<unsigned char> OnEncode() override;
			bool OnDecode(const std::vector<unsigned char>& data) override;
		};

		typedef std::shared_ptr<Ping> PingPtr;
	}
}