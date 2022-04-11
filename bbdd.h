#ifndef _BBDD_H_
#define _BBDD_H_
#include "sqlite3.h"
#include "cliente.h"
#include "accion.h"
#include "cuentacorriente.h"
#include "tarjeta.h"
#include "transaccion.h"

int open(sqlite3 *db);
int close(sqlite3 *db);
int cuantasAcciones(sqlite3 *db);
int cuantosClientes(sqlite3 *db);
Cliente* cogerClientes (sqlite3 *db);
int cuantasCC(sqlite3 *db);
CuentaCorriente* cogerCuentas (sqlite3 *db);
int cuantasTarjetas(sqlite3 *db);
int cuantosTitulares(sqlite3 *db);
int cuentasTransacciones(sqlite3 *db);

#endif