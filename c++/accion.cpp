#include "accion.h"
#include <iostream>
using namespace std;
//namespace ?

//constructor con parametros
Accion:: Accion(int num_valor, float prec_actual, float prec_compra, char* empresa, int dni_cliente)
{
	this->num_valor=num_valor;
	this->prec_actual=prec_actual;
	this->prec_compra=prec_compra;
	this->empresa=empresa;
	this->dni_cliente=dni_cliente;
}

//constructor copia
Accion:: Accion(const Accion &a){
	this->num_valor=a.num_valor;
	this->prec_actual=a.prec_actual;
	this->prec_compra=a.prec_compra;
	this->empresa=a.empresa;
	this->dni_cliente=a.dni_cliente;
}

//destructor
Accion::~Accion(){
	//eliminamos las variables que hagamos new 
}	

//getters y setters
void Accion::setNum_valor(int num_valor){
	this->num_valor=num_valor;
}

int Accion::getNum_valor() const{
	return this->num_valor;
}

void Accion::setPrec_actual(float prec_actual){
	this->prec_actual=prec_actual;
}
		
float Accion::getPrec_actual() const{
	return this->prec_actual;

}

void Accion::setPrec_compra(float prec_compra){
	this->prec_compra=prec_compra;

}

float Accion::getPrec_compra() const{
	return this->prec_compra;
}

void Accion::setEmpresa(char* empresa){
	this->empresa=empresa;
}

char* Accion::getEmpresa() const{
	return this->empresa;
}

void Accion::setDni_cliente(int dni_cliente){
	this->dni_cliente=dni_cliente;
}

int Accion::getDni_cliente() const{
	return this->dni_cliente;
}

void Accion::imprimirAccion(Accion a){
	cout << "Número: " << a.num_valor << " Precio actual: " << a.prec_actual << " Precio de compra: " << a.prec_compra << " Empresa: " << a.empresa << endl;
}
