#include "Arbitrator.h"

namespace Boggart
{
	namespace Transport
	{
		Arbitrator::Arbitrator(std::string id):
			TransportBase(std::string("Arbitrator"), id)
		{

		}

		Arbitrator::~Arbitrator()
		{

		}

		bool Arbitrator::OnOpen()
		{
			return false;
		}

		bool Arbitrator::OnClose()
		{
			return false;
		}

		bool Arbitrator::OnSend(const std::vector<unsigned char>& data)
		{
			return false;
		}

		std::vector<unsigned char> Arbitrator::OnReceive()
		{
			return std::vector<unsigned char>();
		}
	}
}