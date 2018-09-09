#pragma once

#include <iostream>
#include <cstdio>
#include <cstring>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/chrono.hpp>
#include <boost/timer/timer.hpp>


#define HELLO_PORT "80"
#define MESSAGE_LENGTH 600
#define PATH_LENGTH 200
#define PATHS 4

class server
{
public:
	server();
	void startConnection();
	void sendMessage();
	void receiveMessage();
	bool pathCopy();							//guarda el path en el arreglo
	bool CRLF();
	bool ispath();
	~server();
	char receivedMessage[MESSAGE_LENGTH];		//Mensaje recibido

private:
	boost::asio::io_service*  IO_handler;
	boost::asio::ip::tcp::socket* socket_forServer;
	boost::asio::ip::tcp::acceptor* server_acceptor;
	unsigned int lenOfMessage;			//Largo del mensaje recibido
	char path[PATH_LENGTH];				//path recibido
	const char * server_paths[PATHS] = { "/example_path1/folder","/example_path2/folder", "/example_path3/folder","/example_path4/folder" };
};