#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct Pais {
    int id;
    string nombre;
    vector<int> vecinos;  // IDs de países vecinos
    int color;            // Color asignado (-1 = sin colorear)
    int gradoVecindad;    // Cantidad de vecinos (para ordenar)
};

// Comparador: Países con más vecinos primero
bool comparaPaises(struct Pais k, struct Pais g) {
    return k.gradoVecindad > g.gradoVecindad; //Descendente (Mayor a menor)
}

/*
 * ALGORITMO VORAZ PARA COLOREADO DE GRAFOS
 *
 * Estrategia:
 * 1. Ordenar países por grado de vecindad (más vecinos primero)
 *    Razón: Países con más restricciones se colorean primero
 *
 * 2. Para cada país en orden:
 *    a) Identificar colores usados por vecinos ya coloreados
 *    b) Asignar el color MÍNIMO disponible (greedy)
 *    c) Si todos están ocupados, crear un nuevo color
 *
 * 3. Greedy: Siempre elegir el color más pequeño disponible
 *    para minimizar el número total de colores
 *
 * Complejidad: O(n^2 * m) donde n = países, m = promedio de vecinos
 */

int colorearMapa(struct Pais paises[], int n) {
    // Inicialización: Calcular grado de vecindad y marcar sin colorear
    for (int i = 0; i < n; i++) {
        paises[i].gradoVecindad = paises[i].vecinos.size();
        paises[i].color = -1;  // -1 indica sin colorear
    }

    // Ordenar por grado de vecindad (descendente)
    // Los más conectados se colorean primero para evitar conflictos
    sort(paises, paises + n, comparaPaises);

    int maxColor = INT_MIN;  // Rastrear el número máximo de colores usados

    // Colorear cada país en orden
    for (int i = 0; i < n; i++) {
        // Vector para marcar qué colores están ocupados por vecinos
        vector<bool> coloresUsados(n + 1, false);

        for (int vecino : paises[i].vecinos) { // Revisar todos los vecinos del país actual
            for (int j = 0; j < n; j++) { // Buscar el vecino en el arreglo de países
                if (paises[j].id == vecino && paises[j].color != -1) { // Si encontramos al vecino Y ya tiene color asignado
                    coloresUsados[paises[j].color] = true; // Marcar ese color como no disponible
                    break;  // Ya encontramos al vecino, salir del loop
                }
            }
        }

        // Asignar el primer color disponible (Comenzando desde 1)
        // GREEDY: Elegir siempre el color mínimo para minimizar el total de colores
        for (int color = 1; color <= n; color++) { //Como maximo hay n colores (En el peor de los casos)
            if (!coloresUsados[color]) {
                paises[i].color = color;
                // Actualizar el máximo color usado
                if (color > maxColor) {
                    maxColor = color;
                }
                break;  // Ya asignamos color, salir
            }
        }
    }

    return maxColor;  // Retornar número total de colores usados
}

// Función para imprimir resultados agrupados por color
void imprimirResultado(struct Pais paises[], int n, int numColores) {
    cout << "Colores utilizados: " << numColores << endl << endl;

    // Para cada color, imprimir los países que lo usan
    for (int color = 1; color <= numColores; color++) {
        cout << "Color " << color << ": ";
        bool primero = true;  // Bandera para controlar las comas

        for (int i = 0; i < n; i++) {
            if (paises[i].color == color) {
                if (!primero) cout << ", ";  // Coma antes de cada país excepto el primero
                cout << paises[i].nombre;
                primero = false;
            }
        }
        cout << endl;
    }
}

int main() {
    // Definición de los 12 países de Sudamérica con sus fronteras
    // Formato: {id, nombre, {vecinos}, color, gradoVecindad}

    struct Pais paises[] = {
        {1, "Argentina", {4, 2, 8, 3, 11}, -1, 0},           // Vecinos: Chile, Bolivia, Paraguay, Brasil, Uruguay
        {2, "Bolivia", {9, 3, 8, 1, 4}, -1, 0},              // Vecinos: Perú, Brasil, Paraguay, Argentina, Chile
        {3, "Brasil", {11, 1, 8, 2, 9, 5, 12, 7, 10}, -1, 0}, // Vecinos: Uruguay, Argentina, Paraguay, Bolivia, Perú, Colombia, Venezuela, Guyana, Surinam
        {4, "Chile", {9, 2, 1}, -1, 0},                      // Vecinos: Perú, Bolivia, Argentina
        {5, "Colombia", {12, 3, 9, 6}, -1, 0},               // Vecinos: Venezuela, Brasil, Perú, Ecuador
        {6, "Ecuador", {5, 9}, -1, 0},                       // Vecinos: Colombia, Perú
        {7, "Guyana", {12, 3, 10}, -1, 0},                   // Vecinos: Venezuela, Brasil, Surinam
        {8, "Paraguay", {2, 3, 1}, -1, 0},                   // Vecinos: Bolivia, Brasil, Argentina
        {9, "Peru", {6, 5, 3, 2, 4}, -1, 0},                 // Vecinos: Ecuador, Colombia, Brasil, Bolivia, Chile
        {10, "Surinam", {7, 3}, -1, 0},                      // Vecinos: Guyana, Brasil
        {11, "Uruguay", {3, 1}, -1, 0},                      // Vecinos: Brasil, Argentina
        {12, "Venezuela", {5, 3, 7}, -1, 0}                  // Vecinos: Colombia, Brasil, Guyana
    };

    int n = sizeof(paises) / sizeof(paises[0]);

    // Ejecutar algoritmo de coloreado
    int numColores = colorearMapa(paises, n);

    // Mostrar resultados
    imprimirResultado(paises, n, numColores);

    return 0;
}