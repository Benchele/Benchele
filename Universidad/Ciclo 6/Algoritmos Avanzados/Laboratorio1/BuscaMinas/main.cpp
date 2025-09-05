#include <iostream>
#include <iomanip>
using namespace std;

#define N 9
#define M 5
#define MAXMOV 8

int mov[MAXMOV][2];

char tablero[N][M] = {
    {'0','0','0','0','*'},
    {'0','0','0','0','0'},
    {'0','0','*','0','0'},
    {'0','0','0','0','0'},
    {'0','*','*','0','*'},
    {'0','*','*','0','*'},
    {'0','*','0','*','0'},
    {'*','*','*','*','0'},
    {'0','0','0','0','0'}
};

char solucion[N][M]{};
// = {
//     {'0','0','0','0','*'},
//     {'0','0','0','0','0'},
//     {'0','0','*','0','0'},
//     {'0','0','0','0','0'},
//     {'0','*','*','0','*'},
//     {'0','*','0','*','0'},
//     {'*','*','*','*','0'},
//     {'0','0','0','0','0'}
// };


void movimientos(){
    mov[0][0] = -1; mov[0][1] = 0;
    mov[1][0] = -1; mov[1][1] = -1;
    mov[2][0] = 0; mov[2][1] = -1;
    mov[3][0] = 1; mov[3][1] = -1;
    mov[4][0] = 1; mov[4][1] = 0;
    mov[5][0] = 1; mov[5][1] = 1;
    mov[6][0] = 0; mov[6][1] = 1;
    mov[7][0] = -1; mov[7][1] = 1;
}

void imprimir(char tab[][M]) {
    for (int g = 0; g < N; g++) {
        for (int k = 0; k < M; k++) {
            cout << right << setw(2) << tab[g][k] << " ";
        }
        cout << endl;
    }
    cout << "===============" << endl;
}

void inicializa(char tab[][M]) {
    for (int g = 0; g < N; g++) {
        for (int k = 0; k < M; k++) {
            tab[g][k] = '0';
        }

    }
}

int esValido(int x, int y) {
    if (0 <= x and x < N and 0 <= y and y < M and solucion[x][y] == '0') {
        return 1;
    }
    return 0;
}

void descubrirMina(int x, int y) {
    for (int k = 0; k < MAXMOV; k++) {
        int nx = x + mov[k][0];
        int ny = y + mov[k][1];

        if (esValido(nx, ny) and tablero[nx][ny] == '*') {
            solucion[nx][ny] = '*';
        }
    }
}
int cont = 0;
int buscaMinas(int x, int y, char paso) {
    if (x == N - 1 and y == M - 1) {
        //if (cont < 20) {
            imprimir(solucion);
        //}
        cont++;
        //return 1;
        return 0;
    }
    if (x == 0 and y == 0) {
        solucion[x][y] = paso;
    }
    descubrirMina(x, y);

    for (int g = 0; g < MAXMOV; g++) {
        int nx = x + mov[g][0];
        int ny = y + mov[g][1];

        if (esValido(nx, ny)) {
            //if (tablero[nx][ny] != '*') {
                solucion[nx][ny] = paso + 1;
                if (buscaMinas(nx, ny, paso + 1)) {
                    return 1;
                }
                solucion[nx][ny] = '0';
            //}
        }
    }
    return 0;
}
int main() {
    char paso = 'A';

    movimientos();
    inicializa(solucion);
    buscaMinas(0, 0, paso);

    return 0;
}