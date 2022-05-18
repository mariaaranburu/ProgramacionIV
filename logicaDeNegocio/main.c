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


int main(void) {
    sqlite3 *db;
    //Abrir base de datos
	int result = sqlite3_open("bbdd.sqlite", &db);

    //CLIENTES
    int numClientes = cuentosClientes(db);
    Cliente* clientes = (Cliente*)malloc(MAX_CLIENTES*sizeof(Cliente));
    clientes = cogerClientes;
    //ACCIONES
    int numAcciones = cuantasAcciones(db);
    Accion* acciones = (Accion*)malloc(MAX_GENERAL*sizeof(Accion));
    acciones = listaAcciones(db,clientes);
    //CUENTAS CORRIENTES
    int numCC = cuantasCC(db);
    CuentaCorriente* cuentas = (CuentaCorriente*)malloc(MAX_GENERAL*sizeof(CuentaCorriente));
    cuentas = cogerCuentas(db,clientes);
    //TARJETAS
    int numTarjetas = cuantasTarjetas(db);
    Tarjeta* tarjetas = (Tarjeta*)malloc(MAX_GENERAL*sizeof(Tarjeta));
    tarjetas = listaTarjetas(db);
    //TRANSACCIONES
    int numTransacciones = cuantasTransacciones(db);
    Transaccion* transacciones = (Transaccion*)malloc(MAX_GENERAL*sizeof(Transaccion));
    transacciones = listaTransacciones(db,cuentas,numCC);


    int encontrado = iniciarSesion(clientes, MAX_CLIENTES);
    if(encontrado!=0){
        printf("Los datos introducidos no son correctos.\n");
        encontrado = iniciarSesion(clientes,MAX_CLIENTES);
    }else if(encontrado==0){
        printf("Estas dentro!\n");
    imprimirMenu(cuentas,transacciones,numTransacciones,tarjetas,numTarjetas);
    }
       
    return 0;
}

