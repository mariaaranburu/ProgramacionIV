#include "cuentacorriente_.h"
#ifndef TRANSACCION__H_
#define TRANSACCION__H_

//namespace c++
class Transaccion
{
	private:
		int num;
	    float importe;
	    char* descripcion;
	    CuentaCorriente* origen;
	    CuentaCorriente* destino;

	public:
		//constructor por defecto
		Transaccion(); 
		//constructor con parametros
		Transaccion(int num, float importe, char* descripcion, CuentaCorriente* origen, CuentaCorriente* destino);
		//destructor
		~Transaccion();

		void setNum(int num);
		int getNum() const;
		void setImporte(float importe);
		float getImporte() const;
		void setDescripcion(char* descripcion);
		char* getDescripcion() const;
		void setOrigen(CuentaCorriente* origen);
		CuentaCorriente* getOrigen() const;
		void setDestino(CuentaCorriente* destino);
		CuentaCorriente* getDestino() const;

		void imprimirTransaccion(Transaccion t);
		
void Transaccion::hacerTransaccion(CuentaCorriente o, CuentaCorriente d, float importe);
};

#endif