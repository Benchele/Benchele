#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
#include <ctime>
using namespace std;

#define ITERACIONES 1000
#define ALFA 0.5
#define NPUNTOS 10
#define VEL_RAPIDA 80.0  // km/h
#define VEL_NORMAL 40.0  // km/h

struct Punto {
    int id;
    double x;
    double y;
};

struct Segmento {
    int origen;
    int destino;
};

// Datos del problema
Punto puntos[NPUNTOS] = {
    {0, 5, 10},
    {1, 40, 18},
    {2, 100, 54},
    {3, 60, 100},
    {4, 58, 78},
    {5, 4, 54},
    {6, 70, 45},
    {7, 90, 90},
    {8, 93, 3},
    {9, 30, 95}
};

// Segmentos prohibidos
Segmento prohibidos[] = {
    {0, 1}, {2, 3}, {3, 2}, {5, 2}, {8, 2}, {8, 6}
};
int nProhibidos = 6;

// Segmentos rápidos
Segmento rapidos[] = {
    {0, 4}, {4, 0}, {2, 7}, {7, 2}, {2, 8}, {9, 3}
};
int nRapidos = 6;

// Estructura para candidatos
struct Candidato {
    int punto;
    double tiempo;  // Tiempo para llegar a este punto
};

// Calcula la distancia euclidiana entre dos puntos
double calcularDistancia(int p1, int p2) {
    double dx = puntos[p1].x - puntos[p2].x;
    double dy = puntos[p1].y - puntos[p2].y;
    return sqrt(dx * dx + dy * dy);
}

// Verifica si un segmento está prohibido
bool esProhibido(int origen, int destino) {
    for (int k = 0; k < nProhibidos; k++) {
        if (prohibidos[k].origen == origen && prohibidos[k].destino == destino) {
            return true;
        }
    }
    return false;
}

// Verifica si un segmento es rápido
bool esRapido(int origen, int destino) {
    for (int k = 0; k < nRapidos; k++) {
        if (rapidos[k].origen == origen && rapidos[k].destino == destino) {
            return true;
        }
    }
    return false;
}

// Calcula el tiempo de viaje entre dos puntos
double calcularTiempo(int origen, int destino) {
    if (esProhibido(origen, destino)) {
        return -1;  // Segmento prohibido
    }

    double distancia = calcularDistancia(origen, destino);
    double velocidad = esRapido(origen, destino) ? VEL_RAPIDA : VEL_NORMAL;

    return distancia / velocidad;  // Tiempo en horas
}

// Función de comparación para ordenar candidatos por tiempo (ascendente)
bool comparaTiempo(Candidato a, Candidato b) {
    return a.tiempo < b.tiempo;  // Ascendente (Menor a mayor)
}

// Busca cuántos candidatos están en el RCL
int buscarIndiceRCL(vector<Candidato> candidatos, double umbralRCL) {
    int cont = 0;

    for (int k = 0; k < candidatos.size(); k++) {
        if (candidatos[k].tiempo <= umbralRCL) {
            cont++;
        }
    }

    return cont;
}

// Calcula el tiempo total de un recorrido
double calcularTiempoTotal(vector<int> &recorrido) {
    double tiempoTotal = 0;

    for (int k = 0; k < recorrido.size(); k++) {
        int origen = recorrido[k];
        int destino = recorrido[(k + 1) % recorrido.size()];  // El último conecta con el primero

        double tiempo = calcularTiempo(origen, destino);

        if (tiempo < 0) {
            return INT_MAX;  // Recorrido inválido (hay segmento prohibido)
        }

        tiempoTotal += tiempo;
    }

    return tiempoTotal;
}

// GRASP Construcción
void grasp_construccion(vector<int> &recorrido, double &tiempoTotal) {
    vector<bool> visitado(NPUNTOS, false);
    recorrido.clear();

    // Empezar desde el almacén (punto 0)
    int puntoActual = 0;
    recorrido.push_back(puntoActual);
    visitado[puntoActual] = true;

    // Construir el recorrido visitando todos los puntos
    while (recorrido.size() < NPUNTOS) {
        // Construir lista de candidatos (puntos no visitados alcanzables)
        vector<Candidato> candidatos;

        for (int k = 0; k < NPUNTOS; k++) {
            if (!visitado[k]) {
                double tiempo = calcularTiempo(puntoActual, k);

                if (tiempo >= 0) {  // Si no está prohibido
                    Candidato c;
                    c.punto = k;
                    c.tiempo = tiempo;
                    candidatos.push_back(c);
                }
            }
        }

        if (candidatos.empty()) {
            // No hay puntos alcanzables, recorrido inválido
            tiempoTotal = INT_MAX;
            return;
        }

        // Ordenar candidatos por tiempo (greedy: menor tiempo primero)
        sort(candidatos.begin(), candidatos.end(), comparaTiempo);

        // Calcular RCL con ALFA
        double beta = candidatos[0].tiempo;  // Mejor (menor tiempo)
        double tau = candidatos[candidatos.size() - 1].tiempo;  // Peor
        double umbralRCL = beta + ALFA * (tau - beta);

        // Contar candidatos en el RCL
        int indRCL = buscarIndiceRCL(candidatos, umbralRCL);

        // Seleccionar aleatoriamente del RCL
        int indiceAle = rand() % indRCL;
        int siguientePunto = candidatos[indiceAle].punto;

        // Agregar al recorrido
        recorrido.push_back(siguientePunto);
        visitado[siguientePunto] = true;
        puntoActual = siguientePunto;
    }

    // Calcular tiempo total (incluyendo regreso al almacén)
    tiempoTotal = calcularTiempoTotal(recorrido);
}

