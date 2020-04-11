#ifndef REGLA_H
#define REGLA_H

#include <string>
#include <vector>

using namespace std;

class Regla
{
public:
    // Constructor
    Regla(int id);

    // Metodos
    bool containsCondicion(string condicion);
    bool containsAccion(string accion);

    // Métodos Set/Get
    void setId(int id);
    int getId();
    void setPrioridad(int prioridad);
    int getPrioridad();
    void addCondicion(string condicion);
    vector<string> getCondiciones();
    void addAccion(string accion);
    vector<string> getAcciones();

    bool operator==(const Regla &other) const
    {
        // Las reglas son únicas, cada una tiene su propio identificador
        return (id == other.id);
    }

    bool operator<(const Regla &other) const
    {
        return (prioridad > other.prioridad || id < other.id);
    }

private:
    // Atributos
    int id;
    int prioridad;
    vector<string> condiciones;
    vector<string> acciones;
};

#endif
