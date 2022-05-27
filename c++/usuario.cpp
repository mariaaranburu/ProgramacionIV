#include "usuario_.h"
#include <iostream>
#include <string.h>

using namespace std;


Usuario::Usuario(){
    this->nombre=NULL;
    this->contrasenya=NULL;
}

Usuario::Usuario(char* nombre, char* contrasenya)
{
    this->nombre = new char[strlen(nombre)+1];
        for(int i=0; i<(strlen(nombre)+1); i++){
            this->nombre[i] = nombre[i];
        }
    
    this->contrasenya = new char[strlen(contrasenya)+1];
        for(int i=0; i<(strlen(contrasenya)+1); i++)
        {
            this->contrasenya[i] = contrasenya[i];
        }
}

Usuario::~Usuario()
{
    delete[] nombre;
    delete[] contrasenya;
}

char* Usuario::getNombre()
{
    return nombre;
}

char* Usuario::getContrasenya()
{
    return contrasenya;
}

void Usuario::setNombre(char* nombre)
{
    this->nombre = nombre;
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
