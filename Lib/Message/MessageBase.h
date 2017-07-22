#pragma once

#include "IMessage.h"

namespace Boggart
{
	namespace Message
	{
		class MessageBase : public IMessage
		{
		private:
			std::string m_Type;
			std::string m_Source;
			std::string m_Destination;
			std::uint8_t m_SequenceNumber;
			std::uint16_t m_PayloadLength;

			bool m_Valid;

		protected:
			MessageBase(std::string type);
			MessageBase(const std::vector<unsigned char>& data);

		public:
			virtual ~MessageBase() override;

			bool Valid() override;
			std::string Type() override;

			void Source(std::string source) override;
			void Destination(std::string destination) override;

			std::string Source() override;
			std::string Destination() override;

			void SequenceNumber(std::uint8_t sequenceNumber) override;
			std::uint8_t SequenceNumber() override;

			std::vector<unsigned char> Encode() override;

		private:
			bool Decode(const std::vector<unsigned char>& data) override;

		protected:
			virtual std::vector<unsigned char> OnEncode() = 0;
			virtual bool OnDecode(const std::vector<unsigned char>& data) = 0;
		};
	}
}