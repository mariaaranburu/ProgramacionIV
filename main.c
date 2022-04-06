#include <stdio.h>
#include <stdlib.h>

void iniciarSesion(void);
void imprimirMenu(void);
void imprimirMenuCuenta(void);

int main(void) {
    //INICIAR SESIÓN
    printf("  INICIO DE SESION\n");
    printf("--------------------\n");
    printf("Inserta tu nombre: \n");
    char* nombre;
    scanf("%s", nombre);
    printf("Inserta tu contrasenya: \n");
    char* contrasenya;
    scanf("%s", contrasenya);
    
    //COMPROBACION DE INICIO DE SESION: FOR, IF
    for (int i=0; i<10; i++) {
        printf("comer\n");
    }

    //MENU
    int opcion;
    char opcionChar;
    int opcionCuenta;
    while (opcionChar!='q') {
        imprimirMenu();
        scanf("%i", opcion);
        scanf("%c", opcionChar);
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
    prinf("'q' para salir\n");
}

void imprimirMenuCuenta(void) {
    printf("Elige una opcion: \n");
    printf("1.Ver historial de movimientos\n");
    printf("2. Hacer una transferencia\n");
}