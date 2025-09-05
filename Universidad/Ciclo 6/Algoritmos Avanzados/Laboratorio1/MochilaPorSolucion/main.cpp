#include <iostream>
#include <iomanip>
using namespace std;
#define MAX 6

int solucion[MAX] = {0, 0, 0, 0, 0, 0};
int cont = 0;
bool usado[MAX]{false, false, false, false, false, false};

void impresion(int *paq, int k) {
    cout << "{ ";
    for (int i = 0; i < MAX; ++i) {
        if (solucion[i] == 1) {
            cout << paq[i] << " ";
            usado[i] = true;
        }
    }
    cout << "}" << endl;
    cout << endl;
}


int esValido(int *paq, int pos, int n, int k) {
    bool alguno = false;
    for (int i = 0; i < n; i++) {
        if (solucion[i] == 1) {
            alguno = true;
            if (abs(paq[pos] - paq[i]) <= k) return true;
        }
    }
    return !alguno;
}
int empacar(int *paq, int peso, int k, int n, int pos) {


    //if (paq[pos] == peso) { //No cuenta el ultimo paquete
    if (peso == 0) { //Cuenta el ultimo paquete
        impresion(paq, k);
        cont++;
        return 0;
    }
    if (peso < 0 or pos == n) {
        return 0;
    }

    if (esValido(paq, pos, n, k) and !usado[pos]) {
        solucion[pos] = 1;
        if (empacar(paq, peso - paq[pos], k, n, pos + 1)) {
            return 1;
        }
        solucion[pos] = 0;
    }
    //return empacar(paq, peso, k, n, pos + 1);

    if (empacar(paq, peso, k, n, pos + 1)) {
        return 1;
    }
    return 0;
}
int main() {
    int peso = 15;
    int paq[MAX] = {2, 8, 9, 6, 7, 6}; //k=4
    //int paq[MAX] = {2, 8, 9, 6, 7}; //k=4
    //int paq[MAX] = {2, 8, 9, 6, 7, 6}; //k=3
    int n = sizeof(paq) / sizeof(paq[0]);
    int k = 3;


    empacar(paq, peso, k, n, 0);
    cout << "Numero de pedidos que se puede atender de " << peso << " kg: " << cont << endl;

    return 0;
}