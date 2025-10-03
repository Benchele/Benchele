#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Paquete {
    int ganancia;
    int peso;
};

struct Solucion {
    int ganancia;
    int residual;
};

bool compara(struct Paquete k, struct Paquete g) {
    return (double)k.ganancia/k.peso > (double)g.ganancia/g.peso; //Descendente (Mayor a menor)
}

struct Solucion cargaContenedor(Paquete *paquetes, int peso, int n) {
    Solucion solucion;

    //Ordenamos los paquetes
    sort(paquetes, paquetes + n, compara);

    //Caso base
    solucion.ganancia = 0;
    solucion.residual = peso;

    for (int k = 0; k < n; k++) {
        if (solucion.residual - paquetes[k].peso >= 0) { //El paquete entra
            solucion.ganancia += paquetes[k].ganancia;
            solucion.residual -= paquetes[k].peso;
        }
    }

    return solucion;
}
int main() {
    //Siempre tomar en cuenta la formula
    //Todo lo que se tiene que maximizar/todo lo que se tiene que minimizar

    struct Paquete paquetes[] = {
        {10, 2},
        {15, 3},
        {10, 5},
        {24, 12},
        {8, 2}
    };

    //Caso 2
    //struct Paquete paquetes[] = {{10, 2}, {15, 3}, {10, 5}, {14, 12}, {8, 2}, {5, 5}};

    int peso = 16;
    //int peso = 20; //Caso 2

    int n = sizeof(paquetes) / sizeof(paquetes[0]);

    Solucion solucion = cargaContenedor(paquetes, peso, n);

    cout << "Peso sobrante en el contenedor: " << solucion.residual << " Tn" << endl;
    cout << "Ganancia de la exportacion: " << solucion.ganancia << " en miles de dolares" << endl;

    return 0;
}