#include <iostream>
#include <iomanip>
using namespace std;

#define N 8
#define MAXMOV 8

int tablero[N][N]{};
int mov[MAXMOV][2];

void imprimir() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << setw(2) << tablero[i][j] << " ";
        }
        cout << endl;
    }
}

void movimientos() {
    mov[0][0] = -1;mov[0][1] = -1;
    mov[1][0] = -1;mov[1][1] = 0;
    mov[2][0] = -1;mov[2][1] = 1;
    mov[3][0] = 0;mov[3][1] = 1;
    mov[4][0] = 1;mov[4][1] = 1;
    mov[5][0] = 1;mov[5][1] = 0;
    mov[6][0] = 1;mov[6][1] = -1;
    mov[7][0] = 0;mov[7][1] = -1;
}

/////////////////////////////////////////////////////////////////////////
//Parte b

void verificarDiagonales(int fil, int col,int  movFil,int movCol,int &sumaDiagonales) {
    if (fil == N)return;
    sumaDiagonales += tablero[fil][col];
    verificarDiagonales(fil+movFil, fil + movCol, movFil, movCol, sumaDiagonales);
}

int verificarFil(int fil,int col, int suma,int sumaAnt) {
    if (col == N) {
        col = 0;
        fil++;
        if (sumaAnt != 0 and sumaAnt != suma)return 0;
        sumaAnt = suma;
    }
    if (fil == N)return sumaAnt;

    return verificarFil(fil, col + 1, suma + tablero[fil][col], sumaAnt);
}

int verificarCol(int fil, int col, int suma,int sumaAnt) {
    if (fil == N) {
        fil = 0;
        col++;
        if (sumaAnt != 0 and sumaAnt != suma)return 0;
        sumaAnt = suma;
    }
    if (col == N)return sumaAnt;
    return verificarCol(fil + 1, col, suma + tablero[fil][col], sumaAnt);
}

int verificarCuadradoMagico(int fil,int col) {
    int sumaDiagonal1 = 0, sumaDiagonal2 = 0, sumaCol = 0, sumaFil = 0;
    verificarDiagonales(fil, col, 1,1, sumaDiagonal1);
    verificarDiagonales(fil, N - 1, 1,-1, sumaDiagonal2);

    sumaFil = verificarFil(0,0, 0,0);
    sumaCol = verificarCol(0, 0, 0, 0);

    if (sumaDiagonal1 != sumaDiagonal2 or sumaDiagonal2 != sumaCol or sumaCol != sumaFil) {
        cout << "No es cuadrado mágico" << endl; //No es cuadrado Mágico
    }
    else {
        cout << "Si es cuadrado Magico, constante: " << sumaDiagonal1 << endl; //Si es cuadrado Mágico
    }
}

////////////////////////////////////////////////////////////////////////////
//Parte a

int esValido(int x, int y) {
    if (0 <= x and x < N and 0 <= y and y < N and tablero[x][y] == 0) {
        return 1;
    }
    return 0;
}

int rutaRey(int x, int y, int num){
    if (num == N * N + 1) {
        //imprimir();
        return 1;
    }


    for (int i = 0; i < MAXMOV; i++) {
        int mx = x + mov[i][0];
        int my = y + mov[i][1];
        if (esValido(mx, my)) { //Si se puede colocar se coloca
            tablero[mx][my] = num;
            if (rutaRey(mx, my, num + 1)) {
                return 1;
            }
            //Tacha 0, y busca en otro movimiento
            tablero[mx][my] = 0; //Backtracking
        }
    }

    return 0;
}

int main() {

    int f = 0;
    int c = 0;

    movimientos();
    tablero[f][c] = 1;

    if (rutaRey(f, c, 2)) {
        imprimir();
        verificarCuadradoMagico(0, 0);
    }
    else {
        cout << "No se pudo recorrer el tablero" << endl;
    }

    return 0;
}