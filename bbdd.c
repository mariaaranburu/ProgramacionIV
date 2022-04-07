#include <stdio.h>
#include "sqlite3.h"
#include "cliente.h"
#include <string.h>

void cuantosClientes(sqlite3 *db){
    sqlite3_stmt *stmt;

    char sql[] = "select count(*) from CLIENTE";
    int result = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
}

void cogerClientes (sqlite3 *db, Cliente *c){

}