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
#include <string.h>
//#include "../c++/usuario.h"
#include "../c++/cliente_.h"
#include "../c++/cuentacorriente_.h"
#include "../gestionBD/bbdd_cpp.h"
#include "../gestionBD/sqlite3.h"
#include "../c++/administrador_.h"
using namespace std;

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 100
#define DEF 100
#define DEFAULT_PORT "27015"

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
   return dynamic_cast<const Base*>(ptr) != nullptr;
}

char* leerFicheroConf (string fichero);

void compruebaClienteConnect(SOCKET ClientSocket, char* recvbuf, int recvbuflen);
int recibirDNI(SOCKET ClientSocket, char* recvbuf, int recvbuflen );
int recibirContrasenya(SOCKET ClientSocket, char* recvbuf, int recvbuflen );
int comprobarInicioSesion(int dni, int contrasenya,Cliente** listaCliente, sqlite3* db, Administrador** listaAdmins);
int menuSaldo(SOCKET ClientSocket, CuentaCorriente* cuenta, Cliente* cliente);
int recibirCCDestino(SOCKET ClientSocket, char* recvbuf, int recvbuflen);
int recibirImporte(SOCKET ClientSocket, char* recvbuf, int recvbuflen);
char* recibirDescripcion(SOCKET ClientSocket, char* recvbuf, int recvbuflen);


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
    char* recvbuf2 = new char[DEFAULT_BUFLEN];
    char* recvbuf3 = new char[DEFAULT_BUFLEN];



    char* f_pathBD = new char[DEF];
    f_pathBD = leerFicheroConf("../ficheros/path_bbdd.txt");
    //int result_bd = sqlite3_open(f_pathBD, &db);
    //int result_bd = sqlite3_open("bbdd.sqlite", &db);


    
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        cout<<"WSAStartup failed with error: "<<iResult<<endl;
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
    sqlite3 *db;
    int res_bd = sqlite3_open("bbdd.sqlite", &db);
    Cliente* cliente = new Cliente;

    // Receive until the peer shuts down the connection
    do {
        //1: FUNCION CLIENTE SE HA CONECTADO
        compruebaClienteConnect(ClientSocket, recvbuf, recvbuflen);

        //2: FUNCION RECIBIR DNI
        int dni = recibirDNI(ClientSocket, recvbuf2, recvbuflen);

        //3: FUNCION RECIBIR CONTRASENYA
        int contra = recibirContrasenya(ClientSocket, recvbuf3, recvbuflen);

        //4: COMPROBAR DNI Y CONTRASENYA CORRECTOS
        Usuario** listaUsuarios = listaUsuariosf(db);
        int numUsuarios = cuantosUsuarios(db);
        Cliente** listaCliente = deUsuariosAClientes(listaUsuarios, numUsuarios);
        Administrador** listaAdmins = deUsuariosAAdmin(listaUsuarios, numUsuarios);
        int inicio = comprobarInicioSesion(dni, contra, listaCliente, db, listaAdmins);
        
        //Depende de lo que sea llamo a una cosa u otra
        CuentaCorriente** cuentas = listaCC(db);
        Cliente* cliente = cogerCliente(listaCliente, dni, db);
        //4.1: IDENTIFICAR TIPO DE USUARIO
        char* sendbuf1 = new char[15];
        if (inicio == -1) {
            sendbuf1 = "-1\0";
        } else if (inicio == 1) {
            sendbuf1 = "1\0";
        } else {
            sendbuf1 = "0\0";
        }
        iSendResult = send( ClientSocket, sendbuf1, (int)strlen(sendbuf1), 0 );
        
        //MENUS
        if(inicio == -1){
            //ADMINISTRADOR
            
        }else if(inicio == 0){
            cout<<"El cliente no ha introducido los datos correctos."<<endl;
            sendbuf = "0";
            //SALIR
        }else if(inicio==1){
            //CLIENTE
            CuentaCorriente* cc = cogerCCxDNI(cuentas, dni, db);
            int saldo = menuSaldo(ClientSocket, cc, cliente);
        }
        

       
        iResult = shutdown(ClientSocket, SD_SEND);
        if (iResult == SOCKET_ERROR) {
            printf("shutdown failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            return 1;
        }
    
        else if (iResult == 0) {
            printf("Connection closing...\n");
        }
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
            i++;
		}

	}
	my_file.close();
    return c;
}

//1. EL CLIENTE SE HA CONECTADO
void compruebaClienteConnect(SOCKET ClientSocket, char* recvbuf, int recvbuflen){
    int iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {
            char* newText = new char[iResult];
            strcpy(newText, recvbuf);
            newText[iResult] = '\0';
            printf("%s\n", newText);
        }
}

//2. Recibir DNI
int recibirDNI(SOCKET ClientSocket, char* recvbuf, int recvbuflen ){
    int dni_num;
    int iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
    char* dni = new char[iResult];
    strcpy(dni, recvbuf);
    dni[iResult] = '\0';
    printf("DNI recibido: %s\n", dni);
    dni_num = (int)dni;
    return dni_num;
}


//3. FUNCION RECIBIR CONTRASENYA
int recibirContrasenya (SOCKET ClientSocket, char* recvbuf, int recvbuflen){
    cout << "Estoy en recibir";
    
    int iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
    cout << "Estoy en recibir1";
    //char* cont = new char[15];
    cout << "Estoy en recibir2";
    //strcpy(cont, recvbuf);
     cout << "Estoy en recibir3";
    //contrasenya[iResult] = '\0'; 
     cout << "Estoy en recibir4";
    //printf("Contrasenya recibida: %s\n", contrasenya);
    cout << "Esto en mitad ";
    int contrasenya_num = 1111;
    //contrasenya_num = (int)contrasenya;
    return contrasenya_num;
}

