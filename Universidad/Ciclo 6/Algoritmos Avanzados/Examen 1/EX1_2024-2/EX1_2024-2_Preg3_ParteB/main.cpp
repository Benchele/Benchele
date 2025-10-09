#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

struct Tarea {
    char id;
    int horaMaxima;
    int ganancia;
};

struct Solucion {
    char idTarea;
    int horaAsignada;
};

bool compara(struct Tarea k, struct Tarea g) {
    return k.ganancia > g.ganancia; //Descendente (Mayor a menor)
}

//Para la impresion
bool comparaHoraAsignada(struct Solucion k, struct Solucion g) {
    return k.horaAsignada < g.horaAsignada; //Ascendente (Menor a mayor)
}

int elegirTareas(struct Tarea *tareas, int n) {
    //Ordenar por ganancia descendentemente
    sort(tareas, tareas + n, compara);

    // Encontrar la hora máxima entre todas las tareas
    // Esto determina cuántas horas necesitamos en nuestro horario
    int maxHora = 0;
    for (int i = 0; i < n; i++) {
        if (tareas[i].horaMaxima > maxHora) {
            maxHora = tareas[i].horaMaxima;
        }
    }

    // Vector booleano para marcar qué horas están ocupadas
    // horas[1] = true significa que la hora 1 está ocupada
    // Índice 0 no se usa (las horas empiezan en 1)
    vector<bool> horas(maxHora + 1, false);

    //Vector solucion
    vector<struct Solucion> tareasElegidas;
    int ganancia = 0;

    //Por cada tarea
    for (int k = 0; k < n; k++) {
        //Elegir la hora mas cercana a la hora maxima
        for (int g = tareas[k].horaMaxima; g >= 1; g--) {
            if (!horas[g]) { //Si no esta ocupada
                tareasElegidas.push_back({tareas[k].id, g});
                horas[g] = true; //Marcar hora como ocupada
                ganancia += tareas[k].ganancia;
                break; //Ya asignamos esta tarea, pasar a la siguiente
            }
        }
        // Si no encontramos ninguna hora libre (no entra al if), la tarea se descarta automáticamente
    }

    cout << "Se consideran las tareas: ";
    sort(tareasElegidas.begin(), tareasElegidas.end(), comparaHoraAsignada);
    for (int k = 0; k < tareasElegidas.size(); k++) {
        if (k != 0)cout << ", ";
        cout << tareasElegidas[k].idTarea << " ";
    }
    cout << endl;
    cout << "Con una ganancia de: " << ganancia << endl;

    return ganancia;
}

int main() {
    struct Tarea tareas[] = {
        {'A', 2, 100},
        {'B', 1, 19},
        {'C', 2, 27},
        {'D', 1, 25},
        {'E', 3, 15}
    };

    // struct Tarea tareas[] = {
    //     {'A', 4, 20},
    //     {'B', 1, 10},
    //     {'C', 2, 40},
    //     {'D', 2, 30}
    // };

    int n = sizeof(tareas) / sizeof(tareas[0]);

    elegirTareas(tareas, n);

    return 0;
}