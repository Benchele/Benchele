#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <ctime>
#include <climits>
using namespace std;

#define ITERACIONES 10000
#define ALFA 0.4
#define NTAREAS 10
#define TIEMPO_MAX 20  // Aumentado para mayor seguridad

struct Tarea {
    int id;
    int duracion;
    int inicio;      // si (inicio de ventana)
    int fin;         // ei (fin de ventana)
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

// Estructura para candidatos (ahora representa TAREAS, no posiciones)
struct Candidato {
    int indiceTarea;
    int ei;  // Fin de ventana (criterio greedy)
};

// Función de comparación: ordenar por ei ascendente
bool comparaEi(Candidato a, Candidato b) {
    return a.ei < b.ei;
}

// Verifica si un intervalo está disponible
bool estaDisponible(vector<bool> &ocupado, int inicio, int duracion) {
    if (inicio < 0 || inicio + duracion > TIEMPO_MAX) {
        return false;
    }

    for (int k = inicio; k < inicio + duracion; k++) {
        if (ocupado[k]) {
            return false;
        }
    }

    return true;
}

// Marca un intervalo como ocupado
void marcarOcupado(vector<bool> &ocupado, int inicio, int duracion) {
    for (int k = inicio; k < inicio + duracion; k++) {
        ocupado[k] = true;
    }
}

// Busca el primer tiempo disponible para programar una tarea
int buscarTiempoDisponible(vector<bool> &ocupado, Tarea &tarea) {
    for (int k = tarea.inicio; k <= tarea.fin - tarea.duracion + 1; k++) {
        if (estaDisponible(ocupado, k, tarea.duracion)) {
            return k;
        }
    }

    return -1;  // No se puede programar
}

// Busca cuántos candidatos están en el RCL
int buscarIndiceRCL(vector<Candidato> &candidatos, double umbralRCL) {
    int cont = 0;

    for (int k = 0; k < candidatos.size(); k++) {
        if (candidatos[k].ei <= umbralRCL) {
            cont++;
        }
    }

    return cont;
}

// Calcula la penalización total
int calcularPenalizacion(vector<int> &programadas) {
    int penalizacion = 0;

    for (int k = 0; k < NTAREAS; k++) {
        bool estaProgramada = false;

        for (int g = 0; g < programadas.size(); g++) {
            if (programadas[g] == k) {
                estaProgramada = true;
                break;
            }
        }

        if (!estaProgramada) {
            penalizacion += tareas[k].penalizacion;
        }
    }

    return penalizacion;
}

// GRASP Construcción (CORREGIDO)
void grasp_construccion(vector<int> &solucion, int &penalizacion) {
    vector<bool> ocupado(TIEMPO_MAX, false);
    vector<bool> tareaAsignada(NTAREAS, false);
    solucion.clear();

    while (true) {
        // Construir lista de candidatos (TAREAS que se pueden programar)
        vector<Candidato> candidatos;

        for (int k = 0; k < NTAREAS; k++) {
            if (tareaAsignada[k]) continue;

            // Verificar si existe al menos una posición válida
            int tiempo = buscarTiempoDisponible(ocupado, tareas[k]);

            if (tiempo != -1) {  // Si se puede programar
                Candidato c;
                c.indiceTarea = k;
                c.ei = tareas[k].fin;
                candidatos.push_back(c);
            }
        }

        if (candidatos.empty()) {
            break;  // No hay más tareas que programar
        }

        // Ordenar por criterio greedy (menor ei primero)
        sort(candidatos.begin(), candidatos.end(), comparaEi);

        // Calcular RCL
        int beta = candidatos[0].ei;  // Mejor (menor ei)
        int tau = candidatos[candidatos.size() - 1].ei;  // Peor
        double umbralRCL = beta + ALFA * (tau - beta);

        // Contar candidatos en RCL
        int indRCL = buscarIndiceRCL(candidatos, umbralRCL);

        // Seleccionar aleatoriamente del RCL
        int indiceAle = rand() % indRCL;
        int tareaSeleccionada = candidatos[indiceAle].indiceTarea;

        // Buscar el mejor tiempo para programar esta tarea
        int tiempoInicio = buscarTiempoDisponible(ocupado, tareas[tareaSeleccionada]);

        // Programar la tarea
        solucion.push_back(tareaSeleccionada);
        marcarOcupado(ocupado, tiempoInicio, tareas[tareaSeleccionada].duracion);
        tareaAsignada[tareaSeleccionada] = true;
    }

    penalizacion = calcularPenalizacion(solucion);
}

// Imprime la solución
void imprimirSolucion(vector<int> &solucion, int penalizacion) {
    cout << "Tareas programadas: ";
    for (int k = 0; k < solucion.size(); k++) {
        cout << "T" << (tareas[solucion[k]].id);
        if (k < solucion.size() - 1) cout << ", ";
    }
    cout << endl;

    cout << "Penalizacion total: " << penalizacion << endl;
}

// Algoritmo GRASP principal
void ventanasTiempoGRASP() {
    vector<int> mejorSolucion;
    int mejorPenalizacion = INT_MAX;


    for (int k = 0; k < ITERACIONES; k++) {
        vector<int> solucion;
        int penalizacion;

        grasp_construccion(solucion, penalizacion);

        if (penalizacion < mejorPenalizacion) {
            mejorPenalizacion = penalizacion;
            mejorSolucion = solucion;
        }

        if ((k + 1) % 1000 == 0) {
            cout << "Iteracion " << (k + 1) << " - Mejor penalizacion: "
                 << mejorPenalizacion << endl;
        }
    }

    cout << endl << "=== MEJOR SOLUCION ENCONTRADA ===" << endl;
    imprimirSolucion(mejorSolucion, mejorPenalizacion);

    // Mostrar tareas no programadas
    cout << endl << "Tareas no programadas: ";
    bool hayNoProgramadas = false;
    for (int k = 0; k < NTAREAS; k++) {
        bool estaProgramada = false;

        for (int g = 0; g < mejorSolucion.size(); g++) {
            if (mejorSolucion[g] == k) {
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

int main() {
    srand(time(NULL));

    cout << "=== PROGRAMACION EN VENTANAS DE TIEMPO - GRASP ===" << endl;
    cout << "Numero de tareas: " << NTAREAS << endl << endl;

    ventanasTiempoGRASP();

    return 0;
}