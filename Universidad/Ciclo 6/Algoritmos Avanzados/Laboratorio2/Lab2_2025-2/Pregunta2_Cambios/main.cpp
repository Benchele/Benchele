#include <iostream>
#include <iomanip>
using namespace std;

int calcularCambios(int *billetes, int n, int cambios) {
    int dp[n + 1][cambios + 1]{};

    //Inicializar primera columna
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1;
    }

    //Llenar tabla
    for (int fila = 1; fila <= n; fila++) {
        for (int colu = 1; colu <= cambios; colu++) {
            dp[fila][colu] = dp[fila - 1][colu];
            if (colu - billetes[fila - 1] >= 0 and dp[fila][colu] == 0) {
                dp[fila][colu] = dp[fila - 1][colu - billetes[fila - 1]];
            }
        }
    }

    //Imprimir tabla
    for (int colu = 0; colu <= cambios; colu++) {
        cout << setw(2) << colu << " ";
    }
    cout << endl;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= cambios; j++) {
            cout << setw(2) << dp[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    //Soluciones
    cout << "Se puede brindar los siguientes cambios (soles): ";
    for (int i = 1; i <= cambios; i++) {
        if (dp[n][i] == 1) {
            cout << setw(2) << i << " ";
        }
    }
    cout << endl;

    return dp[n][cambios];
}
int main() {
    //int billetes[] = {2, 5, 10, 2, 5};
    int billetes[] = {2, 5, 10};
    int n = sizeof(billetes) / sizeof(billetes[0]);
    int suma = 0;


    cout << "Si se cuenta con las siguientes monedas o billetes (soles): ";
    for (int i = 0; i < n; i++) {
        cout << setw(2) << billetes[i] << " ";
        suma += billetes[i]; //El cambio maximo que puede dar
    }
    cout << endl;

    calcularCambios(billetes, n, suma);

    return 0;
}