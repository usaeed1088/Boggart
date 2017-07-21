#pragma once

#include "IMessage.h"

namespace Boggart
{
	namespace Message
	{
		class MessageBase : public IMessage
		{
		private:
			std::int16_t m_Type;
			std::int16_t m_PayloadLength;

			bool m_Valid;

		protected:
			MessageBase(std::int16_t type);
			MessageBase(const std::vector<unsigned char>& data);

		public:
			virtual ~MessageBase() override;

			bool Valid() override;
			std::int16_t Type() override;

			std::vector<unsigned char> Encode() override;

		private:
			bool Decode(const std::vector<unsigned char>& data) override;

		protected:
			virtual std::vector<unsigned char> OnEncode() = 0;
			virtual bool OnDecode(const std::vector<unsigned char>& data) = 0;
		};
	}
}