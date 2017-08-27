#pragma once

#include <Message/MessageBase.h>

#include "../Subtypes.h"

namespace Boggart
{
	namespace IPC
	{
		class Response : public Message::MessageBase
		{
		private:

		public:
			static std::string TypeString();

		public:
			Response();
			Response(const std::vector<unsigned char>& data);
			~Response() override;

		private:
			std::vector<unsigned char> OnEncode() override;
			bool OnDecode(const std::vector<unsigned char>& data) override;
		};

		typedef std::shared_ptr<Response> ResponsePtr;
	}
}