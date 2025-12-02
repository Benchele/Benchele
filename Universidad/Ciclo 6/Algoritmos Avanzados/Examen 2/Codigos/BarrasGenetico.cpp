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
#define LONGITUD_BARRA 10
#define NBARRAS 9
#define ALPHA 0.3
#define ITERACIONES_GRASP 10000
#define POBLACION_INICIAL 20
#define ITERACIONES_AG 1000
#define TASA_MUTACION 0.3
#define TASA_SELECCION 0.5

typedef vector<int> Individuo; // Cada gen indica qué barra completa usar para ese corte

// Estructura para pedidos indexados
struct Pedido {
    int tamano;
    int indiceOriginal;
};

// Estructura para candidatos
struct Candidato {
    int desperdicio;
    int indiceBarra;
};

// Estructura para manejar el estado de las barras
struct EstadoBarras {
    vector<int> espacioRestante; // Espacio restante en cada barra

    EstadoBarras(int nBarras) {
        espacioRestante.resize(nBarras, LONGITUD_BARRA);
    }

    bool puedeAsignar(int barra, int tamano) {
        return espacioRestante[barra] >= tamano;
    }

    void asignar(int barra, int tamano) {
        espacioRestante[barra] -= tamano;
    }

    int getEspacioRestante(int barra) {
        return espacioRestante[barra];
    }
};

// Función de comparación para ordenar de mayor a menor
bool comparaPedidos(Pedido a, Pedido b) {
    return a.tamano > b.tamano; // Descendente (Mayor a menor)
}

// Función de comparación para candidatos (menor desperdicio primero)
bool comparaCandidatos(Candidato a, Candidato b) {
    return a.desperdicio < b.desperdicio; // Ascendente (Menor a mayor)
}

// Busca cuántos candidatos cumplen con el RCL
int buscarIndiceCandidatos(vector<Candidato> &candidatos, double RCL) {
    int cont = 0;
    for (int k = 0; k < candidatos.size(); k++) {
        if (candidatos[k].desperdicio <= RCL) {
            cont++;
        }
    }
    return cont;
}

// Calcula cuántas barras quedaron incompletas
int contarBarrasIncompletas(Individuo &cromosoma, vector<int> &pedidos) {
    EstadoBarras estado(NBARRAS);

    for (int k = 0; k < cromosoma.size(); k++) {
        estado.asignar(cromosoma[k], pedidos[k]);
    }

    int incompletas = 0;
    for (int k = 0; k < NBARRAS; k++) {
        // Si la barra fue usada pero no se llenó completamente
        if (estado.getEspacioRestante(k) < LONGITUD_BARRA && estado.getEspacioRestante(k) > 0) {
            incompletas++;
        }
    }

    return incompletas;
}

// Calcula el desperdicio total
int calcularDesperdicio(Individuo &cromosoma, vector<int> &pedidos) {
    EstadoBarras estado(NBARRAS);

    for (int k = 0; k < cromosoma.size(); k++) {
        estado.asignar(cromosoma[k], pedidos[k]);
    }

    int desperdicio = 0;
    for (int k = 0; k < NBARRAS; k++) {
        // Solo cuenta desperdicio de barras usadas
        if (estado.getEspacioRestante(k) < LONGITUD_BARRA) {
            desperdicio += estado.getEspacioRestante(k);
        }
    }

    return desperdicio;
}

// Función de fitness (MENOR ES MEJOR)
// Prioridad 1: minimizar barras incompletas
// Prioridad 2: minimizar desperdicio
int calcularFitness(Individuo &cromosoma, vector<int> &pedidos) {
    int incompletas = contarBarrasIncompletas(cromosoma, pedidos);
    int desperdicio = calcularDesperdicio(cromosoma, pedidos);

    // Penalización alta por barras incompletas
    // Fitness = incompletas * 1000 + desperdicio
    return incompletas * 1000 + desperdicio;
}

// Verifica si una solución es válida
bool esValida(Individuo &cromosoma, vector<int> &pedidos) {
    EstadoBarras estado(NBARRAS);

    for (int k = 0; k < cromosoma.size(); k++) {
        if (cromosoma[k] < 0 || cromosoma[k] >= NBARRAS) {
            return false;
        }
        if (!estado.puedeAsignar(cromosoma[k], pedidos[k])) {
            return false;
        }
        estado.asignar(cromosoma[k], pedidos[k]);
    }

    return true;
}

