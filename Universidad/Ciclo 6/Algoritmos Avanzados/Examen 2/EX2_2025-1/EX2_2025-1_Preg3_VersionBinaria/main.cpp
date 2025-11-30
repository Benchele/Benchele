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
#define BITS_POR_PEDIDO 4  // log2(9) = 4 bits
#define ALPHA 0.3
#define ITERACIONES_GRASP 10000
#define POBLACION_INICIAL 20
#define ITERACIONES_AG 1000
#define TASA_MUTACION 0.3
#define TASA_SELECCION 0.5

typedef vector<int> Cromosoma; // Cromosoma binario (0s y 1s)

// Estructuras auxiliares
struct Pedido {
    int tamano;
    int indiceOriginal;
};

struct Candidato {
    int desperdicio;
    int indiceBarra;
};

struct EstadoBarras {
    vector<int> espacioRestante;

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

// ==================== CONVERSIONES BINARIO <-> ENTERO ====================

// Convierte un número entero a binario (BITS_POR_PEDIDO bits)
vector<int> enteroABinario(int numero) {
    vector<int> binario;

    for (int k = 0; k < BITS_POR_PEDIDO; k++) {
        binario.push_back((numero >> k) & 1);  // Extrae bit k
    }

    return binario;
}

vector<int> enteroABinarioOtraForma(int numero) {
    vector<int> binario;
    int base = 2;

    for (int k = 0; k < BITS_POR_PEDIDO; k++) {
        binario.push_back(numero % base);
        numero = numero / base;
    }

    return binario;
}

// Convierte un segmento binario a entero
int binarioAEntero(vector<int> &cromosoma, int inicio) {
    int numero = 0;

    for (int k = 0; k < BITS_POR_PEDIDO; k++) {
        if (inicio + k < cromosoma.size()) {
            numero += cromosoma[inicio + k] * pow(2, k);
        }
    }

    return numero;
}

// Decodifica un cromosoma binario a vector de asignaciones enteras
vector<int> decodificar(Cromosoma &cromosoma, int nPedidos) {
    vector<int> asignaciones;

    for (int k = 0; k < nPedidos; k++) {
        int inicio = k * BITS_POR_PEDIDO;
        int barra = binarioAEntero(cromosoma, inicio);

        // Si el número binario excede NBARRAS-1, ajustar
        if (barra >= NBARRAS) {
            barra = barra % NBARRAS;
        }

        asignaciones.push_back(barra);
    }

    return asignaciones;
}

// Codifica un vector de asignaciones enteras a cromosoma binario
Cromosoma codificar(vector<int> &asignaciones) {
    Cromosoma cromosoma;

    for (int k = 0; k < asignaciones.size(); k++) {
        vector<int> binario = enteroABinario(asignaciones[k]);

        for (int bit : binario) {
            cromosoma.push_back(bit);
        }
    }

    return cromosoma;
}

// ==================== FUNCIONES DE EVALUACIÓN ====================

bool comparaPedidos(Pedido a, Pedido b) {
    return a.tamano > b.tamano;
}

bool comparaCandidatos(Candidato a, Candidato b) {
    return a.desperdicio < b.desperdicio;
}

int buscarIndiceCandidatos(vector<Candidato> &candidatos, double RCL) {
    int cont = 0;
    for (int k = 0; k < candidatos.size(); k++) {
        if (candidatos[k].desperdicio <= RCL) {
            cont++;
        }
    }
    return cont;
}

int contarBarrasIncompletas(vector<int> &asignaciones, vector<int> &pedidos) {
    EstadoBarras estado(NBARRAS);

    for (int k = 0; k < asignaciones.size(); k++) {
        estado.asignar(asignaciones[k], pedidos[k]);
    }

    int incompletas = 0;
    for (int k = 0; k < NBARRAS; k++) {
        if (estado.getEspacioRestante(k) < LONGITUD_BARRA && estado.getEspacioRestante(k) > 0) {
            incompletas++;
        }
    }

    return incompletas;
}

int calcularDesperdicio(vector<int> &asignaciones, vector<int> &pedidos) {
    EstadoBarras estado(NBARRAS);

    for (int k = 0; k < asignaciones.size(); k++) {
        estado.asignar(asignaciones[k], pedidos[k]);
    }

    int desperdicio = 0;
    for (int k = 0; k < NBARRAS; k++) {
        if (estado.getEspacioRestante(k) < LONGITUD_BARRA) {
            desperdicio += estado.getEspacioRestante(k);
        }
    }

    return desperdicio;
}

int calcularFitness(Cromosoma &cromosoma, vector<int> &pedidos) {
    vector<int> asignaciones = decodificar(cromosoma, pedidos.size());
    int incompletas = contarBarrasIncompletas(asignaciones, pedidos);
    int desperdicio = calcularDesperdicio(asignaciones, pedidos);

    return incompletas * 1000 + desperdicio;
}

bool esValida(Cromosoma &cromosoma, vector<int> &pedidos) {
    vector<int> asignaciones = decodificar(cromosoma, pedidos.size());
    EstadoBarras estado(NBARRAS);

    for (int k = 0; k < asignaciones.size(); k++) {
        if (asignaciones[k] < 0 || asignaciones[k] >= NBARRAS) {
            return false;
        }
        if (!estado.puedeAsignar(asignaciones[k], pedidos[k])) {
            return false;
        }
        estado.asignar(asignaciones[k], pedidos[k]);
    }

    return true;
}

// ==================== GRASP CONSTRUCCIÓN ====================

vector<int> grasp_construccion_entero(vector<int> &pedidos) {
    vector<Pedido> vPedidos;
    for (int k = 0; k < pedidos.size(); k++) {
        Pedido p;
        p.tamano = pedidos[k];
        p.indiceOriginal = k;
        vPedidos.push_back(p);
    }

    sort(vPedidos.begin(), vPedidos.end(), comparaPedidos);

    vector<int> asignaciones(pedidos.size());
    EstadoBarras estado(NBARRAS);

    while (!vPedidos.empty()) {
        Pedido pedidoActual = vPedidos[0];

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
            asignaciones[pedidoActual.indiceOriginal] = 0;
            vPedidos.erase(vPedidos.begin());
            continue;
        }

        sort(candidatos.begin(), candidatos.end(), comparaCandidatos);

        int beta = candidatos[0].desperdicio;
        int tau = candidatos[candidatos.size() - 1].desperdicio;
        double RCL = beta + ALPHA * (tau - beta);

        int indRCL = buscarIndiceCandidatos(candidatos, RCL);
        int indAle = rand() % indRCL;
        int barraSeleccionada = candidatos[indAle].indiceBarra;

        asignaciones[pedidoActual.indiceOriginal] = barraSeleccionada;
        estado.asignar(barraSeleccionada, pedidoActual.tamano);

        vPedidos.erase(vPedidos.begin());
    }

