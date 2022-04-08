#include <stdio.h>
#include "tarjeta.h"

void imprimirTarjeta(Tarjeta t){
    printf("[num tarjeta: %i; pin: %i; limite: %i; tipo: %s; num c/c: %i",t.num,t.pin,t.limite,t.tipo,t.num_cc);

}