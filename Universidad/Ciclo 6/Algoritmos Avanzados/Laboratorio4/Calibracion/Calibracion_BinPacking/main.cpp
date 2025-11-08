#include <iostream>
#include <iomanip>
#include <ctime>
#include <climits>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

#define  ITERACIONES 10000

struct Mochila {
    int id;
    int capacidad;
};

struct Solucion {
    int mochila;
    int paquete;
};

bool compara(int k, int g) {
    return k > g; //Descendente (Mayor a menor)
}

bool compara2(struct Mochila k, struct Mochila g) {
    return k.capacidad > g.capacidad; //Descendente (Mayor a menor)
}

int buscarIndice(vector<int> vPaquetes, double RCL) {
    int cont = 0;

    for (int k = 0; k < vPaquetes.size(); k++) {
        if (vPaquetes[k] >= RCL) {
            cont++;
        }
    }

    return cont;
}

int  buscarIndice(vector<struct Mochila> vMochilas, double RCL) {
    int cont = 0;

    for (int k = 0; k < vMochilas.size(); k++) {
        if (vMochilas[k].capacidad >= RCL) {
            cont++;
        }
    }

    return cont;
}

int cargaMochila(int *paquetes, int n, double alfa) {
    vector<Solucion> mejorSolucion;

    int menorCantidad = INT_MAX;

    //srand(time(NULL));

    for (int k = 0; k < ITERACIONES; k++) {
        vector<struct Solucion> resultado;
        vector<int> vPaquetes;
        vector<struct Mochila> vMochilas;

        //Copiamos
        vPaquetes.insert(vPaquetes.begin(), paquetes, paquetes + n);

        //Ordenamos de mayor a menor
        sort(vPaquetes.begin(), vPaquetes.end(), compara);

        int contadorDeMochilas = 0;
        int cantidadMochilas = 0;

        while (!vPaquetes.empty()) { //Mientras hayan paquetes por asignar

            //Paquetes
            int betaPaq = vPaquetes[0];
            int tauPaq = vPaquetes[vPaquetes.size() - 1];

            double RCLPaq = betaPaq - alfa * (betaPaq - tauPaq);

            int indPaq = buscarIndice(vPaquetes, RCLPaq);

            int indAlePaq = rand() % indPaq;

            int paqueteSeleccionado = vPaquetes[indAlePaq]; //Paquete seleccionado

            //Mochilas

            bool entra = false;

            if (!vMochilas.empty()) {
                //Ordenamos las mochilas de mayor a menor capacidad
                sort(vMochilas.begin(), vMochilas.end(), compara2);

                int betaMochila = vMochilas[0].capacidad;
                int tauMochila = vMochilas[vMochilas.size() - 1].capacidad;

                double RCLMochila = betaMochila - alfa * (betaMochila - tauMochila);

                int indMochila = buscarIndice(vMochilas, RCLMochila);

                int indAleMochila = rand() % indMochila;

                if (vMochilas[indAleMochila].capacidad - vPaquetes[indAlePaq] >= 0) {
                    vMochilas[indAleMochila].capacidad -= vPaquetes[indAlePaq];
                    resultado.push_back({vMochilas[indAleMochila].id, vPaquetes[indAlePaq]});
                    entra = true;
                }
            }

            if (!entra) { //Si no entra en ninguna mochila, creamos una nueva
                contadorDeMochilas++;
                struct Mochila mochilaNueva;
                mochilaNueva.id = contadorDeMochilas;
                mochilaNueva.capacidad = 10 - paqueteSeleccionado; //Capacidad - paquete seleccionado

                resultado.push_back({mochilaNueva.id, paqueteSeleccionado}); //Entra en la nueva mochila
                vMochilas.push_back(mochilaNueva); //Se agrega la nueva mochila
            }

            //Eliminamos el paquete seleccionado
            vPaquetes.erase(vPaquetes.begin() + indAlePaq);
        }

        cantidadMochilas = vMochilas.size();

        if (cantidadMochilas < menorCantidad) {
            menorCantidad = cantidadMochilas;
            mejorSolucion.clear();
            mejorSolucion.insert(mejorSolucion.begin(), resultado.begin(), resultado.end());
            //O simplemente
            //mejorSolucion = resultado;
        }
    }

    // //Mapa para la impresion
    // map<int, vector<int>> mochilasConPaquetes;
    //
    // for (auto solucion : mejorSolucion) {
    //     mochilasConPaquetes[solucion.mochila].push_back(solucion.paquete);
    // }
    //
    // for (auto solucion : mochilasConPaquetes) {
    //     cout << "Contenedor " << solucion.first << ": ";
    //     for (auto objetos : solucion.second) {
    //         cout << objetos << " ";
    //     }
    //     cout << endl;
    // }

    return menorCantidad;
}

int mochilaDinamica(double alfa) {

    //int paquetes[] = {2, 2, 12, 1, 4, 3};
    //int paquetes[] = {4, 8, 1, 4, 2, 1};
    int paquetes[] = {9, 8, 7, 6, 5, 5, 4, 4, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1};
    //int paquetes[] = {8, 7, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1};
    int n = sizeof(paquetes) / sizeof(paquetes[0]);

    int menorCantidadMochilas = cargaMochila(paquetes, n, alfa);

    return menorCantidadMochilas;
}

double buscarPromedio(double alfa) {
    int pruebas = 10;

    int cantidadPorIteracion = 0;
    for (int k = 0; k < 10; k++) {
        cantidadPorIteracion += mochilaDinamica(alfa);
    }

    return (double) cantidadPorIteracion / pruebas;
}

int calibracionMochila() {
    double mejorAlfa;
    double menorCantidad = INT_MAX;

    srand(time(NULL));

    for (double alfa = 0; alfa <= 1; alfa += 0.1) {
        cout << "Probando alfa = " << fixed << setprecision(1) << alfa << "... ";

        double actualPromedio = buscarPromedio(alfa);

        cout << "Promedio: " << actualPromedio << endl;

        if (actualPromedio < menorCantidad) {
            menorCantidad = actualPromedio;
            mejorAlfa = alfa;
        }
    }

    cout << "Mejor alfa: " << mejorAlfa << " con promedio de paquetes: " << menorCantidad << endl;

    return 1;
}

int main() {

    calibracionMochila();

    //int paquetes[] = {4, 8, 1, 4, 2, 1};
    //int n = sizeof(paquetes) / sizeof(paquetes[0]);

    //int menorCantidadMochilas = cargaMochila(paquetes, n, 0.3);

    return 0;
}