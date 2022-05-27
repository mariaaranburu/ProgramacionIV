#include "cliente_.h"
#include <iostream>
#include <string.h>
#include "usuario_.h"

using namespace std;

Cliente:: Cliente():Usuario(){
	this->nombre=NULL;
	this->fec_nac=NULL;
	this->sexo=NULL;

}

Cliente:: Cliente(int dni, char* nombre, char* fec_nac, char sexo, char* contrasenya):Usuario(dni, contrasenya)
{
	this->nombre=nombre;
	this->fec_nac = new char[strlen(fec_nac)+1];
		for(int i=0; i<(strlen(fec_nac)+1); i++)
		{
			this->fec_nac[i] = fec_nac[i];
		}
	this->sexo = sexo;
}

Cliente::~Cliente()
{
	delete[] fec_nac;
}	


//getters y setters
void Cliente::setNombre(char* nombre)
{
	this->nombre=nombre;
}

char* Cliente::getNombre() const
{
	return this->nombre;
}

void Cliente::setFec_nac(char* fec_nac)
{
	this->fec_nac=fec_nac;

}

char* Cliente::getFec_nac() const
{
	return this->fec_nac;
}

void Cliente::setSexo(char sexo)
{
	this->sexo=sexo;
}

char Cliente::getSexo() const
{
	return this->sexo;
}

char* Cliente::diHola()
{
	char* mensaje = new char[30];
	mensaje = "¡Hola cliente!";
	return mensaje;
}

char* Cliente::diAdios()
{
	char* mensaje = new char[30];
	mensaje = "¡Adios cliente!";
	return mensaje;
}

char* Cliente::regInicioSesion(const char* fichero)
{
	char* mensaje = new char[50];
	mensaje = "El inicio de sesion ha sido registrado correctamente";
	return mensaje;
}

void Cliente::imprimirCliente (Cliente* c)
{
	cout << "DNI: " << c->getDni() << " Nombre: " << c->getNombre() << " Fecha de nacimiento: " << c->fec_nac << " Sexo: " << c->sexo <<" Contrasenya: " << c->getContrasenya() << endl;
}
