#include <iostream>
#include <iomanip>
#include <climits>
using namespace std;

#define PISOS 5
#define Q 50

void imprimir(int *solucion, int internos, int tipo) {
    if (tipo == 1) {
        for (int i = 0; i < internos; i++) {
            if (solucion[i] != 0) {
                cout << "R" << i + 1 << " ";
            }
        }
    }
    else {
        for (int i = 0; i < internos; i++) {
            if (solucion[i] == 0) {
                cout << "R" << i + 1 << " ";
            }
        }
    }
    cout << endl;
}

int maximizarLavado(int pos, int peso, int &maxPeso, double costo, int internos, int *ropas, int *internosLavados, int *solucion) {
    if (Q < peso) {
        return 0;
    }

    if (pos == internos) {
        if (maxPeso < peso) {
            maxPeso = peso;
            for (int i = 0; i < internos; i++) {
                solucion[i] = internosLavados[i];
            }
        }
        return 0;
    }

    internosLavados[pos] = pos + 1;
    maximizarLavado(pos + 1, peso + ropas[pos], maxPeso, costo, internos, ropas, internosLavados, solucion);
    internosLavados[pos] = 0;
    maximizarLavado(pos + 1, peso, maxPeso, costo, internos, ropas, internosLavados, solucion);

    return 0;
}

int calcularRopaALavar(int *solucion, int internos, int *ropa) {
    int suma = 0;
    for (int i = 0; i < internos; i++) {
        if (solucion[i] == 0) {
            suma += ropa[i];
        }
    }
    return suma;
}
void calcularLavado(double *costos, int *internos, int ropa[PISOS][7]) {
    int suma = 0;
    int maxUso = INT_MIN, minUso = INT_MAX;
    int pisoMax = 0, pisoMin = 0;
    int ropaALavar, maxRopaLavar = INT_MIN, minRopaLavar = INT_MAX;
    int pisoMaxLavar = 0, pisoMinLavar = 0;

    for (int i = 0; i < PISOS; i++) {
        int internosLavados[7]{}, solucion[7]{};
        int maxPeso = 0;
        maximizarLavado(0, 0, maxPeso, costos[i], internos[i], ropa[i], internosLavados, solucion);
        cout << "Para el piso " << i + 1 << " se lavara las ropas de: " << endl;
        imprimir(solucion, internos[i], 1);
        cout << "Para el piso " << i + 1 << " No se lavara las ropas de: " << endl;
        imprimir(solucion, internos[i], 0);
        suma += maxPeso;
        ropaALavar = calcularRopaALavar(solucion, internos[i], ropa[i]);
        if (maxPeso > maxUso) {
            maxUso = maxPeso;
            pisoMax = i + 1;
        }
        if (maxPeso < minUso) {
            minUso = maxPeso;
            pisoMin = i + 1;
        }

        if (ropaALavar > maxRopaLavar) {
            maxRopaLavar = ropaALavar;
            pisoMaxLavar = i + 1;
        }

        if (ropaALavar < minRopaLavar) {
            minRopaLavar = ropaALavar;
            pisoMinLavar = i + 1;
        }
    }

    double porcentaje = (double)suma/(Q * PISOS) * 100;
    cout << "Porcentaje de uso de lavadora " << porcentaje << "%" << endl;
    cout << "Piso que mas ocupa la lavadora " << pisoMax << endl;
    cout << "Piso que menos ocupa la lavadora " << pisoMin << endl;

    cout << "Piso con mas kilos de ropaa lavar por parientes " << pisoMaxLavar << endl;
    cout << "Piso con menos kilos de ropaa lavar por parientes " << pisoMinLavar << endl;
}
int main() {
    double costos[PISOS]{5, 6, 8, 5, 9};

    int internos[PISOS]{6, 7, 4, 5, 2};

    int ropa[PISOS][7] {
        {14, 11, 10, 19, 14, 11},
        {20, 11, 11, 10, 15, 17, 8},
        {15, 16, 15, 16},
        {11, 4, 19, 12, 10},
        {18, 12}
    };

    calcularLavado(costos, internos, ropa);

    return 0;
}