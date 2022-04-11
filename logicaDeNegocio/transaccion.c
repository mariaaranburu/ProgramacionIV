#include <stdio.h>
#include "transaccion.h"
#include "cuentacorriente.h"

void imprimirTransaccion(Transaccion t){
    printf("[num: %i; importe: %.2f; desc: %s; origen: %i; destino: %i]\n",t.num,t.importe,t.descripcion,t.origen->numero, t.destino->numero);
}
