#include <Transporter.h>
#include <Physical/InProcess/InProcess.h>

#include <iostream>
#include <thread>
#include <chrono>
#include <string>

void Sender()
{
	Transport::InProcess physical;
	Transport::Transporter transporter(0x01, physical);

	Transport::InProcess::Subscribe(&physical);

	while (true)
	{
		std::string string("a quick brown fox jumps over the lazy dog");
		Transport::Type::Bytes data(string.begin(), string.end());

		transporter.Send(0x02, data, true);
		transporter.Receive(0x02);

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void Receiver()
{
	Transport::InProcess physical;
	Transport::Transporter transporter(0x02, physical);

	Transport::InProcess::Subscribe(&physical);

	while (true)
	{
		Transport::Type::Bytes data = transporter.Receive(0x01);
		if (!data.empty())
		{
			std::cout << "Received from " << std::hex << 0x01 << " ";
			for (auto c : data) { std::cout << c; }
			std::cout << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}
}

int main(int argc, char* argv[])
{
	std::thread sender(Sender);
	std::thread receiver(Receiver);

	sender.join();
	receiver.join();

	return 0;
}