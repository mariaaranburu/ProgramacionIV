#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x501

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 1024
#define DEFAULT_PORT "27015"
#define DEF 100

char* leerFicheroConf (string fichero);

int __cdecl main() 
{
    char* f_dirIP = new char[DEF];
    char* f_puerto = new char[DEF];
    
    f_dirIP = leerFicheroConf("../ficheros/direccion_IP.txt");
    f_puerto = leerFicheroConf("../ficheros/puertos.txt");
    

    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;
    const char *sendbuf = "¡El cliente se ha conectado!\0\n";
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;


    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(f_dirIP, f_puerto, &hints, &result);
    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Attempt to connect to an address until one succeeds
    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, 
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        // Connect to server.
        iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }

    // Send an initial buffer
    //1: El cliente se ha conectado!
    iResult = send( ConnectSocket, sendbuf, (int)strlen(sendbuf), 0 );
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    //printf("Bytes Sent: %ld\n", iResult);
     
    // Receive until the peer closes the connection
    do {
        //1.1. Enviar DNI
        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        char* mensajeDNI = new char[iResult];
        strcpy(mensajeDNI, recvbuf);
        mensajeDNI[iResult] = '\0';
        printf("%s", mensajeDNI);
        char* dni = new char[15];
        cin >> dni;
        iResult = send(ConnectSocket, dni, (int)strlen(dni), 0);
        
        //1.2. Enviar contrasenya
        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        char* mensajeContrasenya = new char[iResult];
        strcpy(mensajeContrasenya, recvbuf);
        mensajeContrasenya[iResult] = '\0';
        printf("%s", mensajeContrasenya);
        char* contrasenya = new char[15];
        cin >> contrasenya;
        iResult = send(ConnectSocket, contrasenya, (int)strlen(contrasenya), 0);
        

        //2 Recibir opciones menu
        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if ( iResult > 0 ) {
            //printf("Bytes received: %d\n", iResult);
            char* newText = new char[iResult];
            strcpy(newText, recvbuf);
            newText[iResult] = '\0';
            printf("%s", newText);

            //3 Enviar opcion
            char* opcion = new char[15];
            cin >> opcion;
            iResult = send(ConnectSocket, opcion, (int)strlen(opcion), 0);
            if (iResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(ConnectSocket);
                WSACleanup();
                return 1;
            }

            if (opcion=="s" || opcion=="S") {
                //4 Enviar datos nueva transferencia
                //4.1.
                iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
                char* mensajeDestino = new char[iResult];
                strcpy(mensajeDestino, recvbuf);
                mensajeDestino[iResult] = '\0';
                printf("%s", mensajeDestino);
                char* destino = new char[15];
                cin >> destino;
                iResult = send(ConnectSocket, destino, (int)strlen(destino), 0);
            
                //4.2.
                iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
                char* mensajeImporte = new char[iResult];
                strcpy(mensajeImporte, recvbuf);
                mensajeImporte[iResult] = '\0';
                printf("%s", mensajeImporte);
                char* importe = new char[15];
                cin >> importe;
                iResult = send(ConnectSocket, importe, (int)strlen(importe), 0);

                //4.3.
                iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
                char* mensajeDescripcion = new char[iResult];
                strcpy(mensajeDescripcion, recvbuf);
                mensajeDestino[iResult] = '\0';
                printf("%s", mensajeDescripcion);
                char* descripcion = new char[15];
                cin >> descripcion;
                iResult = send(ConnectSocket, descripcion, (int)strlen(descripcion), 0);
            }       

             if (opcion=="n" || opcion=="N")  {
                  printf("De acuerdo, no haremos la transferencia");
             }  

        } else if ( iResult == 0 )
            printf("Connection closed\n");
        else
            printf("recv failed with error: %d\n", WSAGetLastError());
        
    } while( iResult > 0 );

    // shutdown the connection since no more data will be sent
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();

    return 0;
}

char* leerFicheroConf (string fichero){
    char* c = new char[DEF];
    int i = 0;
    fstream my_file;
	my_file.open(fichero, ios::in);
	if (!my_file) {
		cout << "No such file";
	}
	else {
		char ch;

		while (1) {
			my_file >> ch;
			if (my_file.eof())
				break;
            
            c[i] = ch;
            i++;
		}

	}
    cout << c <<endl;
	my_file.close();
    return c;
}