#include "bbdd_cpp.h"
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "bbdd_cpp.h"
#include "../c++/usuario_.h"
#include "../c++/cliente_.h"
#include "../c++/administrador_.h"
#include "../c++/cuentacorriente_.h"


using namespace std;

//FUNCION INSTANCEOF
template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
   return dynamic_cast<const Base*>(ptr) != nullptr;
}

int main(void)
{
    sqlite3 *db;
    //Abrir base de datos
	int result = sqlite3_open("bbdd.sqlite", &db);
    //CLIENTES
    int numUsuarios = cuantosUsuarios(db);
    cout<<numUsuarios<<endl;

    Usuario** usuarios = new Usuario*[numUsuarios];
    usuarios = listaUsuariosf(db);

    Cliente** clientes = new Cliente*[numUsuarios];
    int contClientes = 0;
    Administrador** admins= new Administrador*[numUsuarios];
    int contAdmin = 0;
    
    for(int i=0; i<numUsuarios; i++){
        if(instanceof<Cliente>(usuarios[i])) {
            clientes[contClientes] = (Cliente*)usuarios[i];
            cout<<i<<endl;
        }else{
            admins[contAdmin] = (Administrador*)usuarios[i];
            cout<<"Un admin"<<endl;
        }
    }

    cout<<admins[0]->getNombre()<<endl;

    int numCuentas = cuantasCC(db);
    CuentaCorriente** cuentas = new CuentaCorriente*[numCuentas];
    cuentas = listaCC(db);
    
    cout<<cuentas[2]->getSaldo()<<endl;

    int numTransacciones = cuantasTransacciones(db);
    Transaccion** lista = new Transaccion*[numTransacciones];
    //lista = listaTransacciones(db);

    cout<<"El numero de transacciones son: "<<numTransacciones<<endl;



    int insertar;
    insertar = insertarTransaccion(db, 20, 7684, "movil", 5, 12);
    
    /*Cliente* cliente = new Cliente(); 
    cliente = (Cliente*)usuarios[0];
    cout<<cliente->getFec_nac();
    cout<<usuarios[7]->getNombre();*/
   
    //Cliente* clientes = (Cliente*)malloc(MAX_CLIENTES*sizeof(Cliente));
    //clientes = cogerClientes(db);

    //Cliente* cliente = new Cliente(1234,"Maria","12/23/13",'f',"12455d");

}