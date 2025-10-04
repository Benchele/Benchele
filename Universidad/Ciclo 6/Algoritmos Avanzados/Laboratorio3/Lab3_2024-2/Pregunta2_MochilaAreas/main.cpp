#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

struct Lata {
    int id;
    int cantidad;
    int longitud;
    int altura;
    int areaTotal;
};

struct Solucion {
    int id;
    int cantidad;
};

bool compara(struct Lata k, struct Lata g){
   return (double)k.cantidad*k.longitud*k.altura > (double)g.cantidad*g.longitud*g.altura; //Descendente (Mayor a menor)
}

void hallarArea(struct Lata &lata) {
    lata.areaTotal = lata.cantidad*lata.longitud*lata.altura;
}

string obtenerNombreLata(int id) {
    switch (id) {
        case 1:
            return "Mentolato";
        case 2:
            return "Crema Nivea";
        case 3:
            return "Atun";
        case 4:
            return "Conserva";
        case 5:
            return "Aceite Industrial";
        default:
            return "Desconocido";
    }
}

int realizarRecortes(struct Lata *latas, int lamina, int n) {
    //Ordenamos de mayor a menor las latas por las areas y sus cantidades
    sort(latas, latas + n, compara);

    //Caso base
    int area = lamina;

    vector<struct Solucion> solucion;

    //Analizamos las latas que pueden entrar
    for (int k = 0; k < n; k++){
        hallarArea(latas[k]);
        if (area - latas[k].areaTotal >= 0) { //Si pueden entrar las latas
            area -= latas[k].areaTotal;
            solucion.push_back({latas[k].id, latas[k].cantidad});
        }
    }

    //Imprimir resultados
    string nombre;
    int suma = 0;
    for (int k = 0; k < solucion.size(); k++) {
        suma += solucion[k].cantidad;
        nombre = obtenerNombreLata(solucion[k].id);
        cout << "Latas de " << nombre << " | Cantidad: " << solucion[k].cantidad << endl;
    }
    cout << "Numero de latas usadas: " << suma << endl;

    return area;
}

int main() {
    //En el laboratorio indicaron que simplemente era completar areas -> Como si fuera una mochila

    struct Lata latas[] = {
        {1, 5, 2, 3},    // Latas de mentolato
        {2, 10, 9, 3},   // Latas de crema Nivea
        {3, 15, 14, 7},  // Latas de atún
        {4, 20, 15, 20}, // Latas de conserva
        {5, 20, 22, 18}  // Latas de aceite industrial
    };

    int n = sizeof(latas) / sizeof(latas[0]); // n = 5

    int lamina = 50*50;

    int desperdicio = realizarRecortes(latas, lamina, n);

    // 100%     -       2500
    //   x      -    desperdicio

    double porcentaje = 100*desperdicio/(double)lamina;

    cout << "Porcentaje de merma residual/desperdicio: " << porcentaje << "%" << endl;

    return 0;
}