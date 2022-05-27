#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>
#include "menu_cliente.h"
#include <iostream>
#define MAX 15

// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 100
#define DEFAULT_PORT 27015

void clienteConectado(SOCKET ConnectSocket);
void inicioSesion_dni( SOCKET ConnectSocket);
void inicioSesion_contra( SOCKET ConnectSocket);
void menuAdmin(SOCKET ConnectSocket);
void crearCliente(SOCKET ConnectSocket);

using namespace std;

int main (void){
    int iResult;
    WSADATA wsaData;

    SOCKET ConnectSocket = INVALID_SOCKET;
    struct sockaddr_in clientService; 

    int recvbuflen = DEFAULT_BUFLEN;
    char *sendbuf = "Client: sending data test";
    char* recvbuf = new char[DEFAULT_BUFLEN];


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
    //1
    clienteConectado(ConnectSocket);
    //2
    inicioSesion_dni(ConnectSocket);
    //3
    inicioSesion_contra(ConnectSocket);
    cout<<"Llega aqui";
    //4.1: IDENTIFICAR TIPO DE USUARIO
    cout<<"Llega aqui";
    iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
    char* tipoUsuario = new char[iResult];
    strcpy(tipoUsuario, recvbuf);
    tipoUsuario[iResult] = '\0';
    if ((int)tipoUsuario == 1) {
        //Cliente
        menuSaldo(ConnectSocket);

    } else if ((int)tipoUsuario == -1) {
        //Administrador
        menuAdmin(ConnectSocket);
        crearCliente(ConnectSocket);
    } else {
        cout << "Los datos introducidos no son correctos. Hasta pronto." << endl;
    }

    //5

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
    char* mensaje = new char[15];
    mensaje = "El cliente esta conectado";
    int iResult = send( ConnectSocket, mensaje, (int)strlen(mensaje), 0 );
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
    }
}

void inicioSesion_dni( SOCKET ConnectSocket){

    cout << "INICIO DE SESION"<<endl;

    //PIDE Y MANDA DNI
    cout << "DNI: ";
    char* usuario = new char[15];
    cin >> usuario;
    int iResult = send( ConnectSocket, usuario, (int)strlen(usuario), 0 );
    if (iResult == SOCKET_ERROR) {
        wprintf(L"send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
    }
    cout <<usuario;
    cout <<endl;
}

void inicioSesion_contra( SOCKET ConnectSocket){
    cout<<"Contrasenya: ";
    char* contrasenya = new char[15];
    cin>>contrasenya;

    int iResult = send( ConnectSocket, contrasenya, (int)strlen(contrasenya), 0 );
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
    //RECIBIR MENSAJE
    int iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
    char* mensaje = new char[iResult];
    strcpy(mensaje, recvbuf);
    mensaje[iResult] = '\0';
    cout<<mensaje<<endl;

    //RECIBIR SALDO
    iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
    char* saldo = new char[iResult];
    strcpy(saldo, recvbuf);
    saldo[iResult] = '\0';
    cout<<"Saldo: "<<saldo<<endl;

    //ENTRAR TRANSFERENCIA
    cout << "Quieres hacer una transferencia? " <<endl;
    char* respuesta = new char[MAX];
    cin>>respuesta;
    iResult = send( ConnectSocket, respuesta, (int)strlen(respuesta), 0 );
    
}

void menuTransferencia(SOCKET ConnectSocket){
    char recvbuf[DEFAULT_BUFLEN] = "";
    int recvbuflen = DEFAULT_BUFLEN;
    int iResult;

    //INSERTAR CUENTA DESTINO
    cout << "Cuenta destino: ";
    char* cuentaDes = new char[15];
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
    char* importe = new char[15];
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
    char* descripcion = new char[15];
    cin >> descripcion;
    iResult = send( ConnectSocket, descripcion, (int)strlen(descripcion), 0 );
    if (iResult == SOCKET_ERROR) {
        wprintf(L"send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
    }
    cout <<descripcion;
    cout <<endl;

    cout <<"La transaccion se ha hecho correctamente."<<endl;
    
}

void menuAdmin(SOCKET ConnectSocket){
    //SALUDAR AL ADMIN
    char recvbuf[DEFAULT_BUFLEN] = "";
    int recvbuflen = DEFAULT_BUFLEN;
    //RECIBIR MENSAJE DE HOLA
    int iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
    char* mensaje = new char[iResult];
    strcpy(mensaje, recvbuf);
    mensaje[iResult] = '\0';
    cout<<mensaje<<endl;

    cout<<"a) Crear cliente "<<endl;
    cout<<"b) Estadisticas" <<endl;

    char* opcion = new char[15];
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
    //Recibir dni
    int iResult;
    cout << "CREAR CLIENTE" <<endl;
    cout << "DNI: ";
    char* dni = new char[15];
    cin >> dni;
    iResult = send( ConnectSocket, dni, (int)strlen(dni), 0 );
    if (iResult == SOCKET_ERROR) {
        wprintf(L"send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
    }
    cout <<endl;

    cout << "NOMBRE: ";
    char* nombre = new char[15];
    cin >> nombre;
    iResult = send( ConnectSocket, nombre, (int)strlen(nombre), 0 );
    if (iResult == SOCKET_ERROR) {
        wprintf(L"send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
    }
    cout <<endl;

    cout << "Fecha nacimiento: ";
    char* fec_nac = new char[15];
    cin >> fec_nac;
    iResult = send( ConnectSocket, fec_nac, (int)strlen(fec_nac), 0 );
    if (iResult == SOCKET_ERROR) {
        wprintf(L"send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
    }
    cout <<endl;

    cout << "Sexo: ";
    char* sexo = new char[15];
    cin >> sexo;
    iResult = send( ConnectSocket, sexo, (int)strlen(sexo), 0 );
    if (iResult == SOCKET_ERROR) {
        wprintf(L"send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
    }
    cout <<endl;

    cout << "CONTRASENYA: ";
    char* contra = new char[MAX];
    cin >> contra;
    iResult = send( ConnectSocket, contra, (int)strlen(contra), 0 );
    if (iResult == SOCKET_ERROR) {
        wprintf(L"send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
    }
    cout <<endl;
}


