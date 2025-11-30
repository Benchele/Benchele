#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <ctime>
#include <climits>
#include <cmath>
#include <map>
using namespace std;

#define ITERACIONES_AG 1000
#define POBLACION_INICIAL 10
#define TASA_SELECCION 0.8
#define TASA_MUTACION 0.5
#define NTAREAS 10
#define TIEMPO_MAX 20

struct Tarea {
    int id;
    int duracion;
    int inicio;      // si
    int fin;         // ei
    int penalizacion; // wi
};

// Datos del problema
Tarea tareas[NTAREAS] = {
    {1, 2, 1, 4, 10},   // T1
    {2, 3, 3, 6, 15},   // T2
    {3, 1, 5, 7, 8},    // T3
    {4, 2, 2, 5, 12},   // T4
    {5, 4, 6, 10, 20},  // T5
    {6, 2, 8, 11, 7},   // T6
    {7, 1, 9, 10, 6},   // T7
    {8, 3, 1, 3, 18},   // T8
    {9, 2, 4, 7, 14},   // T9
    {10, 3, 6, 9, 16}   // T10
};

typedef vector<int> Cromosoma; // Orden de prioridad de tareas

// Verifica si un intervalo está disponible
bool estaDisponible(vector<bool> &ocupado, int inicio, int duracion) {
    if (inicio < 0 || inicio + duracion > TIEMPO_MAX) {
        return false;
    }

    for (int t = inicio; t < inicio + duracion; t++) {
        if (ocupado[t]) {
            return false;
        }
    }
    return true;
}

// Marca un intervalo como ocupado
void marcarOcupado(vector<bool> &ocupado, int inicio, int duracion) {
    for (int t = inicio; t < inicio + duracion; t++) {
        ocupado[t] = true;
    }
}

// Busca el primer tiempo disponible para una tarea
int buscarTiempoDisponible(vector<bool> &ocupado, Tarea &tarea) {
    for (int t = tarea.inicio; t <= tarea.fin - tarea.duracion + 1; t++) {
        if (estaDisponible(ocupado, t, tarea.duracion)) {
            return t;
        }
    }
    return -1;
}

// Decodifica un cromosoma y retorna las tareas programadas y la penalización
void decodificarCromosoma(Cromosoma &cromosoma, vector<int> &programadas, int &penalizacion) {
    vector<bool> ocupado(TIEMPO_MAX, false);
    programadas.clear();
    penalizacion = 0;

    // Intentar programar en el orden del cromosoma
    for (int k = 0; k < cromosoma.size(); k++) {
        int indiceTarea = cromosoma[k];
        int tiempo = buscarTiempoDisponible(ocupado, tareas[indiceTarea]);

        if (tiempo != -1) {
            // Se puede programar
            programadas.push_back(indiceTarea);
            marcarOcupado(ocupado, tiempo, tareas[indiceTarea].duracion);
        } else {
            // No se puede programar, incurre en penalización
            penalizacion += tareas[indiceTarea].penalizacion;
        }
    }
}

// Calcula el fitness (menor es mejor)
int calcularFitness(Cromosoma &cromosoma) {
    vector<int> programadas;
    int penalizacion;
    decodificarCromosoma(cromosoma, programadas, penalizacion);
    return penalizacion;
}

// Genera población inicial aleatoria
void generarPoblacionInicial(vector<Cromosoma> &poblacion) {
    cout << "Generando poblacion inicial..." << endl;

    for (int k = 0; k < POBLACION_INICIAL; k++) {
        Cromosoma individuo;

        // Crear un orden aleatorio de tareas [0, 1, 2, ..., 9]
        for (int g = 0; g < NTAREAS; g++) {
            individuo.push_back(g);
        }

        // Mezclar aleatoriamente
        random_shuffle(individuo.begin(), individuo.end());

        poblacion.push_back(individuo);
    }

    cout << "Poblacion inicial: " << poblacion.size() << " individuos" << endl << endl;
}

// Elimina duplicados
void eliminarDuplicados(vector<Cromosoma> &poblacion) {
    map<string, Cromosoma> unicos;

    for (int k = 0; k < poblacion.size(); k++) {
        string key = "";
        for (int g = 0; g < poblacion[k].size(); g++) {
            key += to_string(poblacion[k][g]) + ",";
        }
        unicos[key] = poblacion[k];
    }

    poblacion.clear();
    for (auto par : unicos) {
        poblacion.push_back(par.second);
    }
}

