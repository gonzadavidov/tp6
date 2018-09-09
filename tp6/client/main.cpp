#include "client.h"
#include <iostream>
#include <fstream>

using namespace std;

char*  obtenerHost(int argc, char* argv, char host[]);

int
main(int argc, char* argv[])
{
	client cliente;
	char host[500];
	cout << "Trying to connect to " << SERVER_IP << " on port " << HELLO_PORT_STR << endl;
	cliente.startConnection(obtenerHost(argc,argv,host));
	cliente.receiveMessage();
	
	ofstream archivo_salida("file.txt");			// Se abre el archivo para escribir
	archivo_salida << cliente.mensaje << endl;		// Se escribe en el archivo
	archivo_salida.close();							// Se cierra el archivo

	cout << "Press Enter to exit..." << endl;
	getchar();
	return 0;
}

char*  obtenerHost(int argc, char* argv, char host[]) {
	int i = 0;
	while (*(argv[i]) != "/") {
		host[i] = argv[i];
		i++;
	}
	return host;
}