#include <stdio.h>
#include <string.h>
#include "menu.h"


#define TAM_MAX 20

int iniciarSesion(Cliente* c,int max){
    //Puede acceder 0, resto no entra
    int entra;
    int dni;
    char contra[TAM_MAX];
    char str[15];
    printf("\n");
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

void imprimirMenu(CuentaCorriente c, Transaccion* transacciones,int numTrans,Tarjeta* tarjetas, int numTarj) {
    char r;
    printf("Elige una opcion: \n");
    printf("1. Ver mi cuenta corriente\n");
    printf("2. Ver mis tarjetas\n");
    printf("3. Ver mis acciones\n");
    printf("4. Ver mi perfil\n");
    printf("'q' para salir\n");
    printf("-----------------------------\n");
    printf("Que quieres hacer? \n");
    scanf("%c",&r);
    fflush(stdin);
    switch (r)
        {
            case '1':
                miCuentaCorriente(c,transacciones,numTrans);
                break;
            case '2':
                misTarjetas(tarjetas, numTarj);
                break;
            case '3':
                /* code */
                printf("Caso 3\n");
                break;
            case '4':
                /* code */
                printf("Caso 4\n");
                break;
            case 'q':
                /* code */
                printf("Caso q\n");
                break;
        
        } 
}

void miCuentaCorriente(CuentaCorriente c, Transaccion* t,int numT) {
    char r;
    printf("Elige una opcion: \n");
    printf("1.Consultar saldo\n");
    printf("2. Consultar historial\n");
    printf("3. Hacer transferencias\n");
    scanf("%c",&r);
    fflush(stdin);
    switch (r)
    {
    case '1':
        consultarSaldo(c);
        break;
    case '2':
        consultarHistoria(c, t,numT);
        break;
    case '3':
        //El caso 3 aún no está
        printf("Aqui caso 3 -> Se tiene que hacer");
        break;
    default:
        break;
    } 
}

//Opcion 1 de miCuentaCorriente
void consultarSaldo(CuentaCorriente cuenta){
    printf("------------------------------");
    printf("El saldo es: %2.f",cuenta.saldo);
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
/*void nuevaTransferencia(CuentaCorriente miCuentaCorriente, CuentaCorriente* listaCuentas, int numeroCuentas){
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
}*/

void misTarjetas(Tarjeta* t, int numTarjetas){
    char r;
    printf("Elige una opcion: \n");
    printf("1. Administrar tarjetas\n");
    printf("2. Nueva tarjeta\n");
    scanf("%c",&r);
    fflush(stdin);
    switch (r)
    {
    case '1':
        todasMisTarjetas(t,numTarjetas);
        break;
    case '2':
        introducirDatos();
        break;
    default:
        break;
    }

}

//Opcion 1 misTarjetas
void todasMisTarjetas(Tarjeta* t, int numTarjetas){
    int tarjetaSeleccionada;
    imprimirNumTarjeta(t,numTarjetas);
    printf("Que tarjeta desea visualizar? (salir ->0)" );
    scanf("%i",tarjetaSeleccionada);
    infoTarjeta(t[tarjetaSeleccionada]);
    printf("\n");
}

//Ver la info de una tarjeta
void infoTarjeta(Tarjeta t){
    char r;
    printf("La información de la tarjeta seleccionada es: \n");
    imprimirInfoTarjeta(t);
    printf("Quiere modificar la tarjeta? (s/n)  ");
    scanf("%c",&r);
    switch (r)
    {
    case 's':
        modDatosTarjeta(&t);
        break;
    case 'n':
        break;
    }   
}

//Modificar datos tarjeta
void modDatosTarjeta(Tarjeta* t){
    int i;
    int limite;
    int pin;
    printf("1. Modificar el limite\n");
    printf("2. Modificar el PIN\n");
    scanf("%i",i);
    if(i==1){
        printf("Inserte nuevo limite: ");
        scanf("%i",limite);
        (*t).limite = limite;
        printf("\n");
    }else if(i==2){
        printf("Inserte nuevo pin: ");
        scanf("%i",pin);
        (*t).pin = pin;
        printf("\n");
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

