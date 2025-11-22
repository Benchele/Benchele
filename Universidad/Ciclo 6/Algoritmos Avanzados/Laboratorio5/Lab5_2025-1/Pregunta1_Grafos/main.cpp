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
#define K_REPARTIDORES 2
#define NUM_CLIENTES 6
#define NODO_DEPOSITO 0

// Estructura para representar un individuo
struct Individuo {
    vector<int> cromosoma;  // Permutación de clientes (1-6)
    vector<int> cambio_repartidor;  // Índices donde cambia de repartidor
    int fitness;  // Distancia total
};

// Matriz de distancias del grafo
// Nodos: 0=A, 1=Cliente1, 2=Cliente2, 3=Cliente3, 4=Cliente4, 5=Cliente5, 6=Cliente6
int matrizDistancias[7][7];

// Inicializar la matriz de distancias según el problema
void inicializarMatriz() {
    // Inicializar todo con -1 (no hay conexión)
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            matrizDistancias[i][j] = -1;
        }
    }

    // A -> 1: 4 unidades
    matrizDistancias[0][1] = 4;
    // 1 -> 2: 2 unidades
    matrizDistancias[1][2] = 2;
    // A -> 3: 3 unidades
    matrizDistancias[0][3] = 3;
    // 3 -> 4: 6 unidades
    matrizDistancias[3][4] = 6;
    // 4 -> 5: 5 unidades
    matrizDistancias[4][5] = 5;
    // 5 -> 6: 2 unidades
    matrizDistancias[5][6] = 2;
    // 6 -> A: 3 unidades
    matrizDistancias[6][0] = 3;
    // 2 -> 4: 2 unidades
    matrizDistancias[2][4] = 2;
    // 2 -> A: 8 unidades
    matrizDistancias[2][0] = 8;
}

// Verificar si existe una arista directa entre dos nodos
bool existeArista(int desde, int hacia) {
    return matrizDistancias[desde][hacia] != -1;
}

// Calcular fitness (distancia total de las rutas)
// Estrategia: Recorrer el cromosoma y sumar distancias, considerando
// los cambios de repartidor y los retornos al depósito
int calculaFitness(Individuo &ind) {
    int distanciaTotal = 0;
    int nodoActual = NODO_DEPOSITO;

    for (int i = 0; i < ind.cromosoma.size(); i++) {
        int clienteDestino = ind.cromosoma[i];

        // Verificar si existe arista
        if (!existeArista(nodoActual, clienteDestino)) {
            return INT_MAX; // Ruta inválida
        }

        distanciaTotal += matrizDistancias[nodoActual][clienteDestino];
        nodoActual = clienteDestino;

        // Si hay cambio de repartidor, volver al depósito
        for (int j = 0; j < ind.cambio_repartidor.size(); j++) {
            if (i + 1 == ind.cambio_repartidor[j]) {
                if (!existeArista(nodoActual, NODO_DEPOSITO)) {
                    return INT_MAX;
                }
                distanciaTotal += matrizDistancias[nodoActual][NODO_DEPOSITO];
                nodoActual = NODO_DEPOSITO;
                break;
            }
        }
    }

    // Retornar al depósito al final
    if (!existeArista(nodoActual, NODO_DEPOSITO)) {
        return INT_MAX;
    }
    distanciaTotal += matrizDistancias[nodoActual][NODO_DEPOSITO];

    return distanciaTotal;
}

// Verificar si el cromosoma es una permutación válida
// Estrategia: Verificar que todos los clientes (1-6) aparezcan exactamente una vez
bool esPermutacionValida(vector<int> &cromosoma) {
    vector<bool> visitado(NUM_CLIENTES + 1, false);

    for (int i = 0; i < cromosoma.size(); i++) {
        int cliente = cromosoma[i];
        if (cliente < 1 || cliente > NUM_CLIENTES || visitado[cliente]) {
            return false;
        }
        visitado[cliente] = true;
    }

    return true;
}

