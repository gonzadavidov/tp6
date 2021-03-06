#include "client.h"

client::
client()
{
	IO_handler = new boost::asio::io_service();
	socket_forClient = new boost::asio::ip::tcp::socket(*IO_handler);
	client_resolver = new boost::asio::ip::tcp::resolver(*IO_handler);
}

client::
~client()
{
	socket_forClient->close();
	delete client_resolver;
	delete socket_forClient;
	delete IO_handler;
}

void client::
startConnection(const char* host)
{
	endpoint = client_resolver->resolve(boost::asio::ip::tcp::resolver::query(host, HELLO_PORT_STR));
	boost::system::error_code error;
	boost::asio::connect(*socket_forClient, endpoint, error);
	if (error)
	{
		cout << "Error connecting to " << host << " Error Message: " << error.message() << endl;
		if (error.value() == boost::asio::error::connection_refused)
			cout << "Host " << host << " is not listening on the other side" << endl;
	}
	socket_forClient->non_blocking(true);
}

void client::
receiveMessage()
{
	boost::system::error_code error;
	string buf;
	cout << "Receiving Message" << std::endl;
	boost::timer::cpu_timer t;
	t.start();
	boost::timer::cpu_times pastTime = t.elapsed();
	double elapsedSeconds = 0.0;

	do
	{
		messageLength = socket_forClient->read_some(boost::asio::buffer(buf), error);
		boost::timer::cpu_times currentTime = t.elapsed();

		if ((currentTime.wall - pastTime.wall) > 1e9)
		{
			elapsedSeconds += (currentTime.wall - pastTime.wall) / 1e9;
			pastTime = currentTime;
			cout << "Pasaron " << (int)floor(elapsedSeconds) << " segundos." << endl;
		}

		if (!error)
			buf[messageLength] = '\0';

	} while (error.value() == WSAEWOULDBLOCK);

	if (!error) {
		messageReceived = buf.c_str();
		cout << std::endl << "Server says: " << buf << std::endl;
	}
	else
		cout << "Error while trying to connect to server " << error.message() << std::endl;
}

void client::
sendMessage(const char * mensaje)
{
	boost::system::error_code error;
	do
	{
		socket_forClient->write_some(boost::asio::buffer(mensaje, strlen(mensaje)), error);

	} while (error.value() == WSAEWOULDBLOCK);

	if (error)
	{
		std::cout << "Error al enviar mensaje" << error.message() << std::endl;
	}
}
