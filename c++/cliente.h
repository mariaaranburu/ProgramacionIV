#ifndef CLIENTE_H_
#define CLIENTE_H_

//namespace c++
class Cliente
{
	private:
		int dni;
    	char* nombre;
    	char* fec_nac;
    	char* sexo;
   		char* contrasenya;

	public:
		//constructor por defecto
		Cliente(); 
		//constructor con parametros
		Cliente(int dni, char* nombre, char* fec_nac, char* sexo, char* contrasenya);
		//destructor
		~Cliente();

		void setDni(int dni);
		int getDni() const;
		void setNombre(char* nombre);
		char* getNombre() const;
		void setFec_nac(char* fec_nac);
		char* getFec_nac() const;
		void setSexo(char* sexo);
		char* getSexo() const;
		void setContrasenya(char* contrasenya);
		char* getContrasenya() const;


		void imprimirCliente (Cliente c);
		//Cliente* buscarElCliente(int dniBuscado, Cliente* clientes, int numClientes);
};

#endif