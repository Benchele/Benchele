#include <iostream>
#include <iomanip>
using namespace std;

int empaca(int *paq, int n, int peso, int pos) {
    if (peso < 0 or pos == n)return 0;

    if (paq[pos] == peso) {
        return 1; //Aqui se encuentra la solucion
    }

    if (empaca(paq, n, peso - paq[pos], pos + 1)) {
        return 1;
    }
    else {
        return empaca(paq, n, peso, pos + 1);
    }
}
int main() {
    //int paq[] = {1, 4, 12, 7, 5};
    int paq[] = {1, 1, 12, 2, 1};

    int n = sizeof(paq) / sizeof(paq[0]);

    int peso = 15;

    if (empaca(paq, n, peso, 0)) {
        cout << "Si hay solucion" << endl;
    }
    else {
        cout << "No salió" << endl;
    }

    //Fin, 11:42 am
    return 0;
}