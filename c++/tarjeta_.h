#ifndef TARJETA__H_
#define TARJETA__H_

//namespace c++
class Tarjeta
{
	private:
		int num;
	    int pin;
	    int limite;
	    char* tipo;
	    int numCC;

	public:
		//constructor por defecto
		Tarjeta(); 
		//constructor con parametros
		Tarjeta(int num, int pin, int limite, char* tipo, int numCC);
		//destructor
		~Tarjeta();

		void setNum(int num);
		int getNum() const;
		void setPin(int pin);
		int getPin() const;
		void setLimite(int limite);
		int getLimite() const;
		void setTipo(char* tipo);
		char* getTipo() const;
		void setNumCC(int numCC);
		int getNumCC() const;

		void imprimirInfoTarjeta(Tarjeta t);
		void imprimirNumTarjeta(Tarjeta* t, int numTarjetas);
};

#endif