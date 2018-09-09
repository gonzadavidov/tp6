#include "client.h"
#include <iostream>
#include <fstream>

using namespace std;


int
main(int argc, char* argv[])
{
	client cliente;
	cout << "Trying to connect to " << SERVER_IP << " on port " << HELLO_PORT_STR << endl;
	cliente.startConnection(SERVER_IP);
	cliente.receiveMessage();
	
	ofstream archivo_salida("file.txt");			// Se abre el archivo para escribir
	archivo_salida << cliente.mensaje << endl;		// Se escribe en el archivo
	archivo_salida.close();							// Se cierra el archivo

	cout << "Press Enter to exit..." << endl;
	getchar();
	return 0;
}