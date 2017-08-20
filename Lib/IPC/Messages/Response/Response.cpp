#include "Response.h"

#include <Lib/Message/Utility/Utility.h>

namespace Boggart
{
	namespace IPC
	{
		std::string Response::TypeString()
		{
			return std::string("Response");
		}

		Response::Response():
			MessageBase(TypeString())
		{

		}

		Response::Response(const std::vector<unsigned char>& data):
			MessageBase(data)
		{

		}

		Response::~Response()
		{

		}

		std::vector<unsigned char> Response::OnEncode()
		{
			std::vector<unsigned char> data;

			return data;
		}

		bool Response::OnDecode(const std::vector<unsigned char>& data)
		{
			std::vector<unsigned char> _data = data;

			return true;
		}
	}
}