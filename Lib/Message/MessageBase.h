#pragma once

#include "IMessage.h"

namespace Boggart
{
	namespace Message
	{
		class MessageBase : public IMessage
		{
		protected:
			bool m_Valid;

		private:
			std::string m_Type;

		protected:
			MessageBase(std::string type);
			MessageBase(const std::vector<unsigned char>& data);

		public:
			virtual ~MessageBase() override;

			bool Valid() override;
			std::string Type() override;

			std::vector<unsigned char> Encode() override;
			bool Decode(const std::vector<unsigned char>& data) override;

		protected:
			virtual std::vector<unsigned char> OnEncode() = 0;
			virtual bool OnDecode(const std::vector<unsigned char>& data) = 0;
		};
	}
}