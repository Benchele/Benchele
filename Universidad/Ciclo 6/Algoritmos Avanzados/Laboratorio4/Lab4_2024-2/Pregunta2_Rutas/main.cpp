#include <iostream>
#include <iomanip>
#include <ctime>
#include <climits>
#include <algorithm>
#include <vector>
using namespace std;

#define ITERACIONES 10000
#define alfa 0.4
#define MAX_NODOS 8

enum nodos{A, B, C, D, E, F, G, H};

struct Punto {
    int id;
    int ganancia;
    vector<int> destinos;
};

struct Candidato {
    int id;
    int ganancia;
};

bool compara(Candidato k, Candidato g) {
    return k.ganancia > g.ganancia; //Descendente (Mayor a menor)
}

int  buscarIndice(vector<struct Candidato> listaCandidatos, double RCL) {
    int cont = 0;

    for (int k = 0; k < listaCandidatos.size(); k++) {
        if (listaCandidatos[k].ganancia >= RCL) {
            cont++;
        }
    }

    return cont;
}

void encontrarMejorRuta(struct Punto *puntos, int n) {
    vector<int> solucionMaxima;

    int mejorGanancia = INT_MIN;

    srand(time(NULL));

    for (int iter = 0; iter < ITERACIONES; iter++) {
        vector<int> rutaActual;
        vector<struct Punto> vPuntos;
        vector<struct Candidato> listaCandidatos;

        //Copiamos
        vPuntos.insert(vPuntos.begin(), puntos, puntos + n);

        int gananciaActual = 0;
        int nodoActual = A;  // Siempre empezamos en A

        rutaActual.push_back(nodoActual);

        while (!vPuntos[nodoActual].destinos.empty()) { //Hasta que ya no tenga destinos
            listaCandidatos.clear();

            // Obtener todos los destinos disponibles con sus ganancias
            for (int destino : vPuntos[nodoActual].destinos) {
                listaCandidatos.push_back({destino, vPuntos[destino].ganancia});
            }

            // Ordenar candidatos por ganancia de mayor a menor
            sort(listaCandidatos.begin(), listaCandidatos.end(), compara);

            // Calcular RCL
            int beta = listaCandidatos[0].ganancia;
            int tau = listaCandidatos[listaCandidatos.size() - 1].ganancia;
            double RCL = beta - alfa * (beta - tau);

            int indCandidato = buscarIndice(listaCandidatos, RCL);

            int indAle = rand() % indCandidato;

            int nodoSeleccionado = listaCandidatos[indAle].id;

            // Actualizar ruta y ganancia
            gananciaActual += vPuntos[nodoSeleccionado].ganancia;
            rutaActual.push_back(nodoSeleccionado);
            nodoActual = nodoSeleccionado;
        }

        // Guardar si es la mejor solución
        if (mejorGanancia < gananciaActual) {
            mejorGanancia = gananciaActual;
            solucionMaxima.clear();
            solucionMaxima.insert(solucionMaxima.begin(), rutaActual.begin(), rutaActual.end());
            //O simplemente
            //solucionMaxima = rutaActual;
        }
    }

    // Imprimir resultados
    cout << "Ganancia = " << mejorGanancia << endl;
    cout << "Puntos seleccionados: ";

    // Convertir IDs a letras para imprimir
    char letras[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

    for (int k = 0; k < solucionMaxima.size(); k++) {
        cout << letras[solucionMaxima[k]] << " ";
    }

    cout << endl;
}

int main() {

    struct Punto puntos[MAX_NODOS] = {
        {A, 0,  {B, C, D, E, H}},  // A: Inicio
        {B, 20, {C, D, F, H}},
        {C, 30, {F}},
        {D, 40, {}},
        {E, 40, {C, F, G}},
        {F, 40, {}},
        {G, 10, {}},
        {H, 50, {}}
    };

    int n = sizeof(puntos) / sizeof(puntos[0]);

    encontrarMejorRuta(puntos, n);

    return 0;
}