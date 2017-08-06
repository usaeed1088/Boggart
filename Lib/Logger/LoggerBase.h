#pragma once

#include "ILogger.h"

#include <vector>

namespace Boggart
{
	namespace Logger
	{
		class LoggerBase : public ILogger
		{
		private:
			std::vector<Level> m_EnabledLevels;
			std::vector<std::string> m_EnabledCategories;
			std::vector<std::string> m_EnabledModules;

		public:
			LoggerBase();
			virtual ~LoggerBase() override;

			void EnableLevel(Logger::Level level) override;

			void EnableCategory(std::string category) override;

			void EnableModule(std::string module) override;

			void Log(Logger::Level level, std::string category, std::string module, const char* format, ...);

		protected:
			virtual void _OnLog(std::string data) = 0;

		private:
			bool LevelEnabled(Level level);
			bool CategoryEnabled(std::string category);
			bool ModuleEnabled(std::string module);
		};
	}
}