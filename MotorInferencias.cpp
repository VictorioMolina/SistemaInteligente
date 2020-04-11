#include "MotorInferencias.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <fstream>

MotorInferencias::MotorInferencias(BaseConocimiento &BC, BaseHechos &BH, string f_salida2)
{
    setBC(BC);
    setBH(BH);
    encadenamientoHaciaDelante(f_salida2);
}

bool MotorInferencias::encadenamientoHaciaDelante(string f_salida2)
{
    vector<Regla> conjuntoConflicto;
    vector<Regla> reglasAplicadas;

    do
    {
        // Eliminamos posibles duplicados
        unique(conjuntoConflicto.begin(), conjuntoConflicto.end());
        unique(reglasAplicadas.begin(), reglasAplicadas.end());

        // Quitamos las reglas aplicadas del conjunto de conflictos
        conjuntoConflicto = diferencia(conjuntoConflicto, reglasAplicadas);

        // Equiparación entre BH y BC
        equiparar(conjuntoConflicto, reglasAplicadas);

        if (!conjuntoConflicto.empty())
        {
            // Seleccionamos la siguiente regla a aplicar
            Regla seleccionada = resolverConflictos(conjuntoConflicto);
            if (find(reglasAplicadas.begin(), reglasAplicadas.end(), seleccionada) == reglasAplicadas.end())
            {
                // Aplicamos la regla actualizando la base de hechos
                aplicar(seleccionada, f_salida2);
                // Una vez aplicada la regla, pasará a formar parte del vector de reglas aplicadas
                reglasAplicadas.insert(reglasAplicadas.begin(), seleccionada);
            }
        }

    } while (!(BH.containsObjetivo() || conjuntoConflicto.empty()));

    if (BH.containsObjetivo())
    {
        // Escribimos el resultado en el segundo fichero de salida
        mostrarResultado(f_salida2);
        return true;
    }

    // En caso de no haber alcanzado la meta, lo especificamos en el segundo fichero de salida

    return false;
}

void MotorInferencias::equiparar(vector<Regla> &conjuntoConflicto, vector<Regla> reglasAplicadas)
{
    // Cargamos las reglas y los hechos
    vector<Regla> reglas = BC.getReglas();
    vector<Hecho> hechos = BH.getHechos();

    /* Para cada regla de la BC, en caso de que todas las condiciones del antecedente de la regla no sean hechos,
     no nos interesa la regla (debido a la conjuncion de las condiciones del antecedente) */
    for (auto it_regla = reglas.begin(); it_regla != reglas.end(); it_regla++)
    {
        // Si la regla ya se encuentra en el conjunto de reglas aplicadas, la obviamos...
        if (find_if(reglasAplicadas.begin(), reglasAplicadas.end(), [&](Regla &r) { return r.getId() == it_regla->getId(); }) != reglasAplicadas.end())
        {
            continue;
        }

        bool introducir = false; // Nos indicará si debemos introducir la regla
        vector<string> condiciones = it_regla->getCondiciones(); // Obtenemos las condiciones de la regla

        for (auto it_condicion = condiciones.begin(); it_condicion != condiciones.end(); it_condicion++)
        {
            // Cada condicion del antecedente es un posible hecho (lo será en caso de que sea cierta)
            pair<Hecho, string> posibleHecho = convertirEnHecho(*it_condicion);

            // Buscamos el posible hecho en la BH
            Hecho hecho;
            for (auto it_hecho = hechos.begin(); it_hecho != hechos.end(); it_hecho++)
            {
                if (it_hecho->getNombre() == (get<0>(posibleHecho)).getNombre())
                {
                    introducir = true;
                    hecho = *it_hecho;
                    break;
                }
            }

            // En caso de que no se encuentre todavía en BH, no introducimos la regla
            if (!introducir)
            {
                break;
            }
            else
            {
                // Confirmamos que realmente sea un hecho, actuando segun el tipo de atributo
                if (hecho.getTipo() == "NU")
                {
                    int valorHecho = stoi(hecho.getValor());
                    int valorPosibleHecho = stoi((get<0>(posibleHecho)).getValor());
                    // En funcion del simbolo de la operacion, vemos si se cumple o no el hecho
                    if (get<1>(posibleHecho) == "<" && valorHecho >= valorPosibleHecho)
                    {
                        introducir = false;
                        break;
                    }
                    else if (get<1>(posibleHecho) == "<=" && valorHecho > valorPosibleHecho)
                    {
                        introducir = false;
                        break;
                    }
                    else if (get<1>(posibleHecho) == "=" && valorHecho != valorPosibleHecho)
                    {
                        introducir = false;
                        break;
                    }
                    else if (get<1>(posibleHecho) == ">=" && valorHecho < valorPosibleHecho)
                    {
                        introducir = false;
                        break;
                    }
                    else if (get<1>(posibleHecho) == ">" && valorHecho <= valorPosibleHecho)
                    {
                        introducir = false;
                        break;
                    }
                }
                else
                {
                    // El simbolo de la operacion corresponde siempre con el de la asignación
                    if (hecho.getValor() != (get<0>(posibleHecho)).getValor())
                    {
                        introducir = false;
                        break;
                    }
                }
            }
        }
        // En caso de que todos los antecedentes sean hechos, guardamos la regla
        if (introducir)
        {
            conjuntoConflicto.push_back(*it_regla);
        }
    }
}

