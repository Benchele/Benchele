#include <iostream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
#include <climits>
using namespace std;

#define ITERACIONES 100
#define NUM_INDIVIDUOS 20
#define TSELECCION 0.5
#define PCASAMIENTO 0.8
#define TMUTACION 0.1
#define N 5 // 5 empleados y 5 tareas

// Matriz de ganancias [empleado][tarea]
// Ejemplo: ganancia[i][j] = ganancia de asignar tarea j al empleado i
int ganancia[N][N] = {
    {9, 2, 7, 8, 6},
    {6, 4, 3, 7, 8},
    {5, 8, 1, 8, 3},
    {7, 6, 9, 4, 2},
    {8, 6, 7, 5, 9}
};

////////////////////////////////////////////////////
// Calcular fitness (ganancia total)
// Estrategia: Sumar ganancia[empleado][tarea_asignada] para cada empleado
int calculaFitness(vector<int> cromosoma) {
    int gananciaTotal = 0;

    for (int empleado = 0; empleado < N; empleado++) {
        int tarea = cromosoma[empleado];
        gananciaTotal += ganancia[empleado][tarea];
    }

    return gananciaTotal;
}

// Verificar si es una permutación válida
// Estrategia: Verificar que cada tarea 0-4 aparezca exactamente una vez
bool esPermutacionValida(vector<int> cromosoma) {
    vector<bool> usado(N, false);

    for (int i = 0; i < N; i++) {
        int tarea = cromosoma[i];
        if (tarea < 0 || tarea >= N || usado[tarea]) {
            return false;
        }
        usado[tarea] = true;
    }

    return true;
}

// Detectar aberraciones
// Estrategia: Verificar que sea permutación válida
bool esAberracion(vector<int> cromosoma) {
    return !esPermutacionValida(cromosoma);
}

// Generar individuo aleatorio
// Estrategia: Crear permutación aleatoria de tareas 0-4
vector<int> generarIndividuoAleatorio() {
    vector<int> individuo;

    // Crear permutación de tareas 0 a N-1
    for (int i = 0; i < N; i++) {
        individuo.push_back(i);
    }

    // Mezclar aleatoriamente
    random_shuffle(individuo.begin(), individuo.end());

    return individuo;
}

// Generar población inicial
// Estrategia: Crear NUM_INDIVIDUOS permutaciones aleatorias válidas
void generarPoblacion(vector<vector<int>> &poblacion) {
    srand(time(NULL));

    int cont = 0;
    while (cont < NUM_INDIVIDUOS) {
        vector<int> individuo = generarIndividuoAleatorio();

        // Verificar que no sea aberración
        if (!esAberracion(individuo)) {
            poblacion.push_back(individuo);
            cont++;
        }
    }
}

// Eliminar individuos clones
// Estrategia: Comparar cromosomas y eliminar duplicados
void matarClones(vector<vector<int>> &poblacion) {
    vector<vector<int>> unicos;

    for (int i = 0; i < poblacion.size(); i++) {
        bool esClon = false;

        for (int j = 0; j < unicos.size(); j++) {
            if (poblacion[i] == unicos[j]) {
                esClon = true;
                break;
            }
        }

        if (!esClon) {
            unicos.push_back(poblacion[i]);
        }
    }

    poblacion = unicos;
}

// Calcular probabilidades para la ruleta (MAXIMIZAR ganancia)
// Estrategia: Mayor fitness = mayor probabilidad de selección
void calculaSupervivencia(vector<vector<int>> poblacion, vector<int> &supervivencia) {
    int sumaFitness = 0;

    // Calcular suma total de fitness
    for (int i = 0; i < poblacion.size(); i++) {
        sumaFitness += calculaFitness(poblacion[i]);
    }

    // Evitar división por cero
    if (sumaFitness == 0) {
        int porcentajeIgual = 100 / poblacion.size();
        for (int i = 0; i < poblacion.size(); i++) {
            supervivencia.push_back(porcentajeIgual);
        }
        return;
    }

    // Calcular porcentaje de supervivencia
    for (int i = 0; i < poblacion.size(); i++) {
        int porcentaje = round(100.0 * calculaFitness(poblacion[i]) / sumaFitness);
        supervivencia.push_back(porcentaje);
    }
}

