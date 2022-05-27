#ifndef _BBDD_CPP_H_
#define _BBDD_CPP_H_
#include "sqlite3.h"
#include "../c++/usuario.h"
#include "../c++/cuentacorriente.h"
#include "../c++/transaccion.h"

int cuantosUsuarios(sqlite3 *db);

Usuario** devolverUsu(sqlite3* db);

int cuantasCC(sqlite3* db);

CuentaCorriente** listaCC(sqlite3* db);

int cuantasTransacciones(sqlite3* db);

Transaccion** listaTransacciones(sqlite3* db);


#endif