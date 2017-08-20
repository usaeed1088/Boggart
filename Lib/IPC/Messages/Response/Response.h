#pragma once

#include "../MessageBase.h"

#include "../Subtypes.h"

namespace Boggart
{
	namespace IPC
	{
		class Response : public MessageBase
		{
		private:
			std::string m_SubType;

		public:
			static std::string TypeString();

		public:
			Response(std::string subType);
			Response(const std::vector<unsigned char>& data);
			~Response() override;

			std::string SubType();

		private:
			std::vector<unsigned char> _OnEncode() override;
			bool _OnDecode(const std::vector<unsigned char>& data) override;
		};

		typedef std::shared_ptr<Response> ResponsePtr;
	}
}