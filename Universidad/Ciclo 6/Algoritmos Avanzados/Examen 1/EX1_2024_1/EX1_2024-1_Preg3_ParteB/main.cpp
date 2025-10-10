#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

struct Telar {
    int id;
    int velocidad;
    int tiempoTotal;
    vector<int> telas; // Tamaños de las telas asignadas
};

struct Tela {
    int id;
    int size; // Tamaño del telar
};

bool compara(struct Tela k, struct Tela g) {
    return k.size > g.size or (k.size == g.size and k.id > g.id); //Descendente (Mayor a menor)
}

//Impresion
bool comparaId(struct Telar k, struct Telar g) {
    return k.id < g.id; //Ascendente (Menor a mayor)
}

int asignarTelas(struct Telar *telares, int cantTelares, struct Tela *telas, int cantTelas) {
    sort(telas, telas + cantTelas, compara);

    for (int k = 0; k < cantTelas; k++) {
        int mejorTelar = 0;
        int menorAumento = telares[0].velocidad * telas[k].size;
        int nuevoTiempo = telares[0].tiempoTotal + menorAumento;

        // Buscar el telar con menor aumento de tiempo
        for (int g = 1; g < cantTelares; g++) {
            int aumento = telares[g].velocidad * telas[k].size;
            int tiempoResultante = telares[g].tiempoTotal + aumento;

            // Elegir el que tenga menor tiempo resultante
            if (tiempoResultante < nuevoTiempo) {
                mejorTelar = g;
                menorAumento = aumento;
                nuevoTiempo = tiempoResultante;
            }
        }

        // Asignar la tela al mejor telar
        telares[mejorTelar].telas.push_back(telas[k].size);
        telares[mejorTelar].tiempoTotal += menorAumento;
    }

    //Impresion
    cout << "Asignaciones de telas a los telares:" << endl;

    int tiempoMaximo = 0;

    sort(telares, telares + cantTelares, comparaId);
    for (int k = 0; k < cantTelares; k++) {
        cout << "Telar " << telares[k].id << ": ";
        for (int g = 0; g < telares[k].telas.size(); g++) {
            if (g != 0) cout << ", ";
            cout << telares[k].telas[g];
        }
        cout << " - Tiempo total de trabajo: " << telares[k].tiempoTotal << " unidades de tiempo" << endl;

        tiempoMaximo = max(tiempoMaximo, telares[k].tiempoTotal);
    }

    cout << endl << "Tiempo total para terminar todas las telas: " << tiempoMaximo << " unidades de tiempo" << endl;
    return 1;
}

int main() {
    int k = 3;

    struct Telar telares[] = {
        {0, 5, 0, {}},  // Telar 0: velocidad 5
        {1, 4, 0, {}},  // Telar 1: velocidad 4
        {2, 6, 0, {}}   // Telar 2: velocidad 6
    };

    struct Tela telas[] = {
        {0, 10},
        {1, 7},
        {2, 9},
        {3, 12},
        {4, 6},
        {5, 8}
    };

    int n = sizeof(telas) / sizeof(telas[0]);

    asignarTelas(telares, k, telas, n);

    return 0;
}