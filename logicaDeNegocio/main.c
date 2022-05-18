#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "transaccion.h"
<<<<<<< HEAD
#include"tarjeta.h"
#include "cliente.h"
#include "..\gestionBD\bbdd.h"
=======
#include "..\gestionBD\bbdd.h"
#include "..\logicaDeDatos\ficheros.h"
>>>>>>> 5992b6e5956e004ea33136aab3301e5bf296946f
#define MAX_CLIENTES 10
#define MAX_GENERAL 10*MAX_CLIENTES
#define MAX_CHAR 30


int main(void) {
    sqlite3 *db;
    //Abrir base de datos
<<<<<<< HEAD
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


=======
    int result = sqlite3_open("bbdd.sqlite", &db);

    //CLIENTES
    int numClientes = cuantosClientes(db);
    Cliente* clientes = (Cliente*) malloc (numClientes*sizeof(Cliente));
    clientes = cogerClientes(db);
    //ACCIONES
    int numAcciones = cuantasAcciones(db);
    Accion* acciones = (Accion*)malloc(numAcciones*sizeof(Accion));
    acciones = listaAcciones(db,clientes);
    //CUENTAS CORRIENTES
    int numCC = cuantasCC(db);
    CuentaCorriente* cuentas = (CuentaCorriente*)malloc(numCC*sizeof(CuentaCorriente));
    cuentas = cogerCuentas(db,clientes);
    //TARJETAS
    int numTarjetas = cuantasTarjetas(db);
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
    int numeroTarjetas = 10*10;
>>>>>>> 5992b6e5956e004ea33136aab3301e5bf296946f
    int encontrado = iniciarSesion(clientes, MAX_CLIENTES);
    if(encontrado!=0){
        printf("Los datos introducidos no son correctos.\n");
        encontrado = iniciarSesion(clientes,MAX_CLIENTES);
    }else if(encontrado==0){
        printf("Estas dentro!\n");
    imprimirMenu(cuentas,transacciones,numTransacciones,tarjetas,numTarjetas);
    }
<<<<<<< HEAD
       
=======
    printf("Estas dentro!\n");
    imprimirMenu(cuentas,transacciones,numTransacciones,tarjetas,numeroTarjetas, clientes[0]);
>>>>>>> 5992b6e5956e004ea33136aab3301e5bf296946f
    return 0;
}

