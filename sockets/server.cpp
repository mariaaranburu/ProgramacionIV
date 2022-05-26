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
#include "../c++/usuario.h"
#include "../c++/cliente.h"
#include "../c++/cuentacorriente.h"
#include "../gestionBD/bbdd.h"
using namespace std;

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 1024
#define DEF 100
#define DEFAULT_PORT "27015"

char* leerFicheroConf (string fichero);

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
    char* recvbuf2 = new char[DEFAULT_BUFLEN];
    char* recvbuf3 = new char[DEFAULT_BUFLEN];
    char* recvbuf4 = new char[DEFAULT_BUFLEN];
    char* recvbuf5 = new char[DEFAULT_BUFLEN];
    char* recvbuf6 = new char[DEFAULT_BUFLEN];
    char* recvbuf7 = new char[DEFAULT_BUFLEN];
    char* recvbuf8 = new char[DEFAULT_BUFLEN];
    char* recvbuf9 = new char[DEFAULT_BUFLEN];
    char* recvbuf10 = new char[DEFAULT_BUFLEN];


    char* f_pathBD = new char[DEF];
    f_pathBD = leerFicheroConf("../ficheros/path_bbdd.txt");
    sqlite3 *db;
    int result = sqlite3_open(f_pathBD, &db);

    
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
    char* f_puerto = new char[DEF];
    char* f_dirIP = new char[DEF];
    f_puerto = leerFicheroConf("../ficheros/puertos.txt");
    f_dirIP = leerFicheroConf("../ficheros/direccion_IP.txt");

    iResult = getaddrinfo(NULL, f_puerto, &hints, &result);
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

        //1.2. Recibir contrasenya
        char* mensaje2 = "Introduce tu contrasenya: \n";
        iSendResult = send(ClientSocket, mensaje2, (int)strlen(mensaje2), 0);

        iResult = recv(ClientSocket, recvbuf2, recvbuflen, 0);
        char* contrasenya = new char[iResult];
        strcpy(contrasenya, recvbuf2);
        newText[iResult] = '\0';
        //limpiarBuffer(recvbuf, recvbuflen);
        printf("Contrasenya recibida: %s\n", contrasenya);
        
        //COMPROBAR DNI Y CONTRASENYA CORRECTOS
       
        //2 Enviar opciones menu
        //Cliente* cliente = new Cliente(1234, "Cliente", "01/01/2001", 'f', "1234");
        //CuentaCorriente *cuenta = new CuentaCorriente(1, 200.00, cliente);
        //metodo polimorfico
        sendbuf = "¡Hola %s! \n Tu saldo es: %i\n ¿Quieres hacer alguna transferencia? s/n\n  'q' para salir\n\0", "Malen", 200000;
        iSendResult = send( ClientSocket, sendbuf, (int)strlen(sendbuf), 0 );
            if (iSendResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }
            //printf("Bytes sent: %d\n", iSendResult);
            printf("Text sent: %s\n", sendbuf);

            //3 Recibir opcion
            iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
            if (iResult>0) {
                char* newText = new char[iResult];
                strcpy(newText, recvbuf);
                newText[iResult] = '\0';
                printf("Opcion recibida: %s", newText);
                //limpiarBuffer(recvbuf, recvbuflen);
            }

            //si no funciona probar con strcmp(strg1, strg2)==0
            if(newText=="s" || newText=="S") {
                //4 Pedir datos nueva transferencia
                    //4.1.
                sendbuf = "Introduce CC destino: \n\0";
                iSendResult = send( ClientSocket, sendbuf, (int)strlen(sendbuf), 0 );
                if (iSendResult == SOCKET_ERROR) {
                    printf("send failed with error: %d\n", WSAGetLastError());
                    closesocket(ClientSocket);
                    WSACleanup();
                    return 1;
                }
                printf("Text sent: %s\n", sendbuf);
                iResult = recv(ClientSocket, recvbuf3, recvbuflen, 0);
                if (iResult>0) {
                    char* ccDestino = new char[iResult];
                    strcpy(ccDestino, recvbuf3);
                    ccDestino[iResult] = '\0';
                    printf("CC destino recibida: %s", ccDestino);
                }

                    //4.2.
                sendbuf = "Introduce importe: \n\0";
                iSendResult = send( ClientSocket, sendbuf, (int)strlen(sendbuf), 0 );
                if (iSendResult == SOCKET_ERROR) {
                    printf("send failed with error: %d\n", WSAGetLastError());
                    closesocket(ClientSocket);
                    WSACleanup();
                    return 1;
                }
                printf("Text sent: %s\n", sendbuf);
                iResult = recv(ClientSocket, recvbuf4, recvbuflen, 0);
                if (iResult>0) {
                    char* importe = new char[iResult];
                    strcpy(importe, recvbuf4);
                    importe[iResult] = '\0';
                    printf("Importe recibido: %s", importe);
                }
            
                    //4.3.
                sendbuf = "Introduce descripcion: \n\0";
                iSendResult = send( ClientSocket, sendbuf, (int)strlen(sendbuf), 0 );
                if (iSendResult == SOCKET_ERROR) {
                    printf("send failed with error: %d\n", WSAGetLastError());
                    closesocket(ClientSocket);
                    WSACleanup();
                    return 1;
                }
                printf("Text sent: %s\n", sendbuf);

                iResult = recv(ClientSocket, recvbuf5, recvbuflen, 0);
                if (iResult>0) {
                    char* descripcion = new char[iResult];
                    strcpy(descripcion, recvbuf5);
                    descripcion[iResult] = '\0';
                    printf("Descripcion recibida: %s", descripcion);
                }

            } else if (newText=="n" || newText=="N") {
                //NO HACE TRANSFERENCIA
                printf("De acuerdo, no haremos la transferencia");

            }else{
                //ERROR, LAS LETRAS TIENEN QUE SER S O N
                printf("Error, las letras tienen que ser s o n, se procede a la salida\n");
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
			cout << ch;
            i++;
		}

	}
	my_file.close();
    return c;
}