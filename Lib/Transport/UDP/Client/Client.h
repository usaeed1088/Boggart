#pragma once

#include "../../TransportBase.h"

#include <Lib/Object/Objects/ISocket.h>

#include <string>
#include <cstdint>

namespace Boggart
{
	namespace Transport
	{
		namespace UDP
		{
			class Client : public TransportBase
			{
			private:
				std::string m_ServerIP;
				std::int32_t m_ServerPort;

				PAL::Object::ISocketPtr m_Socket;

			public:
				Client(std::string myId, std::string serverIP, std::int32_t serverPort);
				~Client() override;

			private:
				bool OnOpen() override;

				bool OnClose() override;

				bool OnSend(const std::vector<unsigned char>& data) override;

				std::vector<unsigned char> OnReceive() override;

			private:
				void PokeServer();
			};
		}
	}
}