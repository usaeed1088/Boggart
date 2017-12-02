#include "InProcess.h"

namespace Boggart
{
	namespace Transport
	{
		std::vector<InProcess*> InProcess::s_Subscribers;

		InProcess::InProcess(std::string id):
			TransportBase(std::string("InProcess"), id)
		{
			s_Subscribers.push_back(this);
		}

		InProcess::~InProcess()
		{
			Close();
		}

		bool InProcess::OnOpen()
		{
			return true;
		}

		bool InProcess::OnClose()
		{
			for (std::vector<InProcess*>::iterator it = s_Subscribers.begin(); it != s_Subscribers.end(); ++it)
			{
				if ((*it) == this)
				{
					s_Subscribers.erase(it);
					break;
				}
			}

			return true;
		}

		bool InProcess::OnSend(const std::vector<unsigned char>& data)
		{
			// Push to data queue of all subscribers but 'this'
			for (InProcess* process : s_Subscribers)
			{
				if (process != this)
				{
					process->Push(data);
				}
			}
			return true;
		}

		std::vector<unsigned char> InProcess::OnReceive()
		{
			std::lock_guard<std::mutex> lock(m_DataQueueLock);
			if (m_DataQueue.empty())
			{
				return std::vector<unsigned char>();
			}

			std::vector<unsigned char> data = m_DataQueue.front();
			m_DataQueue.pop();

			return data;
		}

		void InProcess::Push(const std::vector<unsigned char>& data)
		{
			std::lock_guard<std::mutex> lock(m_DataQueueLock);
			m_DataQueue.push(data);
		}
	}
}