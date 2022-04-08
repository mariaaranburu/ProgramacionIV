#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "cuentacorriente.h"
#include "transaccion.h"
#define MAX_CLIENTES 10
#define MAX_CHAR 30

void clearIfNeeded(char *str, int max_line)
{
	// Limpia los caracteres de más introducidos
	if ((strlen(str) == max_line-1) && (str[max_line-2] != '\n'))
		while (getchar() != '\n');
}

void iniciarSesion(void);
void imprimirMenu(void);
void imprimirMenuCuenta(void);

int main(void) {
    Cliente *clientes = (Cliente*) malloc (MAX_CLIENTES*sizeof(Cliente));
    clientes->nombre = (char*) malloc (MAX_CHAR*sizeof(char));
    clientes[0].nombre = "Maria";
    clientes->contrasenya = (char*) malloc (MAX_CHAR*sizeof(char));
    clientes[0].contrasenya = "hola";
    clientes[0].edad = 20;
    char str[10];
    //INICIAR SESIÓN
    int encontrado = -1;
    while (encontrado != 1) {
        printf("      INICIO DE SESION\n");
        printf("-----------------------------\n");
        printf("Inserta tu nombre: \n");
        char* nombre = (char*) malloc (MAX_CHAR*sizeof(char));
        fgets(nombre, MAX_CHAR, stdin);
        sscanf(nombre, "%s");
        clearIfNeeded(nombre, MAX_CHAR);
        printf("-----------------------------\n");
        printf("Inserta tu contrasenya: \n");
        char* contrasenya = (char*) malloc (MAX_CHAR*sizeof(char));
        fgets(contrasenya, MAX_CHAR, stdin);
        sscanf(contrasenya, "%s");
        clearIfNeeded(contrasenya, MAX_CHAR);
        printf("%s, %s\n", nombre, contrasenya);
        for (int i=0; i<MAX_CLIENTES; i++) {
            if (clientes[i].nombre == nombre && clientes[i].contrasenya == contrasenya) {
                encontrado = 1;
            }
        }
        if (encontrado == -1) {
            printf("El usuario y la contrasenya no son correctos. Prueba otra vez.\n");
        }
    }
    //MENU
    int opcion;
    char opcionChar;
    int opcionCuenta;
    while (opcionChar!='q') {
        imprimirMenu();
        scanf("%i", &opcion);
        scanf("%c", &opcionChar);
        if (opcion == 1) {
            imprimirMenuCuenta();
        }
    }
    
    return 0;
}

void imprimirMenu(void) {
    printf("Elige una opcion: \n");
    printf("1. Ver mi cuenta corriente\n");
    printf("2. Ver mis tarjetas\n");
    printf("3. Ver mis acciones\n");
    printf("4. Ver mi perfil\n");
    printf("'q' para salir\n");
}

void imprimirMenuCuenta(void) {
    printf("Elige una opcion: \n");
    printf("1.Ver historial de movimientos\n");
    printf("2. Hacer una transferencia\n");
}