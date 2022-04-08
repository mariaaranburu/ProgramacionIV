#include <stdio.h>
#include "cuentacorriente.h"
#include "cliente.h"

void imprimirCuenta(CuentaCorriente *c) {
    printf("Mi cuenta: [Numero de cuenta: %i, Saldo: %.2f, Cliente: [Nombre: %s]]", c->numero, c->saldo, c->cliente->nombre);
}