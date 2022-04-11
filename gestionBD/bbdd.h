#ifndef _BBDD_H_
#define _BBDD_H_
#include "sqlite3.h"
#include "../logicaDeNegocio/cliente.h"
#include "../logicaDeNegocio/accion.h"
#include "../logicaDeNegocio/cuentacorriente.h"
#include "../logicaDeNegocio/tarjeta.h"
#include "../logicaDeNegocio/transaccion.h"

int open(sqlite3 *db);
int close(sqlite3 *db);
int cuantasAcciones(sqlite3 *db);
int cuantosClientes(sqlite3 *db);
Cliente* cogerClientes (sqlite3 *db);
int cuantasCC(sqlite3 *db);
CuentaCorriente* cogerCuentas (sqlite3 *db, Cliente* clientes);
int cuantasTarjetas(sqlite3 *db);
int cuantosTitulares(sqlite3 *db);
int cuantasTransacciones(sqlite3 *db);
Accion* listaAcciones(sqlite3* db, Cliente* clientes);

#endif