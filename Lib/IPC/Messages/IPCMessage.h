#pragma once
 
#include <Lib/Message/MessageBase.h>

#include <memory>

namespace Boggart
{
	namespace IPC
	{
		const std::string DestinationAny("Any");

		class IPCMessage : public Message::MessageBase
		{
		private:
			std::string m_Source;
			std::string m_Destination;
			std::uint8_t m_SequenceNumber;
			std::vector<unsigned char> m_ApplicationPayload;

			bool m_Valid;

		public:
			IPCMessage(std::string type);
			IPCMessage(const std::vector<unsigned char>& data);

			~IPCMessage() override;

			bool Valid();

			void Source(std::string source);
			void Destination(std::string destination);

			std::string Source();
			std::string Destination();

			void SequenceNumber(std::uint8_t sequenceNumber);
			std::uint8_t SequenceNumber();

			void ApplicationPayload(const std::vector<unsigned char>& payload);
			std::vector<unsigned char> ApplicationPayload();

		private:
			std::vector<unsigned char> OnEncode() override;
			bool OnDecode(const std::vector<unsigned char>& data) override;
		};

		typedef std::shared_ptr<IPCMessage> IPCMessagePtr;
	}
}