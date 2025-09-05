#include <iostream>
#include <iomanip>
using namespace std;

void imprime(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << "=====================" << endl;
}
int cargaRack(int *paq, int *rack, int n, int m, int *solucion, int pos) {
    if (pos == n) {
        //return 1;
        imprime(solucion, m);
        return 0;
    }

    for (int i = 0; i < m; i++) {
        if (rack[i] - solucion[i] >= paq[pos]) {
            solucion[i]+=paq[pos];
            if (cargaRack(paq, rack, n, m, solucion, pos + 1)) {
                return 1;
            }
            solucion[i]-=paq[pos];
        }

    }
    return 0;
}

int main() {
    int paq[] = {2, 3, 1, 4};
    int rack[] = {3, 2, 5, 1, 3};
    int n = sizeof(paq) / sizeof(paq[0]);
    int m = sizeof(rack) / sizeof(rack[0]);
    int solucion[m]{};

    //imprime(solucion, m);

    cargaRack(paq, rack, n, m, solucion, 0);

    return 0;
}
