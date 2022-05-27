#ifndef USUARIO__H_
#define USUSARIO__H_
#pragma once

class Usuario
{
    private:
        char* nombre;
        char* contrasenya;

    public:

        //constructor vacio
        Usuario();

        //constructor con parametros
        Usuario(char* nombre, char* contrasenya);

        //destructor
        ~Usuario();

        char* getNombre();
        char* getContrasenya();
        void setNombre(char* nombre);
        void setContrasenya(char* contrasenya);

        virtual char* diHola();
        virtual char* diAdios();

        virtual char* regInicioSesion(const char* fichero) = 0;
};

#endif