// Calcula supervivencia (fitness inverso)
void calcularSupervivencia(vector<Cromosoma> &poblacion, vector<int> &supervivencia) {
    int maxFitness = 0;

    // Encontrar el peor fitness
    for (int k = 0; k < poblacion.size(); k++) {
        int fit = calcularFitness(poblacion[k]);
        if (fit > maxFitness) {
            maxFitness = fit;
        }
    }

    // Calcular fitness inverso
    vector<int> fitnessInverso;
    int sumaFitnessInv = 0;

    for (int k = 0; k < poblacion.size(); k++) {
        int fitInv = (maxFitness + 1) - calcularFitness(poblacion[k]);
        fitnessInverso.push_back(fitInv);
        sumaFitnessInv += fitInv;
    }

    // Calcular porcentaje de supervivencia
    for (int k = 0; k < poblacion.size(); k++) {
        int superFit;
        if (sumaFitnessInv > 0) {
            superFit = round(100.0 * fitnessInverso[k] / sumaFitnessInv);
        } else {
            superFit = 100 / poblacion.size();
        }
        supervivencia.push_back(superFit);
    }
}

// Carga la ruleta
void cargarRuleta(vector<int> &supervivencia, int *ruleta) {
    int cont = 0;

    for (int k = 0; k < supervivencia.size(); k++) {
        for (int g = 0; g < supervivencia[k]; g++) {
            if (cont < 100) {
                ruleta[cont++] = k;
            }
        }
    }
}

// Selección por ruleta
void seleccion(vector<Cromosoma> &poblacion, vector<Cromosoma> &padres) {
    int ruleta[100];
    for (int k = 0; k < 100; k++) ruleta[k] = -1;

    vector<int> supervivencia;
    calcularSupervivencia(poblacion, supervivencia);
    cargarRuleta(supervivencia, ruleta);

    int numeroPadres = round(poblacion.size() * TASA_SELECCION);

    for (int k = 0; k < numeroPadres; k++) {
        int ticket = rand() % 100;
        int individuoSeleccionado = ruleta[ticket];
        if (individuoSeleccionado != -1) {
            padres.push_back(poblacion[individuoSeleccionado]);
        }
    }
}

// Cruce OX (Order Crossover) - Mantiene permutaciones válidas
void crearHijo(Cromosoma &padre, Cromosoma &madre, Cromosoma &hijo) {
    int n = padre.size();
    hijo.resize(n, -1);

    // Seleccionar dos puntos de corte
    int punto1 = rand() % n;
    int punto2 = rand() % n;

    if (punto1 > punto2) swap(punto1, punto2);

    // Copiar segmento del padre
    for (int k = punto1; k <= punto2; k++) {
        hijo[k] = padre[k];
    }

    // Completar con elementos de la madre en orden
    int posMadre = 0;
    for (int k = 0; k < n; k++) {
        if (hijo[k] == -1) {
            // Buscar el siguiente elemento de la madre que no esté en el hijo
            while (posMadre < n) {
                bool existe = false;
                for (int g = 0; g < n; g++) {
                    if (hijo[g] == madre[posMadre]) {
                        existe = true;
                        break;
                    }
                }

                if (!existe) {
                    hijo[k] = madre[posMadre];
                    posMadre++;
                    break;
                }
                posMadre++;
            }
        }
    }
}

// Casamiento
void casamiento(vector<Cromosoma> &poblacion, vector<Cromosoma> &padres) {
    for (int k = 0; k < padres.size(); k++) {
        for (int g = 0; g < padres.size(); g++) {
            if (k != g) {
                Cromosoma hijo;
                crearHijo(padres[k], padres[g], hijo);
                poblacion.push_back(hijo);
            }
        }
    }
}

// Mutación: Intercambio de dos posiciones (Swap Mutation)
void mutacion(vector<Cromosoma> &poblacion, vector<Cromosoma> &padres) {
    int numeroMutaciones = max(1, (int)round(TASA_MUTACION * padres.size()));

    for (int k = 0; k < numeroMutaciones; k++) {
        if (padres.empty()) break;

        int posAle = rand() % padres.size();
        Cromosoma mutante = padres[posAle];

        // Realizar varios swaps
        int swaps = 1 + rand() % 3; // 1 a 3 swaps
        for (int g = 0; g < swaps; g++) {
            int pos1 = rand() % mutante.size();
            int pos2 = rand() % mutante.size();
            swap(mutante[pos1], mutante[pos2]);
        }

        poblacion.push_back(mutante);
    }
}

