#include <iostream>
#include <iomanip>
using namespace std;

#define MAX_MOV 8
#define MAX_TABLERO 5

int mov[MAX_MOV][2];
int tablero[MAX_TABLERO][MAX_TABLERO];

int cont = 0;


void movimientos() {
    mov[0][0] = -2; mov[0][1] = 1;
    mov[1][0] = -1; mov[1][1] = 2;
    mov[2][0] = 1; mov[2][1] = 2;
    mov[3][0] = 2; mov[3][1] = 1;
    mov[4][0] = 2; mov[4][1] = -1;
    mov[5][0] = 1; mov[5][1] = -2;
    mov[6][0] = -1; mov[6][1] = -2;
    mov[7][0] = -2; mov[7][1] = -1;
}

void inicializa() {
    for (int i = 0; i < MAX_TABLERO; i++) {
        for (int j = 0; j < MAX_TABLERO; j++) {
            tablero[i][j] = 0;
        }
    }
}

void imprimir() {
    for (int g = 0; g < MAX_TABLERO; g++) {
        for (int k = 0; k < MAX_TABLERO; k++) {
            cout << right << setw(2) << tablero[g][k] << " ";
        }
        cout << endl;
    }
}

int esValido(int x, int y) {
    if (0 <= x and x < MAX_TABLERO and 0 <= y and y < MAX_TABLERO and tablero[x][y] == 0) return 1;
    return 0;
}
int saltoCaballo(int x, int y, int numMov) {
    if (numMov == MAX_TABLERO * MAX_TABLERO + 1) {
        imprimir();
        cout << "================" << endl;
        return 0; //Se encontró una solucion
    }

    for (int i = 0; i < MAX_MOV; i++) {
        int mx = x + (mov[i][0]);
        int my = y + (mov[i][1]);

        if (esValido(mx, my)) {
            tablero[mx][my] = numMov;
            if (saltoCaballo(mx, my, numMov + 1)) {
                return 1;
            }
            tablero[mx][my] = 0;
        }
    }
    return 0;
}


int main() {

    movimientos();
    inicializa();
    tablero[0][0] = 1;
    saltoCaballo(0, 0, 2);

    //imprimir();

    return 0;
}