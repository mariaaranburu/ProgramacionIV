#include "cuentacorriente.h"
#include "cliente.h"

#ifndef _TRANSACCION_H_
#define _TRANSACCION_H_

typedef struct {
    int num;
    float importe;
    char* descripcion;
    CuentaCorriente *origen;
    CuentaCorriente *destino;
} Transaccion;


#endif