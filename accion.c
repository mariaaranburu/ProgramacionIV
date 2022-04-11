#include <stdio.h>
#include "accion.h"

void imprimirAccion(Accion a){
    printf("[Numero: %i, Precio actual: %f, Precio compra: %f, Empresa: %s]\n",a.num_valor,a.prec_actual,a.prec_compra, a.empresa);
}

Cliente* buscarCliente(int dniBuscado, Cliente* clientes, int numClientes){
    Cliente* d = (Cliente*)malloc(sizeof(Cliente));
    for(int i=0; i<numClientes;i++){
        if(clientes[i].dni==dniBuscado){
            d->dni = clientes[i].dni;
            int tamNombre = strlen(clientes[i].nombre);
            d->nombre = (char*)malloc((tamNombre+1)*sizeof(char));
            d->nombre = strcpy(d->nombre,clientes[i].nombre);
            int tamFecNac = strlen(clientes[i].fec_nac);
            d->fec_nac = (char*)malloc((tamFecNac+1)*sizeof(char));
            d->fec_nac = strcpy(d->fec_nac,clientes[i].fec_nac);
            int tamSexo = strlen(clientes[i].sexo);
            d->sexo = (char*)malloc((tamSexo+1)*sizeof(char));
            d->sexo = strcpy(d->sexo,clientes[i].sexo);
            int tamContra = strlen(clientes[i].contrasenya);
            d->contrasenya = (char*)malloc((tamContra+1)*sizeof(char));
            d->contrasenya = strcpy(d->contrasenya,clientes[i].contrasenya);
            break;
        }
    }
    return d;
}