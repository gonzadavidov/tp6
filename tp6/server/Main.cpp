#include "Server.h"
int
main(int argc, char* argv[])
{
	server conquering;
	std::cout << std::endl << "Start Listening on port " << PORT << std::endl;
	conquering.startConnection();
	std::cout << "Somebody connected to port " << PORT << std::endl;
	std::cout << "Press Enter to Send Message  " << std::endl;
	getchar();
	conquering.sendMessage();
	Sleep(50); // Le damos 50ms para que llegue el mensaje antes de cerrar el socket.

	return 0;
}