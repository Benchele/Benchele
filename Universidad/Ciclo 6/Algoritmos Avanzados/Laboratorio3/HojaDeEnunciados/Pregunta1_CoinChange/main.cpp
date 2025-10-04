#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

struct Solucion {
    int dinero;
    int cantidad;
};

bool compara(int k, int g) {
    return k > g; //Descendente (Mayor a menor)
}

int buscaCambio(int *dinero, int cambio, int n) {
    vector<struct Solucion> resultado;

    //Ordenar las monedas de mayor a menor
    sort(dinero, dinero + n, compara);

    //Recorrer todas las monedas
    for (int k = 0; k < n; k++) {
        int cantidad = 0;

        //Hallar la maxima cantidad de esa moneda que puedes cambiar
        while (dinero[k] <= cambio) {
            cambio -= dinero[k];
            cantidad++;
        }

        // Solo agregar si usamos esta moneda
        if (cantidad > 0) {
            resultado.push_back({dinero[k], cantidad});
        }
    }

    //Impresion
    cout << "Monedas usadas: ";
    for (int k = 0; k < resultado.size(); k++) {
        if (k != 0)cout << ", ";
        cout << resultado[k].dinero << " x " << resultado[k].cantidad;
    }
    cout << endl << "Total de monedas: " << resultado.size() << endl;

    return resultado.size();
}

int main() {

    int monedas[] = {25, 10, 5, 1};
    int n = sizeof(monedas) / sizeof(monedas[0]);

    int cambio = 63;

    buscaCambio(monedas, cambio, n);

    return 0;
}