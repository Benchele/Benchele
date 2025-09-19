#include <iostream>
#include <iomanip>
#define N 20
using namespace std;

void buscarValoresMochila(int *paq, int n, int peso, int dp[][N]) {
    int mochila = -1;
    //Esto es en caso se pide hallar mochila maxima...#
    for (int k = peso; k >= 0; k--) {
        if (dp[n][k] == 1) {
            mochila = k;
            break;
        }
    }
    if (mochila == -1) {
        cout << "No se pudo llenar la mochila" << endl;
        return;
    }

    //Caso mochila exacta...*
    // if (dp[n][peso] == 0) {
    //     cout << "No se pudo llenar la mochila exacta" << endl;
    //     return;
    // }

    int valores[50]{};
    int cant = 0;
    int pesoActual = mochila;//...#
    //Si fuera mochila exacta -> int pesoActual = peso;...*

    //Buscando valores mochila
    for (int k = n; k > 0 and pesoActual > 0; k--) {
        if (dp[k][pesoActual] == 1 and dp[k - 1][pesoActual] == 0) {//Si es 1 y el de arriba es 0,es decir, son diferentes
            //if (dp[k][pesoActual] != dp[k - 1][pesoActual]){  //Es lo mismo, ya que previamente (En * o en #) se asegura que hay un 1 en dp[k][pesoActual]
            valores[cant++] = paq[k - 1];
            pesoActual -= paq[k - 1];
        }
    }

    //Imprimir valores

    cout << "Valores que entran en la mochila: ";
    for (int i = 0; i < cant; i++) {
        cout << valores[i] << " ";
    }
    cout << endl;

    //Verificar suma
    int suma = 0;
    for (int i = 0; i < cant; i++) {
        suma += valores[i];
    }
    cout << "Suma verificada: " << suma << " -> Debe ser " << mochila << endl;
}

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
    for (int fila = 1; fila <= n; fila++) { //Por cada fila
        for (int colu = 1; colu <= peso; colu++) { //Sus columnas
            dp[fila][colu] = dp[fila - 1][colu]; //Es igual al de arriba
            if (colu - paq[fila - 1] >= 0 and dp[fila][colu] == 0) { //Solo si la resta es mayor o igual a 0 y el anterior es 0
                dp[fila][colu] = dp[fila - 1][colu - paq[fila - 1]];
            }
        }
    }

    //Imprimir la tabla
    for (int k = 0; k <= n; k++) {
        for (int g = 0; g <= peso; g++) {
            cout << dp[k][g] << " ";
        }
        cout << endl;
    }

    //Copiar dp en copiadp -> Es porque no deja pasar como parametro a dp
    int copiaDp[N][N]{};
    for (int k = 0; k <= n; k++) {
        for (int g = 0; g <= peso; g++) {
            copiaDp[k][g] = dp[k][g];
        }
    }

    //Busca los valores que entran en la mochila
    buscarValoresMochila(paq, n, peso, copiaDp);

    //Si te piden la mejor respuesta buscas en el ultima fila el primer 1 buscando de derecha a izquierda

    return dp[n][peso]; //Devuelve si entra o no entra
}

int main() {
    int paq[] = {2, 3, 6};
    int n = sizeof(paq) / sizeof(paq[0]);

    int peso = 10;

    if (subConjunto(paq, n, peso)) {
        cout << "Si entra exacto" << endl;
    }
    else {
        cout << "No entra exacto" << endl;
    }

    return 0;
}