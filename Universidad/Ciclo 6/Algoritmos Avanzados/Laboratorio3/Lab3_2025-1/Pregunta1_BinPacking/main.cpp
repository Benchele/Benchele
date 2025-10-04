#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

struct BD {
    int id;
    int velocidad;
};

struct Disco {
    int id;
    int velocidad;
    vector<int> tablas;
};

bool compara(struct BD k, struct BD g) { //Compara tablas
    return k.velocidad > g.velocidad; //Descendente (Mayor a menor)
}

bool compara_2(struct Disco k, struct Disco g) { //Compara discos
    return k.velocidad > g.velocidad; //Descendente (Mayor a menor)
}

int cargaDiscos(struct BD *tablas, struct Disco *discos, int n, int m){
    //n = numero de tablas | m = numero de discos

    //Ordenamos las tablas de mayor a menor
    sort(tablas, tablas + n, compara);

    int g = 0; //Indice del disco actual
    for (int k = 0; k < n; k++) {
        sort(discos, discos + m, compara_2); //Ordenar los discos para siempre usar el mayor
        if (discos[g].velocidad - tablas[k].velocidad >= 0) { //Siempre se elige el primero (Mayor)
            discos[g].velocidad -= tablas[k].velocidad;
            discos[g].tablas.push_back(tablas[k].id);
        }
    }

    for (int k = 0; k < m; k++) {
        cout << "Disco " << discos[k].id << ": ";
        for (int j = 0; j < discos[k].tablas.size(); j++) {
            if (j != 0)cout << ", ";
            cout << discos[k].tablas[j] << " ";
        }
        cout << endl;
    }

    return 0;
}

int main() {
    struct BD baseDatos[] = {
        {1, 150},
        {2, 100},
        {3, 180},
        {4, 50},
        {5, 120},
        {6, 10},
    };

    struct Disco discos[] = {
        {1, 250, {}},
        {2, 200, {}},
        {3, 200, {}},
        {4, 100, {}},
    };

    int n = sizeof(baseDatos) / sizeof(baseDatos[0]);
    int m = sizeof(discos) / sizeof(discos[0]);

    cargaDiscos(baseDatos, discos, n, m);

    return 0;
}