Regla MotorInferencias::resolverConflictos(vector<Regla> &conjuntoConflicto)
{
    // Ordenamos el conjunto de conflictos segun el peso de la regla
    ordenarConjuntoConflicto(conjuntoConflicto);

    // La regla seleccionada es la primera del conjunto de conflictos
    Regla seleccionada = conjuntoConflicto.front();

    return seleccionada;
}

void MotorInferencias::aplicar(Regla seleccionada, string f_salida2)
{
    /* Introducimos las acciones (consecuente) de la regla a la base de hechos,
    es decir, pasan a ser nuevos hechos. */

    // Escribimos las reglas aplicadas en el segundo fichero de salida
    ofstream salida2;
    salida2.open(f_salida2, fstream::app);
    salida2 << "Aplicando la regla R" << seleccionada.getId() << " concluimos: ";
    for (auto accion : seleccionada.getAcciones())
    {
        // Convertimos cada parte (acciones individuales) del consecuente en un hecho
        Hecho nuevoHecho = get<0>(convertirEnHecho(accion));
        if (accion.length() == 0)
            salida2 << "Nada ";
        else
            salida2 << accion << " ";
        // Lo añadimos a la base de hechos
        BH.addHecho(nuevoHecho);
    }
    salida2 << endl;
    salida2.close();
}

void MotorInferencias::setBC(BaseConocimiento &BC)
{
    MotorInferencias::BC = BC;
}

BaseConocimiento MotorInferencias::getBC()
{
    return BC;
}

void MotorInferencias::setBH(BaseHechos &BH)
{
    MotorInferencias::BH = BH;
}

BaseHechos MotorInferencias::getBH()
{
    return BH;
}

// Métodos Privados
pair<Hecho, string> MotorInferencias::convertirEnHecho(string str)
{
    string nombre;
    string valor;
    stringstream ss(str);
    string palabra, simbolo;

    int i = 0;
    while (ss >> palabra)
    {
        if (i == 0)
        {
            nombre = palabra;
        }
        else if (i == 1)
        {
            simbolo = palabra;
        }
        else
        {
            valor = palabra;
        }
        i++;
    }

    // Retornamos el hecho
    pair<Hecho, string> hecho = make_pair(Hecho(nombre, BH.getAtributo(nombre).tipo, valor), simbolo);
    return hecho;
}

vector<Regla> MotorInferencias::diferencia(vector<Regla> v1, vector<Regla> v2){
    vector<Regla> v3;
    for(auto elemento_v1 : v1){
        for(auto elemento_v2 : v2){
            if(elemento_v1 == elemento_v2) continue;
            v2.push_back(elemento_v1);
        }
    }
    return v3;
}

void MotorInferencias::ordenarConjuntoConflicto(vector<Regla> &conjuntoConflicto)
{
    sort(conjuntoConflicto.begin(), conjuntoConflicto.end());
}

void MotorInferencias::mostrarResultado(string f_salida2)
{
    for (auto hecho : BH.getHechos())
    {
        if (hecho.getNombre() == BH.getObjetivo())
        {
            ofstream salida2;
            salida2.open(f_salida2, fstream::app);
            salida2 << "-------------------------" << endl;
            salida2 << "Conclusion final: " << hecho.getNombre() << " = " << hecho.getValor() << endl;
            salida2.close();
        }
    }
}
