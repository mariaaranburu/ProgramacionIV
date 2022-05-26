#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "transaccion.h"
#include"tarjeta.h"
#include "cliente.h"
#include "..\gestionBD\bbdd.h"
#define MAX_CLIENTES 10
#define MAX_GENERAL 10*MAX_CLIENTES
#define MAX_CHAR 30
#define NUM_MAX_CC 15


int main(void) {
    sqlite3 *db;
    //Abrir base de datos
	int result = sqlite3_open("bbdd.sqlite", &db);
    //CLIENTES
    int numClientes = cuantosClientes(db);
    Cliente* clientes = (Cliente*)malloc(MAX_CLIENTES*sizeof(Cliente));
    clientes = cogerClientes(db);
    //ACCIONES
    int numAcciones = cuantasAcciones(db);
    Accion* acciones = (Accion*)malloc(MAX_GENERAL*sizeof(Accion));

    acciones = listaAcciones(db,clientes);
    //CUENTAS CORRIENTES
    int numCC = cuantasCC(db);
    CuentaCorriente* cuentas = (CuentaCorriente*)malloc(MAX_GENERAL*sizeof(CuentaCorriente));
    cuentas = cogerCuentas(db,clientes);
    //TARJETAS
    //Entre esto 
    int numTarjetas = cuantasTarjetas(db);
    Tarjeta* tarjetas = (Tarjeta*)malloc(MAX_GENERAL*sizeof(Tarjeta));
    tarjetas = listaTarjetas(db);
    //TRANSACCIONES
    int numTransacciones = cuantasTransacciones(db);
    Transaccion* transacciones = (Transaccion*)malloc(MAX_GENERAL*sizeof(Transaccion));
    transacciones = listaTransacciones(db,cuentas,numCC);
    //Y esto hay algo que a veces falla
    //result = sqlite3_close("bbdd.sqlite", &db);

    
    Cliente* cliente = (Cliente*)malloc(sizeof(Cliente));
    printf("HOLA %i",numCC);
    cliente = iniciarSesion(clientes, MAX_CLIENTES);

    CuentaCorriente* cuentasCliente = (CuentaCorriente*)malloc(NUM_MAX_CC*sizeof(CuentaCorriente));
    printf("1\n");
    printf("%i\n",numCC);
    //cuentasCliente = buscarCC_Cliente(cliente->dni,numCC,cuentas);
    printf("2");
    //int numCC_Cliente = cuentasCC_dni(cliente->dni,numCC,cuentas);
    printf("3");
    
    imprimirMenu(clientes,numClientes, transacciones, numTransacciones, tarjetas, numTarjetas, clientes );
    

    return 0;
}

