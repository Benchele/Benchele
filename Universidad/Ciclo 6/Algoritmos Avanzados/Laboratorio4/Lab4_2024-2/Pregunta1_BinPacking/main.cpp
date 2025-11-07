#include <iostream>
#include <iomanip>
#include <ctime>
#include <climits>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

#define ITERACIONES 1000
#define alfa 0.3

struct Caja {
    int id;
    int capacidad;
};

struct Solucion {
    int caja;
    int objeto;
};

bool compara(int k, int g) {
    return k > g; //Descendente (Mayor a menor)
}

bool compara2(struct Caja k, struct Caja g) {
    return k.capacidad > g.capacidad; //Descendente (Mayor a menor)
}

int buscarIndice(vector<int> vObjetos, double RCL) {
    int cont = 0;

    for (int k = 0; k < vObjetos.size(); k++) {
        if (vObjetos[k] >= RCL) {
            cont++;
        }
    }

    return cont;
}

int buscarIndice(vector<struct Caja> vCajas, double RCL) {
    int cont = 0;

    for (int k = 0; k < vCajas.size(); k++) {
        if (vCajas[k].capacidad >= RCL) {
            cont++;
        }
    }

    return cont;
}

void empaquetarObjetos(int *objetos, int n, vector<struct Caja> cajas) {
    vector<struct Solucion> solucionMaxima;

    int menorCantidad = INT_MAX;

    srand(time(NULL));

    for (int k = 0; k < ITERACIONES; k++) {
        vector<struct Solucion> resultado;
        vector<int> vObjetos;
        vector<struct Caja> vCajas;

        //Copiamos
        vObjetos.insert(vObjetos.begin(), objetos, objetos + n);
        vCajas.insert(vCajas.begin(), cajas.begin(), cajas.end());

        //Ordenamos los objetos de mayor a menor -> Para evitar fragmentacion en las cajas
        sort(vObjetos.begin(), vObjetos.end(), compara);

        int contadorCajas = 0;
        int numeroDeCajas = 0;

        while (!vObjetos.empty()) { //Mientras haya objetos por empaquetar

            //Objetos
            int betaObjeto = vObjetos[0];
            int tauObjeto = vObjetos[vObjetos.size() - 1];
            double RCLObjeto = betaObjeto - alfa * (betaObjeto - tauObjeto);

            int indObjeto = buscarIndice(vObjetos, RCLObjeto);

            int indAleObjeto = rand() % indObjeto;

            //Cajas

            bool entra = false;

            if (!vCajas.empty()) {
                sort(vCajas.begin(), vCajas.end(), compara2); //Ordenamos las cajas de mayor a menor

                int betaCaja = vCajas[0].capacidad;
                int tauCaja = vCajas[vCajas.size() - 1].capacidad;
                double RCLCaja = betaCaja - alfa * (betaCaja - tauCaja);

                int indCaja = buscarIndice(vCajas, RCLCaja);

                int indAleCaja = rand() % indCaja;

                if (vCajas[indAleCaja].capacidad - vObjetos[indAleObjeto] >= 0) {
                    vCajas[indAleCaja].capacidad -= vObjetos[indAleObjeto];
                    resultado.push_back({vCajas[indAleCaja].id, vObjetos[indAleObjeto]});
                    entra = true;
                }
            }

            if (!entra) { //Si no entra en ninguna caja, creamos una nueva
                contadorCajas++;
                struct Caja nuevaCaja;
                nuevaCaja.id = contadorCajas;
                nuevaCaja.capacidad = 10 - vObjetos[indAleObjeto]; //Capacidad fija de 10 - el objeto a añadir

                resultado.push_back({nuevaCaja.id, vObjetos[indAleObjeto]}); //Entra en el resultado
                vCajas.push_back(nuevaCaja); //Se añade la nueva caja
            }

            //Eliminamos el objeto ya empaquetado
            vObjetos.erase(vObjetos.begin() + indAleObjeto);
        }

        numeroDeCajas = vCajas.size();

        if (numeroDeCajas < menorCantidad) {
            menorCantidad = numeroDeCajas;
            solucionMaxima.clear();
            solucionMaxima.insert(solucionMaxima.begin(), resultado.begin(), resultado.end());
            //O simplemente
            //solucionMaxima = resultado;
        }
    }

    //Mapa para la impresion
    map<int, vector<int>> cajasConObjetos;

    for (auto solucion : solucionMaxima) {
        cajasConObjetos[solucion.caja].push_back(solucion.objeto);
    }

    for (auto solucion : cajasConObjetos) {
        cout << "Contenedor " << solucion.first << ": ";
        for (auto objetos : solucion.second) {
            cout << objetos << " ";
        }
        cout << endl;
    }

}

int main() {
    int objetos[] = {4, 8, 1, 4, 2, 1};
    int n = sizeof(objetos) / sizeof(objetos[0]);

    vector<Caja> cajas;

    empaquetarObjetos(objetos, n, cajas);

    return 0;
}