#include "bbdd_cpp.h"
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "../c++/usuario_.h"
#include "../c++/cliente_.h"
#include "../c++/cuentacorriente_.h"

using namespace std;

int main(void)
{
    sqlite3 *db;
    //Abrir base de datos
	int result = sqlite3_open("bbdd.sqlite", &db);
    //CLIENTES
    int numClientes = cuantosUsuarios(db);
    cout<<numClientes<<endl;

    Usuario** usuarios = new Usuario*[numClientes];
    usuarios = listaUsuariosf(db);
    Cliente* cliente = (Cliente*)usuarios[0]; 
    cout<<cliente->getFec_nac();
    cout<<usuarios[7]->getNombre();
    //Cliente* clientes = (Cliente*)malloc(MAX_CLIENTES*sizeof(Cliente));
    //clientes = cogerClientes(db);

    Cliente* cliente = new Cliente(1234,"Maria","12/23/13",'f',"12455d");

}