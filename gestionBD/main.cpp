#include "bbdd_cpp.h"
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "../c++/usuario_.h"
#include "../c++/cliente_.h"
#include "../c++/cuentacorriente_.h"
#include "sqlite3.h"

using namespace std;

int main(void)
{
    sqlite3 *db;
    //Abrir base de datos
	int result = sqlite3_open("bbdd.sqlite", &db);
    //CLIENTES
    int numClientes = cuantosUsuarios(db);
    cout<<numClientes<<endl;
    //Cliente* clientes = (Cliente*)malloc(MAX_CLIENTES*sizeof(Cliente));
    //clientes = cogerClientes(db);

};