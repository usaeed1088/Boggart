#pragma once

#include "../../TransportBase.h"

#include <Lib/Object/Objects/ISocket.h>

#include <vector>
#include <queue>

namespace Boggart
{
	namespace Transport
	{
		namespace TCP
		{
			class Server : public TransportBase
			{
			private:
				std::int32_t m_Port;
				PAL::Object::ISocketPtr m_Socket;

			private:
				Timer::IDevicePtr m_ProcessingTimer;

			private:
				std::queue<std::vector<unsigned char>> m_IncomingQueue;
				std::vector<PAL::Object::ISocketPtr> m_Clients;

			public:
				Server(std::string myId, std::int32_t port);
				~Server() override;

			private:
				bool OnOpen() override;

				bool OnClose() override;

				bool OnSend(const std::vector<unsigned char>& data) override;

				std::vector<unsigned char> OnReceive() override;

			private:
				void OnProcessingTimerExpired();
				void ProcessAsynchronousIncoming();
				void ProcessIncomingConnections();
			};
		}
	}
}