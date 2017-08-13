#include "Boggart.h"

#include <Lib/Instantiator.h>

namespace Boggart
{
	std::vector<Boggart*> Boggart::s_Boggarts;

	Boggart::Boggart(std::string name):
		m_IPC(nullptr),
		m_Logger(nullptr),
		m_TimerManager(nullptr),
		m_Transport(nullptr),
		m_Diagnostics(name, std::string("Boggart"))
	{
		s_Boggarts.push_back(this);
	}

	Boggart::~Boggart()
	{
		for (int i=0; i<s_Boggarts.size(); i++)
		{
			if (s_Boggarts[i] == this)
			{
				s_Boggarts.erase(s_Boggarts.begin() + i);
				break;
			}
		}
	}

	void Boggart::InjectIPC(std::shared_ptr<IPC::IPCBase> ipc)
	{
		m_IPC = ipc;
	}

	void Boggart::InjectLogger(std::shared_ptr<Logger::LoggerBase> logger)
	{
		m_Logger = logger;
		m_Diagnostics.InjectLogger(logger);
	}

	void Boggart::InjectTimerManager(std::shared_ptr<Timer::ManagerBase> timerManager)
	{
		m_TimerManager = timerManager;
	}

	void Boggart::InjectTransport(std::shared_ptr<Transport::TransportBase> transport)
	{
		m_Transport = transport;
	}

	void Boggart::Start()
	{
		for (Boggart* boggart : s_Boggarts)
		{
			boggart->InjectDependencies();
			boggart->StartComponents();
		}

		while (true)
		{
			for (Boggart* boggart : s_Boggarts)
			{
				boggart->Process();
			}
			PAL::Instantiator::APIFactory()->GetTranceInstance()->Sleep(10);
		}
	}

	IPC::IIPCPtr Boggart::IPC()
	{
		return m_IPC;
	}

	Logger::ILoggerPtr Boggart::Logger()
	{
		return m_Logger;
	}

	Timer::IManagerPtr Boggart::TimerManager()
	{
		return m_TimerManager;
	}

	void Boggart::Process()
	{
		m_TimerManager->Process();
	}

	void Boggart::InjectDependencies()
	{
		m_Diagnostics.Log(Logger::Level::Information, "Injecting Dependencies");

		// Timer
		if (m_TimerManager)
		{
			m_TimerManager->InjectDependency(m_Logger);
		}

		// Transport
		if (m_Transport)
		{
			m_Transport->InjectDependency(m_Logger);
			m_Transport->InjectDependency(m_TimerManager);
		}

		// IPC
		if (m_IPC)
		{
			m_IPC->InjectDependency(m_Logger);
			m_IPC->InjectDependency(m_TimerManager);
			m_IPC->InjectDependency(m_Transport);
		}
	}

	bool Boggart::StartComponents()
	{
		m_Diagnostics.Log(Logger::Level::Information, "Starting Components");

		if (m_Transport && !m_Transport->Open())
		{
			return false;
		}

		if (m_IPC && !m_IPC->Start())
		{
			return false;
		}

		return true;
	}
}