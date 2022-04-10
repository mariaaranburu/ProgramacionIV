#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#define MAX_CLIENTES 10
#define MAX_CHAR 30


int main(void) {
    CuentaCorriente cuenta = 
    Transaccion* transacciones;
    int numTransacciones;
    Tarjeta* tarjetas;
    int numTarjetas;
    Cliente *clientes = (Cliente*) malloc (MAX_CLIENTES*sizeof(Cliente));
    clientes[0].dni = 73511346;
    clientes[0].contrasenya = "1234A";
    int encontrado = iniciarSesion(clientes,MAX_CLIENTES);
    if (encontrado == 0) {
        printf("Estas dentro!\n");
        imprimirMenu(cuenta,transacciones,numTransacciones,tarjetas,numTarjetas);
    }
    else {
    printf("Los datos introducidos no son correctos.");
    }
    return 0;
}

