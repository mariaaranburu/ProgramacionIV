
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "../c++/usuario_.h"
#include "../c++/cliente_.h"
#include "../c++/administrador_.h"
#include "../c++/cuentacorriente_.h"
#include "../c++/transaccion_.h"
#include "bbdd_cpp.h"
using namespace std;

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
   return dynamic_cast<const Base*>(ptr) != nullptr;
}

Cliente* cogerCliente(Cliente** lista, int dni, sqlite3* db)
{
    Cliente* cliente = new Cliente();
    for (int i; i<cuantosUsuarios(db); i++){
        if ((lista[i]->getDni())==dni){
            cliente = lista[i];
        }
    }
    return cliente;
}

Administrador* cogerAdministrador(Administrador** lista, int dni, sqlite3* db)
{
    Administrador* admin = new Administrador();
    for (int i; i<cuantosUsuarios(db); i++){
        if ((lista[i]->getDni())==dni){
            admin = lista[i];
        }
    }
    return admin;
}

CuentaCorriente* cogerCC(CuentaCorriente** lista, int num, sqlite3* db)
{
    CuentaCorriente* cc = new CuentaCorriente();
    for (int i; i<cuantasTransacciones(db); i++){
        if ((lista[i]->getNumero())==num){
            cc = lista[i];
        }
    }
    return cc;
}

CuentaCorriente* cogerCCxDNI(CuentaCorriente** lista, int dni, sqlite3* db)
{
    CuentaCorriente* cc = new CuentaCorriente();
    for (int i; i<cuantasCC(db); i++){
        if ((lista[i]->getCliente()->getDni())==dni){
            cc = lista[i];
        }
    }
    return cc;
}

int cuantosUsuarios(sqlite3* db){
    sqlite3_stmt *stmt;
    char sql[] = "select * from CLIENTE";
    int result = sqlite3_prepare_v2(db,sql,strlen(sql)+1,&stmt,NULL);

    if(result!=SQLITE_OK){
        cout<<"Error preparando la consulta"<<endl;
        cout<<(sqlite3_errmsg(db))<<endl;
        return result;
    }
    int numFilas = 0;
    do{
        result = sqlite3_step(stmt);
        if(result == SQLITE_ROW){
            numFilas++;
        }
    } while(result == SQLITE_ROW);

    result = sqlite3_finalize(stmt);
    if(result != SQLITE_OK){
        cout <<"Error finalizando la consulta."<<endl;
        cout <<(sqlite3_errmsg(db))<<endl;
        return result;
    }
    return numFilas;
}

Usuario** listaUsuariosf(sqlite3* db)
{
    sqlite3_stmt* stmt;
    char sql[] = "select * from CLIENTE";
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (result != SQLITE_OK)
    {
        cout<<"Error preparing statement (SELECT)"<<endl;
        cout<<sqlite3_errmsg16(db);
    }

    int numFilas = cuantosUsuarios(db);

    Usuario** lista = new Usuario*[numFilas];
    int contador = 0;

    do {
        result = sqlite3_step(stmt);
        if (result == SQLITE_ROW) {
            if (sqlite3_column_int(stmt, 0)==1111) {
                int dni = (int)sqlite3_column_int(stmt, 1);
                int tamContrasenya = strlen((char*)sqlite3_column_text(stmt, 4));
                char* contrasenya = new char[tamContrasenya+1];
                contrasenya = (char*)sqlite3_column_text(stmt, 4);

                Administrador* admin = new Administrador(dni, contrasenya);
                lista[contador] = admin;
                contador++;
            } else {
                int dni = sqlite3_column_int(stmt, 0);
                int tamNombre = strlen((char*)sqlite3_column_text(stmt, 1));
                char* nombre = new char[tamNombre+1];
                nombre = (char*)sqlite3_column_text(stmt, 1);
                int tamFec_nac = strlen((char*)sqlite3_column_text(stmt, 2));
                char* fec_nac = new char[tamFec_nac+1];
                fec_nac = (char*)sqlite3_column_text(stmt, 2);
                int tamSexo = strlen((char*)sqlite3_column_text(stmt, 3));
                char* sexoS = new char[tamSexo+1];
                sexoS = (char*)sqlite3_column_text(stmt, 3);
                char sexo = sexoS[0];
                int tamContrasenya = strlen((char*)sqlite3_column_text(stmt, 4));
                char* contrasenya = new char[tamContrasenya+1];
                contrasenya = (char*)sqlite3_column_text(stmt, 4);

                Cliente* cliente = new Cliente(dni, nombre, fec_nac, sexo, contrasenya);
                lista[contador] = cliente;
                contador++;
            }
        }
    } while (result == SQLITE_ROW);

    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK) {
        cout<< "Error finalizing statement (SELECT)" <<endl;
        cout<< sqlite3_errmsg(db);
    }
    return lista;
}

