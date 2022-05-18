#include <stdio.h>
#include <stdlib.h>
#include "bbdd.h"
#include <string.h>

//Devuelve el numero de acciones.
int cuantasAcciones(sqlite3 *db){
    
    sqlite3_stmt *stmt;
    char sql[] = "select count(*) from ACCION";
    int result = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if(result!=SQLITE_OK){
        printf("Error preparando la consulta.\n");
        printf("%s\n", sqlite3_errmsg(db));
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
        printf("Error finalizando la consulta.\n");
        printf("%s\n",sqlite3_errmsg(db));
        return result;
    }
    return numFilas;
}

//Saca la lista de acciones
Accion* listaAcciones(sqlite3* db, Cliente* clientes){
    sqlite3_stmt *stmt;
    char sql[] = "select * from ACCION";
    int result = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

    int numFilas = cuantasAcciones(db);
    Accion* acciones = (Accion*)malloc(numFilas*sizeof(Accion));
    Cliente* c = (Cliente*)malloc(sizeof(Cliente));
    int numClientes = cuantosClientes(db);
    int dni;
    int contador = 0;

    do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			acciones[contador].num_valor = sqlite3_column_int(stmt,0);
            acciones[contador].prec_actual = sqlite3_column_double(stmt,1);
            acciones[contador].prec_compra = sqlite3_column_double(stmt,2);
            int tamEmpresa = strlen((char*)sqlite3_column_text(stmt,3));
            acciones[contador].empresa = (char*)malloc((tamEmpresa+1)*sizeof(char));
            acciones[contador].empresa = strcpy(acciones[contador].empresa,(char*)sqlite3_column_text(stmt,3));
            dni = sqlite3_column_int(stmt,4);
            c = buscarCliente(dni,c,numClientes);
            contador++;
		}
	} while (result == SQLITE_ROW);
    
    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}
    return acciones;
}

//Devuelve el numero de clientes.
int cuantosClientes(sqlite3 *db){
    sqlite3_stmt *stmt;
    char sql[] = "select * from CLIENTE";
    int result = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if(result!=SQLITE_OK){
        printf("Error preparando la consulta.\n");
        printf("%s\n", sqlite3_errmsg(db));
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
        printf("Error finalizando la consulta.\n");
        printf("%s\n",sqlite3_errmsg(db));
        return result;
    }
    return numFilas;
}

//Devuelve la lista de clientes.
Cliente* cogerClientes (sqlite3 *db){
    sqlite3_stmt *stmt;
    char sql[] = "select * from CLIENTE";
    int result = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

    int numFilas = cuantosClientes(db);

    Cliente* lista = (Cliente*) malloc(numFilas*sizeof(Cliente));
    int contador = 0;

    do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			lista[contador].dni = sqlite3_column_int(stmt, 0);
            int tamNombre = strlen((char*)sqlite3_column_text(stmt,1));
            lista[contador].nombre = (char*)malloc((tamNombre+1)*sizeof(char));
			lista[contador].nombre = (lista[contador].nombre, (char *) sqlite3_column_text(stmt, 1));
            int tamFecNac = strlen((char*)sqlite3_column_text(stmt,2));
            lista[contador].fec_nac = (char*)malloc((tamFecNac+1)*sizeof(char));
            lista[contador].fec_nac = strcpy(lista[contador].fec_nac,(char*)sqlite3_column_text(stmt,2));
            int tamSexo = strlen((char*)sqlite3_column_text(stmt,3));
            lista[contador].sexo = (char*)malloc((tamSexo+1)*sizeof(char));
            lista[contador].sexo = strcpy(lista[contador].sexo,(char *) sqlite3_column_text(stmt, 3));
            int tamContra = strlen((char*)sqlite3_column_text(stmt, 4));
            lista[contador].contrasenya = (char*)malloc((tamContra+1)*sizeof(char));
            lista[contador].contrasenya = strcpy(lista[contador].contrasenya,(char *) sqlite3_column_text(stmt, 4));
            contador++;
		}
	} while (result == SQLITE_ROW);

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	return lista;

}

//Devuelve el numero de cuentas corrientes.
int cuantasCC(sqlite3 *db){
    sqlite3_stmt *stmt;
    char sql[] = "select count(*) from CUENTA_CORRIENTE";
    int result = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if(result!=SQLITE_OK){
        printf("Error preparando la consulta.\n");
        printf("%s\n", sqlite3_errmsg(db));
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
        printf("Error finalizando la consulta.\n");
        printf("%s\n",sqlite3_errmsg(db));
        return result;
    }
    return numFilas;
}

