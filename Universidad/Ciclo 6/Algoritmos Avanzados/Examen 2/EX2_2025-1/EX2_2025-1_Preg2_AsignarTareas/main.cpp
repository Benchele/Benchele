#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <map>
#include <climits>
using namespace std;

// Parámetros del problema
#define NTAREAS 9
#define NAGENTES 3
#define PRESUPUESTO 90
#define ALPHA 0.3
#define NPOB 16
#define NPADRES 16
#define K_TORNEO 2
#define PCROSS 0.5
#define PMUT 0.3
#define NGEN 80
#define LCROM 9  // 9 tareas

typedef vector<int> Cromosoma;  // Vector de enteros [0-3]

// Matrices del problema
int costos[3][9] = {
    {43, 50, 38, 33, 39, 39, 59, 54, 45}, // Agente 1
    {21, 42, 23, 51, 28, 16, 52, 19, 36}, // Agente 2
    {25, 54, 17, 32, 20, 58, 40, 28, 48}  // Agente 3
};

int ganancias[3][9] = {
    {30, 23, 59, 9, 38, 30, 51, 16, 38},  // Agente 1
    {16, 12, 43, 47, 37, 5, 30, 19, 49},  // Agente 2
    {16, 29, 19, 41, 25, 48, 40, 29, 48}  // Agente 3
};

// Estructura para candidatos GRASP
struct Candidato {
    int tarea;
    int agente;
    double ratio;  // ganancia/costo
};

bool comparaRatio(Candidato a, Candidato b) {
    return a.ratio > b.ratio;  // Descendente (mayor ratio primero)
}

// ==================== FUNCIONES DE EVALUACIÓN ====================

// Verifica si cumple restricciones de presupuesto
bool cumplePresupuesto(Cromosoma &cromosoma) {
    vector<int> presupuestoUsado(NAGENTES, 0);

    for (int k = 0; k < NTAREAS; k++) {
        int agente = cromosoma[k];
        if (agente > 0 && agente <= NAGENTES) {
            presupuestoUsado[agente - 1] += costos[agente - 1][k];
        }
    }

    for (int g = 0; g < NAGENTES; g++) {
        if (presupuestoUsado[g] > PRESUPUESTO) {
            return false;
        }
    }

    return true;
}

// Calcula ganancia total
int calcularGanancia(Cromosoma &cromosoma) {
    int gananciaTotal = 0;

    for (int k = 0; k < NTAREAS; k++) {
        int agente = cromosoma[k];
        if (agente > 0 && agente <= NAGENTES) {
            gananciaTotal += ganancias[agente - 1][k];
        }
    }

    return gananciaTotal;
}

// Función de aptitud (fitness)
int calcularFitness(Cromosoma &cromosoma) {
    if (!cumplePresupuesto(cromosoma)) {
        return 0;  // Penalización: fitness = 0 si excede presupuesto
    }

    return calcularGanancia(cromosoma);
}

// ==================== GRASP CONSTRUCCIÓN ====================

int buscarIndiceCandidatos(vector<Candidato> candidatos, double umbralRCL) {
    int cont = 0;

    for (int k = 0; k < candidatos.size(); k++) {
        if (candidatos[k].ratio >= umbralRCL) {
            cont++;
        }
    }

    return cont;
}

Cromosoma grasp_construccion() {
    Cromosoma cromosoma(NTAREAS, 0);  // Inicializar con 0 (no asignado)
    vector<int> presupuestoUsado(NAGENTES, 0);
    vector<bool> tareaAsignada(NTAREAS, false);

    while (true) {
        // Construir lista de candidatos
        vector<Candidato> candidatos;

        for (int k = 0; k < NTAREAS; k++) {
            if (tareaAsignada[k]) continue;

            for (int g = 0; g < NAGENTES; g++) {
                int costo = costos[g][k];
                int ganancia = ganancias[g][k];

                // Verificar si cabe en el presupuesto
                if (presupuestoUsado[g] + costo <= PRESUPUESTO) {
                    Candidato c;
                    c.tarea = k;
                    c.agente = g + 1;  // Agentes van de 1 a 3
                    c.ratio = (costo > 0) ? (double)ganancia / costo : ganancia;
                    candidatos.push_back(c);
                }
            }
        }

        if (candidatos.empty()) {
            break;  // No hay más asignaciones posibles
        }

        // Ordenar por ratio descendente (mejor primero)
        sort(candidatos.begin(), candidatos.end(), comparaRatio);

        // Calcular RCL con ALPHA
        double beta = candidatos[0].ratio;  // Mejor ratio
        double tau = candidatos[candidatos.size() - 1].ratio;  // Peor ratio
        double umbralRCL = beta - ALPHA * (beta - tau);

        // Buscar cuántos candidatos están en el RCL
        int indRCL = buscarIndiceCandidatos(candidatos, umbralRCL);

        // Seleccionar aleatoriamente del RCL
        int indiceAle = rand() % indRCL;
        Candidato seleccionado = candidatos[indiceAle];

        // Asignar
        cromosoma[seleccionado.tarea] = seleccionado.agente;
        presupuestoUsado[seleccionado.agente - 1] += costos[seleccionado.agente - 1][seleccionado.tarea];
        tareaAsignada[seleccionado.tarea] = true;
    }

    return cromosoma;
}

