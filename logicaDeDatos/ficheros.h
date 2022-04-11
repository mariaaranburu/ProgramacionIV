#ifndef _FICHEROS_H_
#define _FICHEROS_H_

#include "..\logicaDeNegocio\cliente.h"

void limpiar (char limpiar []);
void leerFicheroClientes (Cliente* clientes, int* size);
void escribirFicheroClientes (Cliente* clientes, int size);

#endif
