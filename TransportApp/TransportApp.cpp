#include <Transporter.h>
#include <Physical/InProcess/InProcess.h>
#include <Physical/TCP/Server/Server.h>
#include <Physical/TCP/Client/Client.h>

#include <iostream>
#include <thread>
#include <chrono>
#include <string>

void Sender()
{
	Transport::InProcess physical;
	Transport::Transporter transporter(0x01, physical);

	while (true)
	{
		std::string string("a quick brown fox jumps over the lazy dog");
		Transport::DataType::Bytes data(string.begin(), string.end());

		transporter.Send(0x02, data, true);
		transporter.Receive(0x02);

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

void Receiver()
{
	Transport::InProcess physical;
	Transport::Transporter transporter(0x02, physical);

	while (true)
	{
		Transport::DataType::Bytes data = transporter.Receive(0x01);
		if (!data.empty())
		{
			std::cout << "Received from " << std::hex << 0x01 << " ";
			for (auto c : data) { std::cout << c; }
			std::cout << std::endl;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void Server()
{
	Transport::TCP::Server physical(Transport::SocketAddress("127.0.0.1", 9999));
	Transport::Transporter transporter(0x01, physical);

	while (true)
	{
		physical.Process();

		std::string string("a quick brown fox jumps over the lazy dog");
		Transport::DataType::Bytes data(string.begin(), string.end());

		transporter.Send(0x02, data, true);
		transporter.Receive(0x02);

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void Client()
{
	Transport::TCP::Client client(Transport::SocketAddress("127.0.0.1", 9999));
	Transport::Transporter transporter(0x02, client);

	while (true)
	{
		Transport::DataType::Bytes data = transporter.Receive(0x01);
		if (!data.empty())
		{
			std::cout << "Received from " << std::hex << 0x01 << " ";
			for (auto c : data) { std::cout << c; }
			std::cout << std::endl;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

int main(int argc, char* argv[])
{
	std::vector<std::thread> threads;

	threads.push_back(std::thread(Server));
	threads.push_back(std::thread(Client));
	threads.push_back(std::thread(Sender));
	threads.push_back(std::thread(Receiver));

	for (int i = 0; i < threads.size(); i++)
	{
		threads[i].join();
	}

	return 0;
}