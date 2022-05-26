#include "administrador.h"
#include "usuario.h"
#include <iostream>
#include <string.h>

using namespace std;

Administrador::Administrador(char* nombre, char* contrasenya, char* cargo):Usuario(nombre, contrasenya)
{
    this->cargo = new char[strlen(cargo)+1];
        for(int i=0; i<(strlen(cargo)+1); i++)
    {
        this->cargo[i] = cargo[i];
    }
}

Administrador::~Administrador()
{
    delete[] cargo;
}

char* Administrador::getCargo()
{
    return cargo;
}

void Administrador::setCargo(char* cargo)
{
    this->cargo = cargo;
}

char* Administrador::diHola()
{
    char* mensaje = new char[30];
    mensaje = "¡Hola administrador!";
    return mensaje;
}

char* Administrador::diAdios()
{
    char* mensaje = new char[30];
    mensaje = "!Adios administrador!";
    return mensaje;
}

char* Administrador::regInicioSesion(const char* fichero)
{
    char* mensaje = new char[50];
    mensaje = "El inicio de sesion ha sido registrado correctamente";
    return mensaje;
}