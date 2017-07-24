#include "TransportBase.h"

namespace Boggart
{
	namespace Transport
	{
		TransportBase::TransportBase(std::string moduleName):
			DependencyInjectionBase<TransportBase>(std::string("Transport"), moduleName)
		{

		}

		TransportBase::~TransportBase()
		{
			Close();
		}

		bool TransportBase::Open()
		{
			m_Diagnostics.Log(Logger::Level::Information, "Opening Transport");

			return OnOpen();
		}

		bool TransportBase::Close()
		{
			m_Diagnostics.Log(Logger::Level::Information, "Closing Transport");

			return OnClose();
		}

		bool TransportBase::Send(const std::vector<unsigned char>& data)
		{
			m_Diagnostics.Log(Logger::Level::Debug, "Sending Data. Size %d", data.size());

			return OnSend(data);
		}

		std::vector<unsigned char> TransportBase::Receive()
		{
			std::vector<unsigned char> data = OnReceive();

			if (!data.empty())
			{
				m_Diagnostics.Log(Logger::Level::Debug, "Received Data. Size %s", data.size());
			}

			return data;
		}
	}
}