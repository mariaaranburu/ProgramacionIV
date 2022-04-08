#ifndef _MENU_H_
#define _MENU_H_
#include "cliente.h"

int iniciarSesion(Cliente* c,int max);
char imprimirMenu(void);
void miCuentaCorriente(void);
void misTarjetas(void);
void misAcciones(void);
void miPerfil(Cliente c);

#endif