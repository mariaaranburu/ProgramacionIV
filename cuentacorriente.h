#include "cliente.h"
#ifndef _CUENTA_CORRIENTE_H_
#define _CUENTA_CORRIENTE_H_

typedef struct {
    int numero;
    float saldo;
    Cliente *clientes;
} CuentaCorriente;


#endif