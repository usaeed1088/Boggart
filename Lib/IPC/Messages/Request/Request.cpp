#include "Request.h"

#include <Lib/Message/Utility/Utility.h>

namespace Boggart
{
	namespace IPC
	{
		std::string Request::TypeString()
		{
			return std::string("Request");
		}

		Request::Request():
			MessageBase(TypeString())
		{

		}

		Request::Request(const std::vector<unsigned char>& data):
			MessageBase(data)
		{

		}

		Request::~Request()
		{

		}

		std::vector<unsigned char> Request::OnEncode()
		{
			std::vector<unsigned char> data;

			return data;
		}

		bool Request::OnDecode(const std::vector<unsigned char>& data)
		{
			std::vector<unsigned char> _data = data;

			return true;
		}
	}
}