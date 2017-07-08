#include "Level.h"

namespace Boggart
{
	namespace Logger
	{
		const Level::Value Level::Debug			(10);
		const Level::Value Level::Information	(20);
		const Level::Value Level::Warning		(30);
		const Level::Value Level::Error			(40);
		const Level::Value Level::FatalError	(50);

		Level::Level(Value value):
			m_Value(value)
		{

		}

		void Level::operator=(Level& level)
		{
			m_Value = level.m_Value;
		}

		bool Level::operator==(Level& level)
		{
			return m_Value == level.m_Value;
		}

		std::ostream& operator<<(std::ostream& os, Level level)
		{
			switch (level.m_Value)
			{
			case Level::Debug:
				os << std::string("Debug");
				break;
			case Level::Error:
				os << std::string("Error");
				break;
			case Level::FatalError:
				os << std::string("Fatal Error");
				break;
			case Level::Information:
				os << std::string("Information");
				break;
			case Level::Warning:
				os << std::string("Warning");
				break;
			default:
				os << std::string("Unknown");
				break;
			}

			return os;
		}
	}
}