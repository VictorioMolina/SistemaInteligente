#include "BaseConocimiento.h"

#include <fstream>
#include <iostream>
#include <sstream>

// Constructor
BaseConocimiento::BaseConocimiento(string ficheroBaseConocimiento, string f_salida1, string f_salida2)
{
    leerBase(ficheroBaseConocimiento);
    mostrarDatos(f_salida1, f_salida2);

}

// Métodos
void BaseConocimiento::leerBase(string ficheroBaseConocimiento)
{
    ifstream f(ficheroBaseConocimiento);
    string linea;

    // Obtenemos el dominio
    getline(f, linea);
    setDominio(linea);

    // Obtenemos el número de reglas
    getline(f, linea);
    setTam(stoi(linea));


    // Iteramos por cada regla
    for (int i = 0; i < getTam(); i++)
    {
        // Obtenemos el identificador de la regla
        getline(f, linea);
        int id = stoi(linea.substr(linea.find('R') + 1, linea.find(":") - 1));

        // Creamos la regla
        Regla r(id);

        // Obtenemos el antecedente y consecuente de la regla
        string regla = linea.substr(linea.find("Si") + 3, linea.length() - 1);

        /*Condiciones del antecedente*/
        string lhs = regla.substr(0, regla.find("Entonces") - 1);
        stringstream ss_left(lhs);
        string palabra, condicion;
        bool primeraPalabra = true;
        while (ss_left >> palabra)
        {
            if (palabra == "y")
            {
                // Añadimos la condicion a la regla
                r.addCondicion(condicion);
                // Reiniciamos los valores
                condicion = "";
                primeraPalabra = true;
                continue;
            }
            if (primeraPalabra)
            {
                condicion = palabra;
                primeraPalabra = false;
            }
            else
            {
                condicion += (" " + palabra); // Concatenamos
            }
        }
        // Añadimos la ultima condicion del antecedente a la regla
        r.addCondicion(condicion);

        /*Acciones del consecuente*/
        string rhs = regla.substr(regla.find("Entonces") + 9, regla.length() - 1);
        stringstream ss_right(rhs);
        string accion;
        primeraPalabra = true;
        while (ss_right >> palabra)
        {
            if (palabra == "y")
            {
                // Añadimos la accion a la regla
                r.addAccion(accion);
                accion = "";
                primeraPalabra = true;
                continue;
            }
            if (primeraPalabra)
            {
                accion = palabra;
                primeraPalabra = false;
            }
            else
            {
                accion += (" " + palabra); // Concatenamos
            }
        }
        // Añadimos la ultima accion del consecuente a la regla
        r.addAccion(accion);

        // Registramos la regla en el vector de reglas de la base de conocimiento
        addRegla(r);
    }
}


void BaseConocimiento::mostrarDatos(string f_salida1, string f_salida2){
    ofstream salida1, salida2;
    salida1.open(f_salida1);
    salida1 << "Dominio: " << dominio << endl;
    salida1 << "-------------------------" << endl;
    salida1 << "Reglas:" << endl << endl;
    for(auto r : reglas){
        salida1 << "-> R" << r.getId() << ": SI";
        for(auto c : r.getCondiciones()){
            salida1 << " " << c;
        }
        salida1 << " ENTONCES";
        for(auto a : r.getAcciones()){
            salida1 << " " << a;
        }
        salida1 << endl;
    }
    salida1 << "-------------------------" << endl;
    salida1.close();

    salida2.open(f_salida2);
    salida2 << "Dominio: " << dominio << endl;
    salida2 << "-------------------------" << endl;
    salida2.close();
}

void BaseConocimiento::setDominio(string dominio)
{
    BaseConocimiento::dominio = dominio;
}

string BaseConocimiento::getDominio()
{
    return dominio;
}

void BaseConocimiento::addRegla(Regla regla)
{
    reglas.push_back(regla);
}

vector<Regla> BaseConocimiento::getReglas()
{
    return reglas;
}

void BaseConocimiento::setPrioridadReglas(int prioridades[])
{
    for (size_t i = 0; i < getReglas().size(); i++)
    {
        reglas[i].setPrioridad(prioridades[i]);
    }
}
