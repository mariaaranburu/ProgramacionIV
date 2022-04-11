#include <stdio.h>
#include "tarjeta.h"

void imprimirInfoTarjeta(Tarjeta t){
    printf("Num tarjeta: %i\n",t.num);
    printf("pin: %i",t.pin); 
    printf("limite: %i",t.limite); 
    printf("tipo: %s",t.tipo); 
    printf("num c/c: %i",t.num_cc);
}

void imprimirNumTarjeta(Tarjeta* t, int numTarjetas){
    for(int i=0;i<numTarjetas;i++){
        printf("Tarjeta %i: %i\n",i, t->num);
    }
}