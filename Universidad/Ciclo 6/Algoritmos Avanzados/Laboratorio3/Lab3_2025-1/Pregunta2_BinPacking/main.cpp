#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

struct Lavadora {
    int id;
    int tiempo_acumulado;
    vector<int> ordenes;
};

struct Orden {
    int id;
    int tipo;
    int peso;
    double tiempo;
};

bool compara(struct Lavadora k, struct Lavadora g) {
    return k.tiempo_acumulado < g.tiempo_acumulado or
           (k.tiempo_acumulado == g.tiempo_acumulado and k.id < g.id); //Ascendente (Menor a mayor)
}

bool compara_2(struct Lavadora k, struct Lavadora g) {
    return k.id < g.id; //Ascendente (Menor a mayor)
}

void calculaTiempo(struct Orden &orden) {
    if (orden.tipo == 0) { //Si lava
        orden.tiempo = ((double)orden.peso/5)*20;
    }
    else { //Si seca
        orden.tiempo = ((double)orden.peso/5)*10;
    }
}

int asignarTareas(struct Orden *ordenes, struct Lavadora *lavadoras, int n, int m) {
    //n = numero de ordenes | m = numero de lavadoras

    //Recorres las ordenes y vas asignando a las lavadoras
    for (int k = 0; k < n; k++) {
        calculaTiempo(ordenes[k]);
        sort(lavadoras, lavadoras + m, compara);
        lavadoras[0].tiempo_acumulado += ordenes[k].tiempo;
        lavadoras[0].ordenes.push_back(ordenes[k].id);
    }

    //Ordenamos para imprimir
    sort(lavadoras, lavadoras + m, compara_2);
    for (int k = 0; k < m; k++) {
        cout << "Lavadora " << k+1 << ": ";
        for (int g = 0; g < lavadoras[k].ordenes.size(); ++g) {
            if (g != 0)cout << ", ";
            cout << lavadoras[k].ordenes[g];
        }
        cout << left << setw(10) << " | Tiempo total: " << lavadoras[k].tiempo_acumulado << endl;
    }

    return lavadoras[0].id;
}
int main() {
    struct Orden ordenes[] = {
        {1, 0, 10},   // Lavar ropa 10 kilos
        {2, 0, 10},   // Lavar ropa 10 kilos
        {3, 1, 8},    // Secar ropa 8 kilos
        {4, 0, 15},   // Lavar ropa 15 kilos
        {5, 1, 9},    // Secar ropa 9 kilos
        {6, 1, 11},   // Secar ropa 11 kilos
        {7, 0, 12},   // Lavar ropa 12 kilos
        {8, 1, 15},   // Secar ropa 15 kilos
        {9, 0, 6},    // Lavar ropa 6 kilos
        {10, 1, 10},  // Secar ropa 10 kilos
        {11, 0, 8},   // Lavar ropa 8 kilos
        {12, 1, 15},  // Secar ropa 15 kilos
        {13, 0, 11},  // Lavar ropa 11 kilos
        {14, 0, 7},   // Lavar ropa 7 kilos
        {15, 0, 7},   // Lavar ropa 7 kilos
        {16, 1, 8},   // Secar ropa 8 kilos
        {17, 1, 9},   // Secar ropa 9 kilos
        {18, 0, 11},  // Lavar ropa 11 kilos
        {19, 1, 12},  // Secar ropa 12 kilos
        {20, 0, 15}   // Lavar ropa 15 kilos
    };

    int n = sizeof(ordenes) / sizeof(ordenes[0]); // n = 20

    struct Lavadora lavadoras[] = {
        {1, 0, {}},
        {2, 0, {}},
        {3, 0, {}},
        {4, 0, {}},
        {5, 0, {}}
    };

    int m = sizeof(lavadoras) / sizeof(lavadoras[0]);

    asignarTareas(ordenes, lavadoras, n, m);

    return 0;
}