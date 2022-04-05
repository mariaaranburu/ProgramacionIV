#ifndef _CLIENTE_H_
#define _CLIENTE_H_

typedef struct {
    char* nombre;
    int edad;
} Cliente;

void imprimirCliente (Cliente *c);

#endif