//Devuelve la lista de Cuentas Corrientes
CuentaCorriente* cogerCuentas (sqlite3 *db,Cliente* clientes){
    sqlite3_stmt *stmt;
    char sql[] = "select * from CUENTA_CORRIENTE";
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (result != SQLITE_OK){
        printf("Error preparing statemet (SELECT)\n");
        printf("%s\n", sqlite3_errmsg(db));
    }

    int numFilas = cuantasCC(db);
    
    CuentaCorriente* lista = (CuentaCorriente*)malloc(numFilas*sizeof(CuentaCorriente));
    int contador = 0;
    int dni;
    int numClientes = cuantosClientes(db);

    do {
        result = sqlite3_step(stmt);
        if (result == SQLITE_ROW){
            lista[contador].numero = sqlite3_column_int(stmt, 0);
            lista[contador].saldo = sqlite3_column_double(stmt, 1);
            lista[contador].cliente = (Cliente*)malloc(sizeof(Cliente));
            dni = sqlite3_column_int(stmt,2);
            lista[contador].cliente = buscarCliente(dni,clientes,numClientes);
            contador++;
        }
    } while (result == SQLITE_ROW);
    
    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK) {
        printf("Error finalizing statement (SELECT)\n");
        printf("%s\n", sqlite3_errmsg(db));
    }
    return lista;
}

//Devuelve el numero de tarjetas.
int cuantasTarjetas(sqlite3 *db){
    sqlite3_stmt *stmt;
    char sql[] = "select count(*) from TARJETAS";
    int result = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if(result!=SQLITE_OK){
        printf("Error preparando la consulta.\n");
        printf("%s\n", sqlite3_errmsg(db));
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
        printf("Error finalizando la consulta.\n");
        printf("%s\n",sqlite3_errmsg(db));
        return result;
    }
    return numFilas;
}

//Devuelve la lista de tarjetas
Tarjeta* listaTarjetas(sqlite3* db){
    sqlite3_stmt *stmt;
    char sql[] = "select * from TARJETA";
    int result = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

    int numFilas = cuantasTarjetas(db);
    Tarjeta* lista = (Tarjeta*) malloc(numFilas*sizeof(Tarjeta));
    int contador = 0;
    do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			lista[contador].num = sqlite3_column_int(stmt, 0);
            lista[contador].pin = sqlite3_column_int(stmt,1);
            lista[contador].limite = sqlite3_column_int(stmt,2);
            int tamTipo = strlen((char*)sqlite3_column_text(stmt, 3));
            lista[contador].tipo = (char*)malloc((tamTipo+1)*sizeof(char));
            lista[contador].tipo = strcpy(lista[contador].tipo,(char *) sqlite3_column_text(stmt, 3));
            lista[contador].numCC = sqlite3_column_int(stmt,4);
            contador++;
		}
	} while (result == SQLITE_ROW);

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}
	return lista;
}

//Devuelve el numero de titulares.
int cuantosTitulares(sqlite3 *db){
    sqlite3_stmt *stmt;
    char sql[] = "select count(*) from TITULARES";
    int result = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if(result!=SQLITE_OK){
        printf("Error preparando la consulta.\n");
        printf("%s\n", sqlite3_errmsg(db));
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
        printf("Error finalizando la consulta.\n");
        printf("%s\n",sqlite3_errmsg(db));
        return result;
    }
    return numFilas;
}



//Devuelve el numero de transacciones.
int cuantasTransacciones(sqlite3 *db){
    sqlite3_stmt *stmt;
    char sql[] = "select count(*) from TRANSACCIONES";
    int result = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if(result!=SQLITE_OK){
        printf("Error preparando la consulta.\n");
        printf("%s\n", sqlite3_errmsg(db));
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
        printf("Error finalizando la consulta.\n");
        printf("%s\n",sqlite3_errmsg(db));
        return result;
    }
    return numFilas;
}

