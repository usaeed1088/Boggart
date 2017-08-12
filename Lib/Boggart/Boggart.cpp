#include "Boggart.h"

#include <Lib/Instantiator.h>

namespace Boggart
{
	Boggart::Boggart(std::string name):
		m_IPC(nullptr),
		m_Logger(nullptr),
		m_TimerManager(nullptr),
		m_Transport(nullptr),
		m_Diagnostics(name, std::string("Boggart"))
	{

	}

	Boggart::~Boggart()
	{

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

	void Boggart::InjectBoggart(std::shared_ptr<Boggart> boggart)
	{
		m_Boggarts.push_back(boggart);
	}

	void Boggart::Start()
	{
		InjectDependencies();
		
		if (!StartComponents())
		{
			m_Diagnostics.Log(Logger::Level::FatalError, "Could Not Start Components. Terminating...");
			return;
		}

		for (std::shared_ptr<Boggart> boggart : m_Boggarts)
		{
			boggart->InjectDependencies();
			boggart->StartComponents();
		}

		while (true)
		{
			Process();
			ProcessBoggarts();
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

	void Boggart::ProcessBoggarts()
	{
		for (std::shared_ptr<Boggart> boggart : m_Boggarts)
		{
			boggart->Process();
		}
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