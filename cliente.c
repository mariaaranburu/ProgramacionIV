#include <stdio.h>
#include "cliente.h"

void imprimirCliente (Cliente c) {
    printf("[DNI: %i, Nombre: %s, Fecha nacimiento: %s, Sexo: %s, Contrasenya: %s]\n",c.dni,c.nombre,c.fec_nac,c.sexo,c.contrasenya);
}