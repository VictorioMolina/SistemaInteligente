#ifndef BASE_H
#define BASE_H

#include <string>

using namespace std;

// Clase abstracta
class Base
{
public:

    // Constructor
    Base() {/*Vacio*/};

    // M�todos
    virtual void leerBase(string) = 0; // Virtual puro

    // M�todos Set/Get
    void setTam(int tam);
    int getTam();

private:
    // Atributos
    int tam;
};

#endif
