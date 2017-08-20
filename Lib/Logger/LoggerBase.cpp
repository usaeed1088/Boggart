#include "LoggerBase.h"

#include <Lib/Instantiator.h>

#include <sstream>
#include <cstdarg>

namespace Boggart
{
	namespace Logger
	{
		LoggerBase::LoggerBase():
			m_EnabledLevels(),
			m_EnabledCategories(),
			m_EnabledModules()
		{

		}

		LoggerBase::~LoggerBase()
		{

		}

		void LoggerBase::EnableLevel(Logger::Level level)
		{
			if (!LevelEnabled(level))
			{
				m_EnabledLevels.push_back(level);
			}
		}

		void LoggerBase::EnableCategory(std::string category)
		{
			if (!CategoryEnabled(category))
			{
				m_EnabledCategories.push_back(category);
			}
		}

		void LoggerBase::EnableModule(std::string module)
		{
			if (!ModuleEnabled(module))
			{
				m_EnabledModules.push_back(module);
			}
		}

		void LoggerBase::Log(Logger::Level level, std::string category, std::string module, const char* format, ...)
		{
			bool enabled = LevelEnabled(level) || CategoryEnabled(category) || ModuleEnabled(module);

			if (!enabled)
			{
				return;
			}

			// Format
			char buffer[1024] = {};

			va_list args;
			va_start(args, format);
			vsnprintf(buffer, sizeof(buffer), format, args);
			va_end(args);

			std::stringstream ss;

			PAL::API::ITimePtr timeAPI = PAL::Instantiator::APIFactory()->GetTimeInstance();
			std::string datetime = timeAPI->DateFormat() + std::string(" ") + timeAPI->TimeFormat();

			ss << "[" << timeAPI->HumanReadableTimestamp(datetime, true) << "] ";
			ss << "[" << level << "] ";
			ss << "[" << category << "] ";
			ss << "[" << module << "] ";
			ss << "" << std::string(buffer) << "";

			// Log
			_OnLog(ss.str());
		}

		bool LoggerBase::LevelEnabled(Level level)
		{
			bool enabled = false;

			for (std::int32_t i = 0; i < m_EnabledLevels.size(); i++)
			{
				if (m_EnabledLevels[i] == level)
				{
					enabled = true;
					break;
				}
			}

			return enabled;
		}

		bool LoggerBase::CategoryEnabled(std::string category)
		{
			bool enabled = false;

			for (std::int32_t i = 0; i < m_EnabledCategories.size(); i++)
			{
				if (m_EnabledCategories[i] == category)
				{
					enabled = true;
					break;
				}
			}

			return enabled;
		}

		bool LoggerBase::ModuleEnabled(std::string module)
		{
			bool enabled = false;

			for (std::int32_t i = 0; i < m_EnabledModules.size(); i++)
			{
				if (m_EnabledModules[i] == module)
				{
					enabled = true;
					break;
				}
			}

			return enabled;
		}
	}
}