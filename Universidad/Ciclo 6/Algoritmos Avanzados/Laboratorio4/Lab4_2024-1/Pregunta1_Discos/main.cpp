#include <iostream>
#include <iomanip>
#include <climits>
#include <ctime>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

#define ITERACIONES 100000
#define alfa 0.3

struct Objeto {
    int id;
    int velocidad;
    int capacidad;
};

struct Solucion {
    int idDisco;
    int tablaEnDisco;
};

bool compara(struct Objeto k, struct Objeto g) {
    return k.velocidad > g.velocidad; //Descendente (Mayor a menor)
}

int buscarIndice(vector<struct Objeto> objeto, double RCL) {
    int cont = 0;

    for (int k = 0; k < objeto.size(); k++) {
        if (objeto[k].velocidad >= RCL) { //Hasta que llegue al RCL
            cont++;
        }
    }

    return cont;
}

void cargaDisco(struct Objeto *tabla, struct Objeto *disco, int n, int m) {
    vector<struct Solucion> solucionMaxima;

    int mejor = INT_MIN;

    srand(time(NULL)); //Establecer semilla para aleatoriedad

    for (int k = 0; k < ITERACIONES; k++) {
        vector<struct Solucion> resultado; //Resultado actual de la iteracion

        vector<struct Objeto> vTablas;
        vector<struct Objeto> vDiscos;

        //Copiamos
        vTablas.insert(vTablas.begin(), tabla, tabla + n);
        vDiscos.insert(vDiscos.begin(), disco, disco + m);

        //Ordenamos tablas
        sort(vTablas.begin(), vTablas.end(), compara); //Ordenar tablas por velocidad descendentemente

        int residual;

        while (!vTablas.empty()) {

            //Respecto a las tablas
            int betaTabla = vTablas[0].velocidad;
            int tauTabla = vTablas[vTablas.size() - 1].velocidad;

            double RCLTabla = betaTabla - alfa * (betaTabla - tauTabla); //Maximizar velocidad

            int indTabla = buscarIndice(vTablas, RCLTabla);

            int indAleTabla = rand() % indTabla; //Indice aleatorio dentro de la RCLTabla

            //Respecto a los discos
            sort(vDiscos.begin(), vDiscos.end(), compara); //Ordenar discos por velocidad descendentemente
            int betaDisco = vDiscos[0].velocidad;
            int tauDisco = vDiscos[vDiscos.size() - 1].velocidad;

            double RCLDisco = betaDisco - alfa * (betaDisco - tauDisco);

            int indDisco = buscarIndice(vDiscos, RCLDisco);

            int indAleDisco = rand() % indDisco; //Indice aleatorio dentro de la RCLDisco

            if (vDiscos[indAleDisco].velocidad >= vTablas[indAleTabla].velocidad) {
                resultado.push_back({vDiscos[indAleDisco].id, vTablas[indAleTabla].id});
                vDiscos[indAleDisco].velocidad -= vTablas[indAleTabla].velocidad; //Disminuir velocidad del disco
            }

            //Se borra cuando ya se ha asignado la tabla o cuando no se puede asignar la tabla
            vTablas.erase(vTablas.begin() + indAleTabla);
        }

        //Ordenamos de mayor a menor los discos
        sort(vDiscos.begin(), vDiscos.end(), compara);
        residual = vDiscos[vDiscos.size() - 1].velocidad; //El menor disco

        if (mejor < residual) {
            mejor = residual;
            solucionMaxima.clear();
            solucionMaxima.insert(solucionMaxima.begin(), resultado.begin(), resultado.end());
            //O simplemente
            //solucionMaxima = resultado;
        }
    }

    //Mapa para impresion
    map<int, vector<int>> agrupado;

    for (auto solucion : solucionMaxima) {
        agrupado[solucion.idDisco].push_back(solucion.tablaEnDisco);
    }

    for (auto solucion : agrupado) {
        cout << solucion.first << ": ";
        for (auto tablas : solucion.second) {
            cout << tablas << " ";
        }
        cout << endl;
    }
    cout << endl << mejor << endl;
}

int main() {
    //Se busca que la mejor tabla vaya en el mejor disco

    //Los discos varian -> Cada vez que se coloca una tabla en un disco, la velocidad del disco disminuye

    //Debe tener dos RCL

    struct Objeto tablas[] = {
        {1, 150, 20},
        {2, 100, 10},
        {3, 80, 15},
        {4, 50, 100},
        {5, 120, 50},
        {6, 10, 100}
    };
    struct Objeto discos[] = {
        {1, 250, 800},
        {2, 200, 750},
        {3, 200, 850}
    };

    int n = sizeof(tablas) / sizeof(tablas[0]);

    int m = sizeof(discos) / sizeof(discos[0]);

    cargaDisco(tablas, discos, n, m);

    return 0;
}