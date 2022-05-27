#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>
#include "menu_cliente.h"
#include <iostream>
#define MAX 30

// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT 27015

void clienteConectado(SOCKET ConnectSocket);
void inicioSesion_dni(int iResult, SOCKET ConnectSocket);
void inicioSesion_contra(int iResult, SOCKET ConnectSocket);

using namespace std;

int main (void){
    int iResult;
    WSADATA wsaData;

    SOCKET ConnectSocket = INVALID_SOCKET;
    struct sockaddr_in clientService; 

    int recvbuflen = DEFAULT_BUFLEN;
    char *sendbuf = "Client: sending data test";
    char recvbuf[DEFAULT_BUFLEN] = "";

    //----------------------
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != NO_ERROR) {
        wprintf(L"WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    //----------------------
    // Create a SOCKET for connecting to server
    ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ConnectSocket == INVALID_SOCKET) {
        wprintf(L"socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    //----------------------
    // The sockaddr_in structure specifies the address family,
    // IP address, and port of the server to be connected to.
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr( "127.0.0.1" );
    clientService.sin_port = htons( DEFAULT_PORT );

    //----------------------
    // Connect to server.
    iResult = connect( ConnectSocket, (SOCKADDR*) &clientService, sizeof(clientService) );
    if (iResult == SOCKET_ERROR) {
        wprintf(L"connect failed with error: %d\n", WSAGetLastError() );
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }
    clienteConectado(ConnectSocket);
    inicioSesion_dni(iResult,ConnectSocket);
    inicioSesion_contra(iResult,ConnectSocket);
    menuSaldo(ConnectSocket);

    

    // Receive until the peer closes the connection
    /*do {

        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if ( iResult > 0 )
            wprintf(L"Bytes received: %d\n", iResult);
        else if ( iResult == 0 )
            wprintf(L"Connection closed\n");
        else
            wprintf(L"recv failed with error: %d\n", WSAGetLastError());

    } while( iResult > 0 );*/



    // shutdown the connection since no more data will be sent
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        wprintf(L"shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
    }

    // close the socket
    iResult = closesocket(ConnectSocket);
    if (iResult == SOCKET_ERROR) {
        wprintf(L"close failed with error: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    WSACleanup();
    return 0;
}

void clienteConectado(SOCKET ConnectSocket) {
    //1: El cliente se ha conectado!
    char* mensaje = new char[MAX];
    mensaje = "El cliente esta conectado";
    int iResult = send( ConnectSocket, mensaje, (int)strlen(mensaje), 0 );
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
    }
}

void inicioSesion_dni(int iResult, SOCKET ConnectSocket){

    cout << "INICIO DE SESION"<<endl;

    //PIDE Y MANDA DNI
    cout << "DNI: ";
    char* usuario = new char[MAX];
    cin >> usuario;
    iResult = send( ConnectSocket, usuario, (int)strlen(usuario), 0 );
    if (iResult == SOCKET_ERROR) {
        wprintf(L"send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
    }
    cout <<usuario;
    cout <<endl;

}

void inicioSesion_contra(int iResult, SOCKET ConnectSocket){
    cout<<"Contrasenya: ";
    char* contrasenya = new char[MAX];
    cin>>contrasenya;

    iResult = send( ConnectSocket, contrasenya, (int)strlen(contrasenya), 0 );
    if (iResult == SOCKET_ERROR) {
        wprintf(L"send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
    }
    cout <<contrasenya;
    cout <<endl;
}

void menuSaldo(SOCKET ConnectSocket){
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    //RECIBIR NOMBRE
    int iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
    char* nombre = new char[iResult];
    strcpy(nombre, recvbuf);
    nombre[iResult] = '\0';
    cout<<"Hola" <<nombre<<endl;

    //RECIBIR SALDO
    iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
    char* saldo = new char[iResult];
    strcpy(saldo, recvbuf);
    saldo[iResult] = '\0';
    cout<<"Saldo: "<<saldo<<endl;

    //
    cout << "Quieres hacer una transferencia? " <<endl;
    char* respuesta = new char[MAX];
    cin>>respuesta;
    iResult = send( ConnectSocket, respuesta, (int)strlen(respuesta), 0 );

}

void menuTransferencia(SOCKET ConnectSocket){
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    int iResult;

    //INSERTAR CUENTA DESTINO
    cout << "Cuenta destino: ";
    char* cuentaDes = new char[MAX];
    cin >> cuentaDes;
    iResult = send( ConnectSocket, cuentaDes, (int)strlen(cuentaDes), 0 );
    if (iResult == SOCKET_ERROR) {
        wprintf(L"send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
    }
    cout <<cuentaDes;
    cout <<endl;

    //INSERTAR IMPORTE
    cout << "Importe: ";
    char* importe = new char[MAX];
    cin >> importe;
    iResult = send( ConnectSocket, importe, (int)strlen(importe), 0 );
    if (iResult == SOCKET_ERROR) {
        wprintf(L"send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
    }
    cout <<importe;
    cout <<endl;
    
    //INSERTAR DESCRIPCION
    cout << "Descripcion: ";
    char* descripcion = new char[MAX];
    cin >> descripcion;
    iResult = send( ConnectSocket, descripcion, (int)strlen(descripcion), 0 );
    if (iResult == SOCKET_ERROR) {
        wprintf(L"send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
    }
    cout <<descripcion;
    cout <<endl;
}

void menuAdmin(SOCKET ConnectSocket){
    //SALUDAR AL ADMIN
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    //RECIBIR NOMBRE
    int iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
    char* nombre = new char[iResult];
    strcpy(nombre, recvbuf);
    nombre[iResult] = '\0';
    cout<<"Hola" <<nombre<<endl;

    cout<<"a) Crear cliente "<<endl;
    cout<<"b) Estadisticas" <<endl;

    char* opcion = new char[MAX];
    cin >> opcion;
    iResult = send( ConnectSocket, opcion, (int)strlen(opcion), 0 );
    if (iResult == SOCKET_ERROR) {
        wprintf(L"send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
    }
    cout <<endl;
    
}

void crearCliente(SOCKET ConnectSocket){
    int iResult;
    cout << "CREAR CLIENTE" <<endl;
    cout << "DNI: ";
    char* dni = new char[MAX];
    cin >> dni;
    iResult = send( ConnectSocket, dni, (int)strlen(dni), 0 );
    if (iResult == SOCKET_ERROR) {
        wprintf(L"send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
    }
    cout <<endl;

    cout << "Fecha nacimiento: ";
    char* fec_nac = new char[MAX];
    cin >> fec_nac;
    iResult = send( ConnectSocket, fec_nac, (int)strlen(fec_nac), 0 );
    if (iResult == SOCKET_ERROR) {
        wprintf(L"send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
    }
    cout <<endl;

    cout << "Sexo: ";
    char* sexo = new char[MAX];
    cin >> sexo;
    iResult = send( ConnectSocket, sexo, (int)strlen(sexo), 0 );
    if (iResult == SOCKET_ERROR) {
        wprintf(L"send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
    }
    cout <<endl;
}

