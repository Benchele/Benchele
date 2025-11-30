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
#define CRATIO 0.5
#define PMUT 0.3
#define NGEN 80
#define LCROM 18  // 9 tareas × 2 bits cada una
#define BITS_POR_TAREA 2

typedef vector<int> Cromosoma;  // Vector de bits (0s y 1s)

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

// ==================== CONVERSIONES BINARIO <-> ENTERO ====================

// Convierte un número entero a binario (2 bits)
vector<int> enteroABinario(int numero) {
    vector<int> binario;
    binario.push_back(numero & 1);        // Bit 0 (menos significativo)
    binario.push_back((numero >> 1) & 1); // Bit 1 (más significativo)
    return binario;
}

// Convierte un segmento binario (2 bits) a entero
int binarioAEntero(Cromosoma &cromosoma, int inicio) {
    if (inicio + 1 >= cromosoma.size()) return 0;

    int bit0 = cromosoma[inicio];
    int bit1 = cromosoma[inicio + 1];

    return bit0 + bit1 * 2;  // bit0 + bit1*2
}

// Decodifica un cromosoma binario completo a vector de asignaciones enteras
vector<int> decodificar(Cromosoma &cromosoma) {
    vector<int> asignaciones;

    for (int i = 0; i < NTAREAS; i++) {
        int inicio = i * BITS_POR_TAREA;
        int agente = binarioAEntero(cromosoma, inicio);
        asignaciones.push_back(agente);
    }

    return asignaciones;
}

// Codifica un vector de asignaciones enteras a cromosoma binario
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

// ==================== FUNCIONES DE EVALUACIÓN ====================

// Verifica si cumple restricciones de presupuesto
bool cumplePresupuesto(vector<int> &asignaciones) {
    vector<int> presupuestoUsado(NAGENTES, 0);

    for (int t = 0; t < NTAREAS; t++) {
        int agente = asignaciones[t];
        if (agente > 0 && agente <= NAGENTES) {
            presupuestoUsado[agente - 1] += costos[agente - 1][t];
        }
    }

    for (int a = 0; a < NAGENTES; a++) {
        if (presupuestoUsado[a] > PRESUPUESTO) {
            return false;
        }
    }

    return true;
}

// Calcula ganancia total
int calcularGanancia(vector<int> &asignaciones) {
    int gananciaTotal = 0;

    for (int t = 0; t < NTAREAS; t++) {
        int agente = asignaciones[t];
        if (agente > 0 && agente <= NAGENTES) {
            gananciaTotal += ganancias[agente - 1][t];
        }
    }

    return gananciaTotal;
}

// Función de aptitud (fitness)
int calcularFitness(Cromosoma &cromosoma) {
    vector<int> asignaciones = decodificar(cromosoma);

    if (!cumplePresupuesto(asignaciones)) {
        return 0;  // Penalización: fitness = 0 si excede presupuesto
    }

    return calcularGanancia(asignaciones);
}

// ==================== GRASP CONSTRUCCIÓN ====================

int buscarIndiceCandidatos(vector<Candidato> &candidatos, double umbralRCL) {
    int cont = 0;
    for (int k = 0; k < candidatos.size(); k++) {
        if (candidatos[k].ratio >= umbralRCL) {
            cont++;
        }
    }
    return cont;
}

