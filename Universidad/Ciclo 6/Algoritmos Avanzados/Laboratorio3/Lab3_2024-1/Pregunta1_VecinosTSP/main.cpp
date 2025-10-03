#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX 8

struct Nodo {
    int posicion;
    int tiempo;
};

bool compara(struct Nodo k, struct Nodo g) {
    return k.tiempo < g.tiempo; //k va antes que g -> Ascendente (Menor a mayor)
}

int rutaMinima(int inicio, int fin, int mapa[][MAX]) {
    //Condiciones de parada
    //Cuando llegamos al destino o cuando no hay mas vecinos

    int total = 0;
    int ciudad = inicio;

    while (true) {
        if (ciudad == fin) { //Si se llegó al destino
            break;
        }

        vector<struct Nodo> vecinos;
        for (int k = 0; k < MAX; k++) { //Buscamos todos sus vecinos
            if (mapa[ciudad][k] != 0) { //Si es vecino
                struct Nodo paso;
                paso.posicion = k;
                paso.tiempo = mapa[ciudad][k];
                vecinos.push_back(paso); //Guardamos el vecino
            }
        }

        // Si hay vecinos, elegir el más cercano, sino no hay solución
        if (!vecinos.empty()) { //Si tiene vecinos
            sort(vecinos.begin(), vecinos.end(), compara); //Ordenamos para sacar el mas cercano
            total += vecinos[0].tiempo;
            ciudad = vecinos[0].posicion;
        }
        else{
            total = -1;
            break;
        }
    }

    return total;
}

int main() {
    int mapa[][MAX] {
        {0, 4, 5, 6, 0, 0, 0, 0},   //A
        {0, 0, 0, 0, 2, 0, 0, 0},   //B
        {0, 0, 0, 0, 0, 0, 0, 3},   //C
        {0, 0, 0, 0, 0, 3, 0, 0},   //D
        {0, 0, 0, 0, 0, 0, 10, 0},  //E
        {0, 0, 0, 0, 0, 0, 2, 0},   //F
        {0, 0, 0, 0, 0, 0, 0, 0},   //G
        {0, 0, 0, 0, 0, 0, 0, 0}    //H
    };

    int tiempo = rutaMinima(0, 6, mapa);

    if (tiempo >= 0) {
        cout << "Tiempo de viaje " << tiempo << " min" << endl;
    }
    else {
        cout << "No se encontro una solucion" << endl;
    }

    return 0;
}