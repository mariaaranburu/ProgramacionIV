#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "transaccion.h"
#include "cuentacorriente.h"
#include "tarjeta.h"
#define TAM_MAX 20

int iniciarSesion(Cliente* c,int max){
    //Puede acceder 0, resto no entra
    int entra;
    int dni;
    char contra[TAM_MAX];
    char str[15];
    printf("INICIO DE SESION\n");
    printf("-----------------------\n");
    printf("Inserta tu DNI (sin letra):  ");
    fgets(str,15,stdin);
    sscanf(str,"%d",&dni);
    fflush(stdin);
    printf("\n");
    printf("Inserta tu contrasenya: ");
    scanf("%s",contra);
    fflush(stdin);
    printf("\n");

    //Comprobacion
    for(int i=0;i<max;i++){
        if(dni==c[i].dni){
            if(strcmp(contra,c[i].contrasenya)==0){
                return 0;
            }
        } 
    }
    return 1;
}

char imprimirMenu(void) {
    char r;
    printf("Elige una opcion: \n");
    printf("1. Ver mi cuenta corriente\n");
    printf("2. Ver mis tarjetas\n");
    printf("3. Ver mis acciones\n");
    printf("4. Ver mi perfil\n");
    printf("'q' para salir\n");
    printf("Que quieres hacer? ");
    scanf("%c",&r);
    fflush(stdin);
    return r;
}

char miCuentaCorriente(void) {
    char r;
    printf("Elige una opcion: \n");
    printf("1.Consultar saldo\n");
    printf("2. Consultar historial\n");
    printf("3. Hacer transferencias\n");
    scanf("%c",&r);
    fflush(stdin);
    return r;
}

//Opcion 1 de miCuentaCorriente
void consultarSaldo(CuentaCorriente cuenta){
    printf("El saldo es: %f",cuenta.saldo);
}

//Opcion 2 de miCuentaCorriente
void consultarHistoria(CuentaCorriente cuenta, Transaccion* transacciones,int numTransacciones){
    for(int i=0;i<numTransacciones;i++){
        int numDestino = transacciones[i].destino->numero;
        int numOrigen = transacciones[i].origen->numero;
        if(cuenta.numero == (numDestino || numOrigen)){
            imprimirTransaccion(transacciones[i]);
        }
    }
}

//Opcion 3 de miCuentaCorriente
void nuevaTransferencia(CuentaCorriente miCuentaCorriente, CuentaCorriente* listaCuentas, int numeroCuentas){
    Transaccion nuevaTransaccion;
    int num;
    float importe;
    char* descripcion;
    int numDestino;
    CuentaCorriente cuentaDestino;
    printf("Cuenta de destino: \n");
    scanf("%i",&numDestino);
    fflush(stdin);
    printf("Importe: \n");
    scanf("%f", importe);
    fflush(stdin);
    printf("Descripcion: \n");
    scanf("%s", descripcion);
    fflush(stdin);
    nuevaTransaccion.num = rand() %11 + 100000000;
    nuevaTransaccion.origen = 
    nuevaTransaccion.destino =
    nuevaTransaccion.descripcion = descripcion;
    nuevaTransaccion.importe = importe;
    void accederASaldoCuentas(listaCuentas, numeroCuentas, numDestino, importe, 's');
    void accederASaldoCuentas(listaCuentas, numeroCuentas, miCuentaCorriente.numero, importe, 'r');
}

void misTarjetas(void){
    printf("Elige una opcion: \n");
    printf("1. Administrar tarjetas\n");
    printf("2. Nueva tarjeta\n");
}

//Opcion 1 misTarjetas
void misTarjetas(Tarjeta* t, int numTarjetas){
    for(int i=0;i<numTarjetas;i++){
        imprimirTarjeta(t[i]);
    }
}

//Opcion 2 misTarjetas
Tarjeta introducirDatos(void){
    
}

void misAcciones(void){
    printf("Elige una opcion\n");
    printf("1. Consultar acciones\n");
    printf("2. Comprar nuevas acciones\n");
}

void miPerfil(Cliente c){
    char r;
    printf("DNI: %i\n",c.dni);
    printf("Nombre: %s\n",c.nombre);
    printf("Fecha nacimiento: %s\n",c.fec_nac);
    printf("Sexo: %s\n",c.sexo);
    printf("Contrasenya: %s\n",c.contrasenya);
    printf("Modificar los datos (s/n) ");
    scanf("%c",&r);
    fflush(stdin);
    if(r == 's'){
        //Metodo modificar datos
    }
}