// GRASP Construcción - Genera UNA solución
Individuo grasp_construccion(vector<int> &pedidos) {
    // Preparar pedidos indexados
    vector<Pedido> vPedidos;
    for (int k = 0; k < pedidos.size(); k++) {
        Pedido p;
        p.tamano = pedidos[k];
        p.indiceOriginal = k;
        vPedidos.push_back(p);
    }

    // Ordenar de mayor a menor (greedy)
    sort(vPedidos.begin(), vPedidos.end(), comparaPedidos);

    // Vector para reconstruir el orden original
    vector<int> asignaciones(pedidos.size());
    EstadoBarras estado(NBARRAS);

    // Mientras haya pedidos por asignar
    while (!vPedidos.empty()) {
        Pedido pedidoActual = vPedidos[0];

        // Construir lista de candidatos (barras disponibles)
        vector<Candidato> candidatos;

        for (int b = 0; b < NBARRAS; b++) {
            if (estado.puedeAsignar(b, pedidoActual.tamano)) {
                Candidato c;
                c.desperdicio = estado.getEspacioRestante(b) - pedidoActual.tamano;
                c.indiceBarra = b;
                candidatos.push_back(c);
            }
        }

        if (candidatos.empty()) {
            // No hay barra disponible, asignar a la primera como fallback
            asignaciones[pedidoActual.indiceOriginal] = 0; //O cualquier valor -> La validacion de la poblacion se encargara de esto
            vPedidos.erase(vPedidos.begin());
            continue;
        }

        // Ordenar candidatos por menor desperdicio
        sort(candidatos.begin(), candidatos.end(), comparaCandidatos);

        // Calcular RCL con ALPHA
        int beta = candidatos[0].desperdicio; // Mejor (menor desperdicio)
        int tau = candidatos[candidatos.size() - 1].desperdicio; // Peor (mayor desperdicio)
        double RCL = beta + ALPHA * (tau - beta);

        // Buscar cuántos candidatos están en el RCL
        int indRCL = buscarIndiceCandidatos(candidatos, RCL);

        // Seleccionar uno aleatorio del RCL
        int indAle = rand() % indRCL;
        int barraSeleccionada = candidatos[indAle].indiceBarra;

        // Asignar
        asignaciones[pedidoActual.indiceOriginal] = barraSeleccionada;
        estado.asignar(barraSeleccionada, pedidoActual.tamano);

        // Eliminar pedido de la lista
        vPedidos.erase(vPedidos.begin());
    }

    return asignaciones;
}

// Genera población inicial usando GRASP
vector<Individuo> generarPoblacionInicial(vector<int> &pedidos) {
    vector<Individuo> poblacion;

    srand(time(NULL));

    cout << "Generando población inicial con GRASP..." << endl;

    for (int k = 0; k < POBLACION_INICIAL; k++) {
        Individuo mejorSolu;
        int mejorValor = INT_MAX;

        // Ejecutar GRASP múltiples veces por individuo
        for (int iter = 0; iter < ITERACIONES_GRASP / POBLACION_INICIAL; iter++) {
            Individuo solucion = grasp_construccion(pedidos);

            // Solo considerar si es válida
            if (esValida(solucion, pedidos)) {
                int fitness = calcularFitness(solucion, pedidos);

                if (fitness < mejorValor) {
                    mejorValor = fitness;
                    mejorSolu = solucion;
                }
            }
        }

        // Si encontró al menos una solución válida, agregarla
        if (mejorValor != INT_MAX) {
            poblacion.push_back(mejorSolu);
        }

        if ((k + 1) % 5 == 0) {
            cout << "  Generados " << (k + 1) << "/" << POBLACION_INICIAL << " individuos" << endl;
        }
    }

    return poblacion;
}

