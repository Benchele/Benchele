#include <iostream>
#include <iomanip>
using namespace std;


int esPosibleCompletar(int *pesos, int m, int w) {
    int dp[m + 1][w + 1]{};

    for (int k = 0; k <= m; k++) {
        dp[k][0] = 1;
    }

    //Llenar la tabla
    for (int fila = 1; fila <= m; fila++) { //Por cada fila
        for (int colu = 1; colu <= w; colu++) { //Sus columnas
            dp[fila][colu] = dp[fila - 1][colu]; //Es igual al de arriba
            if (colu - pesos[fila - 1] >= 0 and dp[fila][colu] == 0) { //Solo si la resta es mayor o igual a 0 y el anterior es 0
                dp[fila][colu] = dp[fila - 1][colu - pesos[fila - 1]];
            }
        }
    }


    //Imprimir la tabla
    for (int j = 0; j <= w; j++) {
        cout << setw(2) << j << " ";
    }
    cout << endl;
    for (int k = 0; k <= m; k++) {
        for (int g = 0; g <= w; g++) {
            cout << setw(2) << dp[k][g] << " ";
        }
        cout << endl;
    }

    //Buscar el maximo
    int maximo = 0;
    for (int k = w; k >= 0; k--) {
        if (dp[m][k] == 1) {
            maximo = k;
            break;
        }
    }

    //Resultado
    if (maximo == w) {
        cout << "Se logro llegar al peso" << maximo << endl;
    }
    else {
        cout << "No se logro llegar al peso, el maximo fue: " << maximo << endl;
    }

    return maximo;
}

int main() {
    //int pesos[] = {7, 2, 5, 5, 10};
    int pesos[] = {7, 2, 1, 1, 10};
    int m = sizeof(pesos) / sizeof(pesos[0]);
    int w = 25;

    esPosibleCompletar(pesos, m, w);


    return 0;
}