#include <iostream>
#include <iomanip>
#include <climits>
#include <ctime>
#include <algorithm>
#include <vector>
using namespace std;

#define ITERACIONES 10000
#define alfa 0.3

bool compara(int k, int g) {
    return k < g; //Ascendente (Menor a mayor)
}

int buscaIndice(vector<int> paquetes, double RCL) {
    int cont = 0;

    for (int k = 0; k < paquetes.size(); k++) {
        if (paquetes[k] <= RCL) { //Hasta que llegue al RCL
            cont++;
        }
    }

    return cont;
}

void graspMochila(int *paq, int peso, int n) {
    vector<int> solucionMaxima;
    int mejorResidual = INT_MAX;

    srand(time(NULL)); //Inicializando la semilla del random

    for (int k = 0; k < peso; k++) {
        vector<int> soluciones; //Solucion actual
        vector<int> paquetes; //Paquetes disponibles
        sort(paq, paq + n, compara); //Ordenamos los paquetes de menor a mayor

        paquetes.insert(paquetes.begin(), paq, paq + n); // Copiamos los paquetes al vector

        int residual = peso; //Peso residual

        while (!paquetes.empty()) { //Hasta cuando ya no haya mas paquetes
            int beta = paquetes[0]; //Mejor valor
            int tau = paquetes[paquetes.size() - 1]; //Peor valor
            double RCL = beta + alfa * (tau - beta); //Minimizar

            int indP = buscaIndice(paquetes, RCL); //Buscamos el indice maximo del RCL

            //Buscar valor aleatorio
            int indAle = rand() % indP;

            //Analizar si el paquete entra en la mochila
            if (residual - paquetes[indAle] >= 0) {
                soluciones.push_back(paquetes[indAle]);
                residual -= paquetes[indAle];
            }

            //Eliminamos afuera porque si no se puede meter, no tiene sentido seguir
            //Si entra se elimina, si no entra, igual se elimina porque ya no sirve seguir intentando con ese paquete
            paquetes.erase(paquetes.begin() + indAle); //Eliminamos el paquete usado
        }

        for (int k = 0; k < soluciones.size(); k++) {
            cout << soluciones[k] << " ";
        }
        cout << endl << residual << endl;

        //Analizamos si es la mejor solucion
        if (residual < mejorResidual) {
            mejorResidual = residual;
            solucionMaxima.clear();
            solucionMaxima.insert(solucionMaxima.begin(), soluciones.begin(), soluciones.end());

            //O simplemente
            //solucionMaxima = soluciones;
        }
    }

    cout << "Mejor Solucion: " << endl;
    for (int k = 0; k < solucionMaxima.size(); k++) {
        cout << solucionMaxima[k] << " ";
    }
    cout << endl << mejorResidual << endl;
}

int main() {
    //int paq[] = {3, 2, 12, 4, 15};
    int paq[] = {5, 10, 3, 8, 2, 7, 9, 4, 6, 1, 11, 14, 13, 17, 19, 18, 16};
    int n = sizeof(paq) / sizeof(paq[0]);
    int peso = 15;

    graspMochila(paq, peso, n);

    return 0;
}