#include "cuentacorriente.h"
#include "cliente.h"
//namespace ?

CuentaCorriente:: CuentaCorriente(int numero, float saldo, Cliente *cliente)
{
	this->numero=numero;
	this->saldo=saldo;
	this->cliente=cliente;
}

CuentaCorriente::~CuentaCorriente(){
	//eliminamos las variables que hagamos new 
}	

//getters y setters
void CuentaCorriente::setNumero(int numero){
	this->numero=numero;
}

int CuentaCorriente::getNumero() const{
	return this->numero;
}

void CuentaCorriente::setSaldo(float saldo){
	this->saldo=saldo;

}
		
float CuentaCorriente::getSaldo() const{
	return this->saldo;

}

void CuentaCorriente::setCliente(Cliente *cliente){
	this->cliente=cliente;

}

Cliente* CuentaCorriente::getCliente() const{
	return this->cliente;
}

void CuentaCorriente::imprimirCuenta (CuentaCorriente* c){
}
