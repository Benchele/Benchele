#include <iostream>
#include <iomanip>
#include <ctime>
#include <climits>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

#define ITERACIONES 1000
#define alfa 0.3

struct Orden {
    int id;
    int cantidadBotellas;
    int prioridad;
};

struct Linea {
    int id;
    double tiempoAcumulado;
    int ordenAtendida;
};

bool compara(struct Orden k, struct Orden g) {
    return k.cantidadBotellas > g.cantidadBotellas; //Descendente (Mayor a menor)
}

bool compara2(struct Linea k, struct Linea g) {
    return k.tiempoAcumulado < g.tiempoAcumulado; //Ascendente (Menor a mayor)
}

int buscarIndice(vector<struct Orden> vOrdenes, double RCL) {
    int cont = 0;

    for (int k = 0; k < vOrdenes.size(); k++) {
        if (vOrdenes[k].cantidadBotellas >= RCL) {
            cont++;
        }
    }

    return cont;
}

int buscarIndice(vector<struct Linea> vLineas, double RCL) {
    int cont = 0;

    for (int k = 0; k < vLineas.size(); k++) {
        if (vLineas[k].tiempoAcumulado <= RCL) {
            cont++;
        }
    }

    return cont;
}

double calcularTiempo() {
    double tiempo = 0;
    tiempo += 2; //Llenadora de liquido
    tiempo += 1; //Gasificadora
    tiempo += 1.5; //Tapadora
    tiempo += 1.5; //Etiquetadora
    return tiempo;
}

void atiendeOrdenes(struct Orden *ordenes, int n, struct Linea *lineas, int m) {
    vector<struct Linea> solucionMaxima;

    int mejorMakeSpan = INT_MAX;

    srand(time(NULL));

    double tiempoPorProduccion = calcularTiempo();

    for (int k = 0; k < ITERACIONES; k++) {
        vector<struct Linea> resultado;
        vector<struct Orden> vOrdenes;
        vector<struct Linea> vLineas;

        //Copiamos
        vOrdenes.insert(vOrdenes.begin(), ordenes, ordenes + n);
        vLineas.insert(vLineas.begin(), lineas, lineas + m);

        //Ordenamos ordenes por cantidad de botellas
        sort(vOrdenes.begin(), vOrdenes.end(), compara);

        int makeSpan = 0;

        while (!vOrdenes.empty()) { //Mientras haya ordenes por atender

            //Ordenes
            int betaOrden = vOrdenes[0].cantidadBotellas;
            int tauOrden = vOrdenes[vOrdenes.size() - 1].cantidadBotellas;
            double RCLOrden = betaOrden - alfa * (betaOrden - tauOrden);

            int indOrden = buscarIndice(vOrdenes, RCLOrden);

            int indAleOrden = rand() % indOrden;

            //Lineas
            sort(vLineas.begin(), vLineas.end(), compara2); //Ordenamos lineas por tiempo acumulado

            int betaLinea = vLineas[0].tiempoAcumulado;
            int tauLinea = vLineas[vLineas.size() - 1].tiempoAcumulado;

            double RCLLinea = betaLinea + alfa * (tauLinea - betaLinea);

            int indLinea = buscarIndice(vLineas, RCLLinea);

            int indAleLinea = rand() % indLinea;

            //Colocamos ordenes
            struct Orden ordenSeleccionada = vOrdenes[indAleOrden];

            vLineas[indAleLinea].tiempoAcumulado += tiempoPorProduccion * ordenSeleccionada.cantidadBotellas;
            vLineas[indAleLinea].ordenAtendida = ordenSeleccionada.id;
            resultado.push_back(vLineas[indAleLinea]);

            vOrdenes.erase(vOrdenes.begin() + indAleOrden);
        }

        //El makeSpan es el mayor tiempo
        sort(vLineas.begin(), vLineas.end(), compara2); //Menor a mayor tiempo acumulado
        makeSpan = vLineas[vLineas.size() - 1].tiempoAcumulado;

        if (makeSpan < mejorMakeSpan) { //El menor makespan es el mejor
            mejorMakeSpan = makeSpan;
            solucionMaxima.clear();
            solucionMaxima.insert(solucionMaxima.begin(), resultado.begin(), resultado.end());
            //O simplemente
            //solucionMaxima = resultado;
        }
    }

    //Mapa para impresion
    map<int, vector<int>> lineasConOrdenes;

    for (auto solucion : solucionMaxima) {
        lineasConOrdenes[solucion.id].push_back(solucion.ordenAtendida);
    }

    cout << "Mejor MakeSpan: " << mejorMakeSpan << " minutos" << endl;
    for (auto solucion : lineasConOrdenes) {
        cout << "Linea " << solucion.first << ": ";
        for (auto orden : solucion.second) {
            cout << orden << " ";
        }
        cout << endl;
    }
}

int main() {

    struct Orden ordenes[] = {
        {1, 103, 2},
        {2, 58, 1},
        {3, 88, 3},
        {4, 126, 1},
        {5, 195, 2},
        {6, 90, 2},
        {7, 54, 3},
        {8, 195, 1},
        {9, 124, 2},
        {10, 113, 3},
        {11, 193, 2},
        {12, 55, 1},
        {13, 97, 1},
        {14, 97, 2},
        {15, 169, 2},
        {16, 50, 2},
        {17, 167, 3},
        {18, 74, 1},
        {19, 79, 2},
        {20, 109, 1}
    };

    int n = sizeof(ordenes) / sizeof(ordenes[0]);

    struct Linea lineas[] = {
        {1, 0, 0},
        {2, 0, 0},
        {3, 0, 0},
        {4, 0, 0},
        {5, 0, 0}
    };

    int m = sizeof(lineas) / sizeof(lineas[0]);

    atiendeOrdenes(ordenes, n, lineas, m);

    return 0;
}
