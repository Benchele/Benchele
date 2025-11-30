#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <map>
#include <climits>
#include <cstring>
using namespace std;

// ==================== PARÁMETROS DEL PROBLEMA ====================
#define NEXAMENES 5
#define NESTUDIANTES 4
#define NSLOTS 4
#define BITS_POR_EXAMEN 2  // log2(4) = 2 bits

// ==================== PARÁMETROS GRASP ====================
#define ALPHA 0.25
#define ITERACIONES_GRASP 1000

// ==================== PARÁMETROS ALGORITMO GENÉTICO ====================
#define POBLACION_INICIAL 20
#define ITERACIONES_AG 1000
#define TASA_SELECCION 0.5
#define PCASAMIENTO 0.5
#define TASA_MUTACION 0.5
#define LCROM 10  // 5 exámenes × 2 bits = 10 bits

typedef vector<int> Cromosoma;  // Cromosoma binario (bits)

// ==================== DATOS DE ENTRADA ====================

// Matriz de inscripción R[estudiante][examen]
int R[NESTUDIANTES][NEXAMENES] = {
    {1, 1, 0, 0, 0},  // Estudiante 0: e0, e1, e3
    {0, 1, 1, 0, 0},  // Estudiante 1: e1, e2, e4
    {0, 0, 1, 1, 0},  // Estudiante 2: e0, e2, e3
    {1, 0, 0, 1, 1}   // Estudiante 3: e2, e3, e4
};

// Matriz de conflictos (calculada a partir de R)
int conflictos[NEXAMENES][NEXAMENES];

// ==================== FUNCIONES AUXILIARES ====================

// Calcula la matriz de conflictos a partir de la matriz R
void calcularConflictos() {
    for (int k = 0; k < NEXAMENES; k++) {
        for (int g = 0; g < NEXAMENES; g++) {
            if (k == g) {
                conflictos[k][g] = 0;
                continue;
            }

            conflictos[k][g] = 0;
            for (int b = 0; b < NESTUDIANTES; b++) {
                if (R[b][k] == 1 && R[b][g] == 1) {
                    conflictos[k][g] = 1;
                    break;
                }
            }
        }
    }
}

// Cuenta conflictos entre exámenes con el mismo slot
int contarConflictos(vector<int> &asignaciones) {
    int totalConflictos = 0;

    for (int k = 0; k < NEXAMENES; k++) {
        for (int g = k + 1; g < NEXAMENES; g++) {
            // Si tienen el mismo slot y hay conflicto
            if (asignaciones[k] == asignaciones[g] && conflictos[k][g] == 1) {
                totalConflictos++;
            }
        }
    }

    return totalConflictos;
}

// ==================== CONVERSIONES BINARIO <-> ENTERO ====================

// Convierte entero a binario (2 bits)
vector<int> enteroABinario(int numero) {
    vector<int> binario;
    binario.push_back(numero & 1);        // Bit 0
    binario.push_back((numero >> 1) & 1); // Bit 1
    return binario;
}

// Convierte segmento binario a entero
int binarioAEntero(Cromosoma &cromosoma, int inicio) {
    if (inicio + 1 >= cromosoma.size()) return 0;

    int bit0 = cromosoma[inicio];
    int bit1 = cromosoma[inicio + 1];

    return bit0 + bit1 * 2;
}

// Decodifica cromosoma binario completo
vector<int> decodificar(Cromosoma &cromosoma) {
    vector<int> asignaciones;

    for (int k = 0; k < NEXAMENES; k++) {
        int inicio = k * BITS_POR_EXAMEN;
        int slot = binarioAEntero(cromosoma, inicio);
        asignaciones.push_back(slot);
    }

    return asignaciones;
}

// Codifica vector de enteros a cromosoma binario
Cromosoma codificar(vector<int> &asignaciones) {
    Cromosoma cromosoma;

    for (int i = 0; i < asignaciones.size(); i++) {
        vector<int> binario = enteroABinario(asignaciones[i]);

        for (int bit : binario) {
            cromosoma.push_back(bit);
        }
    }

    return cromosoma;
}

