#ifndef _BBDD_H_
#define _BBDD_H_
#include "sqlite3.h"
#include "cliente.h"

int open(sqlite3 *db);
int close(sqlite3 *db);
int cuantasAcciones(sqlite3 *db);
int cuantosClientes(sqlite3 *db);
int cogerClientes (sqlite3 *db, Cliente *c);
int cogerClientes (sqlite3 *db, Cliente *c);
int cuantasCC(sqlite3 *db);
int cuantasTarjetas(sqlite3 *db);
int cuantosTitulares(sqlite3 *db);
int cuentasTransacciones(sqlite3 *db);

#endif