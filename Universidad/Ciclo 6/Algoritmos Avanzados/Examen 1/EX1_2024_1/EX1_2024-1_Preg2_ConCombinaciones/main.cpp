#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

// Variables globales para imprimir las combinaciones
int *g_billetes;
int g_n;
vector<vector<int>> g_combinaciones;

//Backtracking para encontrar las combinaciones
void encontrarCombinaciones(int dp[][100], int fila, int monto, vector<int> &actual) {
    // Caso base: llegamos al monto 0
    if (monto == 0) {
        g_combinaciones.push_back(actual);
        return;
    }

    // Caso base: no hay más monedas disponibles
    if (fila == 0) {
        return;
    }

    // Opción 1: No usar la moneda actual (viene de la fila anterior)
    if (dp[fila - 1][monto] > 0) {
        encontrarCombinaciones(dp, fila - 1, monto, actual);
    }

    // Opción 2: Usar la moneda actual (si es posible)
    if (monto >= g_billetes[fila - 1] and dp[fila][monto - g_billetes[fila - 1]] > 0) {
        actual.push_back(g_billetes[fila - 1]);
        encontrarCombinaciones(dp, fila, monto - g_billetes[fila - 1], actual);
        actual.pop_back(); // Backtracking
    }
}

//Impresion de las combinaciones //Se usa backtracking
void buscarCombinaciones(int *billetes, int n, int monto, int dp[][100]) {
    if (dp[n][monto] > 0) {
        g_billetes = billetes;
        g_n = n;
        g_combinaciones.clear();

        vector<int> combinacionActual;
        encontrarCombinaciones(dp, n, monto, combinacionActual);

        cout << "Las " << g_combinaciones.size() << " combinacion(es) son:" << endl;
        for (int k = 0; k < g_combinaciones.size(); k++) {
            // Ordenar la combinación de menor a mayor
            sort(g_combinaciones[k].begin(), g_combinaciones[k].end());

            cout << "  " << (k + 1) << ". {";
            for (int j = 0; j < g_combinaciones[k].size(); j++) {
                cout << g_combinaciones[k][j];
                if (j < g_combinaciones[k].size() - 1) cout << ", ";
            }
            cout << "}" << endl;
        }
        cout << endl;
    }
}

//Programacion dinamica
int calcularManeras(int *billetes, int n, int monto, bool mostrarCombinaciones) {
    int dp[n + 1][monto + 1];

    //Inicializar la primera fila en 0
    for (int k = 0; k <= monto; k++) {
        dp[0][k] = 0;
    }

    //Inicializar la primera columna en 1
    for (int k = 0; k <= n; k++) {
        dp[k][0] = 1;
    }

    //LLenar la tabla
    for (int fila = 1; fila <= n; fila++) {
        for (int colu = 1; colu <= monto; colu++) {
            dp[fila][colu] = dp[fila - 1][colu]; //Maneras sin usar el billete actual
            if (colu >= billetes[fila - 1]) { //Si el monto actual es mayor o igual al billete actual
                dp[fila][colu] += dp[fila][colu - billetes[fila - 1]]; //Sumar las maneras de hacer el monto restante
            }
        }
    }

    //Impresion
    cout << "   ";
    for (int k = 0; k <= monto; k++) {
        cout << setw(3) << k << " ";
    }
    cout << endl;

    for (int k = 0; k <= n; k++) {
        if (k == 0) cout << setw(3) << "0";
        else cout << setw(2) << billetes[k - 1] << " ";

        for (int g = 0; g <= monto; g++) {
            cout << setw(3) << dp[k][g] << " ";
        }
        cout << endl;
    }
    cout << endl;

    //Mostrar combinaciones
    if (mostrarCombinaciones) { // Encontrar y mostrar combinaciones si se solicita
        int dpCopia[100][100]; //Para poder pasarlo como parametro
        for (int k = 0; k <= monto; k++) {
            for (int g = 0; g <= monto; g++) {
                dpCopia[k][g] = dp[k][g];
            }
        }
        buscarCombinaciones(billetes, n, monto, dpCopia);
    }

    return dp[n][monto];
}

int main() {
    int cambio[] = {2, 5, 10, 20};
    //int cambio[] = {1, 2, 10, 20};

    int n = sizeof(cambio) / sizeof(cambio[0]);

    int monto = 13;

    int maneras = calcularManeras(cambio, n, monto, true);

    cout << "Se desea llegar al monto de " << monto << " dinares" << endl;
    cout << "Respuesta: " << maneras;
    if (maneras == 1) cout << " forma" << endl;
    else cout << " formas" << endl;

    return 0;
}