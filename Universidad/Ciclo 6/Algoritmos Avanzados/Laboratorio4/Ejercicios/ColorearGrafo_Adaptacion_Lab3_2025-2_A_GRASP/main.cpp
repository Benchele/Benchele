#include <iostream>
#include <iomanip>
#include <ctime>
#include <climits>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
using namespace std;

#define ITERACIONES 1000

struct Pais {
    int id;
    string nombre;
    vector<int> vecinos;
    int color;
    int gradoSaturacion;
};

// Compara por grado de saturación (mayor a menor)
bool compara(struct Pais* k, struct Pais* g) {
    return k->gradoSaturacion > g->gradoSaturacion;
}

int buscarIndice(vector<struct Pais*> candidatos, double RCL) {
    int cont = 0;
    for (int k = 0; k < candidatos.size(); k++) {
        if (candidatos[k]->gradoSaturacion >= RCL) {
            cont++;
        }
    }
    return cont;
}

// Calcula el grado de saturación (cantidad de colores diferentes en vecinos)
int obtenerGradoSaturacion(struct Pais& pais, vector<struct Pais>& paises) {
    set<int> coloresVecinos;
    for (int vecino : pais.vecinos) {
        if (paises[vecino].color != -1) {
            coloresVecinos.insert(paises[vecino].color);
        }
    }
    return coloresVecinos.size();
}

// Obtiene el menor color disponible que no usan los vecinos
int obtenerMenorColorDisponible(struct Pais& pais, vector<struct Pais>& paises) {
    set<int> coloresUsados;
    for (int vecino : pais.vecinos) {
        if (paises[vecino].color != -1) {
            coloresUsados.insert(paises[vecino].color);
        }
    }

    // Buscar el menor color disponible
    int color = 0;
    while (coloresUsados.count(color)) {
        color++;
    }
    return color;
}

int colorearMapaGRASP(vector<struct Pais>& paises, double alfa) {
    int mejorCantidadColores = INT_MAX;
    vector<int> mejorSolucion(paises.size());

    for (int iteracion = 0; iteracion < ITERACIONES; iteracion++) {
        vector<struct Pais> vPaises = paises;  // Copia

        // Resetear colores
        for (auto& p : vPaises) {
            p.color = -1;
            p.gradoSaturacion = 0;
        }

        int paisesColoreados = 0;

        while (paisesColoreados < vPaises.size()) {
            // Actualizar grados de saturación
            for (auto& p : vPaises) {
                if (p.color == -1) {
                    p.gradoSaturacion = obtenerGradoSaturacion(p, vPaises);
                }
            }

            // Construir lista de candidatos (países sin colorear)
            vector<struct Pais*> candidatos;
            for (auto& p : vPaises) {
                if (p.color == -1) {
                    candidatos.push_back(&p);
                }
            }

            // Ordenar por grado de saturación (mayor a menor)
            sort(candidatos.begin(), candidatos.end(), compara);

            // Construir RCL
            int betaSaturacion = candidatos[0]->gradoSaturacion;
            int tauSaturacion = candidatos[candidatos.size() - 1]->gradoSaturacion;
            double RCL = betaSaturacion - alfa * (betaSaturacion - tauSaturacion);

            int indRCL = buscarIndice(candidatos, RCL);
            if (indRCL <= 0) indRCL = 1;

            // Selección aleatoria de la RCL
            int indAleatorio = rand() % indRCL;
            struct Pais* paisSeleccionado = candidatos[indAleatorio];

            // Asignar el menor color disponible
            paisSeleccionado->color = obtenerMenorColorDisponible(*paisSeleccionado, vPaises);
            paisesColoreados++;
        }

        // Calcular cantidad de colores usados
        int maxColor = 0;
        for (const auto& p : vPaises) {
            if (p.color > maxColor) {
                maxColor = p.color;
            }
        }
        int cantidadColores = maxColor + 1;

        // Actualizar mejor solución
        if (cantidadColores < mejorCantidadColores) {
            mejorCantidadColores = cantidadColores;
            for (int i = 0; i < vPaises.size(); i++) {
                mejorSolucion[i] = vPaises[i].color;
            }
        }
    }

    // Aplicar mejor solución encontrada
    for (int i = 0; i < paises.size(); i++) {
        paises[i].color = mejorSolucion[i];
    }

    return mejorCantidadColores;
}

