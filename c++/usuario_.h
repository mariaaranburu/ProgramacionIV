#ifndef USUARIO__H_
#define USUSARIO__H_
#pragma once

class Usuario
{
    private:
        int dni;
        char* contrasenya;

    public:

        //constructor vacio
        Usuario();

        //constructor con parametros
        Usuario(int dni, char* contrasenya);

        //destructor
        ~Usuario();

        int getDni();
        char* getContrasenya();
        void setDNI(int dni);
        void setContrasenya(char* contrasenya);

        virtual char* diHola();
        virtual char* diAdios();

        virtual char* regInicioSesion(const char* fichero) = 0;
};

#endif