// ==================== FUNCIÓN DE FITNESS ====================

int calcularFitness(Cromosoma &cromosoma) {
    vector<int> asignaciones = decodificar(cromosoma);
    return contarConflictos(asignaciones);  // Minimizar conflictos
}

// ==================== GRASP CONSTRUCCIÓN ====================

struct Candidato {
    int examen;
    int slot;
    int conflictosResultantes;
};

bool comparaConflictos(Candidato a, Candidato b) {
    return a.conflictosResultantes < b.conflictosResultantes;  // Ascendente (menos conflictos primero)
}

int buscarIndiceRCL(vector<Candidato> &candidatos, int umbralRCL) {
    int cont = 0;
    for (int k = 0; k < candidatos.size(); k++) {
        if (candidatos[k].conflictosResultantes <= umbralRCL) {
            cont++;
        }
    }
    return cont;
}

Cromosoma grasp_construccion() {
    vector<int> asignaciones(NEXAMENES, -1);  // -1 = no asignado
    vector<bool> examenAsignado(NEXAMENES, false);

    // Asignar cada examen a un slot
    for (int numAsignados = 0; numAsignados < NEXAMENES; numAsignados++) {
        // Construir lista de candidatos
        vector<Candidato> candidatos;

        for (int k = 0; k < NEXAMENES; k++) {
            if (examenAsignado[k]) continue;

            // Probar cada slot para este examen
            for (int g = 0; g < NSLOTS; g++) {
                // Simular asignación
                asignaciones[k] = g;

                // Contar conflictos resultantes
                int conflictosNuevos = 0;
                for (int otro = 0; otro < NEXAMENES; otro++) {
                    if (examenAsignado[otro] && asignaciones[otro] == g) {
                        if (conflictos[k][otro] == 1) {
                            conflictosNuevos++;
                        }
                    }
                }

                Candidato c;
                c.examen = k;
                c.slot = g;
                c.conflictosResultantes = conflictosNuevos;
                candidatos.push_back(c);

                // Deshacer simulación
                asignaciones[k] = -1;
            }
        }

        if (candidatos.empty()) break;

        // Ordenar por conflictos (greedy: menos conflictos primero)
        sort(candidatos.begin(), candidatos.end(), comparaConflictos);

        // Calcular RCL con ALPHA
        int beta = candidatos[0].conflictosResultantes;  // Mejor (menos conflictos)
        int tau = candidatos[candidatos.size() - 1].conflictosResultantes;  // Peor
        int umbralRCL = beta + ALPHA * (tau - beta);

        // Buscar cuántos candidatos están en el RCL
        int indRCL = buscarIndiceRCL(candidatos, umbralRCL);

        // Seleccionar aleatoriamente del RCL
        int indiceAle = rand() % indRCL;
        Candidato seleccionado = candidatos[indiceAle];

        // Asignar
        asignaciones[seleccionado.examen] = seleccionado.slot;
        examenAsignado[seleccionado.examen] = true;
    }

    // Codificar a binario
    return codificar(asignaciones);
}

// ==================== POBLACIÓN INICIAL ====================

vector<Cromosoma> generarPoblacionInicial() {
    vector<Cromosoma> poblacion;

    cout << "Generando poblacion inicial con GRASP..." << endl;

    for (int k = 0; k < POBLACION_INICIAL; k++) {
        Cromosoma mejorSolu;
        int mejorFitness = INT_MAX;

        // Ejecutar GRASP múltiples veces por individuo
        for (int iter = 0; iter < ITERACIONES_GRASP / POBLACION_INICIAL; iter++) {
            Cromosoma solucion = grasp_construccion();
            int fitness = calcularFitness(solucion);

            if (fitness < mejorFitness) {
                mejorFitness = fitness;
                mejorSolu = solucion;
            }
        }

        poblacion.push_back(mejorSolu);

        if ((k + 1) % 5 == 0) {
            cout << "  Generados " << (k + 1) << "/" << POBLACION_INICIAL << " individuos" << endl;
        }
    }

    return poblacion;
}

