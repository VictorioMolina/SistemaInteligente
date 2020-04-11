#ifndef BASECONOCIMIENTO_H
#define BASECONOCIMIENTO_H

#include "Base.h"
#include "Regla.h"

#include <string>
#include <vector>

using namespace std;

class BaseConocimiento : public Base
{
public:
    // Constructores
    BaseConocimiento(){ /*Vacio*/ }
    BaseConocimiento(string ficheroBaseConocimiento, string f_salida1, string f_salida2);

    // Métodos
    void leerBase(string ficheroBaseConocimiento);

    // Métodos Set/Get
    void setDominio(string dominio);
    string getDominio();
    void addRegla(Regla regla);
    vector<Regla> getReglas();
    Regla getRegla(string antecedente);
    void setPrioridadReglas(int prioridades[]);

private:
    // Metodos pribados
    void mostrarDatos(string f_salida1, string f_salida2);

    // Atributos
    string dominio;
    vector<Regla> reglas;
};

#endif
