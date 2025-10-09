#include <iostream>
#include <iomanip>
using namespace std;

int maximaGanancia(int *precios, int n, int cantVentas) {
    int dp[cantVentas + 1][n];
    //Inicalizar primera columna -> No hay ganancia
    for (int k = 0; k <= cantVentas; k++) {
        dp[k][0] = 0;
    }

    //Inicializar la primera fila -> No hay transacciones -> No hay ganancia
    for (int g = 0; g < n; g++) {
        dp[0][g] = 0;
    }

    //Cada mes
    for (int fila = 1; fila <= cantVentas; fila++) {
        for (int colu = 1; colu < n; colu++) {
            int maximo = INT_MIN;
            for (int k = 0; k < colu; k++) {
                maximo = max(maximo, precios[colu] - precios[k] + dp[fila - 1][k]);
            }
            dp[fila][colu] = max(maximo, dp[fila][colu - 1]);
        }
    }

    //10:27 pm

    for (int k = 0; k <= cantVentas; k++) {
        for (int g = 0; g < n; g++) {
            cout << setw(4) << dp[k][g] << " ";
        }
        cout << endl;
    }

    cout << endl << "Para K = " << cantVentas << " compras" << endl;
    cout << "La ganancia maxima sera " << dp[cantVentas][n - 1] << " soles" << endl;

    return dp[cantVentas][n - 1];
}


int main() {
    int k = 2;
    int precios[] = {120, 100, 150, 125, 120, 150, 200, 250};
    int n = sizeof(precios) / sizeof(precios[0]);

    //N = 8

    maximaGanancia(precios, n, k);

    return 0;
}