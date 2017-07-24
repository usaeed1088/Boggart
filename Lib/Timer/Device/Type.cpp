#include "Type.h"

#include <string>

namespace Boggart
{
	namespace Timer
	{
		_Type::_Type(Value_t value):
			m_Value(value)
		{

		}

		void _Type::operator=(_Type& type)
		{
			m_Value = type.m_Value;
		}

		bool _Type::operator==(_Type& type)
		{
			return m_Value == type.m_Value;
		}

		_Type::operator int()
		{
			return m_Value;
		}

		std::ostream& operator<<(std::ostream& os, _Type& type)
		{
			switch (type.m_Value)
			{
			case _Type::OneShot:
				os << std::string("One Shot");
				break;
			case _Type::Periodic:
				os << std::string("Periodic");
				break;
			default:
				os << std::string("Unknown");
				break;
			}

			return os;
		}
	}
}