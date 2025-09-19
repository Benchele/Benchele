#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

#define N 50

void buscarValoresMochila(int *pesos, int *valor, int n, int capacidad, int dp[][N]) {
    int pesosQueEntranIndex[N]{};
    int cant = 0;
    int pesoActual = capacidad;

    //Buscando valores que entran en la mochila
    //Considerando k como la fila
    for (int k = n; k > 0 and pesoActual > 0; k --) {
        if (dp[k][pesoActual] != dp[k - 1][pesoActual]) { //Si son diferentes valores
            // Significa que el objeto k-1 fue incluido
            pesosQueEntranIndex[cant++] = k - 1; //Guardamos el índice
            pesoActual -= pesos[k - 1];         //Reducimos la capacidad
        }
    }

    cout << "Objetos elegidos: " << endl;
    for (int i = cant - 1; i >= 0; i--) {
        cout << "(Peso = " << pesos[pesosQueEntranIndex[i]]
             << ", Valor = " << valor[pesosQueEntranIndex[i]] << ") " << endl;
    }
    cout << endl;
}

int mochila(int *pesos, int *valor, int n, int capacidad) {
    int dp[n + 1][capacidad + 1]{};
    int capa = capacidad;

    //Inicializar la primera columna
    for (int k = 0; k <= n; k++) {
        dp[k][0] = 0;
    }

    //Inicializar la primera fila
    for (int k = 0; k <= capa; k++) {
        dp[0][k] = 0;
    }

    //Estos inicializados se pueden hacer colocando llaves en la creacion de dp

    //Completar la tabla
    //Yendo fila por fila
    for (int fila = 1; fila <= n; fila++) {
        for (int colu = 1; colu <= capacidad; colu++) {
            if (colu - pesos[fila - 1] >= 0) {
                dp[fila][colu] = max(dp[fila - 1][colu], valor[fila - 1] + dp[fila - 1][colu - pesos[fila - 1]]);
                //Se elige el maximo entre el anterior o la suma de la mochilas
            }
            else {
                dp[fila][colu] = dp[fila - 1][colu];
            }
        }
    }

    //Yendo columna por columna
    // for (int colu = 1; colu <= capacidad; colu++) {
    //     for (int fila = 1; fila <= n; fila++) {
    //         if (colu - pesos[fila - 1] >= 0) {
    //             dp[fila][colu] = max(dp[fila - 1][colu], valor[fila - 1] + dp[fila - 1][colu - pesos[fila - 1]]);
    //             //Se elige el maximo entre el anterior o la suma de la mochilas
    //         }
    //         else {
    //             dp[fila][colu] = dp[fila - 1][colu];
    //         }
    //     }
    // }

    //Independientemente del recorrido va a quedar igual
    //Ya que cada casilla depende de la fila anterior

    //Imprimir tabla
    for (int k = 0; k <= n; k++) {
        for (int g = 0; g <= capa; g++) {
            cout << setw(4) << dp[k][g] << " ";
        }
        cout << endl;
    }

    cout << "Valor maximo: " << dp[n][capa] << endl;



    //Copiar dp en copiaDp -> Es porque no deja pasar dp como parametro
    int copiaDp[N][N]{};
    for (int k = 0; k <= n; k++) {
        for (int g = 0; g <= capacidad; g++) {
            copiaDp[k][g] = dp[k][g];
        }
    }

    //Busca los valores que entran en la mochila
    buscarValoresMochila(pesos, valor, n, capacidad, copiaDp);

    return dp[n][capa];
}
int main() {
    int pesos[] = {2, 1, 3, 2};
    int valor[] = {12, 10, 20, 15};
    int n = sizeof(pesos) / sizeof(pesos[0]);

    int w = 5;

    //cout << "Valor maximo: " << endl << mochila(pesos, valor, n, w) << endl;

    mochila(pesos, valor, n, w);

    return 0;
}