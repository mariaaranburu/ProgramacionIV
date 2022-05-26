#ifndef ADMINISTRADOR_H_
#define ADMINISTRADOR_H_
#include "usuario.h"

class Administrador: public Usuario
{
    private:
        char* cargo;
    
    public:
        Administrador(char* nombre, char* contrasenya, char* cargo);
        ~Administrador();

        char* getCargo();
        void setCargo(char* cargo);

        virtual char* diHola();
        virtual char* diAdios();

        virtual char* regInicioSesion(const char* fichero);
};

#endif