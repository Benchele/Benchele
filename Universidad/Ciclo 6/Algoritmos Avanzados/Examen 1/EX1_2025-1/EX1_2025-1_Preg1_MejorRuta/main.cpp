#include <iostream>
#include <vector>
#include <iomanip>
#include <climits>
using namespace std;

// Variables globales para almacenar resultados
double distanciaMinima = INT_MAX;
vector<int> rutaOptima;
int contadorRutas = 0;

// Estrategia: Backtracking para generar todas las permutaciones (TSP)

// Función backtracking para generar todas las rutas posibles
int backtracking(vector<int>& ruta, vector<bool>& visitados, const vector<vector<double>>& matriz, int n, double distanciaActual, int posActual) {
    // Caso base: se han visitado todos los puntos
    if (ruta.size() == n + 1) {
        contadorRutas++;

        // Sumar la distancia de regreso al almacén
        double distanciaTotal = distanciaActual + matriz[posActual][0];

        // Actualizar si es mejor que el mínimo actual
        if (distanciaTotal < distanciaMinima) {
            distanciaMinima = distanciaTotal;
            rutaOptima = ruta;
        }

        return 0;
    }

    // Explorar todas las posibles extensiones de la ruta actual
    for (int i = 1; i < n + 1; i++) {
        if (!visitados[i]) {
            // Marcar como visitado
            visitados[i] = true;
            ruta.push_back(i);

            // Acumular la distancia desde la posición actual hacia el siguiente punto
            double nuevaDistancia = distanciaActual + matriz[posActual][i];

            // Llamada recursiva
            if (backtracking(ruta, visitados, matriz, n, nuevaDistancia, i)) {
                return 1;
            }

            // Backtracking
            ruta.pop_back();
            visitados[i] = false;
        }
    }

    return 0;
}

int main() {
    // Matriz de distancias del ejemplo
    vector<vector<double>> matriz = {
        {0.00, 2.24, 2.69, 4.00, 2.06, 3.35},
        {2.24, 0.00, 4.50, 5.39, 1.50, 5.59},
        {2.69, 4.50, 0.00, 5.59, 4.74, 2.55},
        {4.00, 5.39, 5.59, 0.00, 4.03, 3.91},
        {2.06, 1.50, 4.74, 4.03, 0.00, 5.10},
        {3.35, 5.59, 2.55, 3.91, 5.10, 0.00}
    };

    int n = matriz.size() - 1; // Número de puntos a visitar (excluyendo almacén)

    vector<int> ruta;
    vector<bool> visitados(n + 1, false);

    // Marcar el almacén como visitado (punto 0)
    visitados[0] = true;
    ruta.push_back(0);

    // Ejecutar backtracking (comenzando con distancia 0 y posición en almacén)
    backtracking(ruta, visitados, matriz, n, 0.0, 0);

    // Mostrar resultados
    cout << "Número de rutas generadas: " << contadorRutas << endl;
    cout << "Ruta optima: ";
    for (int punto : rutaOptima) {
        cout << punto << " ";
    }
    cout << "(distancia " << fixed << setprecision(2) << distanciaMinima << ")" << endl;

    return 0;
}