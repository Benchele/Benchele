#include <iostream>
#include <iomanip>
#include <climits>
#include <cmath>
using namespace std;

int maxGanancia(int *precios, int cantVentas, int n) {
    int dp[cantVentas + 1][n];

    //Inicalizar primera columna -> No hay ganancia
    for (int k = 0; k <= cantVentas; k++) {
        dp[k][0] = 0;
    }

    //Inicializar la primera fila -> No hay transacciones -> No hay ganancia
    for (int g = 0; g < n; g++) {
        dp[0][g] = 0;
    }

    //Completar tabla
    for (int fila = 1; fila <= cantVentas; fila++) {
        for (int colu = 1; colu < n; colu++) {
            int maximo = INT_MIN;
            for (int k = 0; k < colu; k++) {
                maximo = max(maximo, precios[colu] - precios[k] + dp[fila - 1][k]);
                //La ganacia de la iteracion mas lo maximo que se llego hasta ese dia en la transaccion anterior fila - 1
            }
            dp[fila][colu] = max(maximo, dp[fila][colu - 1]);
            //Se compara el maximo con el valor de la izquierda, ya que puede que no convenga vender en ese dia y se mantenga el valor anterior
        }
    }
    //Esto funciona porque el modelo asume que puedes cerrar una transacción y abrir otra el mismo día.
    //Es decir que puedes vender y comprar el mismo día.
    //Compra    Venta/Otra compra       Venta de la otra compra


    //Impresion
    for (int k = 0; k <= cantVentas; k++) {
        for (int g = 0; g < n; g++) {
            cout << setw(4) << dp[k][g] << " ";
        }
        cout << endl;
    }

    cout << "La ganancia es: " << dp[cantVentas][n - 1] << endl;

    return dp[cantVentas][n - 1];
}
int main() {
    int k = 3;
    int precios[] = {315, 322, 385,	375, 365, 380, 390, 375, 400};
    //int precios[] = {315, 322, 385,	386, 387, 388, 389, 390, 400};
    int n = sizeof(precios) / sizeof(precios[0]);

    //cout << "La ganancia es: " << maxGanancia(precios, k, n) << endl;
    maxGanancia(precios, k, n);

    return 0;
}