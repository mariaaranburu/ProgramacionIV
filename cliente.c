#include <stdio.h>

void imprimirCliente (Cliente *c) {
    printf("[Nombre: %s, Edad: %i]", c->nombre, c->edad);
}