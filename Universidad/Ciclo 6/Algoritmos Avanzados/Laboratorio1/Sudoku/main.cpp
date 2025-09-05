#include <iostream>
#include <iomanip>
using namespace std;

#define N 9
#define NUMEROS 9

int matriz[N][N] =
{
    {0,2,0,0,0,0,0,9,0},
    {3,0,1,9,0,6,5,0,2},
    {0,0,0,8,0,4,0,0,0},
    {0,9,0,0,0,0,0,5,0},
    {5,0,0,2,0,3,0,0,6},
    {0,7,0,0,0,0,0,2,0},
    {0,0,0,4,0,7,0,0,0},
    {8,0,2,5,0,1,7,0,3},
    {0,5,0,0,0,0,0,8,0},
};

int posibilidades[9]{1,2,3,4,5,6,7,8,9};

void imprimir() {
    for (int k = 0; k < N; k++) {
        for (int g = 0; g < N; g++) {
            cout << setw(2) << matriz[k][g];
        }
        cout << endl;
    }
}
int esValido(int x, int y, int numero) {
    //Verificar la fila (En horizontal)
    for (int k = 0; k < N; k++) {
        //if (k == x) continue;
        if (matriz[x][k] == numero) {
            return 0; //Si hay concidencia no puede estar ahí
        }
    }

    //Verificar la columa (En vertical)
    for (int g = 0; g < N; g++) {
        //if (g == y)continue;
        if (matriz[g][y] == numero) {
            return 0; //Si hay concidencia no puede estar ahí
        }
    }

    //Revisar el bloque
    int fila = x / 3 * 3;
    int colu = y / 3 * 3;

    //Es divison entre int, se trunca

    //Ejemplo (5, 4)
    //x = 5/3 = 1*3 = 3 -> Empieza en fila 3
    //y = 4/3 = 1*3 = 3 -> Empiza en columna 3
    //4,7

    for (int k = fila; k < fila + 3; k++) {
        for (int g = colu; g < colu + 3; g++) {
            if (k == x and g == y)continue; //No compararlo con la misma celda
            if (matriz[k][g] == numero) {
                return 0;
            }
        }
    }


    //No se repite en ninguna condiicon
    return 1;

}

void incrementarValor(int &fila, int &colu, int x, int y) {
    //Avanza columna por columna y despues se reinicia, y avanza la fila
    if (N <= y + 1) {
        colu = 0;
        fila = x + 1;
    }
    else {
        colu = y + 1;
    }
}
int resolverSudoku(int x, int y) {
    if (x == N) {
        imprimir();
        return 1;
    }

    int fila = x, colu = y;

    if (matriz[x][y] == 0) {
        for (int i = 0; i < NUMEROS; i++) {
            if (esValido(x, y, posibilidades[i])) {
                matriz[x][y] = posibilidades[i];
                incrementarValor(fila, colu, x, y);
                if (resolverSudoku(fila, colu)) {
                    return 1;
                }
                matriz[x][y] = 0;
            }
        }
    }
    else { //En caso haya un numero
        incrementarValor(fila, colu, x, y);
        return resolverSudoku(fila, colu);
    }
    return 0;
}

int main() {
    resolverSudoku(0, 0);

    return 0;
}