// ==================== OPERADORES GENÉTICOS ====================

void eliminarDuplicados(vector<Cromosoma> &poblacion) {
    map<string, Cromosoma> unicos;

    for (int k = 0; k < poblacion.size(); k++) {
        string key = "";
        for (int g = 0; g < poblacion[k].size(); g++) {
            key += to_string(poblacion[k][g]);
        }
        unicos[key] = poblacion[k];
    }

    poblacion.clear();
    for (auto par : unicos) {
        poblacion.push_back(par.second);
    }
}

void calculoSuperviviencia(vector<Cromosoma> &poblacion, vector<int> &superviviencia) {
    int sumaFitnessInv = 0;
    int maxFitness = 0;

    // Encontrar el peor fitness (para inversión)
    for (int k = 0; k < poblacion.size(); k++) {
        int fit = calcularFitness(poblacion[k]);
        if (fit > maxFitness) {
            maxFitness = fit;
        }
    }

    // Calcular fitness inverso (minimización → maximización)
    vector<int> fitnessInverso;
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
        superviviencia.push_back(superFit);
    }
}

void cargarRuleta(vector<int> &superviviencia, int *ruleta) {
    int cont = 0;

    for (int k = 0; k < superviviencia.size(); k++) {
        for (int g = 0; g < superviviencia[k]; g++) {
            if (cont < 100) {
                ruleta[cont++] = k;
            }
        }
    }

    for (int k = cont; k < 100; k++) {
        ruleta[k] = -1;
    }
}

void seleccion(vector<Cromosoma> &poblacion, vector<Cromosoma> &padres) {
    int ruleta[100];

    for (int k = 0; k < 100; k++) ruleta[k] = -1;

    vector<int> superviviencia;

    calculoSuperviviencia(poblacion, superviviencia);
    cargarRuleta(superviviencia, ruleta);

    int numeroPadres = round(poblacion.size() * TASA_SELECCION);

    for (int k = 0; k < numeroPadres; k++) {
        int ticket = rand() % 100;
        int individuoSeleccionado = ruleta[ticket];
        if (individuoSeleccionado != -1) {
            padres.push_back(poblacion[individuoSeleccionado]);
        }
    }
}

// Casamiento: tasa del 50% (mitad de bloques de cada padre)
void crearHijo(Cromosoma &padre, Cromosoma &madre, Cromosoma &hijo) {
    int numBloques = NEXAMENES;
    int bloqueCorte = numBloques * PCASAMIENTO;  // Mitad de los bloques

    for (int bloque = 0; bloque < numBloques; bloque++) {
        int inicio = bloque * BITS_POR_EXAMEN;

        for (int bit = 0; bit < BITS_POR_EXAMEN; bit++) {
            if (bloque < bloqueCorte) {
                hijo.push_back(padre[inicio + bit]);
            } else {
                hijo.push_back(madre[inicio + bit]);
            }
        }
    }
}

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

// Mutación: cambiar un solo bit de un solo bloque
void mutacion(vector<Cromosoma> &poblacion, vector<Cromosoma> &padres) {
    for (int k = 0; k < padres.size(); k++) {
        double aleatorio = (double)rand() / RAND_MAX;

        if (aleatorio < TASA_MUTACION) {
            Cromosoma mutante = padres[k];

            // Elegir un bloque aleatorio (examen)
            int bloqueAleatorio = rand() % NEXAMENES;
            int inicio = bloqueAleatorio * BITS_POR_EXAMEN;

            // Elegir un bit aleatorio dentro del bloque
            int bitAleatorio = rand() % BITS_POR_EXAMEN;
            int posicion = inicio + bitAleatorio;

            // Flip del bit
            mutante[posicion] = 1 - mutante[posicion];

            poblacion.push_back(mutante);
        }
    }
}

int nAux;

