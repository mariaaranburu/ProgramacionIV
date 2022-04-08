#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include "menu.h"
#define MAX_CLIENTES 10
#define MAX_CHAR 30


int main(void) {
    Cliente *clientes = (Cliente*) malloc (MAX_CLIENTES*sizeof(Cliente));
    clientes[0].dni = 73511346;
    clientes[0].contrasenya = "1234A";
    int encontrado = iniciarSesion(clientes,MAX_CLIENTES);
    if (encontrado == 0) {
        printf("Estas dentro!\n");
        char opcion = imprimirMenu();
        switch (opcion)
        {
            case '1':
                printf("Caso 1\n");
                break;
            case '2':
                printf("Caso 2\n");
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
    else {
    printf("Los datos introducidos no son correctos.");
    }
    return 0;
}