// Cargar ruleta con índices de individuos
void cargarRuleta(vector<int> supervivencia, int *ruleta) {
    int indiceRuleta = 0;

    for (int i = 0; i < supervivencia.size(); i++) {
        for (int j = 0; j < supervivencia[i]; j++) {
            if (indiceRuleta < 100) {
                ruleta[indiceRuleta++] = i;
            }
        }
    }

    // Llenar espacios vacíos si la suma no es exactamente 100
    while (indiceRuleta < 100) {
        ruleta[indiceRuleta++] = 0;
    }
}

// Selección de padres mediante ruleta
// Estrategia: Seleccionar padres proporcionalmente a su fitness
void seleccion(vector<vector<int>> poblacion, vector<vector<int>> &padres) {
    int ruleta[100];
    for (int i = 0; i < 100; i++) ruleta[i] = -1;

    vector<int> supervivencia;
    calculaSupervivencia(poblacion, supervivencia);
    cargarRuleta(supervivencia, ruleta);

    int numeroPadres = max(2, (int)round(poblacion.size() * TSELECCION));

    for (int i = 0; i < numeroPadres; i++) {
        int ticket = rand() % 100;
        int individuoSeleccionado = ruleta[ticket];
        if (individuoSeleccionado != -1 && individuoSeleccionado < poblacion.size()) {
            padres.push_back(poblacion[individuoSeleccionado]);
        }
    }
}

// Operador de casamiento: PMX (Partially Mapped Crossover)
// Estrategia: Cruce que preserva la permutación válida
void casamiento(vector<vector<int>> &poblacion, vector<vector<int>> padres) {
    for (int i = 0; i < padres.size(); i++) {
        for (int j = i + 1; j < padres.size(); j++) {
            // Verificar probabilidad de cruce
            if ((rand() % 100) < (PCASAMIENTO * 100)) {
                vector<int> hijo1, hijo2;

                // Seleccionar dos puntos de corte aleatorios
                int punto1 = rand() % N;
                int punto2 = rand() % N;

                if (punto1 > punto2) swap(punto1, punto2);

                // Inicializar hijos con -1
                hijo1.resize(N, -1);
                hijo2.resize(N, -1);

                // Copiar segmento del padre
                for (int k = punto1; k <= punto2; k++) {
                    hijo1[k] = padres[i][k];
                    hijo2[k] = padres[j][k];
                }

                // Completar hijo1 con valores del padre2
                for (int k = 0; k < N; k++) {
                    int valor = padres[j][k];
                    bool existe = false;

                    for (int m = punto1; m <= punto2; m++) {
                        if (hijo1[m] == valor) {
                            existe = true;
                            break;
                        }
                    }

                    if (!existe) {
                        for (int m = 0; m < N; m++) {
                            if (hijo1[m] == -1) {
                                hijo1[m] = valor;
                                break;
                            }
                        }
                    }
                }

                // Completar hijo2 con valores del padre1
                for (int k = 0; k < N; k++) {
                    int valor = padres[i][k];
                    bool existe = false;

                    for (int m = punto1; m <= punto2; m++) {
                        if (hijo2[m] == valor) {
                            existe = true;
                            break;
                        }
                    }

                    if (!existe) {
                        for (int m = 0; m < N; m++) {
                            if (hijo2[m] == -1) {
                                hijo2[m] = valor;
                                break;
                            }
                        }
                    }
                }

                // Agregar hijos si son válidos
                if (!esAberracion(hijo1)) {
                    poblacion.push_back(hijo1);
                }
                if (!esAberracion(hijo2)) {
                    poblacion.push_back(hijo2);
                }
            }
        }
    }
}

