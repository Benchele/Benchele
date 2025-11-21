#include <iostream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
using namespace std;

#define ITERACIONES 10
#define NUM_INDIVIDUOS 20
#define TSELECCION 0.5
#define PCASAMIENTO 0.5
#define TMUTACION 0.5

//Calcular fitness
int calculaFitness(vector<int> cromosoma, int *paquete) {
    int sumaPeso = 0;

    for (int k = 0; k < cromosoma.size(); k++) {
        if (cromosoma[k] == 1) {
            sumaPeso += paquete[k];
        }

        //O puedes hacerlo asi
        //sumaPeso += paquete[k] * cromosoma[k];
    }

    return sumaPeso;
}

//Imprimir poblacion
void imprimirPoblacion(vector<vector<int>> poblacion, int *paquetes) {
    for (int k = 0; k < poblacion.size(); k++) {
        cout << "Individuo " << k + 1 << ": ";
        for (int g = 0; g < poblacion[k].size(); g++) {
            cout << poblacion[k][g] << " ";
        }
        cout << "| Funcion objetivo: " << calculaFitness(poblacion[k], paquetes) <<endl;
    }
    cout << endl;
}

//////////////////////////////////////////////////
//Convierte a decimal
int convierteADecimal(vector<int> cromosoma) {
    int decimal = 0;

    for (int k = 0; k < cromosoma.size(); k++) {
        decimal += cromosoma[k] * pow(2, k);
    }

    return decimal;
}

//Matar clones
void mataClon(vector<vector<int>> &poblacion) {
    map<int, vector<int>> individuosUnicos;

    for (int k = 0; k < poblacion.size(); k++) {
        int decimal = convierteADecimal(poblacion[k]);
        individuosUnicos[decimal] = poblacion[k]; // La llave es la representacion decimal del cromosoma
    }

    poblacion.clear();

    for (auto par : individuosUnicos) {
        poblacion.push_back(par.second);
    }

    //Otra forma
    // for (map<int, vector<int>>::iterator it = individuosUnicos.begin(); it != individuosUnicos.end(); it++) {
    //     poblacion.push_back(it->second);
    // }
}

///////////////////////////////////////////
//Verificar si es aberracion
int aberracion(vector<int> individuo, int *paquetes, int peso) {
    return calculaFitness(individuo, paquetes) > peso;
}

///////////////////////////////////////////
//Generar poblacion
void generarPoblacion(vector<vector<int>> &poblacion, int *paquetes, int n, int peso) {
    int cont = 0;

    srand(time(NULL));

    while (cont < NUM_INDIVIDUOS) {
        vector<int> individuo;

        for (int k = 0; k < n; k++) {
            individuo.push_back(rand() % 2); //0 o 1 -> Entra o no entra
        }

        //Analizar si es aberracion
        if (!aberracion(individuo, paquetes, peso)) {
            poblacion.push_back(individuo);
            cont++;
        }
    }
}

///////////////////////////////////////////////
void calculaSupervivencia(vector<vector<int>> poblacion, vector<int> &supervivencia, int *paquetes, int n, int peso) {
    int sumaFitness = 0;

    //Calcula el fitness total
    for (int k = 0; k < poblacion.size(); k++) {
        sumaFitness += calculaFitness(poblacion[k], paquetes); //Sumatoria de fitness - 100%
    }

    for (int k = 0; k < poblacion.size(); k++) {
        int superFit; // Dividir cada fitness entre el total
        superFit = round(100 * (double)calculaFitness(poblacion[k], paquetes)/sumaFitness); // Porcentaje de superviviencia
        supervivencia.push_back(superFit);
    }
}

void cargarRuleta(vector<int> supervivencia, int *ruleta) {
    int indiceRuleta = 0;

    for (int k = 0; k < supervivencia.size(); k++) {
        for (int g = 0; g < supervivencia[k]; g++) {
            ruleta[indiceRuleta++] = k; //Indice del individuo
        }
    }
}

void seleccion(vector<vector<int>> poblacion, vector<vector<int>> &padres, int *paquetes, int n, int peso) {
    //Calcular la superviviencia de cada individuo de acuerdo a su fitness

    int ruleta[100];

    for (int k = 0; k < 100; k++) ruleta[k] = -1; //Inicializar ruleta en -1

    vector<int> supervivencia;

    calculaSupervivencia(poblacion, supervivencia, paquetes, n, peso);
    cargarRuleta(supervivencia, ruleta);

    int numeroPadres = round(poblacion.size()*TSELECCION);

    for (int k = 0; k < numeroPadres; k++) {
        int ticket = rand() % 100; //Numero entre 0 y 99
        int individuoSeleccionado = ruleta[ticket];
        if (individuoSeleccionado != -1) {
            padres.push_back(poblacion[individuoSeleccionado]);
        }
    }

    //imprimirPoblacion(padres, paquetes);
}

