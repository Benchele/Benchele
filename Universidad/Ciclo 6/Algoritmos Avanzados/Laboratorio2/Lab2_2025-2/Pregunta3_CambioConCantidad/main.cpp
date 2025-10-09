#include <iostream>
#include <iomanip>
#include <cmath>
#include <climits>
using namespace std;

int calcularCambios(int *billetes, int n, int cambios) {
    int dp[n + 1][cambios + 1]{};

    //Inicializar primera fila
    for (int i = 1; i <= cambios; i++) {
        dp[0][i] = 9999;
    }

    //Inicializar primera columna
    for (int i = 1; i <= n; i++) {
        dp[i][0] = 0;
    }

    //Llenar tabla
    for (int fila = 1; fila <= n; fila++) {
        for (int colu = 1; colu <= cambios; colu++) {
            if (colu % billetes[fila - 1] == 0) {
                dp[fila][colu] = min(dp[fila - 1][colu], colu / billetes[fila - 1]);
            }
            else {
                if (colu < billetes[fila - 1]) {
                    dp[fila][colu] = dp[fila - 1][colu];
                }
                else {
                    int residuo = colu % billetes[fila - 1];
                    if (dp[fila - 1][colu % billetes[fila - 1]] == 9999 and billetes[fila - 1] % residuo != 0) {
                        //Si en caso el residuo no puede completarse, se tiene que buscar otra combinacion
                        int division = colu / billetes[fila - 1] - 1;
                        int resta = colu - division*billetes[fila - 1];
                        dp[fila][colu] = min(dp[fila - 1][colu], dp[fila - 1][resta] + division);
                    }
                    else {
                        dp[fila][colu] = min(dp[fila - 1][colu], dp[fila - 1][colu % billetes[fila - 1]] + colu / billetes[fila - 1]);
                    }
                }

            }
        }
    }

    //Imprimir tabla
    for (int colu = 0; colu <= cambios; colu++) {
        cout << setw(5) << colu << " ";
    }
    cout << endl;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= cambios; j++) {
            cout << setw(5) << dp[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    int cambioCon = dp[n][cambios];
    if (cambioCon == 9999) {
        cambioCon = 0;
    }
    cout << "Se puede brindar el cambio con " << cambioCon << " monedas o billetes" << endl;

    return cambioCon;
}

int main() {
    int billetes[] = {2, 5, 10};
    int n = sizeof(billetes) / sizeof(billetes[0]);
    int suma = 0;

    cout << "Si se cuenta con las siguientes monedas o billetes (soles): ";
    for (int i = 0; i < n; i++) {
        cout << setw(2) << billetes[i] << " ";
    }
    cout << endl;

    int cambio = 19;
    cout << "Y se quiere brindar un cambio de " << cambio << " soles" << endl;

    calcularCambios(billetes, n, cambio);

    //Lo importante es el ultimo dp[n][cambios]

    return 0;
}