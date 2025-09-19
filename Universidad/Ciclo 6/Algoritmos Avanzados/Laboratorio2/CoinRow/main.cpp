#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int elegidas[100]{};

void imprimirMonedasElegidas(int n) {
    for (int k = 0; k < n; k++) {
        //cout << setw(4) << elegidas[k];
        if (elegidas[k] != 0) {
            cout << elegidas[k] << " ";
        }
    }
    cout << endl;
}
int mejorSeleccion(int *monedas, int n) {
    int dp[n + 1];
    dp[0] = 0; //Caso base
    dp[1] = monedas[0]; //Mejor valor con la primera moneda


    for (int i = 2; i <= n; i++) { //A partir de monedas[1] y dp[2]
        dp[i] = max(dp[i - 1],monedas[i - 1] + dp[i - 2]);
        //Comparar el mayor valor hasta el anterior con el valor actual + el mejor valor hasta dos posiciones antes
    }

    //Hallar que monedas se escogieron
    for (int i = n; i > 0; ) {
        if (dp[i] == dp[i - 1]) { //No se ha escogido la moneda i-1
            i--;
        } else { //Se ha escogido la moneda i-1
            elegidas[i - 1] = monedas[i - 1]; //Marcar como escogida
            i -= 2; //Saltar a la posicion i-2
        }
    }

    //imprimirMonedasElegidas(n);

    return dp[n]; //Siempre al final se encuentra el mejor valor -> Principio de Optimalidad
}

int main() {
    //Formula
    // Max {F(n-1), C(n) + F(n-2)}        n > 2
    // F(0) = 0, F(1)=c1

    //int monedas[] = {5, 1, 2, 10, 6, 2};
    int monedas[] = {7, 6, 33, 34, 2, 2};
    int n = sizeof(monedas) / sizeof(monedas[0]);

    cout << "Mejor seleccion: " << mejorSeleccion(monedas, n) << endl;

    imprimirMonedasElegidas(n);

    return 0;
}