int cuantasCC(sqlite3* db)
{
    sqlite3_stmt *stmt;
    char* sql = new char[60];
    sql = "select * from CUENTA_CORRIENTE";
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if(result!=SQLITE_OK){
        cout<<"Error preparando la consulta."<<endl;
        cout<<sqlite3_errmsg(db);
        return result;
    }
    int numFilas = 0;
    do{
        result = sqlite3_step(stmt);
        if (result == SQLITE_ROW){
            numFilas++;
        }
    } while (result == SQLITE_ROW);

    result = sqlite3_finalize(stmt);
    if(result != SQLITE_OK){
        cout<<"Error finalizando la consulta."<<endl;
        cout<<sqlite3_errmsg(db);
        return result;
    }
    return numFilas;
}

CuentaCorriente** listaCC(sqlite3* db)
{
    sqlite3_stmt* stmt;
    char sql[] = "select * from CUENTA_CORRIENTE";
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if(result != SQLITE_OK)
    {
        cout<<"Error preparing statement (SELECT)"<<endl;
        cout<<sqlite3_errmsg16(db);
    }

    int numFilas = cuantasCC(db);

    CuentaCorriente** lista = new CuentaCorriente*[numFilas];
    int contador = 0;

    do {
        result = sqlite3_step(stmt);
        if (result == SQLITE_ROW) {
            int numero = sqlite3_column_int(stmt, 0);
            float saldo = sqlite3_column_double(stmt, 1);
            int dni = sqlite3_column_int(stmt, 3);

            CuentaCorriente* cuenta = new CuentaCorriente(numero, saldo, cogerCliente(deUsuariosAClientes(listaUsuariosf(db), cuantosUsuarios(db)), dni, db));
            lista[contador] = cuenta;
            contador++;
        }
    } while (result == SQLITE_ROW);

    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK){
        cout<<"Error finalizing statement (SELECT)"<<endl;
        cout<<sqlite3_errmsg(db);
    }
    return lista;
}

int cuantasTransacciones(sqlite3* db)
{
    sqlite3_stmt *stmt;
    char* sql = new char[60];
    sql = "select * from TRANSACCIONES";
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if(result!=SQLITE_OK){
        cout<<"Error preparando la consulta."<<endl;
        cout<<sqlite3_errmsg(db);
        return result;
    }
    int numFilas = 0;
    do{
        result = sqlite3_step(stmt);
        if (result == SQLITE_ROW){
            numFilas++;
        }
    } while (result == SQLITE_ROW);

    result = sqlite3_finalize(stmt);
    if(result != SQLITE_OK){
        cout<<"Error finalizando la consulta."<<endl;
        cout<<sqlite3_errmsg(db);
        return result;
    }
    return numFilas;
}

Transaccion** listaTransacciones(sqlite3* db)
{
    sqlite3_stmt* stmt;
    char sql[] = "select * from TRANSACCIONES";
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if(result != SQLITE_OK)
    {
        cout<<"Error preparing statement (SELECT)"<<endl;
        cout<<sqlite3_errmsg16(db);
    }

    int numFilas = cuantasTransacciones(db);

    Transaccion** lista = new Transaccion*[numFilas];
    int contador = 0;

    do {
        result = sqlite3_step(stmt);
        if (result == SQLITE_ROW) {
            int num = sqlite3_column_int(stmt, 0);
            float saldo = sqlite3_column_double(stmt, 1);
            int tamDescripcion = strlen((char*)sqlite3_column_text(stmt, 2));
            char* descripcion = new char[tamDescripcion+1];
            descripcion = (char*)sqlite3_column_text(stmt, 2);
            int destino = sqlite3_column_int(stmt, 3);
            int origen = sqlite3_column_int(stmt, 4);

            Transaccion* transaccion = new Transaccion(num, saldo, descripcion, cogerCC(listaCC(db), origen, db), cogerCC(listaCC(db), destino, db));
            lista[contador] = transaccion;
            contador++;
        }
    } while (result == SQLITE_ROW);

    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK){
        cout<<"Error finalizing statement (SELECT)"<<endl;
        cout<<sqlite3_errmsg(db);
    }
    return lista;
}

