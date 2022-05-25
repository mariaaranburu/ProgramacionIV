#include "cliente.h"
#ifndef CUENTACORRIENTE_H_
#define CUENTACORRIENTE_H_

//namespace c++
class CuentaCorriente
{
	private:
		int numero;
    	float saldo;
    	Cliente *cliente;

	public:
		//constructor por defecto
		CuentaCorriente(); 
		//constructor con parametros
		CuentaCorriente(int numero, float saldo, Cliente *cliente);
		//destructor
		~CuentaCorriente();

		void setNumero(int numero);
		int getNumero() const;
		void setSaldo(float saldo);
		float getSaldo() const;
		void setCliente(Cliente *cliente);
		Cliente* getCliente() const;

		void imprimirCuenta(CuentaCorriente *c);
		CuentaCorriente cogerCuenta(CuentaCorriente* listadoCuentas, int numeroCuentas, int numeroCuenta);
		void accederASaldoCuenta(CuentaCorriente* listadoCuentas, int numeroCuentas, int numeroCuenta, float modificacion, char tipo);
		CuentaCorriente* buscarCC(int numCC, CuentaCorriente* cuentas, int numCuentas);
		CuentaCorriente* buscarCC_Cliente(int dni, int numCuentas, CuentaCorriente* cuentas);
		int cuentasCC_dni (int dni, int numCuentas, CuentaCorriente* cuentas);
};

#endif