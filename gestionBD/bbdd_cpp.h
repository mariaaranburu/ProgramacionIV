#ifndef _BBDD_CPP_H_
#define _BBDD_CPP_H_
#include "sqlite3.h"
#include "../c++/usuario.h"
#include "../c++/cuentacorriente.h"
//#include "../c++/transaccion.h"

int cuantosUsuarios(sqlite3 *db);

<<<<<<< HEAD
Usuario** listaUsuariosf(sqlite3* db);
=======
Usuario** listaUsuarios(sqlite3* db);
>>>>>>> d2d70c494431e15c16c79bd05c447df48fa6b033

int cuantasCC(sqlite3* db);

CuentaCorriente** listaCC(sqlite3* db);

int cuantasTransacciones(sqlite3* db);

//Transaccion** listaTransacciones(sqlite3* db);


#endif