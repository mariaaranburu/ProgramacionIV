#ifndef MENU_H_
#define MENU_H_

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>

void inicioSesion(int iResult, SOCKET ConnectSocket);
void menuSaldo(SOCKET ConnectSocket);

#endif