int insertarCliente(sqlite3* db, int dni, char* nombre, char* fec_nac, char* sexo, char* contrasenya)
{
    sqlite3_stmt *stmt;
    char sql[] = "INSERT INTO CLIENTE (dni, nombre, fec_nac, sexo, contrasenya) values (?,?,?,?,?)";

    int result = sqlite3_prepare_v2(db, sql, strlen(sql)+1, &stmt, NULL);
    if (result != SQLITE_OK){
        cout<<"Error preparing statement (INSERT)"<<endl;
        cout<<sqlite3_errmsg(db);
        return 0;
    }

    cout<<"SQL query prepared (INSERT)"<<endl;

    result = sqlite3_bind_int(stmt, 1, dni);
    if(result != SQLITE_OK)
    {
        cout<<"Error binding parameters1"<<endl;
        cout<<sqlite3_errmsg(db);
        return 0;
    }

    result = sqlite3_bind_text(stmt, 2, nombre, strlen(nombre), SQLITE_STATIC);
    if(result != SQLITE_OK)
    {
        cout<<"Error binding parameters2"<<endl;
        cout<<sqlite3_errmsg(db);
        return 0;
    }

    result = sqlite3_bind_text(stmt, 3, fec_nac, strlen(fec_nac), SQLITE_STATIC);
    if(result != SQLITE_OK)
    {
        cout<<"Error binding parameters3"<<endl;
        cout<<sqlite3_errmsg(db);
        return 0;
    }

    result = sqlite3_bind_text(stmt, 4, sexo, strlen(sexo), SQLITE_STATIC);
    if(result != SQLITE_OK)
    {
        cout<<"Error binding parameters4"<<endl;
        cout<<sqlite3_errmsg(db);
        return 0;
    }

    result = sqlite3_bind_text(stmt, 5, contrasenya, strlen(contrasenya), SQLITE_STATIC);
    if(result != SQLITE_OK)
    {
        cout<<"Error binding parameters5"<<endl;
        cout<<sqlite3_errmsg(db);
        return 0;
    }

    result = sqlite3_step(stmt);
    if(result != SQLITE_DONE){
        cout<<"Error inserting new data into CLIENTE table"<<endl;
        return 0;
    }

    result = sqlite3_finalize(stmt);
    if(result != SQLITE_OK){
        cout<<"Error finalizing statement (INSERT)"<<endl;
        cout<<sqlite3_errmsg(db);
        return 0; 
    }

    cout<<"Prepared statement finalized (INSERT)"<<endl;

    return 1;
}

int insertarTarjeta(sqlite3* db, int num, int pin, int limite, char* tipo, int numCC)
{
    sqlite3_stmt *stmt;
    char sql[] = "INSERT INTO TARJETA (num, pin, limite, tipo, num_CC) values (?,?,?,?,?)";

    int result = sqlite3_prepare_v2(db, sql, strlen(sql)+1, &stmt, NULL);
    if (result != SQLITE_OK){
        cout<<"Error preparing statement (INSERT)"<<endl;
        cout<<sqlite3_errmsg(db);
        return 0;
    }

    cout<<"SQL query prepared (INSERT)"<<endl;

    result = sqlite3_bind_int(stmt, 1, num);
    if(result != SQLITE_OK)
    {
        cout<<"Error binding parameters1"<<endl;
        cout<<sqlite3_errmsg(db);
        return 0;
    }

    result = sqlite3_bind_int(stmt, 2, pin);
    if(result != SQLITE_OK)
    {
        cout<<"Error binding parameters2"<<endl;
        cout<<sqlite3_errmsg(db);
        return 0;
    }

    result = sqlite3_bind_int(stmt, 3, limite);
    if(result != SQLITE_OK)
    {
        cout<<"Error binding parameters3"<<endl;
        cout<<sqlite3_errmsg(db);
        return 0;
    }

    result = sqlite3_bind_text(stmt, 4, tipo, strlen(tipo), SQLITE_STATIC);
    if(result != SQLITE_OK)
    {
        cout<<"Error binding parameters4"<<endl;
        cout<<sqlite3_errmsg(db);
        return 0;
    }

    result = sqlite3_bind_int(stmt, 5, numCC);
    if(result != SQLITE_OK)
    {
        cout<<"Error binding parameters5"<<endl;
        cout<<sqlite3_errmsg(db);
        return 0;
    }

    result = sqlite3_step(stmt);
    if(result != SQLITE_DONE){
        cout<<"Error inserting new data into TRANSACCION table"<<endl;
        return 0;
    }

    result = sqlite3_finalize(stmt);
    if(result != SQLITE_OK){
        cout<<"Error finalizing statement (INSERT)"<<endl;
        cout<<sqlite3_errmsg(db);
        return 0; 
    }

    cout<<"Prepared statement finalized (INSERT)"<<endl;

    return 1;
}

