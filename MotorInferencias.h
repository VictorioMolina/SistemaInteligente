#ifndef MOTORINFERENCIA_H
#define MOTORINFERENCIA_H

#include "BaseConocimiento.h"
#include "BaseHechos.h"

#include <string>

class MotorInferencias
{
public:
    // Constructor
    MotorInferencias(BaseConocimiento &BC, BaseHechos &BH, string f_salida2);

    // Métodos
    bool encadenamientoHaciaDelante(string f_salida2);
    void equiparar(vector<Regla> &conjuntoConflicto, vector<Regla> reglasAplicadas);
    Regla resolverConflictos(vector<Regla> &conjuntoConflicto);
    void aplicar(Regla seleccionada, string f_salida2);

    // Metodos Set/Get
    void setBC(BaseConocimiento &BC);
    BaseConocimiento getBC();
    void setBH(BaseHechos &BH);
    BaseHechos getBH();

private:
    // Metodos privados
    pair<Hecho, string> convertirEnHecho(string str);
    vector<Regla> diferencia(vector<Regla> v1, vector<Regla> v2);
    void ordenarConjuntoConflicto(vector<Regla> &conjuntoConflicto);
    void mostrarResultado(string f_salida2);

    // Atributos
    BaseConocimiento BC;
    BaseHechos BH;
};

#endif // MOTORINFERENCIA_H
