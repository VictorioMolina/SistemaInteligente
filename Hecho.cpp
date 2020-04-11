#include "Hecho.h"

// Constructor
Hecho::Hecho(string nombre, string tipo, string valor)
{
    setNombre(nombre);
    setTipo(tipo);
    setValor(valor);
}

// Metodos Set/Get
void Hecho::setNombre(string nombre)
{
    Hecho::nombre = nombre;
}

string Hecho::getNombre()
{
    return nombre;
}

void Hecho::setTipo(string tipo)
{
    Hecho::tipo = tipo;
}

string Hecho::getTipo()
{
    return tipo;
}

void Hecho::setValor(string valor)
{
    Hecho::valor = valor;
}

string Hecho::getValor()
{
    return valor;
}
