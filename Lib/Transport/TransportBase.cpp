#include "TransportBase.h"

namespace Boggart
{
	namespace Transport
	{
		TransportBase::TransportBase(std::string moduleName, std::string id):
			DependencyInjectionBase<TransportBase>(std::string("Transport"), moduleName),
			m_Id(id)
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

		std::string TransportBase::Id()
		{
			return m_Id;
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
				m_Diagnostics.Log(Logger::Level::Debug, "Received Data. Size %d", data.size());
			}

			return data;
		}
	}
}