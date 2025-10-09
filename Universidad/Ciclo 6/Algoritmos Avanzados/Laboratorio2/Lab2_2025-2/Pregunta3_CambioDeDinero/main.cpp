#include <iostream>
#include <iomanip>
#include <climits>
using namespace std;

int calcularCambios(int *billetes, int n, int cambios) {
    int dp[n + 1][cambios + 1];

    // Inicializar primera fila (sin monedas disponibles)
    dp[0][0] = 0;
    for (int i = 1; i <= cambios; i++) {
        dp[0][i] = INT_MAX - 1; // Usamos INT_MAX - 1 para evitar overflow
    }

    // Llenar la tabla
    for (int fila = 1; fila <= n; fila++) {
        for (int colu = 0; colu <= cambios; colu++) {
            // Opción 1: No usar el billete actual
            dp[fila][colu] = dp[fila - 1][colu];

            // Opción 2: Usar el billete actual (si es posible)
            if (colu >= billetes[fila - 1] && dp[fila][colu - billetes[fila - 1]] != INT_MAX - 1) {
                dp[fila][colu] = min(dp[fila][colu], dp[fila][colu - billetes[fila - 1]] + 1);
            }
        }
    }

    // Imprimir tabla
    cout << "   ";
    for (int colu = 0; colu <= cambios; colu++) {
        cout << setw(3) << colu << " ";
    }
    cout << endl;

    for (int i = 0; i <= n; i++) {
        if (i == 0) cout << "[] ";
        else cout << setw(2) << billetes[i-1] << " ";

        for (int j = 0; j <= cambios; j++) {
            if (dp[i][j] >= INT_MAX - 1) {
                cout << setw(3) << "X" << " ";
            } else {
                cout << setw(3) << dp[i][j] << " ";
            }
        }
        cout << endl;
    }
    cout << endl;

    int resultado = dp[n][cambios];
    if (resultado >= INT_MAX - 1) {
        cout << "No es posible dar el cambio exacto" << endl;
        return -1;
    }

    cout << "Se puede brindar el cambio con " << resultado << " monedas o billetes" << endl;
    return resultado;
}

int main() {
    int billetes[] = {2, 5, 10};
    int n = sizeof(billetes) / sizeof(billetes[0]);

    cout << "Si se cuenta con las siguientes monedas o billetes (soles): ";
    for (int i = 0; i < n; i++) {
        cout << setw(2) << billetes[i] << " ";
    }
    cout << endl;

    int cambio = 20;
    cout << "Y se quiere brindar un cambio de " << cambio << " soles" << endl;
    cout << endl;

    calcularCambios(billetes, n, cambio);

    return 0;
}