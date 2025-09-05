#include <iostream>
#include <iomanip>
using namespace std;
#define N 4
#define MAX_DIA 4

int matriz[N][N];

int diagonales[4][2];

void inicializa() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matriz[i][j] = 0;
        }
    }
}

void imprimir() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
void movimientos() {
    diagonales[0][0] = -1; diagonales[0][1] = -1;
    diagonales[1][0] = -1; diagonales[1][1] = 1;
    diagonales[2][0] = 1; diagonales[2][1] = 1;
    diagonales[3][0] = 1; diagonales[3][1] = -1;
}

int esValido(int fila, int colu) {
    //La recursion garantiza que no se repita la reina en la fila
    for (int k = 0; k < N; k++) { //Si estan en la misma columna
        if (matriz[k][colu] == 1)return 0; //Hay otra reina en la columna

    }

    //Diagonales
    int nfila, ncolu;
    for (int g = 0; g < MAX_DIA; g++) {
        for (int k = 1; k < N; k++) {
            nfila = fila + diagonales[g][0] * k;
            ncolu = colu + diagonales[g][1] * k;
            if (0 <= ncolu and ncolu < N and 0 <= nfila and nfila < N and matriz[nfila][ncolu] == 1) {
                //Si esta dentro del rango y hay otra reina en esta diagonal no se puede
                return 0;
            }
        }
    }
    return 1;
}
int reinas(int fila) {
    if (fila == N) {
        imprimir();
        return 0; //Varias soluciones
        //return 1; //Una solucion

    }

    for (int i = 0; i < N; i++) {
        if (esValido(fila, i)) {
            matriz[fila][i] = 1; //Coloca en una columa
            if (reinas(fila + 1)) { //A la otra fila
                return 1;
            }
            matriz[fila][i] = 0; //Busca en otra columna de la misma fila
        }
    }
    return 0;
}
int main() {
    movimientos();
    inicializa();
    reinas(0); //Solo se trabaja con filas porque no va a estar en una misma fila que la anterior reina
    //imprimir();

    return 0;
}