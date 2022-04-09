#ifndef _MENU_H_
#define _MENU_H_
#include "cliente.h"
#include "cuentacorriente.h"
#include "tarjeta.h"
#include "transaccion.h"

int iniciarSesion(Cliente* c,int max);
void imprimirMenu(void);
void miCuentaCorriente(void);
void consultarSaldo(CuentaCorriente cuenta);
void consultarHistoria(CuentaCorriente cuenta, Transaccion* transacciones,int numTransacciones);
void misTarjetas(void);
int todasMisTarjetas(Tarjeta* t, int numTarjetas);
void infoTarjeta(Tarjeta t);
void modDatosTarjeta(Tarjeta* t);
Tarjeta introducirDatos(void);
void misAcciones(void);
void miPerfil(Cliente c);

#endif