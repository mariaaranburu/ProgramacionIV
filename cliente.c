#include <stdio.h>
#include "cliente.h"

void imprimirCliente (Cliente *c) {
    printf("[Nombre: %s, Edad: %i]", c->nombre, c->edad);
}