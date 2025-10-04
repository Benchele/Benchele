#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

struct Actividad {
    int id;
    int inicio;
    int fin;
};

bool compara(struct Actividad k, struct Actividad g) {
    return k.fin < g.fin or (k.fin == g.fin and k.inicio < g.inicio); //Ascendente (Menor a mayor)
}

int conjuntoActividades(struct Actividad *actividades, int n) {
    //Ordenamos por longitud de intervalos de menor a mayor
    sort(actividades, actividades + n, compara);

    //Solucion
    vector<struct Actividad> solucion;

    // Siempre seleccionamos la primera actividad (termina más temprano)
    solucion.push_back(actividades[0]);
    int ultimo_fin = actividades[0].fin;

    //Recorremos las actividades
    for (int k = 1; k < n; k++) {
        if (actividades[k].inicio >= ultimo_fin) { //Si el inicio es mayor o igual al ultimo fin entra a la solucion
            solucion.push_back(actividades[k]);
            ultimo_fin = actividades[k].fin;
        }
    }

    //Impresion
    cout << "Actividades seleccionadas: ";
    for (int g = 0; g < solucion.size(); g++) {
        if (g != 0)cout << ", ";
        cout << "A" << solucion[g].id;
    }
    cout << endl;
    cout << "Maximo subconjunto de actividades compatibles = " << solucion.size() << " actividades" << endl;

    return solucion.size();
}

int main() {
    struct Actividad actividades[] = {
        {1, 1, 4},
        {2, 3, 5},
        {3, 0, 6},
        {4, 5, 7},
        {5, 8, 9},
        {6, 5, 9},
    };

    int n = sizeof(actividades)/sizeof(actividades[0]);

    conjuntoActividades(actividades, n);

    return 0;
}
