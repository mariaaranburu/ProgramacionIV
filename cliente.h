#ifndef _CLIENTE_H_
#define _CLIENTE_H_

#include "fecha.h"

typedef struct {
    int dni;
    char* nombre;
    Fecha fec_nac;
    char sexo;
    char* contrasenya;
} Cliente;

void imprimirCliente (Cliente *c);

#endif