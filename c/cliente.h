#ifndef _CLIENTE_H_
#define _CLIENTE_H_

typedef struct {
    int dni;
    char* nombre;
    char* fec_nac;
    char* sexo;
    char* contrasenya;
} Cliente_;

void imprimirCliente (Cliente_ c);

Cliente_* buscarElCliente(int dniBuscado, Cliente_* clientes, int numClientes);

#endif