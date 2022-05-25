#include "cliente.h"
#include <iostream>
using namespace std;
//namespace ?

Cliente:: Cliente(int dni, char* nombre, char* fec_nac, char* sexo, char* contrasenya)
{
	this->dni=dni;
	this->nombre=nombre;
	this->fec_nac=fec_nac;
	this->sexo=sexo;
	this->contrasenya=contrasenya;
}

Cliente::~Cliente(){
	//eliminamos las variables que hagamos new 
}	


//getters y setters
void Cliente::setDni(int dni){
	this->dni=dni;
}

int Cliente::getDni() const{
	return this->dni;
}

void Cliente::setNombre(char* nombre){
	this->nombre=nombre;

}
		
char* Cliente::getNombre() const{
	return this->nombre;

}

void Cliente::setFec_nac(char* fec_nac){
	this->fec_nac=fec_nac;

}

char* Cliente::getFec_nac() const{
	return this->fec_nac;
}

void Cliente::setSexo(char* sexo){
	this->sexo=sexo;
}

char* Cliente::getSexo() const{
	return this->sexo;
}

void Cliente::setContrasenya(char* contrasenya){
	this->contrasenya=contrasenya;
}

char* Cliente::getContrasenya() const{
	return this->contrasenya;
}

void Cliente::imprimirCliente (Cliente c){
	cout << "DNI: " << c.dni << " Nombre: " << c.nombre << " Fecha de nacimiento: " << c.fec_nac << " Sexo: " << c.sexo <<" Contrasenya: " << c.contrasenya << endl;
}
