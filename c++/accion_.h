#ifndef ACCION_H_
#define ACCION_H_

//namespace c++

class Accion
{
	private:
   		int num_valor;
    	float prec_actual;
    	float prec_compra;
    	char* empresa;
    	int dni_cliente; 

	public:
		//constructor por defecto
		Accion(); 
		//constructor con parametros
		Accion(int num_valor, float prec_actual, float prec_compra, char* empresa, int dni_cliente);
		//constructor copia
		Accion(const Accion &a);
		//destructor
		~Accion();

		void setNum_valor(int dni);
		int getNum_valor() const;
		void setPrec_actual(float prec_actual);
		float getPrec_actual() const;
		void setPrec_compra(float prec_compra);
		float getPrec_compra() const;
		void setEmpresa(char* empresa);
		char* getEmpresa() const;
		void setDni_cliente(int dni_cliente);
		int getDni_cliente() const;

		void imprimirAccion(Accion a);
};

#endif