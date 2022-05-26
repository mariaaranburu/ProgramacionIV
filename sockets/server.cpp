#undef UNICODE

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


// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 1024
#define DEFAULT_PORT "27015"

string leerFicheroConf (char* fichero);
//void limpiarBuffer(char* buffer, int bufferLen);

int __cdecl main(void) 
{
    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo *result = NULL, *ptr = NULL, hints;

    int iSendResult;
    char* recvbuf = new char[DEFAULT_BUFLEN];
    char* sendbuf = new char[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    char* recvbuf1 = new char[DEFAULT_BUFLEN];
    
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // Accept a client socket
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // No longer need server socket
    closesocket(ListenSocket);

    // Receive until the peer shuts down the connection
    do {
        //1: El cliente se ha conectado!
        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {
            char* newText = new char[iResult];
            strcpy(newText, recvbuf);
            newText[iResult] = '\0';
            printf("%s\n", newText);

        // Echo the buffer back to the sender
        //1.1. Recibir DNI
        char* mensaje = "Introduce DNI sin letra: \n";
        iSendResult = send(ClientSocket, mensaje, (int)strlen(mensaje), 0);

        iResult = recv(ClientSocket, recvbuf1, recvbuflen, 0);
        char* dni = new char[iResult];
        strcpy(dni, recvbuf1);
        newText[iResult] = '\0';
        //limpiarBuffer(recvbuf, recvbuflen);
        printf("DNI recibido: %s\n", dni);

        //2
        sendbuf = "Elige una opcion: \n a. Ver cuenta\n b. Hacer transaccion\n 'q' para salir\n\0";
        iSendResult = send( ClientSocket, sendbuf, (int)strlen(sendbuf), 0 );
            if (iSendResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }
            //printf("Bytes sent: %d\n", iSendResult);
            printf("Text sent: %s\n", sendbuf);

            //3
            iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
            if (iResult>0) {
                char* newText = new char[iResult];
                strcpy(newText, recvbuf);
                newText[iResult] = '\0';
                printf("Opcion recibida: %s", newText);
                //limpiarBuffer(recvbuf, recvbuflen);
            }
            
            
            //printf("%s", recvbuf);

            //iSendResult = send(ClientSocket, recvbuf, iResult, 0);
            
            // shutdown the connection since we're done
        iResult = shutdown(ClientSocket, SD_SEND);
        if (iResult == SOCKET_ERROR) {
            printf("shutdown failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            return 1;
        }
        }
        else if (iResult == 0)
            printf("Connection closing...\n");
        else  {
            printf("recv failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            return 1;
        }

    } while (iResult > 0);

    

    // cleanup
    closesocket(ClientSocket);
    WSACleanup();

    return 0;
}

/*char* leerFicheroConf(char* fichero) {
   FILE* f;
    char c;

	int num_lines = 0;

	//abrir fichero para lectura
	f = fopen("prueba.txt", "r");
       
	//leer mientras no se llegue al final del fichero EOF
	while ((c = fgetc(f)) != EOF)
	{
		if (c == '\n')
			num_lines++;  
		putchar(c);
	}
	//cerrar fichero
	fclose(f);

	printf("El fichero tiene %i líneas\n", num_lines);
}*/

string leerFicheroConf (char* fichero){
    string line;
    ifstream file;
    file.open(fichero);
    if(file.is_open()){
        getline(file,line);
    }else{
        cout << "No se ha podido abrir el fichero. \n";
    }
    return line;
}