#include "BaseHechos.h"

#include <fstream>
#include <algorithm>
#include <string>
#include <iostream>
#include <stdlib.h>

BaseHechos::BaseHechos(vector<atributo> atributos, string objetivo, string ficheroBaseHechos, string f_salida1, string f_salida2)
{
    // Inicializamos miembros
    setAtributos(atributos);
    setObjetivo(objetivo);
    leerBase(ficheroBaseHechos);

    // Mostramos la base de hechos inicial
    mostrarDatosIniciales(f_salida1, f_salida2);
}

void BaseHechos::leerBase(string ficheroBaseHechos)
{
    ifstream f(ficheroBaseHechos);
    string linea;
    getline(f, linea);
    setTam(stoi(linea));

    for (int i = 0; i < getTam(); i++)
    {
        // Extraemos el atributo del hecho
        getline(f, linea, ' ');
        string atributo = linea;

        /*
            Buscamos el tipo del atributo en el vector de atributos
            de la base de hechos
        */
        string tipo;
        for (auto it = BaseHechos::atributos.begin(); it != BaseHechos::atributos.end(); it++)
        {
            // En caso de encontrar el atributo con el mismo nombre...
            if (it->nombre == atributo)
            {
                tipo = it->tipo;
            }
        }

        // Ignoramos el igual
        getline(f, linea, ' ');

        // Extraemos el valor del hecho
        getline(f, linea, '\n');
        string valor = linea;

        // En caso de que el valor no sea válido salimos
        if (getAtributo(atributo).tipo == "Nom")
        {
            vector<string> valores = getAtributo(atributo).valores;
            if (find(valores.begin(), valores.end(), valor) == valores.end())
            {
                cout << "Corrija el fichero de la base de hechos." << endl;
                exit(EXIT_FAILURE);
            }
        }
        Hecho hecho = Hecho(atributo, tipo, valor);

        // Añadimos el hecho al vector de hechos
        addHecho(hecho);
    }

    f.close();
}

bool BaseHechos::containsObjetivo()
{
    /* Retorna verdadero en caso de que se haya encontrado un hecho del
     mismo tipo que el objetivo */

    return (find_if(hechos.begin(), hechos.end(), [&](Hecho &h) { return (h.getNombre() == objetivo); }) != hechos.end());
}

void BaseHechos::setAtributos(vector<atributo> atributos)
{
    BaseHechos::atributos = atributos;
}

vector<atributo> BaseHechos::getAtributos()
{
    return atributos;
}

Atributo BaseHechos::getAtributo(string nombre)
{
    Atributo atributo;
    for (auto it = atributos.begin(); it != atributos.end(); it++)
    {
        if (it->nombre == nombre)
        {
            atributo = *it;
        }
    }
    return atributo;
}

void BaseHechos::setObjetivo(string objetivo)
{
    BaseHechos::objetivo = objetivo;
}

string BaseHechos::getObjetivo()
{
    return objetivo;
}

void BaseHechos::addHecho(Hecho hecho)
{
    hechos.push_back(hecho);
    // Eliminamos duplicados
    unique(hechos.begin(), hechos.end());
}

vector<Hecho> BaseHechos::getHechos()
{
    return hechos;
}


void BaseHechos::mostrarDatosIniciales(string f_salida1, string f_salida2){
    ofstream salida1;
    salida1.open(f_salida1, fstream::app);
    // Escribimos el objetivo en el primer fichero se salida
    salida1 << "Objetivo: " << objetivo << endl;

    // Escribimos los hechos iniciales
    salida1 << "-------------------------" << endl;
    salida1 << "Hechos Iniciales:" << endl << endl;
    for(auto hecho : getHechos()){
        salida1 << hecho.getNombre() << " = " << hecho.getValor() << endl;
    }
    salida1 << "-------------------------" << endl;

    // Wscribimos los atributos junto a su tipo y valores
    salida1 << "Atributos: " << endl << endl;
    for(auto a : atributos){
        salida1 << a.nombre << " " << a.tipo;
        if (a.tipo == "NU"){
            salida1 << endl;
            continue;
        }
        salida1 << " {";
        for(auto v : a.valores){
            salida1 << " " << v;
        }
        salida1 << " }" << endl;
    }
    salida1 << "-------------------------" << endl;

    salida1.close();

}
