#ifndef _TARJETA_H_
#define _TARJETA_H_

typedef struct {
    int num;
    int pin;
    int limite;
    char* tipo;
    int num_cc;
} Tarjeta;

#endif