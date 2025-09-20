#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int CalcularCuadradosPerfectos(int n){
    vector<int> dp(n+1, 999999);
    dp[0] = 0;

    for(int i = 1; i <= n; i++){
        for(int j = 1; j * j <= i; j++){
            dp[i] = min(dp[i], dp[i - j*j] + 1);
        }
    }

    return dp[n];
}

int main() {
    int n;

    // Casos de prueba
    vector<int> casos = {12, 13, 26, 100, 7, 1, 4, 9, 16, 25};

    cout << "Menor cantidad de cuadrados perfectos necesarios:" << endl;
    cout << "=================================================" << endl;

    for(int i = 0; i < casos.size(); i++){
        n = casos[i];
        int resultado = CalcularCuadradosPerfectos(n);
        cout << "N = " << n << " -> " << resultado << " cuadrados perfectos" << endl;
    }

    cout << endl << "Prueba con tu propio numero:" << endl;
    cout << "Ingresa un numero entre 1 y 500: ";
    cin >> n;

    if(n >= 1 and n <= 500){
        int resultado = CalcularCuadradosPerfectos(n);
        cout << "Para N = " << n << " se necesitan " << resultado << " cuadrados perfectos" << endl;
    }
    else {
        cout << "Numero fuera del rango permitido (1-500)" << endl;
    }

    return 0;
}