    return asignaciones;
}

// GRASP que devuelve cromosoma binario
Cromosoma grasp_construccion(vector<int> &pedidos) {
    vector<int> asignaciones = grasp_construccion_entero(pedidos);
    return codificar(asignaciones);
}

// ==================== POBLACIÓN INICIAL ====================

vector<Cromosoma> generarPoblacionInicial(vector<int> &pedidos) {
    vector<Cromosoma> poblacion;

    cout << "Generando población inicial con GRASP..." << endl;

    for (int k = 0; k < POBLACION_INICIAL; k++) {
        Cromosoma mejorSolu;
        int mejorValor = INT_MAX;

        for (int iter = 0; iter < ITERACIONES_GRASP / POBLACION_INICIAL; iter++) {
            Cromosoma solucion = grasp_construccion(pedidos);

            if (esValida(solucion, pedidos)) {
                int fitness = calcularFitness(solucion, pedidos);

                if (fitness < mejorValor) {
                    mejorValor = fitness;
                    mejorSolu = solucion;
                }
            }
        }

        if (mejorValor != INT_MAX) {
            poblacion.push_back(mejorSolu);
        }

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

void calculoSuperviviencia(vector<Cromosoma> &poblacion, vector<int> &superviviencia, vector<int> &pedidos) {
    int sumaFitnessInv = 0;
    int maxFitness = 0;

    for (int k = 0; k < poblacion.size(); k++) {
        int fit = calcularFitness(poblacion[k], pedidos);
        if (fit > maxFitness) {
            maxFitness = fit;
        }
    }

    vector<int> fitnessInverso;
    for (int k = 0; k < poblacion.size(); k++) {
        int fitInv = (maxFitness + 1) - calcularFitness(poblacion[k], pedidos);
        fitnessInverso.push_back(fitInv);
        sumaFitnessInv += fitInv;
    }

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

void seleccion(vector<Cromosoma> &poblacion, vector<Cromosoma> &padres, vector<int> &pedidos) {
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

// Cruce de un punto (opera sobre BITS, no bloques)
void crearHijo(Cromosoma &padre, Cromosoma &madre, Cromosoma &hijo, vector<int> &pedidos) {
    int puntoCorte = padre.size() / 2;

    for (int k = 0; k < padre.size(); k++) {
        if (k < puntoCorte) {
            hijo.push_back(padre[k]);
        } else {
            hijo.push_back(madre[k]);
        }
    }
}

void casamiento(vector<Cromosoma> &poblacion, vector<Cromosoma> &padres, vector<int> &pedidos) {
    for (int k = 0; k < padres.size(); k++) {
        for (int g = 0; g < padres.size(); g++) {
            if (k != g) {
                Cromosoma hijo;
                crearHijo(padres[k], padres[g], hijo, pedidos);

                if (esValida(hijo, pedidos)) {
                    poblacion.push_back(hijo);
                } else {
                    hijo = grasp_construccion(pedidos);
                    poblacion.push_back(hijo);
                }
            }
        }
    }
}

// Mutación: invierte bits individuales
void mutacion(vector<Cromosoma> &poblacion, vector<Cromosoma> &padres, vector<int> &pedidos) {
    int numeroMutaciones = max(1, (int)round(padres[0].size() * TASA_MUTACION));

    for (int k = 0; k < padres.size(); k++) {
        Cromosoma mutante = padres[k];

        for (int g = 0; g < numeroMutaciones; g++) {
            int posicion = rand() % mutante.size();
            mutante[posicion] = 1 - mutante[posicion];  // Flip bit (0->1, 1->0)
        }

        if (esValida(mutante, pedidos)) {
            poblacion.push_back(mutante);
        }
    }
}

// Inversión de un segmento binario
void inversion(vector<Cromosoma> &poblacion, vector<Cromosoma> &padres, vector<int> &pedidos) {
    for (int k = 0; k < padres.size(); k++) {
        Cromosoma invertido = padres[k];

        int inicio = rand() % invertido.size();
        int fin = inicio + rand() % (invertido.size() - inicio);

        reverse(invertido.begin() + inicio, invertido.begin() + fin + 1);

        if (esValida(invertido, pedidos)) {
            poblacion.push_back(invertido);
        }
    }
}

int nAux;

void regenerarPoblacion(vector<Cromosoma> &poblacion, vector<int> &pedidos) {
    eliminarDuplicados(poblacion);

    nAux = pedidos.size();

    sort(poblacion.begin(), poblacion.end(),
        [&pedidos](Cromosoma &a, Cromosoma &b) {
            return calcularFitness(a, pedidos) < calcularFitness(b, pedidos);
        }
    );

    if (POBLACION_INICIAL < poblacion.size()) {
        poblacion.erase(poblacion.begin() + POBLACION_INICIAL, poblacion.end());
    }
}

void muestraMejor(vector<Cromosoma> &poblacion, vector<int> &pedidos) {
    int mejor = 0;

    for (int k = 0; k < poblacion.size(); k++) {
        if (calcularFitness(poblacion[mejor], pedidos) > calcularFitness(poblacion[k], pedidos)) {
            mejor = k;
        }
    }

    vector<int> asignaciones = decodificar(poblacion[mejor], pedidos.size());
    int incompletas = contarBarrasIncompletas(asignaciones, pedidos);
    int desperdicio = calcularDesperdicio(asignaciones, pedidos);

    cout << "Mejor fitness: " << calcularFitness(poblacion[mejor], pedidos);
    cout << " (Incompletas: " << incompletas << ", Desperdicio: " << desperdicio << ")" << endl;
}

void imprimirSolucionFinal(Cromosoma &solucion, vector<int> &pedidos) {
    vector<int> asignaciones = decodificar(solucion, pedidos.size());

    cout << endl << "=== MEJOR SOLUCION FINAL ===" << endl;
    cout << "Cromosoma binario (" << solucion.size() << " bits): ";
    for (int k = 0; k < solucion.size(); k++) {
        cout << solucion[k];
        if ((k + 1) % BITS_POR_PEDIDO == 0 && k < solucion.size() - 1) cout << "|";
    }
    cout << endl;

    cout << "Asignaciones (entero): [";
    for (int k = 0; k < asignaciones.size(); k++) {
        cout << asignaciones[k];
        if (k < asignaciones.size() - 1) cout << ", ";
    }
    cout << "]" << endl;

    int incompletas = contarBarrasIncompletas(asignaciones, pedidos);
    int desperdicio = calcularDesperdicio(asignaciones, pedidos);

    cout << "Barras incompletas: " << incompletas << endl;
    cout << "Desperdicio total: " << desperdicio << " metros" << endl;
    cout << "Fitness: " << calcularFitness(solucion, pedidos) << endl;

    EstadoBarras estado(NBARRAS);
    for (int k = 0; k < asignaciones.size(); k++) {
        estado.asignar(asignaciones[k], pedidos[k]);
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

// ==================== ALGORITMO GENÉTICO ====================

void algoritmoGenetico(vector<int> &pedidos) {
    vector<Cromosoma> poblacion;

    poblacion = generarPoblacionInicial(pedidos);

    eliminarDuplicados(poblacion);

    cout << endl << "Iniciando Algoritmo Genetico BINARIO..." << endl;
    cout << "Tamaño del cromosoma: " << pedidos.size() * BITS_POR_PEDIDO << " bits" << endl;
    cout << "Poblacion inicial: " << poblacion.size() << " individuos" << endl << endl;

    for (int k = 0; k < ITERACIONES_AG; k++) {
        vector<Cromosoma> padres;

        seleccion(poblacion, padres, pedidos);
        casamiento(poblacion, padres, pedidos);
        inversion(poblacion, padres, pedidos);
        mutacion(poblacion, padres, pedidos);
        regenerarPoblacion(poblacion, pedidos);

        if ((k + 1) % 100 == 0) {
            cout << "Generacion " << (k + 1) << " - ";
            muestraMejor(poblacion, pedidos);
        }
    }

    imprimirSolucionFinal(poblacion[0], pedidos);
}

int main() {
    srand(time(NULL));

    vector<int> pedidos = {5, 2, 3, 10, 3, 7, 2, 10};

    cout << "=== BIN PACKING - VERSION BINARIA ===" << endl;
    cout << "Longitud de barras completas: " << LONGITUD_BARRA << " metros" << endl;
    cout << "Numero de barras disponibles: " << NBARRAS << endl;
    cout << "Bits por pedido: " << BITS_POR_PEDIDO << " (log2(" << NBARRAS << "))" << endl;
    cout << "Pedidos: [";
    for (int k = 0; k < pedidos.size(); k++) {
        cout << pedidos[k];
        if (k < pedidos.size() - 1) cout << ", ";
    }
    cout << "]" << endl << endl;

    algoritmoGenetico(pedidos);

    return 0;
}