// Función para imprimir resultados
void imprimirSolucion(vector<struct Pais>& paises, int cantidadColores) {
    cout << "\n=== RESULTADOS ===" << endl;
    cout << "Colores necesarios: " << cantidadColores << endl << endl;

    for (int color = 0; color < cantidadColores; color++) {
        cout << "Color " << (color + 1) << ": ";
        bool primero = true;
        for (const auto& p : paises) {
            if (p.color == color) {
                if (!primero) cout << ", ";
                cout << p.nombre;
                primero = false;
            }
        }
        cout << endl;
    }
}

// Inicializar el grafo de Sudamérica
void inicializarGrafoSudamerica(vector<struct Pais>& paises) {
    // Definir los 12 países con sus vecinos (usando índices 0-11)
    paises = {
        {0, "Argentina", {3, 1, 7, 2, 10}, -1, 0},           // Vecinos: Chile, Bolivia, Paraguay, Brasil, Uruguay
        {1, "Bolivia", {8, 2, 7, 0, 3}, -1, 0},              // Vecinos: Perú, Brasil, Paraguay, Argentina, Chile
        {2, "Brasil", {10, 0, 7, 1, 8, 4, 11, 6, 9}, -1, 0}, // Vecinos: Uruguay, Argentina, Paraguay, Bolivia, Perú, Colombia, Venezuela, Guyana, Surinam
        {3, "Chile", {8, 1, 0}, -1, 0},                      // Vecinos: Perú, Bolivia, Argentina
        {4, "Colombia", {11, 2, 8, 5}, -1, 0},               // Vecinos: Venezuela, Brasil, Perú, Ecuador
        {5, "Ecuador", {4, 8}, -1, 0},                       // Vecinos: Colombia, Perú
        {6, "Guyana", {11, 2, 9}, -1, 0},                    // Vecinos: Venezuela, Brasil, Surinam
        {7, "Paraguay", {1, 2, 0}, -1, 0},                   // Vecinos: Bolivia, Brasil, Argentina
        {8, "Peru", {5, 4, 2, 1, 3}, -1, 0},                 // Vecinos: Ecuador, Colombia, Brasil, Bolivia, Chile
        {9, "Surinam", {6, 2}, -1, 0},                       // Vecinos: Guyana, Brasil
        {10, "Uruguay", {2, 0}, -1, 0},                      // Vecinos: Brasil, Argentina
        {11, "Venezuela", {4, 2, 6}, -1, 0}                  // Vecinos: Colombia, Brasil, Guyana
    };
}

// Calibración de alfa
void calibracion() {
    double mejorAlfa = 0;
    double menorPromedio = INT_MAX;

    cout << "=== CALIBRACION DE ALFA ===" << endl << endl;

    for (double alfa = 0.0; alfa <= 1.0; alfa += 0.1) {
        cout << "Probando alfa = " << fixed << setprecision(1) << alfa << "... ";

        // Probar 10 veces
        int totalColores = 0;
        for (int test = 0; test < 10; test++) {
            vector<struct Pais> paises;
            inicializarGrafoSudamerica(paises);
            totalColores += colorearMapaGRASP(paises, alfa);
        }
        double promedio = (double)totalColores / 10.0;

        cout << "Promedio: " << promedio << endl;

        if (promedio < menorPromedio) {
            menorPromedio = promedio;
            mejorAlfa = alfa;
        }
    }

    cout << "\nMejor alfa: " << fixed << setprecision(1) << mejorAlfa
         << " con promedio de colores: " << menorPromedio << endl;
}

int main() {
    srand(time(NULL));

    // Descomentar para hacer calibración
    // calibracion();

    // Resolver con alfa óptimo
    double alfa = 0.3;

    vector<struct Pais> paises;
    inicializarGrafoSudamerica(paises);

    cout << "Coloreando mapa de Sudamerica con GRASP (alfa = " << alfa << ")..." << endl;

    int cantidadColores = colorearMapaGRASP(paises, alfa);

    imprimirSolucion(paises, cantidadColores);

    return 0;
}