int insertarTransaccion(sqlite3* db, int num, float importe, char* descripcion, int numD, int numO)
{
    sqlite3_stmt *stmt;
    char sql[] = "INSERT INTO TRANSACCIONES (num, importe, desc, num_cc_d, num_cc_o) values (?,?,?,?,?)";

    int result = sqlite3_prepare_v2(db, sql, strlen(sql)+1, &stmt, NULL);
    if (result != SQLITE_OK){
        cout<<"Error preparing statement (INSERT)"<<endl;
        cout<<sqlite3_errmsg(db);
        return 0;
    }

    cout<<"SQL query prepared (INSERT)"<<endl;

    result = sqlite3_bind_int(stmt, 1, num);
    if(result != SQLITE_OK)
    {
        cout<<"Error binding parameters1"<<endl;
        cout<<sqlite3_errmsg(db);
        return 0;
    }

    result = sqlite3_bind_double(stmt, 2, importe);
    if(result != SQLITE_OK)
    {
        cout<<"Error binding parameters2"<<endl;
        cout<<sqlite3_errmsg(db);
        return 0;
    }

    result = sqlite3_bind_text(stmt, 3, descripcion, strlen(descripcion), SQLITE_STATIC);
    if(result != SQLITE_OK)
    {
        cout<<"Error binding parameters3"<<endl;
        cout<<sqlite3_errmsg(db);
        return 0;
    }

    result = sqlite3_bind_int(stmt, 4, numD);
    if(result != SQLITE_OK)
    {
        cout<<"Error binding parameters4"<<endl;
        cout<<sqlite3_errmsg(db);
        return 0;
    }

    result = sqlite3_bind_int(stmt, 5, numO);
    if(result != SQLITE_OK)
    {
        cout<<"Error binding parameters5"<<endl;
        cout<<sqlite3_errmsg(db);
        return 0;
    }

    result = sqlite3_step(stmt);
    if(result != SQLITE_DONE){
        cout<<"Error inserting new data into TRANSACCION table"<<endl;
        return 0;
    }

    result = sqlite3_finalize(stmt);
    if(result != SQLITE_OK){
        cout<<"Error finalizing statement (INSERT)"<<endl;
        cout<<sqlite3_errmsg(db);
        return 0; 
    }

    cout<<"Prepared statement finalized (INSERT)"<<endl;

    return 1;
}

Cliente** deUsuariosAClientes(Usuario** usuarios, int numUsuarios){
    Cliente** clientes = new Cliente*[numUsuarios];
    int contClientes = 0;

    for(int i=0; i<numUsuarios; i++){
        if(instanceof<Cliente>(usuarios[i])){
            clientes[contClientes] = (Cliente*)usuarios[i];
        }
    }
    return clientes;
}

Administrador** deUsuariosAAdmin(Usuario** usuarios, int numUsuarios){
    Administrador** admin = new Administrador*[numUsuarios];
    int contAdmin = 0;

    for(int i=0; i<numUsuarios; i++){
        if(instanceof<Cliente>(usuarios[i])){
            admin[contAdmin] = (Administrador*)usuarios[i];
        }
    }
    return admin;
}


