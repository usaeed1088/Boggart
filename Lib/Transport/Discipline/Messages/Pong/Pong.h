#pragma once

#include <Message/MessageBase.h>

namespace Boggart
{
	namespace Transport
	{
		class Pong : public Message::MessageBase
		{
		private:
			static const std::string s_Type;

		public:
			static std::string TypeString();

		public:
			Pong();
			Pong(const std::vector<unsigned char> data);
			~Pong() override;

		private:
			std::vector<unsigned char> OnEncode() override;
			bool OnDecode(const std::vector<unsigned char>& data) override;
		};

		typedef std::shared_ptr<Pong> PongPtr;
	}
}