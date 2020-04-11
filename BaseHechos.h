#ifndef BASEHECHOS_H
#define BASEHECHOS_H

#include "Base.h"
#include "Hecho.h"

#include <vector>

using namespace std;

struct Atributo
{
    string nombre;
    string tipo;
    vector<string> valores;
};

typedef struct Atributo atributo;

class BaseHechos : public Base
{
public:
    // Constructores
    BaseHechos(){/*Vacio*/};
    BaseHechos(vector<atributo> atributos, string objetivo, string ficheroBaseHechos, string f_salida1, string f_salida2);

    // Métodos
    void leerBase(string ficheroBaseHechos);
    bool containsObjetivo();

    // Métodos Set/Get
    void setAtributos(vector<atributo> atributos);
    vector<atributo> getAtributos();
    Atributo getAtributo(string nombre);
    void setObjetivo(string objetivo);
    string getObjetivo();
    void addHecho(Hecho hecho);
    vector<Hecho> getHechos();

private:
    // Métodos privados
    void mostrarDatosIniciales(string f_salida1, string f_salida2);

    // Atributos
    vector<atributo> atributos;
    string objetivo;
    vector<Hecho> hechos;
};

#endif
