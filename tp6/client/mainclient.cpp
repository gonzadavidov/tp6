#include "client.h"

using namespace std;

char*  obtenerHost(char* entrada, char host[]);
string crearMensaje(char* path);
int
main(int argc, char* argv[])
{
	client cliente;
	cout << "Tratando de conectarse a " << obtenerHost(argv[1], host) << " Puerto: " << HELLO_PORT_STR << endl; //mensaje
	cliente.startConnection(obtenerHost(argv[1], host));  //conecta al host
	string mensajeSolicitud = crearMensaje(argv[1]);		//se crea el mensaje para solicitarle al server en el  formato q interpreta
	cliente.mandarMensaje(mensajeSolicitud.c_str);		//se envia mensaje al servidor
	cliente.receiveMessage();					//espera y recibe respuesta del server
	ofstream archivo_salida("wwwPaginacom.txt");	// Se abre el archivo TXT para escribir	
	archivo_salida << cliente.mensaje;		// Se escribe en el archivo TXT el mensaje recibido del servidor
	archivo_salida.close();							// Se cierra el archivo
	cout << "Press Enter to exit..." << endl;

	getchar();
	return 0;
}

char*  obtenerHost(char* entrada, char host[]) {
	int i = 0;
	while (*entrada != '/') {
		host[i] = *entrada;
		i++;
		entrada++;
	}
	return host;
}

string crearMensaje(char * path)
{
	string mensaje;
	string a = GET, b = path, c = "HTTP / 1.1 CRLF Host : 127.0.0.1 CRLF CRLF";
	return mensaje = a + b + c;
}