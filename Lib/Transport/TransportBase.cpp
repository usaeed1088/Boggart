#include "TransportBase.h"

#include "Helper/Helper.h"

namespace Boggart
{
	namespace Transport
	{
		TransportBase::TransportBase(std::string moduleName, std::string id):
			DependencyInjection(std::string("Transport"), moduleName),
			m_Id(id),
			m_IncomingBuffer(),
			m_ProcessingTimer(nullptr)
		{

		}

		TransportBase::~TransportBase()
		{
			Close();

			m_TimerManager->Stop(m_ProcessingTimer);
			m_TimerManager->Destroy(m_ProcessingTimer);
		}

		bool TransportBase::Open()
		{
			m_Diagnostics->Log(Logger::Level::Information, "Opening Transport");

			m_ProcessingTimer = m_TimerManager->Create
			(
				Timer::Span_t(20),
				Timer::Type_t::Periodic,
				std::bind(&TransportBase::OnProcessingTimerExpired, this)
			);

			m_TimerManager->Start(m_ProcessingTimer);

			return OnOpen();
		}

		bool TransportBase::Close()
		{
			m_Diagnostics->Log(Logger::Level::Information, "Closing Transport");

			return OnClose();
		}

		std::string TransportBase::Id()
		{
			return m_Id;
		}

		bool TransportBase::Send(const std::vector<unsigned char>& data)
		{
			m_Diagnostics->Log(Logger::Level::Debug, "Sending Data. Size %d", data.size());

			std::vector<unsigned char> wrapped = Helper::Wrap(data);

			return OnSend(wrapped);
		}

		std::vector<unsigned char> TransportBase::Receive()
		{
			std::vector<unsigned char> data = m_IncomingBuffer.GetNextMessage();

			if (data.empty())
			{
				return std::vector<unsigned char>();
			}

			std::vector<unsigned char> unwrapped = Helper::Unwrap(data);

			if (!unwrapped.empty())
			{
				m_Diagnostics->Log(Logger::Level::Debug, "Received Data. Size %d", unwrapped.size());
			}

			return unwrapped;
		}

		void TransportBase::OnProcessingTimerExpired()
		{
			ProcessIncomingData();
		}

		void TransportBase::ProcessIncomingData()
		{
			std::vector<unsigned char> data = OnReceive();

			while (!data.empty())
			{
				m_IncomingBuffer.ProcessIncomingData(data);
				data = OnReceive();
			}
		}
	}
}