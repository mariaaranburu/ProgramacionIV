#ifndef _BBDD_CPP_H_
#define _BBDD_CPP_H_
#pragma once
#include "../c++/usuario_.h"
#include "sqlite3.h"
#include "../c++/cliente_.h"
#include "../c++/cuentacorriente_.h"
#include "../c++/administrador_.h"
#include "../c++/transaccion_.h"

Cliente* cogerCliente(Cliente** lista, int dni, sqlite3* db);
CuentaCorriente* cogerCCxDNI(CuentaCorriente** lista, int dni, sqlite3* db);

Administrador* cogerAdministrador(Administrador** lista, int dni, sqlite3* db);

CuentaCorriente* cogerCC(CuentaCorriente** lista, int num, sqlite3* db);

int cuantosUsuarios(sqlite3 *db);

Usuario** listaUsuariosf(sqlite3* db);

int cuantasCC(sqlite3* db);

CuentaCorriente** listaCC(sqlite3* db);

int cuantasTransacciones(sqlite3* db);

Transaccion** listaTransacciones(sqlite3* db);

int insertarCliente(sqlite3* db, int dni, char* nombre, char* fec_nac, char* sexo, char* contrasenya);

int insertarTarjeta(sqlite3* db, int num, int pin, int limite, char* tipo, int numCC);

int insertarTransaccion(sqlite3* db, int num, float importe, char* descripcion, int numD, int numO);

Administrador** deUsuariosAAdmin(Usuario** usuarios, int numUsuarios);

Cliente** deUsuariosAClientes(Usuario** usuarios, int numUsuarios);


#endif