#pragma once

#include <string>
#include <ostream>
#include <cstdint>

namespace Boggart
{
	namespace Logger
	{
		class Level
		{
		public:
			typedef int8_t Value;

		private:
			Value m_Value;

		public:
			Level(Value value);

		public:
			static const Value Debug;
			static const Value Information;
			static const Value Warning;
			static const Value Error;
			static const Value FatalError;

			void operator=(Level& level);
			bool operator==(Level& level);
			friend std::ostream& operator<<(std::ostream& os, Level level);
		};
	}
}