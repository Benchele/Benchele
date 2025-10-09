#include <iostream>
#include <iomanip>
using namespace std;

int calcularManeras(int *billetes, int n, int monto) {
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

    return dp[n][monto];
}

int main() {
    int cambio[] = {2, 5, 10, 20};
    //int cambio[] = {1, 2, 10, 20};

    int n = sizeof(cambio) / sizeof(cambio[0]);

    int monto = 13;

    int maneras = calcularManeras(cambio, n, monto);

    cout << "Se desea llegar al monto de " << monto << " dinares" << endl;
    cout << "Respuesta: " << maneras;
    if (maneras == 1) cout << " forma" << endl;
    else cout << " formas" << endl;

    return 0;
}