// ==================== POBLACIÓN INICIAL ====================

vector<Cromosoma> generarPoblacionInicial() {
    vector<Cromosoma> poblacion;

    cout << "Generando poblacion inicial con GRASP..." << endl;

    for (int k = 0; k < NPOB; k++) {
        Cromosoma solucion = grasp_construccion();
        poblacion.push_back(solucion);
    }

    cout << "Poblacion generada: " << poblacion.size() << " individuos" << endl << endl;
    return poblacion;
}

// ==================== SELECCIÓN POR TORNEO ====================

void seleccionTorneo(vector<Cromosoma> &poblacion, vector<Cromosoma> &padres) {
    for (int k = 0; k < NPADRES; k++) {
        // Seleccionar K individuos aleatorios para el torneo
        vector<int> torneo;
        for (int t = 0; t < K_TORNEO; t++) {
            torneo.push_back(rand() % poblacion.size());
        }

        // Seleccionar al mejor del torneo
        int mejor = torneo[0];
        for (int g = 1; g < K_TORNEO; g++) {
            if (calcularFitness(poblacion[torneo[g]]) > calcularFitness(poblacion[mejor])) {
                mejor = torneo[g];
            }
        }

        padres.push_back(poblacion[mejor]);
    }
}

// ==================== CRUCE (UNIFORM CROSSOVER) ====================

void crearHijo(Cromosoma &padre, Cromosoma &madre, Cromosoma &hijo) {
    for (int k = 0; k < LCROM; k++) {
        double aleatorio = (double)rand() / RAND_MAX;

        // Con probabilidad PCROSS, heredar del padre, sino de la madre
        if (aleatorio < PCROSS) {
            hijo.push_back(padre[k]);
        } else {
            hijo.push_back(madre[k]);
        }
    }
}

void casamiento(vector<Cromosoma> &padres, vector<Cromosoma> &hijos) {
    // Emparejar padres sucesivamente: 0-1, 2-3, 4-5, etc.
    for (int k = 0; k < padres.size() - 1; k += 2) {
        Cromosoma hijo1, hijo2;
        crearHijo(padres[k], padres[k + 1], hijo1);
        crearHijo(padres[k + 1], padres[k], hijo2);  // Invertir orden para hijo2
        hijos.push_back(hijo1);
        hijos.push_back(hijo2);
    }
}

// ==================== MUTACIÓN ====================

void mutacion(Cromosoma &cromosoma) {
    double aleatorio = (double)rand() / RAND_MAX;

    if (aleatorio < PMUT) {
        // Escoger aleatoriamente una posición
        int pos = rand() % LCROM;
        int valorActual = cromosoma[pos];

        // Generar nuevo valor distinto (entre 0 y NAGENTES)
        int nuevoValor = rand() % (NAGENTES + 1);

        // Asegurar que sea diferente
        while (nuevoValor == valorActual) {
            nuevoValor = rand() % (NAGENTES + 1);
        }

        cromosoma[pos] = nuevoValor;
    }
}

void aplicarMutacion(vector<Cromosoma> &hijos) {
    for (int k = 0; k < hijos.size(); k++) {
        mutacion(hijos[k]);
    }
}

// ==================== REEMPLAZO ====================

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

void reemplazo(vector<Cromosoma> &poblacion, vector<Cromosoma> &hijos) {
    // Unir población actual con hijos
    for (int k = 0; k < hijos.size(); k++) {
        poblacion.push_back(hijos[k]);
    }

    // Eliminar duplicados
    eliminarDuplicados(poblacion);

    // Ordenar por fitness descendente (mejor primero)
    sort(poblacion.begin(), poblacion.end(),
        [](Cromosoma &k, Cromosoma &g) {
            return calcularFitness(k) > calcularFitness(g);
        }
    );

    // Seleccionar los NPOB mejores
    if (poblacion.size() > NPOB) {
        poblacion.erase(poblacion.begin() + NPOB, poblacion.end());
    }
}

