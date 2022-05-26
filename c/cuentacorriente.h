#ifndef _CUENTA_CORRIENTE_H_
#define _CUENTA_CORRIENTE_H_
#include "../c/cliente.h"

typedef struct {
    int numero;
    float saldo;
    Cliente *cliente;
} CuentaCorriente;

void imprimirCuenta(CuentaCorriente *c);

CuentaCorriente cogerCuenta(CuentaCorriente* listadoCuentas, int numeroCuentas, int numeroCuenta);

void accederASaldoCuenta(CuentaCorriente* listadoCuentas, int numeroCuentas, int numeroCuenta, float modificacion, char tipo);

CuentaCorriente* buscarCC(int numCC, CuentaCorriente* cuentas, int numCuentas);

CuentaCorriente* buscarCC_Cliente(int dni, int numCuentas, CuentaCorriente* cuentas);

int cuentasCC_dni (int dni, int numCuentas, CuentaCorriente* cuentas);

#endif