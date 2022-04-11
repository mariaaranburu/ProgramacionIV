#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "transaccion.h"
#define MAX_CLIENTES 10
#define NUM_TARJETAS 10*MAX_CLIENTES
#define MAX_CHAR 30


int main(void) {
    CuentaCorriente cuenta;
    Transaccion *transacciones;
    int numTransacciones;
    Tarjeta* tarjetas = (Tarjeta*) malloc (NUM_TARJETAS*sizeof(Tarjeta));
    tarjetas->num = 123456;
    tarjetas->pin = 1111;
    tarjetas->limite = 1000;
    tarjetas->tipo = "credito";
    tarjetas->numCC = 1;
    int numTarjetas = NUM_TARJETAS;
    Cliente *clientes = (Cliente*) malloc (MAX_CLIENTES*sizeof(Cliente));
    clientes[0].dni = 73511346;
    clientes[0].contrasenya = "1234A";
    int encontrado = iniciarSesion(clientes, MAX_CLIENTES);
    while (encontrado!=0) {
        printf("Los datos introducidos no son correctos.\n");
        encontrado = iniciarSesion(clientes,MAX_CLIENTES);
    }
    printf("Estas dentro!\n");
    imprimirMenu(cuenta,transacciones,numTransacciones,tarjetas,numTarjetas);
    return 0;
}

