#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;

#define ITERACIONES 100000
#define alfa 0.3
#define N 15

struct Paquete {
    int id;
    int w, h;
    int x, y; // posición dentro del camión
    bool colocado;
};

struct Camion {
    vector<vector<int> > mapa; // 0 = libre, id del paquete = ocupado
};

Camion nuevoCamion(int tamanho) {
    Camion c;
    vector<int> fila;
    fila.assign(tamanho, 0);
    c.mapa.assign(tamanho, fila);
    return c;
}

// Verifica si el paquete cabe en la posición (x,y) sin rotación
bool cabe(const Camion &c, const Paquete &p, int x, int y) {
    if (x + p.w > N || y + p.h > N)
        return false;
    for (int i = y; i < y + p.h; i++)
        for (int j = x; j < x + p.w; j++)
            if (c.mapa[i][j] != 0)
                return false;
    return true;
}

// Coloca el paquete en la posición (x,y)
void colocar(Camion &c, Paquete &p, int x, int y) {
    for (int i = y; i < y + p.h; i++)
        for (int j = x; j < x + p.w; j++)
            c.mapa[i][j] = p.id;
}

// Mostrar el camión (matriz 2D)
void mostrarCamion(const Camion &c) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (c.mapa[i][j] == 0) cout<<setw(4)  << ".";
            else cout<<setw(4) << c.mapa[i][j];
        }
        cout << endl;
    }
}

bool compara(const Paquete &p1, const Paquete &p2) {
    return p1.w * p1.h > p2.w * p2.h;
}

int buscaInd(const vector<Paquete> &vector, double rcl_val) {
    int contador = 0;
    for (int i = 0; i < vector.size(); i++) {
        if (vector[i].h * vector[i].w >= rcl_val) {
            contador++;
        }
    }
    return contador;
}

// GRASP para 2D Bin Packing (sin rotación)
void grasp2DNoRotacion(vector<Paquete> paqs) {
    srand(time(NULL));
    Camion mejorCamion = nuevoCamion(N);
    int mejorEspacioLibre = N * N;


    for (int it = 0; it < ITERACIONES; it++) {
        Camion c = nuevoCamion(N);
        vector<Paquete> paquetes = paqs;

        // Ordenamos por área descendente
        sort(paquetes.begin(), paquetes.end(), compara);
        bool noSirve = false;
        int espacioLibre = N * N;

        while (!paquetes.empty()) {
            // Construcción del RCL (basado en área)
            int beta = paquetes.front().w * paquetes.front().h;
            int tau = paquetes.back().w * paquetes.back().h;
            double rcl_val = beta - alfa * (beta - tau);
            int ind = buscaInd(paquetes, rcl_val);
            int indA = rand() % ind;

            bool colocado = false;
            // Intentamos colocarlo (sin rotación)
            for (int y = 0; y < N && !colocado; y++)
                for (int x = 0; x < N && !colocado; x++)
                    if (cabe(c, paquetes[indA], x, y)) {
                        colocar(c, paquetes[indA], x, y);
                        espacioLibre -= paquetes[indA].w * paquetes[indA].h;
                        colocado = true;
                    }

            if (!colocado)noSirve=true;
            // Quitamos el paquete de la lista
            paquetes.erase(paquetes.begin() + indA);
        }
        // Si mejor, guardamos
        if (espacioLibre < mejorEspacioLibre and !noSirve) {
            mejorEspacioLibre = espacioLibre;
            mejorCamion = c;
        }
    }

    cout << "Mejor espacio libre: " << mejorEspacioLibre << " unidades." << endl;
    cout << "Distribución final:" << endl;
    mostrarCamion(mejorCamion);
}

int main() {
    vector<Paquete> paquetes = {
        {1, 4, 1},
        {2, 1, 3},
        {3, 2, 2},
        {4, 1, 2},
        {5, 3, 4},
        {6, 1, 3},
        {7, 5, 3},
        {8, 1, 2},
        {9, 6, 5},
        {10, 1, 8},
        {11, 2, 7},
        {12, 3, 6},
        {13, 4, 5}
    };

    grasp2DNoRotacion(paquetes);
    return 0;
}
