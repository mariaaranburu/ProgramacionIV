#include "usuario_.h"
#include <iostream>
#include <string.h>

using namespace std;


Usuario::Usuario(){
    this->dni=0;
    this->contrasenya=NULL;
}

Usuario::Usuario(int dni, char* contrasenya)
{
    this->dni = dni;
    
    this->contrasenya = new char[strlen(contrasenya)+1];
        for(int i=0; i<(strlen(contrasenya)+1); i++)
        {
            this->contrasenya[i] = contrasenya[i];
        }
}

Usuario::~Usuario()
{
    delete[] contrasenya;
}

 int Usuario::getDni() {
    return this->dni;
 }


char* Usuario::getContrasenya()
{
    return contrasenya;
}

void Usuario::setDNI(int dni)
{
    this->dni = dni;
}

void Usuario::setContrasenya(char* contrasenya)
{
    this->contrasenya = contrasenya;
}

char* Usuario::diHola()
{
    char* mensaje = new char[30];
    mensaje = "¡Hola usuario!";
    return mensaje;
}

char* Usuario::diAdios()
{
    char* mensaje = new char[30];
    mensaje = "¡Adios usario!";
    return mensaje;
}
