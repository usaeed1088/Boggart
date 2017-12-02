#pragma once

#include "../../MessageBase.h"

namespace Boggart
{
	namespace Message
	{
		namespace Type
		{
			class Generic : public MessageBase
			{
			private:
				std::vector<unsigned char> m_Payload;

			public:
				Generic(std::string type, std::vector<unsigned char> payload);
				Generic(const std::vector<unsigned char>& data);

				std::vector<unsigned char> Payload();

			private:
				std::vector<unsigned char> OnEncode() override;
				bool OnDecode(const std::vector<unsigned char>& data) override;
			};
		}
	}
}