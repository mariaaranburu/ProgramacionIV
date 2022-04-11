#include "accion.h"

void imprimirAccion(Accion a){
    printf("[Numero: %i, Precio actual: %f, Precio compra: %f, Empresa: %s]\n",a.num_valor,a.prec_actual,a.prec_compra, a.empresa);
}