// Verificar si hay repartidores sin clientes
// Estrategia: Verificar que ningún segmento entre cortes esté vacío
bool hayRepartidorSinClientes(Individuo &ind) {
    if (ind.cambio_repartidor.empty()) return false;

    int inicio = 0;
    for (int i = 0; i < ind.cambio_repartidor.size(); i++) {
        int fin = ind.cambio_repartidor[i];
        if (fin <= inicio || fin > ind.cromosoma.size()) {
            return true;
        }
        inicio = fin;
    }

    // Verificar último segmento
    if (inicio >= ind.cromosoma.size()) {
        return true;
    }

    return false;
}

// Detectar aberraciones
// Estrategia: Verificar todas las condiciones de validez del individuo
bool esAberracion(Individuo &ind) {
    // A. Cromosoma no permutacional
    if (!esPermutacionValida(ind.cromosoma)) {
        return true;
    }

    // C. Repartidor sin clientes
    if (hayRepartidorSinClientes(ind)) {
        return true;
    }

    // B. Ruta inválida (se verifica en calculaFitness)
    ind.fitness = calculaFitness(ind);
    if (ind.fitness == INT_MAX) {
        return true;
    }

    return false;
}

// Generar un individuo aleatorio
// Estrategia: Crear permutación aleatoria y punto de corte aleatorio
Individuo generarIndividuoAleatorio() {
    Individuo ind;

    // Crear permutación de clientes 1-6
    for (int i = 1; i <= NUM_CLIENTES; i++) {
        ind.cromosoma.push_back(i);
    }
    random_shuffle(ind.cromosoma.begin(), ind.cromosoma.end());

    // Generar punto de corte aleatorio (no puede ser 0 ni NUM_CLIENTES)
    int corte = 1 + rand() % (NUM_CLIENTES - 1);
    ind.cambio_repartidor.push_back(corte);

    return ind;
}

// Generar población inicial
// Estrategia: Generar individuos aleatorios válidos hasta completar la población
void generarPoblacion(vector<Individuo> &poblacion) {
    srand(time(NULL));

    int cont = 0;
    while (cont < NUM_INDIVIDUOS) {
        Individuo ind = generarIndividuoAleatorio();

        if (!esAberracion(ind)) {
            poblacion.push_back(ind);
            cont++;
        }
    }
}

