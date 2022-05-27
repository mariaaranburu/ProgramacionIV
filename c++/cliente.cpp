#include "cliente_.h"
#include <iostream>
#include <string.h>
#include "usuario_.h"

using namespace std;

Cliente:: Cliente(int dni, char* nombre, char* fec_nac, char sexo, char* contrasenya):Usuario(nombre, contrasenya)
{
	this->dni=dni;
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
void Cliente::setDni(int dni)
{
	this->dni=dni;
}

int Cliente::getDni() const
{
	return this->dni;
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
	cout << "DNI: " << c->dni << " Nombre: " << c->getNombre() << " Fecha de nacimiento: " << c->fec_nac << " Sexo: " << c->sexo <<" Contrasenya: " << c->getContrasenya() << endl;
}
