#include <iostream>
#include <iomanip>
using namespace std;


#define N 3
#define M 4
#define MAXMOV 4

char matriz[N][M] = {
    {'A', 'B', 'C', 'E'},
    {'S', 'F', 'C', 'S'},
    {'A', 'D', 'E', 'E'}
};


int mov[4][2];

void movimientos() {
    mov[0][0] = -1;mov[0][1] = 0;
    mov[1][0] = 0;mov[1][1] = 1;
    mov[2][0] = 1;mov[2][1] = 0;
    mov[3][0] = 0;mov[3][1] = -1;


}

int esValido(int x, int y) {
    if (0 <= x and x < N and 0 <= y and y < M and matriz[x][y] != '0') {
        return 1;
    }
    return 0;
}

int encontrar(int x, int y, char *palabra, int tam, int pos) {
    if (matriz[x][y] != palabra[pos]) {
        return 0; //No encuentra coincidencia
    }
    if (pos == tam - 1) {
        return 1; //Se encontro toda la palabra
    }

    char temp = matriz[x][y];
    matriz[x][y] = '0'; //Ya encontramos esa letra

    for (int i = 0; i < MAXMOV; i++) {
        int nx = x + mov[i][0];
        int ny = y + mov[i][1];

        if (esValido(nx, ny)) {
            //matriz[nx][ny] = '0';
            if (encontrar(nx, ny, palabra, tam, pos + 1)) {
                matriz[x][y] = temp;
                return 1;
            }
        }
    }
    matriz[x][y] = temp;
    return 0;

}
int encuentraPalabras(char *palabra, int n) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (palabra[0] == matriz[i][j]) {
                if (encontrar(i, j, palabra, n, 0)) {
                    return 1;
                }
            }

        }
    }
    return 0;
}

int main() {
    //char palabra[]{'A', 'B', 'C', 'C', 'E', 'D'};

    //char palabra[]{'S', 'E', 'E'};

    //char palabra[]{'A', 'B', 'C', 'B'};

    //char palabra[]{'A', 'B', 'C', 'B'};

    //char palabra[]{'C', 'E', 'S', 'A'};

    char palabra[]{'A','B','C','E',
                  'S','C','F','S',
                  'A','D','E','E'};

    // char palabra[]{'A','B','C','E',
    //               'S','F','C','S',
    //               'A','D','E','E'};

    int n = sizeof(palabra) / sizeof(palabra[0]);
    cout << "Palabra: " ;
    cout << '"';

    for (int i = 0; i < n; i++) {
        cout << palabra[i];
    }
    cout << '"' << " => ";

    movimientos();

    if (encuentraPalabras(palabra, n)) {
        cout << "True" << endl;
    }
    else {
        cout << "false" << endl;
    }

    return 0;
}