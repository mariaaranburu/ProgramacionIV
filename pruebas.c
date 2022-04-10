#include <stdio.h>
#include <stdlib.h>
#include "bbdd.h"
#include "cliente.h"

int main (void){
    sqlite3 *db;
    //Abrir base de datos
	int result = sqlite3_open("bbdd.sqlite", &db);
	if (result != SQLITE_OK) {
		printf("Error opening database\n");
		return result;
	}
    printf("Database opened\n");
    ////////////////////////////////////////////////////////////////////

    int p;
    p = cuantosClientes(db);
    printf("lineas: %i\n",p);
    printf("Hola");
    Cliente* c = (Cliente*)malloc(p*sizeof(Cliente));
    printf("Hola");
    c = cogerClientes(db);
    printf("Hola");
    printf("DNI: %i",c[1].dni);
    
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
