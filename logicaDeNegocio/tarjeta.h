#ifndef _TARJETA_H_
#define _TARJETA_H_

typedef struct {
    int num;
    int pin;
    int limite;
    char* tipo;
    int numCC;
} Tarjeta;

void imprimirInfoTarjeta(Tarjeta t);
void imprimirNumTarjeta(Tarjeta* t, int numTarjetas);

#endif