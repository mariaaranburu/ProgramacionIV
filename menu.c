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

void imprimirMenuCuenta(void) {
    printf("Elige una opcion: \n");
    printf("1.Ver historial de movimientos\n");
    printf("2. Hacer una transferencia\n");
}