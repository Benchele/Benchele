#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

bool compara(int k, int g) {
    return k < g; // Ascendente (Menor a mayor)
    // return k > g; // Descendente (Mayor a menor)
}

void imprimir(int *paquete, int n) {
    for (int k = 0; k < n; k++) {
        cout << paquete[k] << " ";
    }
    cout << endl;
}

int cargaMochila(int *paquete, int peso, int n) {
    //Ordenar los paquetes de menor a mayor
    sort(paquete, paquete + n, compara);
    imprimir(paquete, n);

    //Caso base
    int residual = peso;

    for (int k = 0; k < n; k++) { //Recorrer todos los paquetes
        if (residual - paquete[k] >= 0) { //El paquete cabe en la mochila
            residual -= paquete[k]; //Actualizar el peso residual
        }
    }

    return residual;
}

int main() {
    //En este caso se quiere meter la mayor cantidad de paquetes en una mochila

    int paquete[] = {3, 2, 2, 10, 4};
    int peso = 15;
    int n = sizeof(paquete)/sizeof(paquete[0]);

    cout << "Espacio sobrante: " << cargaMochila(paquete, peso, n) << endl;

    return 0;
}