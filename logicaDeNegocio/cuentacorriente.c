#include <stdio.h>
#include <stdlib.h>
#include "cuentacorriente.h"
#include "cliente.h"

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