// Operador de mutación: Intercambio de dos posiciones
// Estrategia: Intercambiar dos tareas aleatorias para mantener diversidad
void mutacion(vector<vector<int>> &poblacion, vector<vector<int>> padres) {
    for (int i = 0; i < padres.size(); i++) {
        // Verificar probabilidad de mutación
        if ((rand() % 100) < (TMUTACION * 100)) {
            vector<int> mutante = padres[i];

            // Intercambiar dos posiciones aleatorias
            int pos1 = rand() % N;
            int pos2 = rand() % N;

            swap(mutante[pos1], mutante[pos2]);

            if (!esAberracion(mutante)) {
                poblacion.push_back(mutante);
            }
        }
    }
}

// Regenerar población: eliminar clones y mantener los mejores
// Estrategia: Ordenar por fitness descendente y mantener NUM_INDIVIDUOS mejores
void regenerarPoblacion(vector<vector<int>> &poblacion) {
    matarClones(poblacion);

    // Ordenar por fitness descendente (mayor ganancia primero)
    sort(poblacion.begin(), poblacion.end(),
        [](const vector<int> &a, const vector<int> &b) {
            return calculaFitness(a) > calculaFitness(b);
        }
    );

    // Mantener solo los mejores NUM_INDIVIDUOS
    if (poblacion.size() > NUM_INDIVIDUOS) {
        poblacion.erase(poblacion.begin() + NUM_INDIVIDUOS, poblacion.end());
    }
}

// Mostrar el mejor individuo
void mostrarMejor(vector<vector<int>> poblacion, int generacion) {
    vector<int> mejor = poblacion[0];

    cout << "\n=== GENERACION " << generacion << " ===" << endl;
    cout << "Ganancia maxima: " << calculaFitness(mejor) << endl;
    cout << "Asignaciones:" << endl;

    for (int empleado = 0; empleado < N; empleado++) {
        int tarea = mejor[empleado];
        cout << "  Empleado " << empleado << " -> Tarea " << tarea
             << " (Ganancia: " << ganancia[empleado][tarea] << ")" << endl;
    }
}

// Imprimir población
void imprimirPoblacion(vector<vector<int>> poblacion) {
    for (int i = 0; i < min(10, (int)poblacion.size()); i++) {
        cout << "Individuo " << i + 1 << ": [";
        for (int j = 0; j < N; j++) {
            cout << poblacion[i][j];
            if (j < N - 1) cout << ",";
        }
        cout << "] | Fitness: " << calculaFitness(poblacion[i]) << endl;
    }
    if (poblacion.size() > 10) {
        cout << "... (" << poblacion.size() - 10 << " individuos mas)" << endl;
    }
    cout << endl;
}

// Algoritmo genético principal
void asignacionGenetica() {
    vector<vector<int>> poblacion;

    generarPoblacion(poblacion);

    cout << "=== POBLACION INICIAL ===" << endl;
    imprimirPoblacion(poblacion);
    mostrarMejor(poblacion, 0);

    for (int gen = 1; gen <= ITERACIONES; gen++) {
        vector<vector<int>> padres;

        seleccion(poblacion, padres);
        casamiento(poblacion, padres);
        mutacion(poblacion, padres);
        regenerarPoblacion(poblacion);

        // Mostrar progreso cada 100 ITERACIONES
        if (gen % 100 == 0 || gen == ITERACIONES) {
            mostrarMejor(poblacion, gen);
        }
    }

    cout << "\n=== SOLUCION FINAL ===" << endl;
    mostrarMejor(poblacion, ITERACIONES);
}

//////////////////////////////////////////////////

int main() {
    cout << "=== MATRIZ DE GANANCIAS ===" << endl;
    cout << "     T0  T1  T2  T3  T4" << endl;
    for (int i = 0; i < N; i++) {
        cout << "E" << i << ": ";
        for (int j = 0; j < N; j++) {
            cout << setw(3) << ganancia[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    asignacionGenetica();

    return 0;
}