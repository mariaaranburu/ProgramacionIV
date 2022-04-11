#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ficheros.h"
#include "cliente.h"

#define MAX_LINE 30

void limpiar (char limpiar [])
{
	for (int i=0; i<MAX_LINE; i++)
	{
		limpiar[i] = '\0';
	}
}

void leerFicheroClientes (Cliente * clientes, int* size){

	char str [MAX_LINE];

	FILE * f;
	f=fopen ("clientes.txt", "r");

	if(f){
		fgets(str, MAX_LINE, f);
		sscanf(str, "%i", size);
	}

	char c;
	char dni [MAX_LINE];
	limpiar (dni);
	char contrasenya [MAX_LINE];
	limpiar (contrasenya);
    
    for (int i=0; i<*size; i++){
		for (int i=0; ((c!=';')&& (c!='\n')&& (c!=EOF)); i++){
			c=fgetc(f);

			if (c!=';' && c!='\n'){
				//dni[i]=malloc ((MAX_LINE)*sizeof (char));
				dni[i]=c;
			}
		}
		char *b;
		sscanf(dni, "%i", &b);
        clientes[i].dni=strcpy(clientes[i].dni, b);
		//clientes[i].setDni(b);
		// sscanf(dni, "%i", &usuarios[i].setDni(dni));

		c='a';

		for (int i=0; c!=';'; i++){
			c=fgetc(f);

			if (c!=';'){
				//contrasenya[i]=malloc ((MAX_LINE)*sizeof (char));
				contrasenya[i]=c;
			}
		}
		
        clientes[i].contrasenya=strcpy(clientes[i].contrasenya, contrasenya);
        //clientes[i].setContrasenya(contrasenya);
		// sscanf(contrasenya, "%s", clientes[i].setContrasenya(contrasenya));
		limpiar (contrasenya);
	}
	fclose (f);
}


void escribirFicheroClientes (Cliente* clientes, int size){

    FILE* f;
    f=fopen("clientes.txt", "w");
    fprintf(f, "%i\n", size);

    for (int i=0; i<size; i++){
        fprintf(f, "%s, %s\n", (clientes+i)->dni, (clientes+i)->contrasenya);
    }

    fclose (f);

}