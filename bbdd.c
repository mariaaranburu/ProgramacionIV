#include <stdio.h>
#include "sqlite3.h"
#include "cliente.h"
#include "fecha.h"
#include <string.h>

void cuantosClientes(sqlite3 *db){
    sqlite3_stmt *stmt;

    char sql[] = "select count(*) from CLIENTE";
    int result = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
}

int cogerClientes (sqlite3 *db, Cliente *c){
    sqlite3_stmt *stmt;
    char sql[] = "select * from CLIENTE";
    int result = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    printf("SQL query prepared (SELECT)\n");

    int dni;
    char* nombre;
    char* sexo;
    char* contrasenya;
    int contador = 0;

    do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			c[contador].dni = sqlite3_column_int(stmt, 0);
			strcpy(c[contador].nombre, (char *) sqlite3_column_text(stmt, 1));
            strcpy(c[contador].sexo,(char *) sqlite3_column_text(stmt, 3));
            strcpy(c[contador].contrasenya,(char *) sqlite3_column_text(stmt, 4));
            contador++;
		}
	} while (result == SQLITE_ROW);

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Prepared statement finalized (SELECT)\n");
    return SQLITE_OK;

}