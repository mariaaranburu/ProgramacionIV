#ifndef _BBDD_H_
#define _BBDD_H_
#include "sqlite3.h"
#include "../c/cliente.h"
#include "../c/accion.h"
#include "../c/cuentacorriente.h"
#include "../c/tarjeta.h"
#include "../c/transaccion.h"

int cuantasAcciones(sqlite3 *db);
int cuantosClientes(sqlite3 *db);
Cliente* cogerClientes (sqlite3 *db);
int cuantasCC(sqlite3 *db);
CuentaCorriente* cogerCuentas (sqlite3 *db, Cliente* clientes);
int cuantasTarjetas(sqlite3 *db);
Tarjeta* listaTarjetas(sqlite3* db);
int cuantosTitulares(sqlite3 *db);
int cuantasTransacciones(sqlite3 *db);
Accion* listaAcciones(sqlite3* db, Cliente* clientes);
Transaccion* listaTransacciones(sqlite3* db,CuentaCorriente* cuentas, int numCuentas);
CuentaCorriente* buscar(int numCC, CuentaCorriente* cuentas, int numCuentas);
Cliente* buscarCliente(int dniBuscado, Cliente* clientes, int numClientes);

#endif