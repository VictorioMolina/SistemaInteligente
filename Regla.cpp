#include "Regla.h"

#include <algorithm>

Regla::Regla(int id)
{
    setId(id);
}

bool Regla::containsCondicion(string condicion)
{
    return find(condiciones.begin(), condiciones.end(), condicion) != condiciones.end();
}

bool Regla::containsAccion(string accion)
{
    return find(acciones.begin(), acciones.end(), accion) != acciones.end();
}

void Regla::setId(int id)
{
    Regla::id = id;
}

int Regla::getId()
{
    return id;
}

void Regla::setPrioridad(int prioridad)
{
    Regla::prioridad = prioridad;
}

int Regla::getPrioridad()
{
    return prioridad;
}

void Regla::addCondicion(string condicion)
{
    condiciones.push_back(condicion);
}

vector<string> Regla::getCondiciones()
{
    return condiciones;
}

void Regla::addAccion(string accion)
{
    acciones.push_back(accion);
}

vector<string> Regla::getAcciones()
{
    return acciones;
}