Cromosoma grasp_construccion() {
    vector<int> asignaciones(NTAREAS, 0);  // Inicializar con 0 (no asignado)
    vector<int> presupuestoUsado(NAGENTES, 0);
    vector<bool> tareaAsignada(NTAREAS, false);

    while (true) {
        // Construir lista de candidatos
        vector<Candidato> candidatos;

        for (int t = 0; t < NTAREAS; t++) {
            if (tareaAsignada[t]) continue;

            for (int a = 0; a < NAGENTES; a++) {
                int costo = costos[a][t];
                int ganancia = ganancias[a][t];

                // Verificar si cabe en el presupuesto
                if (presupuestoUsado[a] + costo <= PRESUPUESTO) {
                    Candidato c;
                    c.tarea = t;
                    c.agente = a + 1;  // Agentes van de 1 a 3
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
        asignaciones[seleccionado.tarea] = seleccionado.agente;
        presupuestoUsado[seleccionado.agente - 1] += costos[seleccionado.agente - 1][seleccionado.tarea];
        tareaAsignada[seleccionado.tarea] = true;
    }

    // Codificar a binario
    return codificar(asignaciones);
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
        for (int t = 1; t < K_TORNEO; t++) {
            if (calcularFitness(poblacion[torneo[t]]) > calcularFitness(poblacion[mejor])) {
                mejor = torneo[t];
            }
        }

        padres.push_back(poblacion[mejor]);
    }
}

// ==================== CRUCE (ONE-POINT CROSSOVER) ====================

void crearHijo(Cromosoma &padre1, Cromosoma &padre2, Cromosoma &hijo) {
    int puntoCorte = LCROM * CRATIO;  // CRATIO = 0.5 → corta en el bit 9

    for (int k = 0; k < LCROM; k++) {
        if (k < puntoCorte) {
            hijo.push_back(padre1[k]);
        } else {
            hijo.push_back(padre2[k]);
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

// ==================== MUTACIÓN (BIT FLIP) ====================

void mutacion(Cromosoma &cromosoma) {
    double aleatorio = (double)rand() / RAND_MAX;

    if (aleatorio < PMUT) {
        // Mutar PMUT * LCROM bits
        int numBitsMutar = round(PMUT * LCROM);

        for (int k = 0; k < numBitsMutar; k++) {
            int pos = rand() % LCROM;
            cromosoma[pos] = 1 - cromosoma[pos];  // Flip: 0→1, 1→0
        }
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
        [](Cromosoma &a, Cromosoma &b) {
            return calcularFitness(a) > calcularFitness(b);
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

void imprimirSolucionFinal(Cromosoma &cromosoma) {
    vector<int> asignaciones = decodificar(cromosoma);

    cout << endl << "=== MEJOR SOLUCION FINAL ===" << endl;

    // Imprimir cromosoma binario
    cout << "Cromosoma binario (" << LCROM << " bits): ";
    for (int k = 0; k < cromosoma.size(); k++) {
        cout << cromosoma[k];
        // Separador cada 2 bits (cada tarea)
        if ((k + 1) % BITS_POR_TAREA == 0 && k < cromosoma.size() - 1) {
            cout << "|";
        }
    }
    cout << endl;

    // Imprimir cromosoma decodificado
    cout << "Cromosoma (entero): [";
    for (int k = 0; k < asignaciones.size(); k++) {
        cout << asignaciones[k];
        if (k < asignaciones.size() - 1) cout << " ";
    }
    cout << "]" << endl;

    // Mostrar asignaciones por agente
    vector<int> presupuestoUsado(NAGENTES, 0);
    vector<int> gananciaAgente(NAGENTES, 0);

    for (int a = 0; a < NAGENTES; a++) {
        cout << endl << "Agente " << (a + 1) << ": ";
        bool tieneAsignacion = false;

        for (int t = 0; t < NTAREAS; t++) {
            if (asignaciones[t] == a + 1) {
                cout << "T" << (t + 1) << " ";
                presupuestoUsado[a] += costos[a][t];
                gananciaAgente[a] += ganancias[a][t];
                tieneAsignacion = true;
            }
        }

        if (!tieneAsignacion) {
            cout << "(ninguna)";
        }

        cout << endl << "  Presupuesto usado: " << presupuestoUsado[a] << "/" << PRESUPUESTO;
        cout << endl << "  Ganancia: " << gananciaAgente[a];
    }

    // Tareas no asignadas
    cout << endl << endl << "Tareas no asignadas: ";
    bool hayNoAsignadas = false;
    for (int t = 0; t < NTAREAS; t++) {
        if (asignaciones[t] == 0) {
            cout << "T" << (t + 1) << " ";
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
    cout << "Representacion: BINARIA (" << LCROM << " bits = " << NTAREAS << " tareas × " << BITS_POR_TAREA << " bits)" << endl;
    cout << "Metodo de seleccion: Torneo (K=" << K_TORNEO << ")" << endl;
    cout << "Metodo de cruce: One-Point Crossover (CRATIO=" << CRATIO << ")" << endl;
    cout << "Tasa de mutacion: " << PMUT << " (" << (int)(PMUT * LCROM) << " bits)" << endl << endl;

    int mejorGananciaGlobal = 0;
    Cromosoma mejorSolucionGlobal;

    for (int gen = 0; gen < NGEN; gen++) {
        // Selección por torneo
        vector<Cromosoma> padres;
        seleccionTorneo(poblacion, padres);

        // Cruce (one-point crossover)
        vector<Cromosoma> hijos;
        casamiento(padres, hijos);

        // Mutación (bit flip)
        aplicarMutacion(hijos);

        // Reemplazo
        reemplazo(poblacion, hijos);

        // Actualizar mejor solución global
        int mejorGen = calcularFitness(poblacion[0]);
        if (mejorGen > mejorGananciaGlobal) {
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

    cout << "=== ASIGNACION DE TAREAS CON PRESUPUESTO (BINARIO) ===" << endl;
    cout << "Tareas: " << NTAREAS << endl;
    cout << "Agentes: " << NAGENTES << endl;
    cout << "Presupuesto por agente: " << PRESUPUESTO << endl;
    cout << "Poblacion: " << NPOB << endl;
    cout << "Generaciones: " << NGEN << endl << endl;

    algoritmoGenetico();

    return 0;
}