#include "tarjeta_.h"
//namespace ?

Tarjeta:: Tarjeta(int num, int pin, int limite, char* tipo, int numCC)
{
	this->num=num;
	this->pin=pin;
	this->limite=limite;
	this->tipo=tipo;
	this->numCC=numCC;
}

Tarjeta::~Tarjeta(){
	//eliminamos las variables que hagamos new 
}	

//getters y setters
void Tarjeta::setNum(int num){
	this->num=num;
}

int Tarjeta::getNum() const{
	return this->num;
}

void Tarjeta::setPin(int pin){
	this->pin=pin;
}
		
int Tarjeta::getPin() const{
	return this->pin;
}

void Tarjeta::setLimite(int limite){
	this->limite=limite;
}

int Tarjeta::getLimite() const{
	return this->limite;
}

void Tarjeta::setTipo(char* tipo){
	this->tipo=tipo;
}

char* Tarjeta::getTipo() const{
	return this->tipo;
}

void Tarjeta::setNumCC(int numCC){
	this->numCC=numCC;
}

int Tarjeta::getNumCC() const{
	return this->numCC;
}

void Tarjeta::imprimirInfoTarjeta(Tarjeta t){

}
void Tarjeta::imprimirNumTarjeta(Tarjeta* t, int numTarjetas){
	
}
