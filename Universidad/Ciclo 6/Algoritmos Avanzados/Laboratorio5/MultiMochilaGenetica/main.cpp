#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <map>
#include <cmath>
using namespace std;

#define ITERACIONES 20
#define INDIVIDUOS 30
#define TSELECCION 0.5
#define PCASAMIENTO 0.5
#define TMUTACION 0.3

typedef vector<int> Individuo;

// Estructura para manejar múltiples mochilas
struct Mochilas {
    int numMochilas;
    vector<int> capacidades;

    Mochilas(int n, vector<int> caps) : numMochilas(n), capacidades(caps) {} // Sirve para inicializar
};

// Calcula fitness: suma total de valores en todas las mochilas
int calculaFitness(Individuo cromosoma, int *valores, int n) {
    int suma = 0;

    for (int k = 0; k < n; k++) {
        // Si el item está asignado a alguna mochila (no es 0)
        if (cromosoma[k] > 0) {
            suma += valores[k];
        }
    }

    return suma;
}

// Verifica si viola restricciones de peso en alguna mochila
bool esAberracion(Individuo individuo, int *pesos, int n, Mochilas mochilas) {
    // Vector para acumular peso de cada mochila
    vector<int> pesosPorMochila(mochilas.numMochilas + 1, 0);

    for (int k = 0; k < n; k++) {
        int mochila = individuo[k];
        if (mochila > 0 && mochila <= mochilas.numMochilas) {
            pesosPorMochila[mochila] += pesos[k];
        }
    }

    // Verificar si alguna mochila excede su capacidad
    for (int m = 1; m <= mochilas.numMochilas; m++) {
        if (pesosPorMochila[m] > mochilas.capacidades[m-1]) {
            return true;
        }
    }

    return false;
}

void generaPoblacion(vector<Individuo> &poblacion, int *pesos, int *valores, int n, Mochilas mochilas) {
    int cont = 0;
    srand(time(NULL));

    while (cont < INDIVIDUOS) {
        Individuo individuo;

        for (int k = 0; k < n; k++) {
            // Genera número entre 0 y numMochilas (0 = no asignado)
            individuo.push_back(rand() % (mochilas.numMochilas + 1));
        }

        if (!esAberracion(individuo, pesos, n, mochilas)) {
            poblacion.push_back(individuo);
            cont++;
        }
    }
}

void imprimirPoblacion(vector<Individuo> poblacion, int *valores, int n) {
    for (int k = 0; k < poblacion.size(); k++) {
        cout << "Individuo " << k+1 << ": [";
        for (int g = 0; g < poblacion[k].size(); g++) {
            cout << poblacion[k][g];
            if (g < poblacion[k].size()-1) cout << ",";
        }
        cout << "] | Fitness: " << calculaFitness(poblacion[k], valores, n) << endl;
    }
}

int convierteADecimal(Individuo cromosoma, int base) {
    int decimal = 0;

    for (int k = 0; k < cromosoma.size(); k++) {
        decimal += cromosoma[k] * pow(base, k);
    }

    return decimal;
}

void mataClon(vector<Individuo> &poblacion, int numMochilas) {
    map<int, Individuo> individuosUnicos;

    for (int k = 0; k < poblacion.size(); k++) {
        int decimal = convierteADecimal(poblacion[k], numMochilas + 1);
        individuosUnicos[decimal] = poblacion[k];
    }

    poblacion.clear();

    for (auto par : individuosUnicos) {
        poblacion.push_back(par.second);
    }
}

void calculoSuperviviencia(vector<Individuo> poblacion, vector<int> &superviviencia, int *valores, int n) {
    int sumaFitness = 0;

    for (int k = 0; k < poblacion.size(); k++) {
        sumaFitness += calculaFitness(poblacion[k], valores, n);
    }

    if (sumaFitness == 0) sumaFitness = 1; // Evitar división por cero

    for (int k = 0; k < poblacion.size(); k++) {
        int superFit;
        superFit = round(100 * (double) calculaFitness(poblacion[k], valores, n) / sumaFitness);
        superviviencia.push_back(superFit);
    }
}

void cargarRuleta(vector<int> superviviencia, int *ruleta) {
    int cont = 0;

    for (int k = 0; k < superviviencia.size(); k++) {
        for (int g = 0; g < superviviencia[k]; g++) {
            if (cont < 100) {
                ruleta[cont++] = k;
            }
        }
    }
}

void seleccion(vector<Individuo> poblacion, vector<Individuo> &padres, int *valores, int n) {
    int ruleta[100];

    for (int k = 0; k < 100; k++) ruleta[k] = -1;

    vector<int> superviviencia;

    calculoSuperviviencia(poblacion, superviviencia, valores, n);
    cargarRuleta(superviviencia, ruleta);

    int numeroPadres = round(poblacion.size() * TSELECCION);

    for (int k = 0; k < numeroPadres; k++) {
        int ticket = rand() % 100;
        int individuoSeleccionado = ruleta[ticket];
        if (individuoSeleccionado != -1) {
            padres.push_back(poblacion[individuoSeleccionado]);
        }
    }
}

void crearHijo(Individuo padre, Individuo madre, Individuo &hijo) {
    int indiceCorte = round(padre.size() * PCASAMIENTO);

    for (int k = 0; k < padre.size(); k++) {
        if (k < indiceCorte) {
            hijo.push_back(padre[k]);
        }
        else {
            hijo.push_back(madre[k]);
        }
    }
}

