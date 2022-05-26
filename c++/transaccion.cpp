#include "transaccion.h"
//namespace c++

using namespace std;

Transaccion:: Transaccion(int num, float importe, char* descripcion, CuentaCorriente* origen, CuentaCorriente* destino)
{
	this->num=num;
	this->importe=importe;
	this->descripcion=descripcion;
	this->origen=origen;
	this->destino=destino;
}

Transaccion::~Transaccion(){
	//eliminamos las variables que hagamos new 
}	

//getters y setters
void Transaccion::setNum(int num){
	this->num=num;
}

int Transaccion::getNum() const{
	return this->num;
}
void Transaccion::setImporte(float importe){
	this->importe=importe;
}
float Transaccion::getImporte() const{
	return this->importe;
}
void Transaccion::setDescripcion(char* descripcion){
	this->descripcion=descripcion;
}
char* Transaccion::getDescripcion() const{
	return this->descripcion;
}
void Transaccion::setOrigen(CuentaCorriente* origen){
    this->origen=origen;
}
CuentaCorriente* Transaccion::getOrigen() const{
    return this->origen;
}
void Transaccion::setDestino(CuentaCorriente* destino){
    this->destino=destino;
}
CuentaCorriente* Transaccion::getDestino() const{
    return this->destino;
}

void Transaccion::imprimirTransaccion(Transaccion t){
	//cout << "Num: "<<(t.getNum())<<endl;
	cout << "Importe: "<<t.getImporte()<<endl;
	cout << "Descripcion: "<<t.getDescripcion()<<endl;
	cout << "Cuenta origen: "<<t.getOrigen()->getNumero()<<endl;
	cout << "Cuenta destino: "<<t.getDestino()->getNumero()<<endl;
}

void Transaccion::hacerTransaccion(CuentaCorriente o, CuentaCorriente d, float importe){
	float saldo_o = o.getSaldo() - importe;
	o.setSaldo(saldo_o);
	float saldo_d = d.getSaldo() + importe;
	d.setSaldo(saldo_d);
}