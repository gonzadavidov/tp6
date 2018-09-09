#include "Server.h"

server::
server()
{
	IO_handler = new boost::asio::io_service();
	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(), HELLO_PORT);

	socket_forServer = new boost::asio::ip::tcp::socket(*IO_handler);
	server_acceptor = new boost::asio::ip::tcp::acceptor(*IO_handler, ep);
	contenido = "";
}

void server::
startConnection()
{

	//Uncomment if non-blocking mode is desired
	//
	//When non-blocking mode is chosen accept operation
	//will fail with boost::asio::error::would_block
	//if there's no client inmediatelly connected when accept operation is performed.
	//Must comment blocking mode.
	//
	server_acceptor->non_blocking(true);
	boost::system::error_code error;
	do
	{
		server_acceptor->accept(*socket_forServer, error);
	} while ((error.value() == WSAEWOULDBLOCK));
	if (error)
	{
		std::cout << "Error while trying to listen to " << HELLO_PORT << "Port " << error.message() << std::endl;
	}

	//server_acceptor->accept(*socket_forServer);
	socket_forServer->non_blocking(true);
}

void server::
sendMessage()
{
	char buf[512] = "Hello from server.";

	size_t len;
	boost::system::error_code error;

	do
	{
		len = socket_forServer->write_some(boost::asio::buffer(buf, strlen(buf)), error);
	} while ((error.value() == WSAEWOULDBLOCK));
	if (error)
		std::cout << "Error while trying to connect to server " << error.message() << std::endl;
}



void server::
receiveMessage()
{
	boost::system::error_code error;
	lenOfMessage = 0;
	std::cout << "Receiving Message" << std::endl;
	boost::timer::cpu_timer t;
	t.start();
	boost::timer::cpu_times pastTime = t.elapsed();
	double elapsedSeconds = 0.0;

	do
	{
		lenOfMessage = socket_forServer->read_some(boost::asio::buffer(receivedMessage), error);

		boost::timer::cpu_times currentTime = t.elapsed();

		if ((currentTime.wall - pastTime.wall) > 1e9)
		{
			elapsedSeconds += (currentTime.wall - pastTime.wall) / 1e9;
			pastTime = currentTime;
			std::cout << "Pasaron " << (int)floor(elapsedSeconds) << " segundos." << std::endl;
		}

		if (!error)
			receivedMessage[lenOfMessage] = '\0';

	} while (error.value() == WSAEWOULDBLOCK);

	if (!error)
		std::cout << std::endl << "Server sais: " << receivedMessage << std::endl;
	else
		std::cout << "Error while trying to connect to server " << error.message() << std::endl;
}


bool server::
CRLF()
{
	bool found = false;
	int CRLFCount = 0;
	for (int count = 0; count < MESSAGE_LENGTH; count++)
	{
		if (CRLFCount = 0 && receivedMessage[count] != '/r')
		{
			firstLine[count] = receivedMessage[count];
		}
		else if (CRLFCount = 1 && receivedMessage[count] != '/r')
		{
			secondLine[count] = receivedMessage[count];
		}
		if (receivedMessage[count] == '/r')   //ingresa al encontrar inicio del path
		{
			if (receivedMessage[count + 1] == '/n')
			{
					CRLFCount++;
					if (CRLFCount == 3)
					{
						found = true;
						count = MESSAGE_LENGTH;
					}
			}
			else
			{
				if (CRLFCount = 0)
				{
					firstLine[count] = receivedMessage[count];
				}
				else if (CRLFCount = 1)
				{
					secondLine[count] = receivedMessage[count];
				}
			}
		}
	}
	return found;
}

bool server::
first_line()
{
	char correct = false;
	char * lineOne;
	const char * firstWord = "GET";
	const char * secondWord = "HTTP/1.1";
	lineOne = strtok(firstLine, " ");
	if (!strcmp(lineOne, firstWord))
	{
		strtok(NULL, " ");				//salteo el path
		lineOne = strtok(NULL, " ");	//busco HTTP/1.1
		if (!strcmp(lineOne, secondWord))
		{
			correct = true;
		}
	}
	return correct;
}

bool server::
second_line()
{
	char correct = false;
	char * lineTwo;
	const char * firstWord = "Host:127.0.0.1";
	lineTwo = strtok(secondLine, " ");
	if (!strcmp(lineTwo, firstWord))
	{
		correct = true;
	}
	return correct;
}

bool server::
pathCopy()
{
	for (int count = 0; count < MESSAGE_LENGTH; count++)   
	{
		if (receivedMessage[count] == '/')   //ingresa al encontrar inicio del path
		{
			int i = 0;   
			while (receivedMessage[count] != ' ' && (count < MESSAGE_LENGTH))   //si encuentra espacio, termino el path
			{

				path[i] = receivedMessage[count];   
				++i;
				++count;   //para que pase al elemento siguiente

			}
			count = MESSAGE_LENGTH; //para que salga del for
		}
	}
}

bool server::
ispath()
{
	bool result = false;
	for (int count = 0; count <= PATHS && result != true; count++)
	{
		result = strcmp(path, server_paths[count]);
		if (result == 0)
		{
			result = true;
		}
	}
	return result;
}

bool server::
fillContent(FILE* file)
{
	unsigned int i = 0;
	char c;
	do
	{
		contenido =contenido + (char) getc(file);
		i++;
	} while (c != EOF);
}
server::
~server()
{
	server_acceptor->close();
	socket_forServer->close();
	delete server_acceptor;
	delete socket_forServer;
	delete IO_handler;
}
