#ifndef _CUENTA_CORRIENTE_H_
#define _CUENTA_CORRIENTE_H_
#include "../c/cliente.h"

typedef struct {
    int numero;
    float saldo;
    Cliente *cliente;
} Cuenta_Corriente;

void imprimirCuenta(Cuenta_Corriente *c);

Cuenta_Corriente cogerCuenta(Cuenta_Corriente* listadoCuentas, int numeroCuentas, int numeroCuenta);

void accederASaldoCuenta(Cuenta_Corriente* listadoCuentas, int numeroCuentas, int numeroCuenta, float modificacion, char tipo);

Cuenta_Corriente* buscarCC(int numCC, Cuenta_Corriente* cuentas, int numCuentas);

Cuenta_Corriente* buscarCC_Cliente(int dni, int numCuentas, Cuenta_Corriente* cuentas);

int cuentasCC_dni (int dni, int numCuentas, Cuenta_Corriente* cuentas);

#endif