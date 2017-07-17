#pragma once

#include <ostream>
#include <cstdint>

namespace Boggart
{
	namespace Logger
	{
		class Level
		{
		public:
			typedef std::int8_t Value_t;

		private:
			Value_t m_Value;

		public:
			Level(Value_t value);

			static const Value_t Debug;
			static const Value_t Information;
			static const Value_t Warning;
			static const Value_t Error;
			static const Value_t FatalError;

			void operator=(Level& level);
			bool operator==(Level& level);
			friend std::ostream& operator<<(std::ostream& os, Level level);
		};
	}
}