// Elimina duplicados
void eliminarDuplicados(vector<Individuo> &poblacion) {
    map<string, Individuo> unicos;

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

// Calcula la supervivencia de cada individuo (fitness inverso para ruleta)
void calculoSuperviviencia(vector<Individuo> &poblacion, vector<int> &superviviencia, vector<int> &pedidos) {
    int sumaFitnessInv = 0;
    int maxFitness = 0;

    // Encontrar el peor fitness (máximo)
    for (int k = 0; k < poblacion.size(); k++) {
        int fit = calcularFitness(poblacion[k], pedidos);
        if (fit > maxFitness) {
            maxFitness = fit;
        }
    }

    // Calcular fitness inverso (mientras menor fitness, mayor supervivencia)
    vector<int> fitnessInverso;
    for (int k = 0; k < poblacion.size(); k++) {
        int fitInv = (maxFitness + 1) - calcularFitness(poblacion[k], pedidos);
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

// Carga la ruleta con los índices según supervivencia
void cargarRuleta(vector<int> &superviviencia, int *ruleta) {
    int cont = 0;

    for (int k = 0; k < superviviencia.size(); k++) {
        for (int g = 0; g < superviviencia[k]; g++) {
            if (cont < 100) {
                ruleta[cont++] = k;
            }
        }
    }
}

// Selección por ruleta (mismo formato que tu código)
void seleccion(vector<Individuo> &poblacion, vector<Individuo> &padres, vector<int> &pedidos) {
    int ruleta[100];

    for (int k = 0; k < 100; k++) ruleta[k] = -1;

    vector<int> superviviencia;

    calculoSuperviviencia(poblacion, superviviencia, pedidos);
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

// Operador de cruce (One-Point Crossover)
void crearHijo(Individuo &padre, Individuo &madre, Individuo &hijo, vector<int> &pedidos) {
    int puntoCorte = padre.size() / 2;

    for (int k = 0; k < padre.size(); k++) {
        if (k < puntoCorte) {
            hijo.push_back(padre[k]);
        } else {
            hijo.push_back(madre[k]);
        }
    }
}

// Casamiento (cruce entre padres)
void casamiento(vector<Individuo> &poblacion, vector<Individuo> &padres, vector<int> &pedidos) {
    // Recorrer todos los padres
    for (int k = 0; k < padres.size(); k++) {
        for (int g = 0; g < padres.size(); g++) {
            if (k != g) {
                Individuo hijo;
                crearHijo(padres[k], padres[g], hijo, pedidos);

                // Si el hijo es válido, agregarlo
                if (esValida(hijo, pedidos)) {
                    poblacion.push_back(hijo);
                } else {
                    // Si no es válido, reparar con GRASP
                    hijo = grasp_construccion(pedidos);
                    poblacion.push_back(hijo);
                }
            }
        }
    }
}

// Operador de mutación
void mutacion(vector<Individuo> &poblacion, vector<Individuo> &padres, vector<int> &pedidos) {
    int numeroMutaciones = max(1, (int)round(padres[0].size() * TASA_MUTACION));

    for (int k = 0; k < padres.size(); k++) {
        Individuo mutante = padres[k];

        for (int g = 0; g < numeroMutaciones; g++) {
            int posicion = rand() % mutante.size();
            int nuevaBarra = rand() % NBARRAS;
            mutante[posicion] = nuevaBarra;
        }

        if (esValida(mutante, pedidos)) {
            poblacion.push_back(mutante);
        }
    }
}

// Operador de inversión
void inversion(vector<Individuo> &poblacion, vector<Individuo> &padres, vector<int> &pedidos) {
    for (int k = 0; k < padres.size(); k++) {
        Individuo invertido = padres[k];

        // Invertir un segmento del cromosoma
        int inicio = rand() % invertido.size();
        int fin = inicio + rand() % (invertido.size() - inicio);

        reverse(invertido.begin() + inicio, invertido.begin() + fin + 1);

        if (esValida(invertido, pedidos)) {
            poblacion.push_back(invertido);
        }
    }
}

// Variable auxiliar para el sort
int nAux;

// Regenerar población
void regenerarPoblacion(vector<Individuo> &poblacion, vector<int> &pedidos) {
    eliminarDuplicados(poblacion);

    nAux = pedidos.size();

    // Ordenar por fitness (menor es mejor)
    sort(poblacion.begin(), poblacion.end(),
        [&pedidos](Individuo &k, Individuo &g) {
            return calcularFitness(k, pedidos) < calcularFitness(g, pedidos);
        }
    );

    // Cortar al tamaño deseado
    if (POBLACION_INICIAL < poblacion.size()) {
        poblacion.erase(poblacion.begin() + POBLACION_INICIAL, poblacion.end());
    }
}

// Muestra el mejor individuo
void muestraMejor(vector<Individuo> &poblacion, vector<int> &pedidos) {
    int mejor = 0;

    for (int k = 0; k < poblacion.size(); k++) {
        if (calcularFitness(poblacion[k], pedidos) < calcularFitness(poblacion[mejor], pedidos)) {
            mejor = k;
        }
    }

    int incompletas = contarBarrasIncompletas(poblacion[mejor], pedidos);
    int desperdicio = calcularDesperdicio(poblacion[mejor], pedidos);

    cout << "Mejor fitness: " << calcularFitness(poblacion[mejor], pedidos);
    cout << " (Incompletas: " << incompletas << ", Desperdicio: " << desperdicio << ")" << endl;
}

// Imprimir solución final detallada
void imprimirSolucionFinal(Individuo &solucion, vector<int> &pedidos) {
    cout << endl << "=== MEJOR SOLUCION FINAL ===" << endl;
    cout << "Cromosoma: [";
    for (int k = 0; k < solucion.size(); k++) {
        cout << solucion[k];
        if (k < solucion.size() - 1) cout << ", ";
    }
    cout << "]" << endl;

    int incompletas = contarBarrasIncompletas(solucion, pedidos);
    int desperdicio = calcularDesperdicio(solucion, pedidos);

    cout << "Barras incompletas: " << incompletas << endl;
    cout << "Desperdicio total: " << desperdicio << " metros" << endl;
    cout << "Fitness: " << calcularFitness(solucion, pedidos) << endl;

    // Mostrar distribución
    EstadoBarras estado(NBARRAS);
    for (int k = 0; k < solucion.size(); k++) {
        estado.asignar(solucion[k], pedidos[k]);
    }

    cout << endl << "Distribucion por barras:" << endl;
    for (int k = 0; k < NBARRAS; k++) {
        int usado = LONGITUD_BARRA - estado.getEspacioRestante(k);
        if (usado > 0) {
            cout << "  Barra " << k << ": " << usado << "/" << LONGITUD_BARRA
                 << " metros (restante: " << estado.getEspacioRestante(k) << ")" << endl;
        }
    }
}

// Algoritmo Genético principal
void algoritmoGenetico(vector<int> &pedidos) {
    vector<Individuo> poblacion;

    // Genera población inicial con GRASP
    poblacion = generarPoblacionInicial(pedidos);

    // Mata clon
    eliminarDuplicados(poblacion);

    cout << endl << "Iniciando Algoritmo Genetico..." << endl;
    cout << "Poblacion inicial: " << poblacion.size() << " individuos" << endl << endl;

    for (int k = 0; k < ITERACIONES_AG; k++) {
        vector<Individuo> padres;

        // Selección
        seleccion(poblacion, padres, pedidos);

        // Casamiento
        casamiento(poblacion, padres, pedidos);

        // Inversión
        inversion(poblacion, padres, pedidos);

        // Mutación
        mutacion(poblacion, padres, pedidos);

        // Regenerar población
        regenerarPoblacion(poblacion, pedidos);

        // Mostrar mejor cada 100 generaciones
        if ((k + 1) % 100 == 0) {
            cout << "Generacion " << (k + 1) << " - ";
            muestraMejor(poblacion, pedidos);
        }
    }

    // Imprimir solución final
    imprimirSolucionFinal(poblacion[0], pedidos);
}

int main() {
    // Datos del problema
    vector<int> pedidos = {5, 2, 3, 10, 3, 7, 2, 10};

    cout << "=== CUTTING STOCK PROBLEM ===" << endl;
    cout << "Longitud de barras completas: " << LONGITUD_BARRA << " metros" << endl;
    cout << "Numero de barras disponibles: " << NBARRAS << endl;
    cout << "Pedidos: [";
    for (int k = 0; k < pedidos.size(); k++) {
        cout << pedidos[k];
        if (k < pedidos.size() - 1) cout << ", ";
    }
    cout << "]" << endl << endl;

    algoritmoGenetico(pedidos);

    return 0;
}