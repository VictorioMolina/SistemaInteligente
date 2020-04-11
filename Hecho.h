#ifndef HECHO_H
#define HECHO_H

#include <string>

using namespace std;

class Hecho
{
public:
    // Constructores
    Hecho(){ /*Vacio*/ }
    Hecho(string nombre, string tipo, string valor);

    bool operator==(const Hecho &other) const
    {
        return (nombre == other.nombre && tipo == other.tipo && valor == other.valor);
    }

    // Metodos Set/Get
    void setNombre(string nombre);
    string getNombre();
    void setTipo(string tipo);
    string getTipo();
    void setValor(string valor);
    string getValor();

private:
    // Atributos
    string nombre;
    string tipo;
    string valor;
};

#endif
