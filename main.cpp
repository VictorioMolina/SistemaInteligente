#include "MotorInferencias.h"
#include "BaseHechos.h"
#include "BaseConocimiento.h"

#include <string>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <iostream>

using namespace std;

// Variables globales
string f_salida1 = "salida1";
string f_salida2 = "salida2";

// Prototipos de funcion
void establecerNombresFicherosSalida(string ficheroBH);
void establecerConfiguracion(BaseConocimiento &BC, BaseHechos &BH, string ficheroConfig,
                             string ficheroBC, string ficheroBH);

int main(int argc, char **argv)
{
    string ficheroBaseConocimiento = argv[1];
    string ficheroConfig = argv[2];
    string ficheroBaseHechos = argv[3];

    // Establecemos el nombre de los ficheros de salida
    establecerNombresFicherosSalida(ficheroBaseHechos);

    BaseConocimiento BC;
    BaseHechos BH;

    // Establecemos la configuración
    establecerConfiguracion(BC, BH, ficheroConfig, ficheroBaseConocimiento, ficheroBaseHechos);

    // Creamos el motor de inferencias
    MotorInferencias MI(BC, BH, f_salida2);

    return 0;
}


void establecerNombresFicherosSalida(string ficheroBH){
    /* Método que establece los nombres de los ficheros de
    salida en funcion del nombre del fichero de base de hechos */


    string sufijo = ficheroBH.substr(ficheroBH.find_last_of("-"), ficheroBH.length() -1);
    f_salida1+=sufijo;
    f_salida2+=sufijo;
}


void establecerConfiguracion(BaseConocimiento &BC, BaseHechos &BH, string ficheroConfig,
                             string ficheroBC, string ficheroBH)
{
    ifstream f(ficheroConfig);
    string linea;
    getline(f, linea); // Despreciamos la primera linea

    // Leemos el número de atributos
    getline(f, linea);
    int numAtributos = stoi(linea);

    /* Obtenemos los atributos */
    vector<atributo> atributos;
    for (int i = 0; i < numAtributos; i++)
    {
        // Creamos el atributo
        Atributo atributo;

        // Obtenemos el nombre
        getline(f, linea, ' ');
        atributo.nombre = linea;

        // Obtenemos el tipo
        getline(f, linea, ' ');
        atributo.tipo = linea;

        if (atributo.tipo == "NU")
        {
            atributos.push_back(atributo);
            getline(f, linea, '\n'); // Consumimos el salto de linea
            continue;
        }
        // Obtenemos la lista de valores
        getline(f, linea, '\n');
        string valores = linea.substr(linea.find('{') + 1, linea.find('}') - 1);

        istringstream ss(valores);
        string valor;

        while (getline(ss, valor, ','))
        {
            atributo.valores.push_back(valor);
        }
        atributos.push_back(atributo);
    }

    // Ignoramos la siguiente linea
    getline(f, linea);

    // Obtenemos el objetivo
    getline(f, linea);
    string objetivo = linea;

    // Ignoramos la siguiente linea
    getline(f, linea);

    // Recuperamos las reglas
    getline(f, linea);
    int numReglas = stoi(linea);
    int prioridades[numReglas];

    for (int i = 0; i < numReglas; i++)
    {
        getline(f, linea);
        prioridades[i] = stoi(linea);
    }

    f.close();

    // Cargamos la base de conocimiento
    BC = BaseConocimiento(ficheroBC, f_salida1, f_salida2);
    BC.setPrioridadReglas(prioridades);

    // Cargamos la base de hechos
    BH = BaseHechos(atributos, objetivo, ficheroBH, f_salida1, f_salida2);
}
