#include "Boggart.h"

#include <Lib/Instantiator.h>

namespace Boggart
{
	std::vector<Boggart*> Boggart::s_Boggarts;

	Boggart::Boggart(std::string name):
		Subscribable(name),
		m_IPC(nullptr),
		m_Logger(nullptr),
		m_TimerManager(nullptr),
		m_Transport(nullptr),
		m_Diagnostics(name, std::string("Boggart")),
		m_Name(name)
	{
		s_Boggarts.push_back(this);
		LoadDefaultDependencies();
	}

	Boggart::~Boggart()
	{
		for (std::size_t i=0; i<s_Boggarts.size(); i++)
		{
			if (s_Boggarts[i] == this)
			{
				s_Boggarts.erase(s_Boggarts.begin() + i);
				break;
			}
		}
	}

	void Boggart::LoadDefaultDependencies()
	{
		InjectIPC(std::shared_ptr<IPC::IPCBase>(new IPC::Asynchronous(m_Name)));
		InjectLogger(std::shared_ptr<Logger::LoggerBase>(new Logger::Console()));
		InjectTimerManager(std::shared_ptr<Timer::ManagerBase>(new Timer::SoftTimerManager()));
		InjectTransport(std::shared_ptr<Transport::TransportBase>(new Transport::InProcess(m_Name)));

		Logger()->EnableLevel(Logger::Level::Information);
		Logger()->EnableLevel(Logger::Level::Error);
		Logger()->EnableLevel(Logger::Level::FatalError);

		m_Diagnostics.Log(Logger::Level::Information, "%s Boggart Loaded Default Dependencies", m_Name.c_str());
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

	bool Boggart::SubscribeMessage(std::string type, IPC::Callback_t callback)
	{
		return m_IPC->SubscribeMessage(shared_from_this(), type, callback);
	}

	bool Boggart::SubscribeSource(std::string type, IPC::Callback_t callback)
	{
		return m_IPC->SubscribeSource(shared_from_this(), type, callback);
	}

	bool Boggart::Send(std::string destination, Message::IMessagePtr message)
	{
		return m_IPC->Send(destination, message);
	}

	void Boggart::Start()
	{
		// Setup the Boggarts
		for (Boggart* boggart : s_Boggarts)
		{
			boggart->InjectDependencies();
			boggart->StartComponents();
		}

		// Start processing
		while (true)
		{
			for (Boggart* boggart : s_Boggarts)
			{
				boggart->Process();
			}
			PAL::Instantiator::APIFactory()->GetTranceInstance()->Sleep(10);
		}
	}

	Logger::ILoggerPtr Boggart::Logger()
	{
		return m_Logger;
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
