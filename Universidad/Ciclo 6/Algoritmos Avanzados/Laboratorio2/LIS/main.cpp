#include <iostream>
#include <iomanip>
using namespace std;

int mayorLongitud(int *valores, int n) {
    int dp[n];
    int previo[n]; // previo[i] = índice anterior en la subsecuencia


    //Inicialización
    for (int i = 0; i < n; i++) {
        dp[i] = 1; // Inicializar todas las longitudes a 1
        previo[i] = -1; // Inicializar todos los previos a -1 (sin previo)
    }

    int maxLongitud = 1;
    int ultimoIndice = 0; // Índice del último elemento de la subsecuencia más larga


    //LIS
    for (int k = 1; k < n; k++) {
        for (int g = 0; g <= k - 1; g++) {
            if (valores[g] < valores[k] and dp[g] + 1 > dp[k]) {
                dp[k] = dp[g] + 1; // Actualizar la longitud máxima
                previo[k] = g; // Actualizar el índice previo

            }
        }
        if (dp[k] > maxLongitud) {
            maxLongitud = dp[k];
            ultimoIndice = k; // Actualizar el índice del último elemento
        }
    }

    //Reconstrucción de la subsecuencia
    //int subSecuencia[maxLongitud]{}; //MaxLongitud no está reconocido en tiempo de compilacion
    int subSecuencia[50]{};
    int k = maxLongitud - 1;

    for (int g = ultimoIndice; g != -1; g = previo[g]) {
        subSecuencia[k] = valores[g]; //Del ultimo al primero
        k--;
    }

    //Impresión de la subsecuencia
    cout << "Mayor longitud de subsecuencia: " << maxLongitud << endl;
    cout << "Subsecuencia: ";
    for (int i = 0; i < maxLongitud; i++) {
        cout << subSecuencia[i] << " ";
    }
    cout << endl;

    return 1;
}
int main() {
    //Formula
    //F(i) = 1 + maxj=0....i-1 (F(j), Xj < Xi)  i > 0
    //F(i) = 1   i = 0

    //int valores[] = {-7, 10, 9, 8, 2, 3, 8, 8, 1};
    int valores[] = {-7, 10, 9, 8, 2, 3, 8, 8, 1, 2, 3, 4};
    int n = sizeof(valores) / sizeof(valores[0]);

    //cout << "Mayor longitud de subsecuencia: " << mayorLongitud(valores, n) << endl;

    mayorLongitud(valores, n);

    return 0;
}