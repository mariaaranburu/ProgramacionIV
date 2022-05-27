#ifndef ADMINISTRADOR__H_
#define ADMINISTRADOR__H_
#include "usuario_.h"
#pragma once


class Administrador: public Usuario
{
    private:
        char* cargo;
    
    public:
        //Constructor vacio
        Administrador();

        //Constructor con parametros
        Administrador(char* nombre, char* contrasenya);
        Administrador(char* nombre, char* contrasenya, char* cargo);

        //Destructor
        ~Administrador();

        char* getCargo();
        void setCargo(char* cargo);

        virtual char* diHola();
        virtual char* diAdios();

        virtual char* regInicioSesion(const char* fichero);
};

#endif