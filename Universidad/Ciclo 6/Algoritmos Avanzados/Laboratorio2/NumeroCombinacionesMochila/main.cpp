#include <iostream>
#include  <iomanip>
using namespace std;

int subConjunto(int *paq, int n, int peso) {
    int dp[n + 1][peso + 1]{};

    //Inicializar primera columna
    for (int k = 0; k <= n; k++) {
        dp[k][0] = 1;
    }

    //Inicializar primera fila
    for (int g = 1; g <= peso; g++) {
        dp[0][g] = 0;
    }

    //Llenar la tabla

    //Cuantas combinaciones de estos valores llegaron a ese peso
    //Cuantas combinaciones de paquetes puedo hacer para llenar la mochila

    for (int fila = 1; fila <= n; fila++) { //Por cada fila
        for (int colu = 1; colu <= peso; colu++) { //Sus columnas
            // Caso 1: No incluir el elemento actual
            dp[fila][colu] = dp[fila - 1][colu];

            // Caso 2: Incluir el elemento actual (si es posible)
            if (colu >= paq[fila - 1]) {//colu - paq[fila - 1] >= 0
                dp[fila][colu] += dp[fila - 1][colu - paq[fila - 1]];
            }
        }
    }

    //Imprimir la tabla
    cout << "Tabla DP (filas=mochilas, columnas=pesos):" << endl;
    cout << "     ";
    for (int g = 0; g <= peso; g++) {
        cout << setw(2) << g << " ";
    }
    cout << endl;

    for (int k = 0; k <= n; k++) {
        if (k == 0) cout << " 0 : ";
        else cout << setw(2) << paq[k-1] << " : ";

        for (int g = 0; g <= peso; g++) {
            cout << setw(2) << dp[k][g] << " ";
        }

        cout << endl;
    }

    //Comentario adicional
    //Es mas que todo una combinatoria no una permutacion
    //Solo importa qué elementos seleccionas

    /*El ultimo ejemplo de
        Para {2, 3, 5, 7, 10} y peso 10:
    COMBINACIONES (lo que encuentras):

    -    {2, 3, 5} ✅
    -    {3, 7} ✅
    -    {10} ✅
    Combinaciones = 3
    */

    return dp[n][peso]; //Devuelve la cantidad de combinaciones
}

int main() {
    //int paq[] = {2, 3, 6};
    //int paq[] = {2, 4, 6};
    //int paq[] = {2, 3, 5, 7};
    int paq[] = {2, 3, 5, 7, 10};
    int n = sizeof(paq) / sizeof(paq[0]);

    int peso = 10;

    int comb = subConjunto(paq, n, peso);
    cout << "Cantidad combinaciones encontradas en " << peso << ": " << comb << endl;
    if (comb) {
        cout << "Si entra exacto" << endl;
    }
    else {
        cout << "No entra exacto" << endl;
    }
    return 0;
}