// Imprime un recorrido
void imprimirRecorrido(vector<int> &recorrido, double tiempo) {
    cout << "Recorrido: [";
    for (int k = 0; k < recorrido.size(); k++) {
        cout << recorrido[k];
        if (k < recorrido.size() - 1) cout << ", ";
    }
    cout << "]" << endl;

    cout << "Tiempo total: " << tiempo << " horas" << endl;
    cout << "Tiempo total: " << (tiempo * 60) << " minutos" << endl;
}

// Imprime detalles del recorrido
void imprimirDetallesRecorrido(vector<int> &recorrido) {
    cout << endl << "=== DETALLES DEL RECORRIDO ===" << endl;

    double tiempoAcumulado = 0;

    for (int k = 0; k < recorrido.size(); k++) {
        int origen = recorrido[k];
        int destino = recorrido[(k + 1) % recorrido.size()];

        double distancia = calcularDistancia(origen, destino);
        double tiempo = calcularTiempo(origen, destino);
        double velocidad = esRapido(origen, destino) ? VEL_RAPIDA : VEL_NORMAL;

        tiempoAcumulado += tiempo;

        cout << "Segmento " << (k + 1) << ": ";
        cout << "P" << origen << " -> P" << destino;

        if (esRapido(origen, destino)) {
            cout << " [VIA RAPIDA]";
        }

        cout << " | Distancia: " << distancia << " km";
        cout << " | Velocidad: " << velocidad << " km/h";
        cout << " | Tiempo: " << (tiempo * 60) << " min";
        cout << " | Acumulado: " << (tiempoAcumulado * 60) << " min" << endl;
    }
}

// Algoritmo GRASP principal
void ruteoGRASP() {
    vector<int> mejorRecorrido;
    double mejorTiempo = INT_MAX;

    for (int k = 0; k < ITERACIONES; k++) {
        vector<int> recorrido;
        double tiempo;

        // Construir solución con GRASP
        grasp_construccion(recorrido, tiempo);

        // Actualizar mejor solución
        if (tiempo < mejorTiempo) {
            mejorTiempo = tiempo;
            mejorRecorrido = recorrido;
        }

        // Mostrar progreso cada 100 iteraciones
        if ((k + 1) % 100 == 0) {
            cout << "Iteracion " << (k + 1) << " - Mejor tiempo: "
                 << mejorTiempo << " h (" << (mejorTiempo * 60) << " min)" << endl;
        }
    }

    cout << endl << "=== MEJOR SOLUCION ENCONTRADA ===" << endl;
    imprimirRecorrido(mejorRecorrido, mejorTiempo);
    //imprimirDetallesRecorrido(mejorRecorrido);
}

// Muestra información de segmentos especiales
void mostrarSegmentosEspeciales() {
    cout << "Segmentos Prohibidos:" << endl;
    for (int k = 0; k < nProhibidos; k++) {
        cout << "  (" << prohibidos[k].origen << ", " << prohibidos[k].destino << ")" << endl;
    }

    cout << "\nSegmentos Rapidos (80 km/h):" << endl;
    for (int k = 0; k < nRapidos; k++) {
        cout << "  (" << rapidos[k].origen << ", " << rapidos[k].destino << ")" << endl;
    }

    cout << "\nSegmentos normales: 40 km/h" << endl << endl;
}

// Muestra información de las coordenadas
void mostrarPuntos() {
    cout << "\nCoordenadas de los puntos:" << endl;
    cout << "Punto | Coord X | Coord Y" << endl;
    cout << "------+---------+--------" << endl;
    for (int k = 0; k < NPUNTOS; k++) {
        cout << "  " << puntos[k].id << "   |   " << puntos[k].x
             << "    |   " << puntos[k].y << endl;
    }
    cout << endl;
}

int main() {
    srand(time(NULL));

    cout << "=== PROBLEMA DE RUTEO - SMARTCOURIER ===" << endl;
    cout << "Numero de puntos: " << NPUNTOS << endl << endl;

    //mostrarPuntos();
    //mostrarSegmentosEspeciales();

    // Ejecutar GRASP
    ruteoGRASP();

    return 0;
}