//4. COMPROBAR DNI Y CONTRASEÑA
int comprobarInicioSesion(int dni, int contrasenya,Cliente** listaCliente, sqlite3* db, Administrador** listaAdmins){
    int dev = 0;
    if(dni==1111){
        Administrador* admin = new Administrador();
        admin = cogerAdministrador(listaAdmins, dni, db);
        if((int)admin->getContrasenya() == contrasenya){
            dev = -1;
        }
    }else{
        Cliente* cliente = new Cliente();
        //Faltan argumentos
        cliente = cogerCliente( listaCliente, dni, db);
        if((int)cliente->getContrasenya() == contrasenya){
            dev = 1; 
        }

    }
    return dev;
}

//5. MENU SALDO
int menuSaldo(SOCKET ClientSocket, CuentaCorriente* cuenta, Cliente* cliente) {
    //ENVIAR HOLA CLIENTE
    char* sendbuf = new char[DEFAULT_BUFLEN];
    sendbuf =  cuenta->getCliente()->diHola();
    int iSendResult = send( ClientSocket, sendbuf, (int)strlen(sendbuf), 0 );
    if (iSendResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }
    //ENVIAR SALDO
    char* sendbuf1 = new char[DEFAULT_BUFLEN];
    sprintf(sendbuf1, "%f",cuenta->getSaldo());
    iSendResult = send( ClientSocket, sendbuf1, (int)strlen(sendbuf1), 0 );
    if (iSendResult == SOCKET_ERROR) {
        cout<<"send failed with error: "<<WSAGetLastError()<<endl;
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }

    // Recibir opcion transaccion si o no 
    char* recvbuf = new char[DEFAULT_BUFLEN];
    int iResult = recv(ClientSocket, recvbuf, DEFAULT_BUFLEN, 0);
    char* opcionRec = new char[iResult];
    if (iResult>0) {
        strcpy(opcionRec, recvbuf);
        opcionRec[iResult] = '\0';
        printf("Opcion recibida: %s", opcionRec);
    }
    int res = strcmp(opcionRec,"s\0" );
    //transaccion si
    if(res = 0){
        //ENTRA MENU TRANSACCION
        int recvbuflen = DEFAULT_BUFLEN;
        int destino = recibirCCDestino(ClientSocket, recvbuf, recvbuflen);
        int importe =recibirImporte(ClientSocket, recvbuf, recvbuflen);
        char* descripcion = recibirDescripcion(ClientSocket, recvbuf, recvbuflen);
        cout << "Se ha hecho una nueva transaccion";
        
    }else{
        //No hace transaccion, se sale
        cout<<"El cliente ha salido"<<endl;
    } 

}

 //RECIBIR CCDESTINO
int recibirCCDestino(SOCKET ClientSocket, char* recvbuf, int recvbuflen){
    int ccdestino;
        int iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        char* destino = new char[iResult];
        strcpy(destino, recvbuf);
        destino[iResult] = '\0';
        printf("CC destino recibido: %s\n", destino);
        ccdestino = (int)destino;
    return ccdestino;
}

//RECIBIR IMPORTE
int recibirImporte(SOCKET ClientSocket, char* recvbuf, int recvbuflen){
    int importe;
        int iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        char* imp = new char[iResult];
        strcpy(imp, recvbuf);
        imp[iResult] = '\0';
        printf("Importe recibido: %s\n", imp);
        importe = (int)imp;

    return importe;
}

//RECIBIR DESCRIPCION
char* recibirDescripcion(SOCKET ClientSocket, char* recvbuf, int recvbuflen){
    char* descripcion;
    int iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
    descripcion = new char[iResult];
    strcpy(descripcion, recvbuf);
    descripcion[iResult] = '\0';
    printf("Descripcion recibida: %s\n", descripcion);
    return descripcion;
}
//ADMIN HOLA
void menuAdmin(Administrador* admin, SOCKET ClientSocket){
    char* sendbuf = new char[DEFAULT_BUFLEN];
    sendbuf = admin->diHola();
    int iSendResult = send(ClientSocket, sendbuf, (int)strlen(sendbuf), 0 );
    
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    int iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
    char* opcion = new char[iResult];
    strcpy(opcion, recvbuf);
    opcion[iResult] = '\0';
    char* opA = "a";
    char* opB = "b";

    if(strcmp(opcion,opA)==0){
        //Recibir dni
        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        char* dni = new char[iResult];
        strcpy(dni, recvbuf);
        dni[iResult] = '\0';

        //Recibir nombre
        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        char* nombre = new char[iResult];
        strcpy(nombre, recvbuf);
        nombre[iResult] = '\0';

        //Recibir fec nac
        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        char* fec_nac = new char[iResult];
        strcpy(fec_nac, recvbuf);
        fec_nac[iResult] = '\0';

        //Recibir sexo
        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        char* sexo = new char[iResult];
        strcpy(sexo, recvbuf);
        sexo[iResult] = '\0';

        //Recibir contrasenya
        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        char* contrasenya = new char[iResult];
        strcpy(contrasenya, recvbuf);
        contrasenya[iResult] = '\0';

    }else if(strcmp(opcion,opB)==0){

    }
}


