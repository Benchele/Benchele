#include <iostream>
#include <iomanip>
using namespace std;

#define N 5
#define MAX_MOV 4

int mov[4][2];

int solucion[N][N];
int visitado[N][N];

void movimientos() {
    mov[0][0] = 1; mov[0][1] = 0;  // Down
    mov[1][0] = -1; mov[1][1] = 0; // Up
    mov[2][0] = 0; mov[2][1] = 1;  // Right
    mov[3][0] = 0; mov[3][1] = -1; // Left
}

void inicializar(int matriz[][N]) {
    for (int k = 0; k < N; k++) {
        for (int g = 0; g < N; ++g) {
            matriz[k][g] = 0;
        }
    }
}

void copiarMapa(int mapa[][N]) {
    for (int k = 0; k < N; k++) {
        for (int g = 0; g < N; ++g) {
            solucion[k][g] = visitado[k][g];
        }
    }
}

int esValido(int mapa[][N], int x, int y) {
    if (0 <= x and x < N and 0 <= y and y < N and mapa[x][y] != 0 and visitado[x][y] == 0) {
        return 1;
    }
    return 0;
}

void encontrarCamino(int mapa[][N], int x, int y, int costoActual, int &costoMinimo) {
    if (x == N - 1 and y == N - 1) {
        if (costoActual < costoMinimo) {
            costoMinimo = costoActual;
            copiarMapa(mapa);
        }
        return;
    }

    for (int g = 0; g < MAX_MOV; ++g) {
        int mx = x + mov[g][0];
        int my = y + mov[g][1];
        if (esValido(mapa, mx, my)) {
            visitado[mx][my] = 1;
            //costoActual += mapa[mx][my]; // Es mejor pasarlo por valor, pero si lo aumentas como variable tambien lo tienes que restar ...*

            //encontrarCamino(mapa, mx, my, costoActual, costoMinimo);// ... *
            encontrarCamino(mapa, mx, my, costoActual + mapa[mx][my], costoMinimo);

            visitado[mx][my] = 0;
            //costoActual -= mapa[mx][my]; // ...*
        }
    }
}

void imprimir(int costoMinimo) {
    cout << "Costo Minimo: " << costoMinimo << endl;
    cout << "Camino: " << endl;
    for (int k = 0; k < N; k++) {
        for (int g = 0; g < N; ++g) {
            cout << setw(3) << solucion[k][g] << " ";
        }
        cout << endl;
    }
}

int main() {
    int mapa[N][N] = {
        {1, 2, 0, 0, 1},
        {3, 2, 3, 1, 1},
        {0, 1, 2, 0, 0},
        {3, 1, 1, 2, 3},
        {0, 1, 3, 1, 1}
    };

    movimientos();

    int x = 0, y = 0;

    inicializar(solucion);
    inicializar(visitado);

    int costoMinimo = INT_MAX;
    int costoInicial = mapa[x][y];
    visitado[x][y] = 1;

    encontrarCamino(mapa, x, y, costoInicial, costoMinimo);

    imprimir(costoMinimo);

    return 0;
}