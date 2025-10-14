#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

// Estrategia: Algoritmo Voraz (Greedy)
// En cada paso, asignamos la orden a la línea de producción con menor carga acumulada

struct Orden {
    int id;
    int cantidad;
};

struct Linea {
    int id;
    double cargaTotal;
    vector<int> ordenesAsignadas;
};

////Impresion
bool comparaId(struct Linea k, struct Linea g) {
    return k.id < g.id; //Ascendente (Menor a mayor)
}

//Mostrar resultados
void imprimir(struct Linea *lineas, struct Orden *ordenes, int M) {
    cout << "Línea, Ordenes asignadas, Carga total (minutos)" << endl;
    double makespan = 0;
    sort(lineas, lineas + M, comparaId);

    for (int i = 0; i < M; i++) {
        cout << "Línea " << lineas[i].id << ", ";

        // Imprimir órdenes asignadas
        for (int j = 0; j < lineas[i].ordenesAsignadas.size(); j++) {
            int ordenId = lineas[i].ordenesAsignadas[j];
            int cantidad = ordenes[ordenId - 1].cantidad;
            cout << "Orden" << ordenId << "(" << cantidad << ")";
            if (j < lineas[i].ordenesAsignadas.size() - 1) {
                cout << ", ";
            }
        }

        cout << ", " << fixed << setprecision(1) << lineas[i].cargaTotal << endl;

        // El makespan es la máxima carga entre todas las líneas
        if (lineas[i].cargaTotal > makespan) {
            makespan = lineas[i].cargaTotal;
        }
    }

    cout << "\nTiempo acumulado de trabajo = " << fixed << setprecision(0) << makespan << " minutos (makespan)" << endl;
}

///////Algoritmo Voraz

bool compara(struct Linea k, struct Linea g) {
    return k.cargaTotal < g.cargaTotal; //Ascendente (Menor a mayor)
}

int procesarOrdenes(struct Orden *ordenes, int N, struct Linea *lineas, int M, double tiempoPorBotella) {
    //N = numero de ordenes | M = numero de lineas

    // Algoritmo Voraz: para cada orden, asignarla a la línea con menor carga

    for (int k = 0; k < N; k++) {
        //Ordenamos para que la linea que tenga menos carga esté al inicio
        sort(lineas, lineas + M, compara);

        double cargaOrden = ordenes[k].cantidad * tiempoPorBotella; // Calcular carga de esta orden

        // Asignar la orden a esa línea
        lineas[0].cargaTotal += cargaOrden;
        lineas[0].ordenesAsignadas.push_back(ordenes[k].id);
    }

    imprimir(lineas, ordenes, M);

    return 1;
}

int main() {
    // Datos: 5 líneas de producción, 20 órdenes
    int M = 5;  // Número de líneas
    int N = 20; // Número de órdenes

    // Tiempos de máquinas (en minutos por botella)
    double tiempoLlenadora = 2.0;
    double tiempoGasificadora = 1.0;
    double tiempoTapadora = 1.5;
    double tiempoEtiquetadora = 1.5;

    // Tiempo total por botella = suma de todos los procesos
    double tiempoPorBotella = tiempoLlenadora + tiempoGasificadora + tiempoTapadora + tiempoEtiquetadora;
    // tiempoPorBotella = 2 + 1 + 1.5 + 1.5 = 6 minutos por botella

    // Array de órdenes con sus cantidades
    Orden ordenes[N] = {
        {1, 103}, {2, 58}, {3, 88}, {4, 126}, {5, 195},
        {6, 90}, {7, 54}, {8, 195}, {9, 124}, {10, 113},
        {11, 193}, {12, 55}, {13, 97}, {14, 97}, {15, 169},
        {16, 50}, {17, 167}, {18, 74}, {19, 79}, {20, 109}
    };

    // Inicializar las 5 líneas de producción
    struct Linea lineas[M];
    for (int i = 0; i < M; i++) {
        lineas[i].id = i + 1;
        lineas[i].cargaTotal = 0.0;
    }

    procesarOrdenes(ordenes, N, lineas, M, tiempoPorBotella);

    return 0;
}