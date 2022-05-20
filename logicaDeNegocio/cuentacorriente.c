#include <stdio.h>
#include <stdlib.h>
#include "cuentacorriente.h"
#include "cliente.h"
#define NUM_MAX_CC 15

void imprimirCuenta(CuentaCorriente *c) {
    printf("Mi cuenta: [Numero de cuenta: %i, Saldo: %.2f, Cliente: [Nombre: %s]]", c->numero, c->saldo, c->cliente->nombre);
}

CuentaCorriente cogerCuenta(CuentaCorriente* listadoCuentas, int numeroCuentas, int numeroCuenta){
    CuentaCorriente cuentaSeleccionada;
    for(int i; i<numeroCuentas; i++){
        if(listadoCuentas[i].numero==numeroCuenta)
        cuentaSeleccionada = listadoCuentas[i];
    }
    return cuentaSeleccionada;
}

void accederASaldoCuenta(CuentaCorriente* listadoCuentas, int numeroCuentas, int numeroCuenta, float modificacion, char tipo){
    CuentaCorriente cuentaSeleccionada = cogerCuenta(listadoCuentas, numeroCuentas, numeroCuenta);
    if(tipo=='s'){
        cuentaSeleccionada.saldo = cuentaSeleccionada.saldo + modificacion;
    }else{
        cuentaSeleccionada.saldo = cuentaSeleccionada.saldo - modificacion;
    }
}


CuentaCorriente* buscarCC(int numCC, CuentaCorriente* cuentas, int numCuentas){
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

CuentaCorriente* buscarCC_Cliente(int dni, int numCuentas, CuentaCorriente* cuentas){
    CuentaCorriente* c = (CuentaCorriente*)malloc(NUM_MAX_CC*sizeof(CuentaCorriente));
    int contador = 0;
    for(int i=0; i<numCuentas;i++){
        if(cuentas[i].cliente->dni == dni){
            c[contador].numero = cuentas[i].numero;
            c[contador].saldo = cuentas[i].saldo;
            c[contador].cliente->dni= dni;
            int tamNombre = strlen(cuentas[i].cliente->nombre);
            c[contador].cliente->nombre = (char*)malloc((tamNombre+1)*sizeof(char));
            c[contador].cliente->nombre = strcpy(c[contador].cliente->nombre,cuentas[i].cliente->nombre);
            int tamFecNac = strlen(cuentas[i].cliente->fec_nac);
            c[contador].cliente->fec_nac = (char*)malloc((tamFecNac+1)*sizeof(char));
            c[contador].cliente->fec_nac = strcpy(c[contador].cliente->fec_nac,cuentas[i].cliente->fec_nac);
            int tamSexo = strlen(cuentas[i].cliente->sexo);
            c[contador].cliente->sexo = (char*)malloc((tamSexo+1)*sizeof(char));
            c[contador].cliente->sexo = strcpy(c[contador].cliente->sexo,cuentas[i].cliente->sexo);
            int tamContra = strlen(cuentas[i].cliente->contrasenya);
            c[contador].cliente->contrasenya = (char*)malloc((tamContra+1)*sizeof(char));
            c[contador].cliente->contrasenya = strcpy(c[contador].cliente->contrasenya,cuentas[i].cliente->contrasenya);
            contador++;
            printf("B1");
        }else{
            continue;
        }
        printf("B2");
    }
    printf("B3");
    return c;
}

//Busca cuantas CC tiene una persona concreta.
int cuentasCC_dni (int dni, int numCuentas, CuentaCorriente* cuentas){
    int contador = 0;
    for(int i=0; i<numCuentas; i++){
        if(cuentas[i].cliente->dni == dni){
            contador++;
        }
    }
    return contador;
}
