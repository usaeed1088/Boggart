#pragma once

#include "../../TransportBase.h"

#include <Lib/Object/Objects/ISocket.h>

#include <vector>
#include <queue>

namespace Boggart
{
	namespace Transport
	{
		namespace UDP
		{
			class Server : public TransportBase
			{
			private:
				struct Peer
				{
					Peer(std::string ip, std::int32_t port) :
						IP(ip), Port(port) {}
					std::string IP;
					std::int32_t Port;
				};

			private:
				std::int32_t m_Port;
				PAL::Object::ISocketPtr m_Socket;

			private:
				Timer::IDevicePtr m_ProcessingTimer;

			private:
				std::queue<std::vector<unsigned char>> m_IncomingQueue;
				std::vector<Peer> m_Peers;

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

				std::int32_t FindIndexOf(std::string source, std::int32_t port);
				bool IsPokeMessage(const std::vector<unsigned char>& data);
				void AddToListIfNotPresent(std::string source, std::int32_t port);
			};
		}
	}
}