#ifndef _MENU_H_
#define _MENU_H_
#include "cliente.h"
#include "cuentacorriente.h"
#include "tarjeta.h"
#include "transaccion.h"
#include "accion.h"

Cliente* iniciarSesion(Cliente* c,int max);
void imprimirMenu( CuentaCorriente* c, int numCC, Transaccion* transacciones,int numTrans,Tarjeta* tarjetas, int numTarj, Cliente* clientes);
void miCuentaCorriente(CuentaCorriente* c, int numCC, Transaccion* t,int numT);
void consultarSaldo(CuentaCorriente* cuenta);
void consultarHistoria(CuentaCorriente* cuenta, Transaccion* transacciones,int numTransacciones);
void misTarjetas(Tarjeta* t, int numTarjetas);
void todasMisTarjetas(Tarjeta* t, int numTarjetas);
void infoTarjeta(Tarjeta t);
void modDatosTarjeta(Tarjeta* t);
Tarjeta introducirDatos(void);
void misAcciones(void);
void miPerfil(Cliente c);
void modPerfil(Cliente c);

#endif