#ifndef _BBDD_CPP_H_
#define _BBDD_CPP_H_
#pragma once
#include "sqlite3.h"
#include "../c++/usuario_.h"
#include "../c++/cliente_.h"
#include "../c++/cuentacorriente_.h"
//#include "../c++/transaccion.h"
#include "sqlite3.h"

int cuantosUsuarios(sqlite3 *db);

Usuario** listaUsuariosf(sqlite3* db);

int cuantasCC(sqlite3* db);

CuentaCorriente** listaCC(sqlite3* db);

int cuantasTransacciones(sqlite3* db);

//Transaccion** listaTransacciones(sqlite3* db);


#endif