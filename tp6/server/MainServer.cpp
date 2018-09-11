#include "Server.h"
int
main(int argc, char* argv[])
{
	server serv;
	std::cout << std::endl << "Start Listening on port " << PORT << std::endl;
	serv.startConnection();
	std::cout << "Somebody connected to port " << PORT << std::endl;
	std::cout << "Press Enter to Send Message  " << std::endl;
	getchar();
	if(serv.receiveMessage())
	{
		if (serv.messageCheck())
		{
			if (serv.isPath())
			{
				serv.message(true);
			}
			else
			{
				serv.message(false);
			}
		}
		else
		{
			std::cout << "Message in wrong format" << std::endl;
			return 0;
		}
	}
	else
	{
		std::cout << "No message received " << std::endl;
	}
	serv.sendMessage();
	Sleep(50); // Le damos 50ms para que llegue el mensaje antes de cerrar el socket.

	return 0;
}