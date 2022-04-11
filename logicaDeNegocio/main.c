#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "transaccion.h"
#define MAX_CLIENTES 10
#define NUM_TARJETAS 10*MAX_CLIENTES
#define MAX_CHAR 30


int main(void) {
    Cliente *clientes = (Cliente*) malloc (MAX_CLIENTES*sizeof(Cliente));
    clientes[0].dni = 73511346;
    clientes[0].contrasenya = "1234A";
    clientes[0].nombre = "Jose";
    CuentaCorriente *cuentas = (CuentaCorriente*) malloc(2*sizeof(CuentaCorriente));
    cuentas->numero = 1;
    cuentas->saldo = 1000;
    cuentas->cliente = clientes;
    cuentas[1].numero = 2;
    cuentas[1].saldo = 1500;
    cuentas[1].cliente = clientes;
    Transaccion *transacciones = (Transaccion*) malloc (NUM_TARJETAS*sizeof(Transaccion));
    int numTransacciones = MAX_CLIENTES;
    transacciones->num = 1;
    transacciones->importe = 20;
    transacciones->descripcion = "comida";
    transacciones->origen = cuentas;
    transacciones->destino = cuentas+1;
    transacciones[1].num = 2;
    transacciones[1].importe = 120;
    transacciones[1].descripcion = "transferencia";
    transacciones[1].origen = cuentas+1;
    transacciones[1].destino = cuentas;
    Tarjeta* tarjetas = (Tarjeta*) malloc (NUM_TARJETAS*sizeof(Tarjeta));
    tarjetas->num = 123456;
    tarjetas->pin = 1111;
    tarjetas->limite = 1000;
    tarjetas->tipo = "credito";
    tarjetas->numCC = 1;
    int numTarjetas = NUM_TARJETAS;
    int encontrado = iniciarSesion(clientes, MAX_CLIENTES);
    while (encontrado!=0) {
        printf("Los datos introducidos no son correctos.\n");
        encontrado = iniciarSesion(clientes,MAX_CLIENTES);
    }
    printf("Estas dentro!\n");
    imprimirMenu(cuentas,transacciones,numTransacciones,tarjetas,numTarjetas, clientes[0]);
    return 0;
}