//Devuelve la lista de transacciones
Transaccion* listaTransacciones(sqlite3* db,CuentaCorriente* cuentas, int numCuentas){
    sqlite3_stmt *stmt;
    char sql[] = "select * from TRANSACCIONES";
    int result = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

    int numFilas = cuantasTransacciones(db);
    Transaccion* lista = (Transaccion*)malloc(numFilas*sizeof(Transaccion));
    int numOrigen;
    
    int contador = 0;
    do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			lista[contador].num = sqlite3_column_int(stmt, 0);
            lista[contador].importe = sqlite3_column_double(stmt,1);
            int tamDesc = strlen((char*)sqlite3_column_text(stmt,2));
            lista[contador].descripcion = (char*)malloc((tamDesc+1)*sizeof(char));
            lista[contador].descripcion = strcpy(lista[contador].descripcion,(char*)sqlite3_column_text(stmt,3));
            lista[contador].origen = (CuentaCorriente*)malloc(sizeof(CuentaCorriente));
            numOrigen = sqlite3_column_int(stmt,4);
            lista[contador].origen = buscar(numOrigen,cuentas,numCuentas);
            int numDestino = sqlite3_column_int(stmt,5);
            lista[contador].destino = (CuentaCorriente*)malloc(sizeof(CuentaCorriente));
            lista[contador].destino = buscar(numDestino,cuentas,numCuentas);
            contador++;
		}
	} while (result == SQLITE_ROW);

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}
	return lista;
}

//Devuelve el numero de acciones.
int cuentasAcciones(sqlite3 *db){
    sqlite3_stmt *stmt;
    char sql[] = "select count(*) from ACCIONE";
    int result = sqlite3_prepare_v2(db,sql,-1,&stmt,NULL);
    if(result!=SQLITE_OK){
        printf("Error preparando la consulta.\n");
        printf("%s\n", sqlite3_errmsg(db));
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
        printf("Error finalizando la consulta.\n");
        printf("%s\n",sqlite3_errmsg(db));
        return result;
    }
    return numFilas;
}

//Devuelve la lista de acciones.
Accion* cogerAccion (sqlite3 *db){
    sqlite3_stmt *stmt;
    char sql[] = "select * from ACCIONES";
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (result != SQLITE_OK){
        printf("Error preparing statemet (SELECT)\n");
        printf("%s\n", sqlite3_errmsg(db));
    }

    int numFilas = cuantasAcciones(db);
    
    Accion* lista = (Accion*)malloc(numFilas*sizeof(Accion));
    int contador = 0;

    do {
        result = sqlite3_step(stmt);
        if (result == SQLITE_ROW){
            lista[contador].num_valor = sqlite3_column_int(stmt, 0);
            lista[contador].prec_actual = sqlite3_column_double(stmt, 1);
            lista[contador].prec_compra = sqlite3_column_double(stmt, 2);
            int tamNomEmpresa = strlen((char*)sqlite3_column_text(stmt,3));
            lista[contador].empresa = (char*)malloc((tamNomEmpresa+1)*sizeof(char));
			lista[contador].empresa = (lista[contador].empresa, (char *) sqlite3_column_text(stmt, 3));
            lista[contador].dni_cliente = sqlite3_column_int(stmt, 4);
        }
    } while (result == SQLITE_ROW);
    
    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK) {
        printf("Error finalizing statement (SELECT)\n");
        printf("%s\n", sqlite3_errmsg(db));
    }
    return lista; 
}

CuentaCorriente* buscar(int numCC, CuentaCorriente* cuentas, int numCuentas){
    CuentaCorriente* c = (CuentaCorriente*)malloc(sizeof(CuentaCorriente));
    for(int i=0; i<numCuentas;i++){
        if(cuentas[i].numero == numCC){
            c->numero = cuentas[i].numero;
            c->saldo = cuentas[i].saldo;
            (*c).cliente = (Cliente*)malloc(sizeof(Cliente));
            (*c).cliente = cuentas[i].cliente;
            }
        }
    return c;
}

Cliente* buscarCliente(int dniBuscado, Cliente* clientes, int numClientes){
    Cliente* d = (Cliente*)malloc(sizeof(Cliente));
    for(int i=0; i<numClientes;i++){
        if(clientes[i].dni==dniBuscado){
            d->dni = clientes[i].dni;
            int tamNombre = strlen(clientes[i].nombre);
            d->nombre = (char*)malloc((tamNombre+1)*sizeof(char));
            d->nombre = strcpy(d->nombre,clientes[i].nombre);
            int tamFecNac = strlen(clientes[i].fec_nac);
            d->fec_nac = (char*)malloc((tamFecNac+1)*sizeof(char));
            d->fec_nac = strcpy(d->fec_nac,clientes[i].fec_nac);
            int tamSexo = strlen(clientes[i].sexo);
            d->sexo = (char*)malloc((tamSexo+1)*sizeof(char));
            d->sexo = strcpy(d->sexo,clientes[i].sexo);
            int tamContra = strlen(clientes[i].contrasenya);
            d->contrasenya = (char*)malloc((tamContra+1)*sizeof(char));
            d->contrasenya = strcpy(d->contrasenya,clientes[i].contrasenya);
            break;
        }
    }
    return d;
} 