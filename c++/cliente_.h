#ifndef CLIENTE__H_
#define CLIENTE__H_
#include "usuario_.h"
#pragma once

class Cliente: public Usuario
{
	private:
		char* nombre;
    	char* fec_nac;
    	char sexo;

	public:
		//constructor vacio
		Cliente();
		//constructor con parametros
		Cliente(int dni, char* nombre, char* fec_nac, char sexo, char* contrasenya);
		//destructor
		~Cliente();

		void setNombre(char* nombre);
		char* getNombre() const;
		void setFec_nac(char* fec_nac);
		char* getFec_nac() const;
		void setSexo(char sexo);
		char getSexo() const;

		virtual char* diHola();
		virtual char* diAdios();

		virtual char* regInicioSesion(const char* fichero);

		void imprimirCliente (Cliente* c);
		//Cliente* buscarElCliente(int dniBuscado, Cliente* clientes, int numClientes);
};

#endif