// ==================== IMPRESIÓN ====================

void imprimirEstadisticasGeneracion(vector<Cromosoma> &poblacion, int gen) {
    int mejorGen = calcularFitness(poblacion[0]);
    cout << "Gen " << gen << " - Mejor ganancia: " << mejorGen << endl;
}

void imprimirSolucionFinal(Cromosoma cromosoma) {
    cout << endl << "=== MEJOR SOLUCION FINAL ===" << endl;

    cout << "Cromosoma: [";
    for (int k = 0; k < cromosoma.size(); k++) {
        cout << cromosoma[k];
        if (k < cromosoma.size() - 1) cout << " ";
    }
    cout << "]" << endl;

    // Mostrar asignaciones por agente
    vector<int> presupuestoUsado(NAGENTES, 0);
    vector<int> gananciaAgente(NAGENTES, 0);

    for (int k = 0; k < NAGENTES; k++) {
        cout << endl << "Agente " << (k + 1) << ": ";
        bool tieneAsignacion = false;

        for (int g = 0; g < NTAREAS; g++) {
            if (cromosoma[g] == k + 1) {
                cout << "T" << (g + 1) << " ";
                presupuestoUsado[k] += costos[k][g];
                gananciaAgente[k] += ganancias[k][g];
                tieneAsignacion = true;
            }
        }

        if (!tieneAsignacion) {
            cout << "(ninguna)";
        }

        cout << endl << "  Presupuesto usado: " << presupuestoUsado[k] << "/" << PRESUPUESTO;
        cout << endl << "  Ganancia: " << gananciaAgente[k];
    }

    // Tareas no asignadas
    cout << endl << endl << "Tareas no asignadas: ";
    bool hayNoAsignadas = false;
    for (int k = 0; k < NTAREAS; k++) {
        if (cromosoma[k] == 0) {
            cout << "T" << (k + 1) << " ";
            hayNoAsignadas = true;
        }
    }

    if (!hayNoAsignadas) {
        cout << "(ninguna)";
    }

    cout << endl << endl << "GANANCIA TOTAL: " << calcularFitness(cromosoma) << endl;
}

// ==================== ALGORITMO GENÉTICO ====================

void algoritmoGenetico() {
    vector<Cromosoma> poblacion;

    // Generar población inicial con GRASP
    poblacion = generarPoblacionInicial();

    cout << "Iniciando Algoritmo Genetico..." << endl;
    cout << "Representacion: ENTERA (" << LCROM << " genes)" << endl;
    cout << "Metodo de seleccion: Torneo (K=" << K_TORNEO << ")" << endl;
    cout << "Metodo de cruce: Uniform Crossover (PCROSS=" << PCROSS << ")" << endl;
    cout << "Tasa de mutacion: " << PMUT << endl << endl;

    int mejorGananciaGlobal = 0;
    Cromosoma mejorSolucionGlobal;

    for (int gen = 0; gen < NGEN; gen++) {
        // Selección por torneo
        vector<Cromosoma> padres;
        seleccionTorneo(poblacion, padres);

        // Cruce (uniform crossover)
        vector<Cromosoma> hijos;
        casamiento(padres, hijos);

        // Mutación
        aplicarMutacion(hijos);

        // Reemplazo
        reemplazo(poblacion, hijos);

        // Actualizar mejor solución global
        int mejorGen = calcularFitness(poblacion[0]);

        if (mejorGananciaGlobal < mejorGen) {
            mejorGananciaGlobal = mejorGen;
            mejorSolucionGlobal = poblacion[0];
        }

        // Imprimir generaciones pares
        if (gen % 2 == 0) {
            imprimirEstadisticasGeneracion(poblacion, gen);
        }
    }

    // Imprimir mejor solución final
    imprimirSolucionFinal(mejorSolucionGlobal);
}

// ==================== MAIN ====================

int main() {
    srand(time(NULL));

    cout << "=== ASIGNACION DE TAREAS CON PRESUPUESTO ===" << endl;
    cout << "Tareas: " << NTAREAS << endl;
    cout << "Agentes: " << NAGENTES << endl;
    cout << "Presupuesto por agente: " << PRESUPUESTO << endl;
    cout << "Poblacion: " << NPOB << endl;
    cout << "Generaciones: " << NGEN << endl << endl;

    algoritmoGenetico();

    return 0;
}