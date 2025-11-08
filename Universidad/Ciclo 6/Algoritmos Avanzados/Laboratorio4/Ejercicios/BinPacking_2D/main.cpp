#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;

#define ITERACIONES 10000
#define ALFA 0.3
#define N 15

struct Paquete {
    int id;
    int w, h;
    int x, y;
    bool colocado;
};

struct Camion {
    vector<vector<int> > mapa;
};

Camion nuevoCamion(int tamanho) {
    Camion c;
    vector<int> fila;
    fila.assign(tamanho, 0);
    c.mapa.assign(tamanho, fila);
    return c;
}

bool cabe(const Camion &c, const Paquete &p, int x, int y) {
    if (x + p.w > N || y + p.h > N)
        return false;
    for (int i = y; i < y + p.h; i++)
        for (int j = x; j < x + p.w; j++)
            if (c.mapa[i][j] != 0)
                return false;
    return true;
}

void colocar(Camion &c, Paquete &p, int x, int y) {
    for (int i = y; i < y + p.h; i++)
        for (int j = x; j < x + p.w; j++)
            c.mapa[i][j] = p.id;
    p.x = x;
    p.y = y;
    p.colocado = true;
}

void mostrarCamion(const Camion &c) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (c.mapa[i][j] == 0)
                cout << setw(4) << ".";
            else
                cout << setw(4) << c.mapa[i][j];
        }
        cout << endl;
    }
}

bool compara(const Paquete &p1, const Paquete &p2) {
    return p1.w * p1.h > p2.w * p2.h;
}

int buscaInd(const vector<Paquete> &vec, double rcl_val) {
    int contador = 0;
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i].h * vec[i].w >= rcl_val) {
            contador++;
        }
    }
    return contador;
}

void grasp2DNoRotacion(vector<Paquete> paqs) {
    srand(time(NULL));

    Camion mejorCamion = nuevoCamion(N);
    int mejorPaquetesColocados = 0;
    int mejorEspacioUsado = 0;

    for (int it = 0; it < ITERACIONES; it++) {
        Camion c = nuevoCamion(N);
        vector<Paquete> paquetes = paqs;

        // Ordenar por área descendente
        sort(paquetes.begin(), paquetes.end(), compara);

        int paquetesColocados = 0;
        int espacioUsado = 0;

        while (!paquetes.empty()) {
            // Construcción del RCL
            int beta = paquetes.front().w * paquetes.front().h;
            int tau = paquetes.back().w * paquetes.back().h;
            double rcl_val = beta - ALFA * (beta - tau);

            int ind = buscaInd(paquetes, rcl_val);

            // Protección contra división por cero
            if (ind == 0) {
                ind = 1;
            }

            int indA = rand() % ind;
            bool colocado = false;

            // Intentar colocar el paquete
            for (int y = 0; y < N && !colocado; y++) {
                for (int x = 0; x < N && !colocado; x++) {
                    if (cabe(c, paquetes[indA], x, y)) {
                        colocar(c, paquetes[indA], x, y);
                        espacioUsado += paquetes[indA].w * paquetes[indA].h;
                        paquetesColocados++;
                        colocado = true;
                    }
                }
            }

            // Eliminar el paquete de la lista (colocado o no)
            paquetes.erase(paquetes.begin() + indA);
        }

        // Actualizar mejor solución
        // Primero: más paquetes colocados
        // Segundo: más espacio usado
        if (paquetesColocados > mejorPaquetesColocados ||
            (paquetesColocados == mejorPaquetesColocados &&
             espacioUsado > mejorEspacioUsado)) {
            mejorPaquetesColocados = paquetesColocados;
            mejorEspacioUsado = espacioUsado;
            mejorCamion = c;
        }
    }

    // Mostrar resultados
    cout << "=== MEJOR SOLUCION ENCONTRADA ===" << endl;
    cout << "Paquetes colocados: " << mejorPaquetesColocados
         << "/" << paqs.size() << endl;
    cout << "Espacio usado: " << mejorEspacioUsado
         << "/" << (N*N) << " unidades" << endl;
    cout << "Porcentaje de ocupacion: "
         << fixed << setprecision(2)
         << (mejorEspacioUsado * 100.0) / (N*N) << "%" << endl;
    cout << "\nDistribucion final:" << endl;
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