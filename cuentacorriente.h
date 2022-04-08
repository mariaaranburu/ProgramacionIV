#include "cliente.h"
#ifndef _CUENTA_CORRIENTE_H_
#define _CUENTA_CORRIENTE_H_

typedef struct {
    int numero;
    float saldo;
    Cliente *cliente;
} CuentaCorriente;

void imprimirCuenta(CuentaCorriente *c);

CuentaCorriente cogerCuenta(CuentaCorriente* listadoCuentas, int numeroCuentas, int numeroCuenta);

void accederASaldoCuenta(CuentaCorriente* listadoCuentas, int numeroCuentas, int numeroCuenta, float modificacion, char tipo);

#endif