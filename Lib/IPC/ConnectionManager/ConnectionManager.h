#pragma once

#include <Lib/Message/IMessage.h>
#include <Lib/Common/Patterns/DependencyInjection/DependencyInjection.h>

#include "../Messages/Request/Request.h"
#include "../Messages/Response/Response.h"

#include "../Subscribable/Subscribable.h"

#include <string>
#include <vector>
#include <cstdint>
#include <functional>

namespace Boggart
{
	namespace IPC
	{
		class ConnectionManager : public DependencyInjection, public Subscribable
		{
		private:
			struct Properties
			{
				Properties() :Id(), Attempts(0) {}
				Properties(std::string id) : Id(id), Attempts(0) {}

				std::string Id;
				std::uint8_t Attempts;
			};

			typedef std::function<void(std::string, IPCMessagePtr)> DataSendCallback;

		private:
			std::string m_MyId;
			DataSendCallback m_DataSendCallback;
			Properties m_HostConnection;
			std::vector<Properties> m_PeerConnections;

			Timer::IDevicePtr m_ProcessingTimer;

		public:
			ConnectionManager(std::string myId, DataSendCallback callback);
			~ConnectionManager();

			void Start();

			void OnIncomingMessage(IPCMessagePtr message);

		private:
			void OnRequest(RequestPtr request);
			void OnResponse(ResponsePtr response);

			std::int32_t Find(std::string id);

		private:
			void OnProcessingTimerExpired();
			void ProcessHostConnection();
			void ProcessPeerConnections();
		};
	}
}