void regenerarPoblacion(vector<Cromosoma> &poblacion) {
    eliminarDuplicados(poblacion);

    // Ordenar por fitness (menor es mejor)
    sort(poblacion.begin(), poblacion.end(),
        [](Cromosoma &a, Cromosoma &b) {
            return calcularFitness(a) < calcularFitness(b);
        }
    );

    if (POBLACION_INICIAL < poblacion.size()) {
        poblacion.erase(poblacion.begin() + POBLACION_INICIAL, poblacion.end());
    }
}

void muestraMejor(vector<Cromosoma> &poblacion) {
    int mejor = 0;

    for (int k = 0; k < poblacion.size(); k++) {
        if (calcularFitness(poblacion[k]) < calcularFitness(poblacion[mejor])) {
            mejor = k;
        }
    }

    cout << "Mejor fitness (conflictos): " << calcularFitness(poblacion[mejor]) << endl;
}

void imprimirSolucionFinal(Cromosoma &cromosoma) {
    vector<int> asignaciones = decodificar(cromosoma);

    cout << endl << "=== MEJOR SOLUCION FINAL ===" << endl;

    // Imprimir cromosoma binario
    cout << "Cromosoma binario: ";
    for (int k = 0; k < cromosoma.size(); k++) {
        cout << cromosoma[k];
        if ((k + 1) % BITS_POR_EXAMEN == 0 && k < cromosoma.size() - 1) {
            cout << "|";
        }
    }
    cout << endl;

    // Imprimir asignaciones
    cout << "Asignaciones (examen -> slot):" << endl;
    for (int k = 0; k < asignaciones.size(); k++) {
        cout << "  e" << k << " -> Slot " << asignaciones[k] << endl;
    }

    // Mostrar distribución por slots
    cout << endl << "Distribucion por slots:" << endl;
    for (int s = 0; s < NSLOTS; s++) {
        cout << "  Slot " << s << ": ";
        bool hayExamenes = false;

        for (int e = 0; e < NEXAMENES; e++) {
            if (asignaciones[e] == s) {
                cout << "e" << e << " ";
                hayExamenes = true;
            }
        }

        if (!hayExamenes) {
            cout << "(vacio)";
        }
        cout << endl;
    }

    cout << endl << "Total de conflictos: " << calcularFitness(cromosoma) << endl;
}

// ==================== ALGORITMO GENÉTICO ====================

void algoritmoGenetico() {
    vector<Cromosoma> poblacion;

    poblacion = generarPoblacionInicial();

    eliminarDuplicados(poblacion);

    cout << endl << "Iniciando Algoritmo Genetico..." << endl;
    cout << "Poblacion inicial: " << poblacion.size() << " individuos" << endl << endl;

    for (int k = 0; k < ITERACIONES_AG; k++) {
        vector<Cromosoma> padres;

        seleccion(poblacion, padres);
        casamiento(poblacion, padres);
        mutacion(poblacion, padres);
        regenerarPoblacion(poblacion);

        if ((k + 1) % 100 == 0) {
            cout << "Generacion " << (k + 1) << " - ";
            muestraMejor(poblacion);
        }
    }

    imprimirSolucionFinal(poblacion[0]);
}

// ==================== IMPRESIÓN DE DATOS ====================

void imprimirDatos() {
    // Mostrar matriz de conflictos
    cout << endl << "Matriz de conflictos:" << endl;
    cout << "   ";
    for (int j = 0; j < NEXAMENES; j++) {
        cout << "e" << j << " ";
    }
    cout << endl;

    for (int i = 0; i < NEXAMENES; i++) {
        cout << "e" << i << " ";
        for (int j = 0; j < NEXAMENES; j++) {
            cout << " " << conflictos[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// ==================== MAIN ====================

int main() {
    srand(time(NULL));

    // Calcular matriz de conflictos
    calcularConflictos();

    cout << "=== EXAM TIME TABLING PROBLEM ===" << endl;
    cout << "Examenes: " << NEXAMENES << endl;
    cout << "Estudiantes: " << NESTUDIANTES << endl;
    cout << "Slots disponibles: " << NSLOTS << endl;
    cout << "Bits por examen: " << BITS_POR_EXAMEN << endl << endl;

    //imprimirDatos();

    algoritmoGenetico();

    return 0;
}