//////////////////////////////////////////////
void crearHijo(vector<int> padre, vector<int> madre, vector<int> &hijo){
    int posI = round(padre.size()*PCASAMIENTO);

    for (int k = 0; k < padre.size(); k++) {
        if (k < posI) {
            hijo.push_back(padre[k]);
        } else {
            hijo.push_back(madre[k]);
        }
    }

    //Otra forma

    // for (int k = 0; k < posI; k++) {
    //     hijo.push_back(padre[k]);
    // }
    // for (int k = posI; k < madre.size(); k++) {
    //     hijo.push_back(madre[k]);
    // }
}

void casamiento(vector<vector<int>> &poblacion, vector<vector<int>> padres, int *paquetes, int peso) {
    //Se va a generar una nueva poblacion aqui
    for (int k = 0; k < padres.size(); k++) {
        for (int g = 0; g < padres.size(); g++) {
            if (k != g) {
                vector<int> hijo;
                crearHijo(padres[k], padres[g], hijo);
                if (!aberracion(hijo, paquetes, peso)) {
                    poblacion.push_back(hijo);
                }
            }
        }
    }
}

//////////////////////////////////////////////
void regenerarPoblacion(vector<vector<int>> &poblacion, int *paquetes, int peso) {
    mataClon(poblacion);

    sort(poblacion.begin(), poblacion.end(),
        [paquetes](const vector<int> &k, const vector<int> &g) { //Funcion lambda
            return calculaFitness(k, paquetes) > calculaFitness(g, paquetes);
        }
    );

    if (NUM_INDIVIDUOS < poblacion.size()) { //Tener los mejores N individuos
        poblacion.erase(poblacion.begin() + NUM_INDIVIDUOS, poblacion.end());
    }
}

//////////////////////////////////////////////
int muestarMejor(vector<vector<int>> poblacion, int *paquetes, int peso) {
    int mejor = 0;

    //Se puede asumir que la mejor poblacion esta en la posicion 0
    for (int k = 0; k < poblacion.size(); k++) {
        if (calculaFitness(poblacion[mejor], paquetes) < calculaFitness(poblacion[k], paquetes)) {
            mejor = k;
        }
    }

    cout << endl << "La mejor solucion actual es: " << calculaFitness(poblacion[mejor], paquetes) << endl;

    for (int k = 0; k < poblacion[mejor].size(); k++) {
        cout << poblacion[mejor][k] << " ";
    }
    cout << endl;

    return peso - calculaFitness(poblacion[mejor], paquetes);
}

//////////////////////////////////////////////
void inversion(vector<vector<int>> &poblacion, vector<vector<int>> padres, int *paquetes, int peso) {
    for (int k = 0; k < padres.size(); k++) {
        vector<int> nuevo;

        for (int g = 0; g < padres[k].size(); g++) {
            if (padres[k][g] == 0) {
                nuevo.push_back(1);
            }
            else {
                nuevo.push_back(0);
            }
        }

        if (!aberracion(nuevo, paquetes, peso)) {
            poblacion.push_back(nuevo);
        }
    }
}

//////////////////////////////////////////////
void mutacion(vector<vector<int>> &poblacion, vector<vector<int>> padres, int *paquetes, int peso) {
    int numeroMutaciones = round(padres[0].size()*TMUTACION);

    for (int k = 0; k < padres.size(); k++) {
        for (int g = 0; g < numeroMutaciones; g++) {
            int indice = rand() % padres[0].size();
            if (padres[k][indice] == 1) {
                padres[k][indice] = 0;
            } else {
                padres[k][indice] = 1;
            }
        }

        if (!aberracion(padres[k], paquetes, peso)) {
            poblacion.push_back(padres[k]);
        }
    }
}

//////////////////////////////////////////////
//Principal
void mochilaGenetica(int *paquetes, int n, int peso) {
    vector<vector<int>> poblacion;

    generarPoblacion(poblacion, paquetes, n, peso);
    mataClon(poblacion);
    imprimirPoblacion(poblacion, paquetes);


    for (int k = 0; k < ITERACIONES; k++) {
        vector<vector<int>> padres;

        seleccion(poblacion, padres, paquetes, n, peso);
        casamiento(poblacion, padres, paquetes, peso);
        inversion(poblacion, padres, paquetes, peso);
        mutacion(poblacion, padres, paquetes, peso);
        regenerarPoblacion(poblacion, paquetes, peso);
        muestarMejor(poblacion, paquetes, peso);
    }
}

int main() {
    //Generar poblacion
    //Matar clones
    //Seleccionar padres
    //Casamiento
    //Regenerar la poblacion
    //Mostrar la mejor solucion

    int paquetes[] = {10, 20, 40, 50, 45, 70, 80, 100};
    //int paquetes[] = {1, 2, 2, 12, 4};
    int n = sizeof(paquetes)/sizeof(paquetes[0]);

    int peso = 120;
    //int peso = 15;

    mochilaGenetica(paquetes, n, peso);

    return 0;
}