void casamiento(vector<Individuo> &poblacion, vector<Individuo> padres, int *pesos, int n, Mochilas mochilas) {
    for (int k = 0; k < padres.size(); k++) {
        for (int g = 0; g < padres.size(); g++) {
            if (k != g) {
                Individuo hijo;
                crearHijo(padres[k], padres[g], hijo);
                if (!esAberracion(hijo, pesos, n, mochilas)) {
                    poblacion.push_back(hijo);
                }
            }
        }
    }
}

// Inversión: invierte las asignaciones de mochilas
void inversion(vector<Individuo> &poblacion, vector<Individuo> padres, int *pesos, int n, Mochilas mochilas) {
    for (int k = 0; k < padres.size(); k++) {
        Individuo nuevo;

        for (int g = 0; g < padres[k].size(); g++) {
            int valorActual = padres[k][g];
            int nuevoValor;

            if (valorActual == 0) {
                // Si no está asignado, se mantiene sin asignar
                nuevoValor = 0;
            } else {
                // Inversión: 1 -> n, 2 -> n - 1, ..., n -> 1
                nuevoValor = (mochilas.numMochilas + 1) - valorActual;
            }

            nuevo.push_back(nuevoValor);
        }

        if (!esAberracion(nuevo, pesos, n, mochilas)) {
            poblacion.push_back(nuevo);
        }
    }
}

// Mutación: cambia la mochila asignada a algunos items
void mutacion(vector<Individuo> &poblacion, vector<Individuo> padres, int *pesos, int n, Mochilas mochilas) {
    int numeroMutaciones = max(1, (int)round(padres[0].size() * TMUTACION));

    for (int k = 0; k < padres.size(); k++) {
        Individuo mutante = padres[k];

        for (int g = 0; g < numeroMutaciones; g++) {
            int posicion = rand() % n;
            // Cambia a una mochila aleatoria diferente
            int nuevaMochila = rand() % (mochilas.numMochilas + 1);
            mutante[posicion] = nuevaMochila;
        }

        if (!esAberracion(mutante, pesos, n, mochilas)) {
            poblacion.push_back(mutante);
        }
    }
}

int nAux;
void regenerarPoblacion(vector<Individuo> &poblacion, int *valores, int n, Mochilas mochilas) {
    mataClon(poblacion, mochilas.numMochilas);
    nAux = n;

    sort(poblacion.begin(), poblacion.end(),
        [valores](const vector<int> &k, const vector<int> &g) {
            return calculaFitness(k, valores, nAux) > calculaFitness(g, valores, nAux);
        }
    );

    if (INDIVIDUOS < poblacion.size()) {
        poblacion.erase(poblacion.begin() + INDIVIDUOS, poblacion.end());
    }
}

void muestraMejor(vector<Individuo> poblacion, int *pesos, int *valores, int n, Mochilas mochilas) {
    int mejor = 0;

    for (int k = 0; k < poblacion.size(); k++) {
        if (calculaFitness(poblacion[mejor], valores, n) < calculaFitness(poblacion[k], valores, n)) {
            mejor = k;
        }
    }

    cout << endl << "=== MEJOR SOLUCION ===" << endl;
    cout << "Valor total: " << calculaFitness(poblacion[mejor], valores, n) << endl;

    // Mostrar distribución por mochilas
    for (int m = 1; m <= mochilas.numMochilas; m++) {
        cout << endl << "Mochila " << m << " (Capacidad: " << mochilas.capacidades[m-1] << "):" << endl;
        int pesoTotal = 0;
        int valorTotal = 0;

        cout << "  Items: ";
        for (int k = 0; k < n; k++) {
            if (poblacion[mejor][k] == m) {
                cout << k << " ";
                pesoTotal += pesos[k];
                valorTotal += valores[k];
            }
        }
        cout << endl << "  Peso usado: " << pesoTotal << "/" << mochilas.capacidades[m-1];
        cout << endl << "  Valor: " << valorTotal << endl;
    }

    cout << endl << "Cromosoma: [";
    for (int k = 0; k < n; k++) {
        cout << poblacion[mejor][k];
        if (k < n-1) cout << ", ";
    }
    cout << "]" << endl;
}

void mochilaAG(int *pesos, int *valores, int n, Mochilas mochilas) {
    vector<Individuo> poblacion;

    generaPoblacion(poblacion, pesos, valores, n, mochilas);
    mataClon(poblacion, mochilas.numMochilas);

    cout << "Generacion inicial: " << poblacion.size() << " individuos" << endl;

    for (int k = 0; k < ITERACIONES; k++) {
        vector<Individuo> padres;
        seleccion(poblacion, padres, valores, n);
        casamiento(poblacion, padres, pesos, n, mochilas);
        inversion(poblacion, padres, pesos, n, mochilas);
        mutacion(poblacion, padres, pesos, n, mochilas);
        regenerarPoblacion(poblacion, valores, n, mochilas);

        if (k % 5 == 0 || k == ITERACIONES-1) {
            cout << endl << "--- Iteracion " << k + 1 << " ---";
            muestraMejor(poblacion, pesos, valores, n, mochilas);
        }
    }
}

int main() {
    // Items: peso y valor
    int pesos[] =   {10, 5, 15, 8, 12, 6, 20, 9};
    int valores[] = {20, 8, 25, 12, 18, 10, 30, 15};
    int n = sizeof(pesos) / sizeof(pesos[0]);

    // 3 mochilas con diferentes capacidades
    vector<int> capacidades = {25, 20, 30};
    Mochilas mochilas(3, capacidades);

    cout << "=== PROBLEMA DE MULTIMOCHILA ===" << endl;
    cout << "Items: " << n << endl;
    cout << "Mochilas: " << mochilas.numMochilas << endl;
    cout << "Capacidades: ";
    for (int c : capacidades) cout << c << " ";
    cout << endl << endl;

    mochilaAG(pesos, valores, n, mochilas);

    return 0;
}