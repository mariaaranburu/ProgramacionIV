#include <stdio.h>
#include <stdlib.h>
#include "bbdd.h"
#include "../logicaDeNegocio/cliente.h"

int main (void){
    sqlite3 *db;
    //Abrir base de datos
	int result = sqlite3_open("bbdd.sqlite", &db);
    ////////////////////////////////////////////////////////////////////

    int numClientes;
    numClientes = cuantosClientes(db);
    printf("lineas: %i\n",numClientes);
    Cliente* c = (Cliente*)malloc(numClientes*sizeof(Cliente));
    c = cogerClientes(db);
    int numCuentas = cuantasCC(db);
    printf("Num cuentas: %i\n",numCuentas);
    CuentaCorriente* cuenta = (CuentaCorriente*)malloc(numCuentas*sizeof(CuentaCorriente));
    cuenta = cogerCuentas(db,c);
    printf("%i\n",cuenta[5].cliente->dni);
    
    //Cerrar base de datos
    result = sqlite3_close(db);
	if (result != SQLITE_OK) {
		printf("Error opening database\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Database closed\n") ;
    ////////////////////////////////////////////////////////////////////
    return 0;
}