// Detectar y eliminar clones
// Estrategia: Comparar cromosoma y lista de cortes de cada par de individuos
void matarClones(vector<Individuo> &poblacion) {
    vector<Individuo> unicos;

    for (int i = 0; i < poblacion.size(); i++) {
        bool esClon = false;

        for (int j = 0; j < unicos.size(); j++) {
            if (poblacion[i].cromosoma == unicos[j].cromosoma &&
                poblacion[i].cambio_repartidor == unicos[j].cambio_repartidor) {
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

// Calcular probabilidades de supervivencia para la ruleta
// Estrategia: Como queremos minimizar, invertimos los fitness
void calculaSupervivencia(vector<Individuo> &poblacion, vector<int> &supervivencia) {
    // Encontrar el peor fitness para invertir
    int peorFitness = 0;
    for (int i = 0; i < poblacion.size(); i++) {
        if (poblacion[i].fitness > peorFitness) {
            peorFitness = poblacion[i].fitness;
        }
    }

    // Invertir fitness (mejor fitness = mayor supervivencia)
    int sumaInvertida = 0;
    vector<int> fitnessInvertido;
    for (int i = 0; i < poblacion.size(); i++) {
        int invertido = peorFitness - poblacion[i].fitness + 1;
        fitnessInvertido.push_back(invertido);
        sumaInvertida += invertido;
    }

    // Calcular porcentajes
    for (int i = 0; i < poblacion.size(); i++) {
        int porcentaje = round(100.0 * fitnessInvertido[i] / sumaInvertida);
        supervivencia.push_back(porcentaje);
    }
}

// Cargar ruleta con índices de individuos
void cargarRuleta(vector<int> &supervivencia, int *ruleta) {
    int indiceRuleta = 0;

    for (int i = 0; i < supervivencia.size(); i++) {
        for (int j = 0; j < supervivencia[i]; j++) {
            if (indiceRuleta < 100) {
                ruleta[indiceRuleta++] = i;
            }
        }
    }
}

// Selección de padres mediante ruleta
// Estrategia: Usar ruleta proporcional al fitness invertido
void seleccion(vector<Individuo> &poblacion, vector<Individuo> &padres) {
    int ruleta[100];
    for (int i = 0; i < 100; i++) ruleta[i] = -1;

    vector<int> supervivencia;
    calculaSupervivencia(poblacion, supervivencia);
    cargarRuleta(supervivencia, ruleta);

    int numeroPadres = round(poblacion.size() * TSELECCION);

    for (int i = 0; i < numeroPadres; i++) {
        int ticket = rand() % 100;
        int individuoSeleccionado = ruleta[ticket];
        if (individuoSeleccionado != -1) {
            padres.push_back(poblacion[individuoSeleccionado]);
        }
    }
}

// Operador de casamiento (PMX - Partially Mapped Crossover)
// Estrategia: Cruce que preserva la permutación válida
void casamiento(vector<Individuo> &poblacion, vector<Individuo> &padres) {
    for (int i = 0; i < padres.size(); i++) {
        for (int j = i + 1; j < padres.size(); j++) {
            if (rand() % 100 < PCASAMIENTO * 100) {
                Individuo hijo;

                // Cruce simple: tomar parte del padre1 y completar con padre2
                int punto = rand() % NUM_CLIENTES;

                // Copiar primera parte del padre1
                for (int k = 0; k < punto; k++) {
                    hijo.cromosoma.push_back(padres[i].cromosoma[k]);
                }

                // Completar con elementos del padre2 que no estén
                for (int k = 0; k < NUM_CLIENTES; k++) {
                    bool existe = false;
                    for (int m = 0; m < hijo.cromosoma.size(); m++) {
                        if (padres[j].cromosoma[k] == hijo.cromosoma[m]) {
                            existe = true;
                            break;
                        }
                    }
                    if (!existe) {
                        hijo.cromosoma.push_back(padres[j].cromosoma[k]);
                    }
                }

                // Heredar punto de corte (aleatorio entre los padres)
                if (rand() % 2 == 0) {
                    hijo.cambio_repartidor = padres[i].cambio_repartidor;
                } else {
                    hijo.cambio_repartidor = padres[j].cambio_repartidor;
                }

                if (!esAberracion(hijo)) {
                    poblacion.push_back(hijo);
                }
            }
        }
    }
}

// Operador de mutación
// Estrategia: Intercambiar dos genes aleatorios o cambiar punto de corte
void mutacion(vector<Individuo> &poblacion, vector<Individuo> &padres) {
    for (int i = 0; i < padres.size(); i++) {
        if (rand() % 100 < TMUTACION * 100) {
            Individuo mutante = padres[i];

            // Tipo de mutación aleatoria
            int tipoMutacion = rand() % 2;

            if (tipoMutacion == 0) {
                // Intercambiar dos posiciones
                int pos1 = rand() % NUM_CLIENTES;
                int pos2 = rand() % NUM_CLIENTES;
                swap(mutante.cromosoma[pos1], mutante.cromosoma[pos2]);
            } else {
                // Cambiar punto de corte
                int nuevoCorte = 1 + rand() % (NUM_CLIENTES - 1);
                mutante.cambio_repartidor[0] = nuevoCorte;
            }

            if (!esAberracion(mutante)) {
                poblacion.push_back(mutante);
            }
        }
    }
}

// Regenerar población: eliminar clones y quedarse con los mejores
void regenerarPoblacion(vector<Individuo> &poblacion) {
    matarClones(poblacion);

    // Ordenar por fitness (menor es mejor)
    sort(poblacion.begin(), poblacion.end(),
        [](const Individuo &a, const Individuo &b) {
            return a.fitness < b.fitness;
        }
    );

    // Mantener solo los mejores
    if (poblacion.size() > NUM_INDIVIDUOS) {
        poblacion.erase(poblacion.begin() + NUM_INDIVIDUOS, poblacion.end());
    }
}

// Mostrar el mejor individuo con sus rutas
void mostrarMejor(vector<Individuo> &poblacion, int iteracion) {
    Individuo mejor = poblacion[0];

    cout << "\n=== ITERACION " << iteracion << " ===" << endl;
    cout << "Distancia total minima: " << mejor.fitness << " unidades" << endl;
    cout << "Cromosoma: ";
    for (int i = 0; i < mejor.cromosoma.size(); i++) {
        cout << mejor.cromosoma[i] << " ";
    }
    cout << endl;
    cout << "Cambio de repartidor en posicion: " << mejor.cambio_repartidor[0] << endl;

    // Mostrar rutas detalladas
    cout << "\nRutas:" << endl;
    int nodoActual = NODO_DEPOSITO;
    int distanciaRepartidor = 0;
    int numRepartidor = 1;

    cout << "Repartidor " << numRepartidor << ": A";

    for (int i = 0; i < mejor.cromosoma.size(); i++) {
        int cliente = mejor.cromosoma[i];
        cout << " -> " << cliente;
        distanciaRepartidor += matrizDistancias[nodoActual][cliente];
        nodoActual = cliente;

        // Verificar cambio de repartidor
        bool cambio = false;
        for (int j = 0; j < mejor.cambio_repartidor.size(); j++) {
            if (i + 1 == mejor.cambio_repartidor[j]) {
                distanciaRepartidor += matrizDistancias[nodoActual][NODO_DEPOSITO];
                cout << " -> A (Distancia: " << distanciaRepartidor << ")" << endl;
                numRepartidor++;
                cout << "Repartidor " << numRepartidor << ": A";
                nodoActual = NODO_DEPOSITO;
                distanciaRepartidor = 0;
                cambio = true;
                break;
            }
        }
    }

    // Completar última ruta
    distanciaRepartidor += matrizDistancias[nodoActual][NODO_DEPOSITO];
    cout << " -> A (Distancia: " << distanciaRepartidor << ")" << endl;
}

// Imprimir población
void imprimirPoblacion(vector<Individuo> &poblacion) {
    for (int i = 0; i < poblacion.size(); i++) {
        cout << "Individuo " << i + 1 << ": ";
        for (int j = 0; j < poblacion[i].cromosoma.size(); j++) {
            cout << poblacion[i].cromosoma[j] << " ";
        }
        cout << "| Corte: " << poblacion[i].cambio_repartidor[0];
        cout << " | Fitness: " << poblacion[i].fitness << endl;
    }
    cout << endl;
}

// Función principal del algoritmo genético
void mtspGenetico() {
    vector<Individuo> poblacion;

    inicializarMatriz();
    generarPoblacion(poblacion);

    cout << "=== POBLACION INICIAL ===" << endl;
    imprimirPoblacion(poblacion);

    for (int i = 0; i < ITERACIONES; i++) {
        vector<Individuo> padres;

        seleccion(poblacion, padres);
        casamiento(poblacion, padres);
        mutacion(poblacion, padres);
        regenerarPoblacion(poblacion);

        if (i % 10 == 0 || i == ITERACIONES - 1) {
            mostrarMejor(poblacion, i + 1);
        }
    }

    cout << "\n=== SOLUCION FINAL ===" << endl;
    mostrarMejor(poblacion, ITERACIONES);
}

int main() {

    mtspGenetico();

    return 0;
}