// Inversión: Invertir un segmento
void inversion(vector<Cromosoma> &poblacion, vector<Cromosoma> &padres) {
    for (int k = 0; k < padres.size(); k++) {
        Cromosoma invertido = padres[k];

        int inicio = rand() % invertido.size();
        int fin = inicio + rand() % (invertido.size() - inicio);

        reverse(invertido.begin() + inicio, invertido.begin() + fin + 1);

        poblacion.push_back(invertido);
    }
}

// Regenerar población
void regenerarPoblacion(vector<Cromosoma> &poblacion) {
    eliminarDuplicados(poblacion);

    // Ordenar por fitness (menor es mejor)
    sort(poblacion.begin(), poblacion.end(),
        [](Cromosoma &a, Cromosoma &b) {
            return calcularFitness(a) < calcularFitness(b);
        }
    );

    // Mantener solo los mejores
    if (POBLACION_INICIAL < poblacion.size()) {
        poblacion.erase(poblacion.begin() + POBLACION_INICIAL, poblacion.end());
    }
}

// Muestra el mejor individuo
void mostrarMejor(vector<Cromosoma> &poblacion) {
    int mejor = 0;

    for (int k = 0; k < poblacion.size(); k++) {
        if (calcularFitness(poblacion[k]) < calcularFitness(poblacion[mejor])) {
            mejor = k;
        }
    }

    int fitness = calcularFitness(poblacion[mejor]);
    cout << "Mejor fitness (penalizacion): " << fitness << endl;
}

// Imprime solución final
void imprimirSolucionFinal(Cromosoma &cromosoma) {
    vector<int> programadas;
    int penalizacion;

    decodificarCromosoma(cromosoma, programadas, penalizacion);

    cout << endl << "=== MEJOR SOLUCION FINAL ===" << endl;
    cout << "Orden del cromosoma: [";
    for (int k = 0; k < cromosoma.size(); k++) {
        cout << "T" << (tareas[cromosoma[k]].id);
        if (k < cromosoma.size() - 1) cout << ", ";
    }
    cout << "]" << endl;

    cout << "\nTareas programadas: ";
    for (int k = 0; k < programadas.size(); k++) {
        cout << "T" << (tareas[programadas[k]].id);
        if (k < programadas.size() - 1) cout << ", ";
    }
    cout << endl;

    cout << "Penalizacion total: " << penalizacion << endl;

    // Tareas no programadas
    cout << "\nTareas no programadas: ";
    bool hayNoProgramadas = false;
    for (int k = 0; k < NTAREAS; k++) {
        bool estaProgramada = false;

        for (int g = 0; g < programadas.size(); g++) {
            if (programadas[g] == k) {
                estaProgramada = true;
                break;
            }
        }

        if (!estaProgramada) {
            cout << "T" << (tareas[k].id) << " ";
            hayNoProgramadas = true;
        }
    }

    if (!hayNoProgramadas) {
        cout << "(ninguna)";
    }
    cout << endl;
}

// Algoritmo Genético principal
void algoritmoGenetico() {
    vector<Cromosoma> poblacion;

    generarPoblacionInicial(poblacion);
    eliminarDuplicados(poblacion);

    cout << "Iniciando Algoritmo Genetico..." << endl << endl;

    for (int k = 0; k < ITERACIONES_AG; k++) {
        vector<Cromosoma> padres;

        seleccion(poblacion, padres);
        casamiento(poblacion, padres);
        inversion(poblacion, padres);
        mutacion(poblacion, padres);
        regenerarPoblacion(poblacion);

        if ((k + 1) % 100 == 0) {
            cout << "Generacion " << (k + 1) << " - ";
            mostrarMejor(poblacion);
        }
    }

    imprimirSolucionFinal(poblacion[0]);
}

int main() {
    srand(time(NULL));

    cout << "=== PROGRAMACION EN VENTANAS DE TIEMPO - ALGORITMO GENETICO ===" << endl;
    cout << "Numero de tareas: " << NTAREAS << endl << endl;

    algoritmoGenetico();

    return 0;
}