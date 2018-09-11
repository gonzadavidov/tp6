#pragma once

#include <iostream>
#include <cstdio>
#include <cstring>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/chrono.hpp>
#include <boost/timer/timer.hpp>
#include <stdlib.h>


#define END "\u000d\u000a"
#define CRT_SECURE_NO_WARNINGS
#define PORT 80
#define MESSAGE_LENGTH 600
#define PATH_LENGTH 150
#define LINE_LENGTH 200
#define PATHS 4
#define SENT_MESSAGE_LENGTH 600
#define LOCALHOST (127.0.0.1)

class server
{
public:
	server();
	void startConnection();
	void sendMessage();
	bool receiveMessage();							
	bool isPath();
	bool message(bool);
	bool messageCheck();
	~server();
	char receivedMessage[MESSAGE_LENGTH];		//Mensaje recibido
	char sentMessage[SENT_MESSAGE_LENGTH];

private:
	boost::asio::io_service*  IO_handler;
	boost::asio::ip::tcp::socket* socket_forServer;
	boost::asio::ip::tcp::acceptor* server_acceptor;
	unsigned int lenOfMessage;			//Largo del mensaje recibido
	char path[PATH_LENGTH];				//path recibido
	char firstLine[LINE_LENGTH];
	char secondLine[LINE_LENGTH];		
	bool CRLF();						//busca que esten los 3 CRLF
	bool first_line();					//se fija que la primera linea sea correcta
	bool second_line();					//se fija que la segunda linea sea correcta
	void pathCopy();					//guarda el path en el arreglo
	void fillContent(FILE* file);
	int messageLength;
	const char * server_paths[PATHS] = { "/example_paths1/file","/example_paths2/file","/example_paths3/file","/example_paths4/file" };
	
	std::string contenido;
};