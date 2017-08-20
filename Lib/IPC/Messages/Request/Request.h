#pragma once

#include <Message/MessageBase.h>

#include "../Subtypes.h"

namespace Boggart
{
	namespace IPC
	{
		class Request : public Message::MessageBase
		{
		public:
			static std::string TypeString();

		public:
			Request();
			Request(const std::vector<unsigned char>& data);

			~Request() override;

		private:
			std::vector<unsigned char> OnEncode() override;
			bool OnDecode(const std::vector<unsigned char>& data) override;
		};

		typedef std::shared_ptr<Request> RequestPtr;
	}
}