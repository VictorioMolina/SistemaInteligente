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

    // Métodos
    virtual void leerBase(string) = 0; // Virtual puro

    // Métodos Set/Get
    void setTam(int tam);
    int getTam();

private:
    // Atributos
    int tam;
};

#endif
