#ifndef _CLIENTE_H_
#define _CLIENTE_H_

typedef struct {
    int dni;
    char* nombre;
    char* fec_nac;
    char* sexo;
    char* contrasenya;
} Cliente;

void imprimirCliente (Cliente c);

Cliente* buscarCliente(int dniBuscado, Cliente* clientes, int numClientes);

#endif