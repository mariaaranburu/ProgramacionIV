
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "../c++/usuario_.h"
#include "../c++/cliente_.h"
#include "../c++/administrador_.h"

using namespace std;

int cuantosUsuarios(sqlite3 *db);

Usuario** listaUsuariosf(sqlite3* db);

int cuantasCC(sqlite3* db);

//CuentaCorriente** listaCC(sqlite3* db);

int cuantasTransacciones(sqlite3* db);

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
        cout<<"Error finalizando la consulta."<<endl;
        cout<<(sqlite3_errmsg(db))<<endl;
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
            if (sqlite3_column_int(stmt, 0)==0000) {
                int tamNombre = strlen((char*)sqlite3_column_text(stmt, 1));
                char* nombre = new char[tamNombre+1];
                nombre = (char*)sqlite3_column_text(stmt, 1);
                int tamContrasenya = strlen((char*)sqlite3_column_text(stmt, 4));
                char* contrasenya = new char[tamContrasenya+1];
                contrasenya = (char*)sqlite3_column_text(stmt, 4);

                Administrador* admin = new Administrador(nombre, contrasenya);
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

//CuentaCorriente** listaCC(sqlite3* db)

int cuantasTransacciones(sqlite3* db)
{

}

//Transaccion** listaTransacciones(sqlite3* db)
//{

//}


