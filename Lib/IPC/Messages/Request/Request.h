#pragma once

#include "../MessageBase.h"

namespace Boggart
{
	namespace IPC
	{
		class Request : public MessageBase
		{
		private:
			std::string m_SubType;

		public:
			static std::string TypeString();

		public:
			Request(std::string subType);
			Request(const std::vector<unsigned char>& data);

			~Request() override;

			std::string SubType();

		private:
			std::vector<unsigned char> _OnEncode() override;
			bool _OnDecode(const std::vector<unsigned char>& data) override;
		};
	}
}