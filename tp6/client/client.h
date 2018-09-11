#pragma once
#include <iostream>
#include <cstdio>
#include <boost/asio.hpp>
#include <boost/chrono.hpp>
#include <boost/timer/timer.hpp>
#include <fstream>


#define HELLO_PORT_STR "80"
#define SERVER_IP "localhost"
#define MESSAGE_LENGTH 400

using namespace std;

class client
{
public:
	client();
	void startConnection(const char* host);
	void receiveMessage();
	void sendMessage();
	unsigned int messageLength;
	string messageReceived;
	~client();
	char message [MESSAGE_LENGTH];

private:
	boost::asio::io_service* IO_handler;
	boost::asio::ip::tcp::socket* socket_forClient;
	boost::asio::ip::tcp::resolver* client_resolver;
	boost::asio::ip::tcp::resolver::iterator endpoint;
};

