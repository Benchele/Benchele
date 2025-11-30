#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <map>
#include <climits>
using namespace std;

#define TSELECCION 0.5

// Parámetros configurables
int N = 4;                    // Tamaño del mapa (se cambiará según la parte)
int PESO_MAX = 100;           // Peso máximo permitido
int POBLACION_INICIAL = 5;    // Tamaño de población
int ITERACIONES = 1000;       // Número de generaciones
double TASA_MUTACION = 0.8;   // Tasa de mutación
double TASA_CRUCE = 0.5;      // Tasa de cruce

// Mapas de prueba
int mapa3[3][3] = {
    {4, 3, 8},
    {6, 3, 4},
    {2, 1, 2}
};

int mapa4[4][4] = {
    {4, 3, 8, 20},
    {6, 3, 4, 10},
    {2, 1, 2, 20},
    {10, 4, 9, 4}
};

int mapa5[5][5] = {
    {5, 10, 3, 8, 15},
    {12, 4, 7, 2, 9},
    {6, 11, 1, 14, 5},
    {8, 3, 13, 6, 10},
    {4, 9, 2, 7, 3}
};

int mapa6[6][6] = {
    {5, 8, 3, 12, 7, 10},
    {9, 4, 11, 2, 15, 6},
    {7, 13, 5, 9, 3, 14},
    {11, 2, 8, 6, 12, 4},
    {3, 10, 7, 14, 5, 9},
    {8, 4, 11, 3, 13, 2}
};

typedef vector<int> Cromosoma;

// Obtiene el valor de la celda del mapa actual
int obtenerValorMapa(int fila, int col) {
    if (N == 3) return mapa3[fila][col];
    if (N == 4) return mapa4[fila][col];
    if (N == 5) return mapa5[fila][col];
    if (N == 6) return mapa6[fila][col];
    return 0;
}

// Muestra el mapa actual
void mostrarMapa() {
    cout << "Mapa " << N << "x" << N << ":" << endl;
    for (int k = 0; k < N; k++) {
        for (int g = 0; g < N; g++) {
            cout << obtenerValorMapa(k, g) << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

// Decodifica un cromosoma y calcula el peso recolectado
// Retorna el peso total (o -1 si excede el límite o es inválido)
int decodificarCromosoma(Cromosoma &cromosoma) {
    int fila = 0, col = 0;
    int pesoTotal = obtenerValorMapa(0, 0); // Empieza en (0,0)

    // Verificar que el cromosoma tenga el tamaño correcto
    if (cromosoma.size() != (N - 1) * 2) {
        return -1; // Cromosoma inválido
    }

    // Contar movimientos
    int movAbajo = 0, movDerecha = 0;
    for (int k = 0; k < cromosoma.size(); k++) {
        if (cromosoma[k] == 1) movAbajo++;
        else movDerecha++;
    }

    // Verificar que tenga exactamente N-1 de cada movimiento
    if (movAbajo != N - 1 || movDerecha != N - 1) {
        return -1; // Cromosoma inválido
    }

    // Simular el recorrido
    for (int k = 0; k < cromosoma.size(); k++) {
        if (cromosoma[k] == 1) {
            // Movimiento abajo
            fila++;
        } else {
            // Movimiento derecha
            col++;
        }

        // Verificar límites
        if (fila >= N || col >= N) {
            return -1; // Fuera de límites
        }

        // Recolectar peso
        pesoTotal += obtenerValorMapa(fila, col);

        // Verificar si excede el peso máximo
        if (pesoTotal > PESO_MAX) {
            return -1; // Excede el peso permitido
        }
    }

    // Verificar que llegó al destino
    if (fila != N - 1 || col != N - 1) {
        return -1;
    }

    return pesoTotal;
}

// Calcula el fitness (peso recolectado, mayor es mejor)
int calcularFitness(Cromosoma &cromosoma) {
    int peso = decodificarCromosoma(cromosoma);
    return peso >= 0 ? peso : 0; // Si es inválido, fitness = 0
}

// ===============================================
// PARTE A: Generación de población inicial básica
// ===============================================
void generarPoblacionInicialBasica(vector<Cromosoma> &poblacion) {
    cout << "Generando poblacion inicial (PARTE A - basica)..." << endl;

    int intentos = 0;
    int maxIntentos = 10000;

    while (poblacion.size() < POBLACION_INICIAL && intentos < maxIntentos) {
        Cromosoma individuo;

        // Generar cromosoma aleatorio de tamaño (N-1)*2
        for (int k = 0; k < (N - 1) * 2; k++) {
            individuo.push_back(rand() % 2);
        }

        // Verificar si es válido (tiene exactamente N-1 unos)
        int contUnos = 0;
        for (int k = 0; k < individuo.size(); k++) {
            if (individuo[k] == 1) contUnos++;
        }

        if (contUnos == N - 1 && decodificarCromosoma(individuo) >= 0) {
            poblacion.push_back(individuo);
        }

        intentos++;
    }

    cout << "Poblacion generada: " << poblacion.size() << " individuos" << endl;
}

// ===============================================
// PARTE C: Generación con restricción de genes con valor 1
// ===============================================
void generarPoblacionInicialRestringida(vector<Cromosoma> &poblacion) {
    cout << "Generando poblacion inicial (PARTE C - restringida)..." << endl;
    cout << "Restriccion: Exactamente " << (N - 1) << " genes con valor 1" << endl;

    // Estrategia: Crear un vector con exactamente N-1 unos y N-1 ceros,
    // luego mezclarlo aleatoriamente

    for (int k = 0; k < POBLACION_INICIAL; k++) {
        Cromosoma individuo;

        // Agregar N-1 unos (movimientos abajo)
        for (int g = 0; g < N - 1; g++) {
            individuo.push_back(1);
        }

        // Agregar N-1 ceros (movimientos derecha)
        for (int g = 0; g < N - 1; g++) {
            individuo.push_back(0);
        }

        // Mezclar aleatoriamente
        random_shuffle(individuo.begin(), individuo.end());

        // Verificar que sea válido y no exceda peso
        if (decodificarCromosoma(individuo) >= 0) {
            poblacion.push_back(individuo);
        } else {
            // Si no es válido, generar otro
            k--;
        }
    }

    cout << "Poblacion generada: " << poblacion.size() << " individuos" << endl;
}

// Convierte cromosoma a decimal (para eliminar duplicados)
int convierteADecimal(Cromosoma &cromosoma) {
    int decimal = 0;
    for (int k = 0; k < cromosoma.size(); k++) {
        decimal += cromosoma[k] * pow(2, k);

        //O tambien
        //decimal += cromosoma[k] << k;
    }

    return decimal;
}

// Elimina duplicados
void eliminarDuplicados(vector<Cromosoma> &poblacion) {
    map<int, Cromosoma> unicos;

    for (int k = 0; k < poblacion.size(); k++) {
        int decimal = convierteADecimal(poblacion[k]);
        unicos[decimal] = poblacion[k];
    }

    poblacion.clear();
    for (auto par : unicos) {
        poblacion.push_back(par.second);
    }
}

// Calcula supervivencia
void calcularSupervivencia(vector<Cromosoma> &poblacion, vector<int> &supervivencia) {
    int sumaFitness = 0;

    for (int k = 0; k < poblacion.size(); k++) {
        sumaFitness += calcularFitness(poblacion[k]);
    }

    for (int k = 0; k < poblacion.size(); k++) {
        int superFit;
        if (sumaFitness > 0) {
            superFit = round(100.0 * calcularFitness(poblacion[k]) / sumaFitness);
        } else {
            superFit = 100 / poblacion.size();
        }
        supervivencia.push_back(superFit);
    }
}

// Carga la ruleta
void cargarRuleta(vector<int> &supervivencia, int *ruleta) {
    int cont = 0;

    for (int k = 0; k < supervivencia.size(); k++) {
        for (int g = 0; g < supervivencia[k]; g++) {
            if (cont < 100) {
                ruleta[cont++] = k;
            }
        }
    }
}

// Selección por ruleta
void seleccion(vector<Cromosoma> &poblacion, vector<Cromosoma> &padres) {
    int ruleta[100];
    for (int k = 0; k < 100; k++) ruleta[k] = -1;

    vector<int> supervivencia;
    calcularSupervivencia(poblacion, supervivencia);
    cargarRuleta(supervivencia, ruleta);

    int numeroPadres = max(2, (int)(poblacion.size() * TSELECCION));

    for (int k = 0; k < numeroPadres; k++) {
        int ticket = rand() % 100;
        int individuoSeleccionado = ruleta[ticket];
        if (individuoSeleccionado != -1 && individuoSeleccionado < poblacion.size()) {
            padres.push_back(poblacion[individuoSeleccionado]);
        }
    }
}

// Cruce de un punto (asegurando cromosomas válidos)
void crearHijo(Cromosoma &padre, Cromosoma &madre, Cromosoma &hijo) {
    int puntoCorte = 1 + rand() % (padre.size() - 1);

    for (int k = 0; k < padre.size(); k++) {
        if (k < puntoCorte) {
            hijo.push_back(padre[k]);
        } else {
            hijo.push_back(madre[k]);
        }
    }
}

// Casamiento (cruzamiento)
void casamiento(vector<Cromosoma> &poblacion, vector<Cromosoma> &padres) {
    for (int k = 0; k < padres.size(); k++) {
        for (int g = k + 1; g < padres.size(); g++) {
            if (rand() / (double)RAND_MAX < TASA_CRUCE) {
                Cromosoma hijo;
                crearHijo(padres[k], padres[g], hijo);
                poblacion.push_back(hijo);
            }
        }
    }
}

// Mutación (intercambio de bits)
void mutacion(vector<Cromosoma> &poblacion, vector<Cromosoma> &padres) {
    for (int k = 0; k < padres.size(); k++) {
        if (rand() / (double)RAND_MAX < TASA_MUTACION) {
            Cromosoma mutante = padres[k];

            // Intercambiar dos posiciones aleatorias (swap mutation)
            // Esto mantiene el número de unos constante
            int pos1 = rand() % mutante.size();
            int pos2 = rand() % mutante.size();

            swap(mutante[pos1], mutante[pos2]);

            poblacion.push_back(mutante);
        }
    }
}

// Inversión
void inversion(vector<Cromosoma> &poblacion, vector<Cromosoma> &padres) {
    for (int k = 0; k < padres.size(); k++) {
        Cromosoma invertido = padres[k];

        int inicio = rand() % invertido.size();
        int fin = inicio + rand() % (invertido.size() - inicio);

        reverse(invertido.begin() + inicio, invertido.begin() + fin + 1);

        poblacion.push_back(invertido);
    }
}

// ===============================================
// PARTE B: Control de población
// ===============================================
// Regenera la población manteniendo solo los mejores individuos
// Criterio: Ordena por fitness (mayor peso es mejor) y mantiene solo POBLACION_INICIAL
void regenerarPoblacion(vector<Cromosoma> &poblacion) {
    // Eliminar duplicados
    eliminarDuplicados(poblacion);

    // Ordenar por fitness (mayor peso primero = mejor)
    sort(poblacion.begin(), poblacion.end(),
        [](Cromosoma &a, Cromosoma &b) {
            return calcularFitness(a) > calcularFitness(b);
        }
    );

    // Mantener solo los mejores POBLACION_INICIAL individuos
    if (poblacion.size() > POBLACION_INICIAL) {
        poblacion.erase(poblacion.begin() + POBLACION_INICIAL, poblacion.end());
    }
}

// Muestra el mejor individuo
void mostrarMejor(vector<Cromosoma> &poblacion, int generacion) {
    int mejor = 0;

    for (int k = 0; k < poblacion.size(); k++) {
        if (calcularFitness(poblacion[k]) > calcularFitness(poblacion[mejor])) {
            mejor = k;
        }
    }

    cout << "Gen " << generacion << " - Mejor peso: "
         << calcularFitness(poblacion[mejor]) << " kg" << endl;
}

// Imprime el recorrido del cromosoma
void imprimirRecorrido(Cromosoma &cromosoma) {
    cout << endl << "Recorrido:" << endl;
    int fila = 0, col = 0;
    cout << "(" << fila << "," << col << ")[" << obtenerValorMapa(fila, col) << "]";

    int pesoAcum = obtenerValorMapa(0, 0);


    for (int k = 0; k < cromosoma.size(); k++) {
        if (cromosoma[k] == 1) {
            fila++;
            cout << " -> D -> ";
        } else {
            col++;
            cout << " -> R -> ";
        }

        pesoAcum += obtenerValorMapa(fila, col);
        cout << "(" << fila << "," << col << ")[" << obtenerValorMapa(fila, col)
             << "] (acum: " << pesoAcum << ")";
    }
    cout << endl;
}

// Imprime solución final
void imprimirSolucionFinal(Cromosoma &cromosoma) {
    cout << endl << "=== MEJOR SOLUCION FINAL ===" << endl;
    cout << "Cromosoma: [";
    for (int k = 0; k < cromosoma.size(); k++) {
        cout << cromosoma[k];
        if (k < cromosoma.size() - 1) cout << ", ";
    }
    cout << "]" << endl;

    cout << "Peso maximo transportado: " << calcularFitness(cromosoma) << " kg" << endl;

    // Mostrar recorrido
    //imprimirRecorrido(cromosoma);

    cout << endl << "========================================" << endl;
}

// Algoritmo Genético principal
void algoritmoGenetico(bool usarGeneracionRestringida) {
    vector<Cromosoma> poblacion;

    // Generar población inicial según la parte
    if (usarGeneracionRestringida) {
        generarPoblacionInicialRestringida(poblacion);
    } else {
        generarPoblacionInicialBasica(poblacion);
    }

    eliminarDuplicados(poblacion);

    cout << endl << "Iniciando Algoritmo Genetico..." << endl;
    cout << "Poblacion: " << poblacion.size() << " individuos" << endl << endl;

    for (int k = 0; k < ITERACIONES; k++) {
        vector<Cromosoma> padres;

        seleccion(poblacion, padres);
        casamiento(poblacion, padres);
        mutacion(poblacion, padres);
        inversion(poblacion, padres);

        // PARTE B: Control de población
        regenerarPoblacion(poblacion);

        if ((k + 1) % 100 == 0) {
            mostrarMejor(poblacion, k + 1);
        }
    }

    imprimirSolucionFinal(poblacion[0]);
}

// Ejecuta todas las partes del examen
void inicializar() {
    cout << endl << "========================================" << endl;
    cout << "PARTE A: Poblacion inicial basica" << endl;
    cout << "N = 3 y N = 4, P = 100 kg" << endl;
    cout << "Poblacion = 5, Tasa Mutacion = 0.8" << endl;
    cout << "========================================" << endl;

    // Parte A con N=3
    N = 3;
    PESO_MAX = 100;
    POBLACION_INICIAL = 5;
    TASA_MUTACION = 0.8;
    ITERACIONES = 1000;

    mostrarMapa();
    algoritmoGenetico(false);

    // Parte A con N=4
    N = 4;
    mostrarMapa();
    algoritmoGenetico(false);

    cout << endl << "========================================" << endl;
    cout << "PARTE B: Control de poblacion" << endl;
    cout << "N = 4 y N = 5, P = 200 kg" << endl;
    cout << "Poblacion = 10" << endl;
    cout << "========================================" << endl;

    // Parte B con N=4
    N = 4;
    PESO_MAX = 200;
    POBLACION_INICIAL = 10;

    mostrarMapa();
    algoritmoGenetico(false);

    // Parte B con N=5
    N = 5;
    mostrarMapa();
    algoritmoGenetico(false);

    cout << endl << "========================================" << endl;
    cout << "PARTE C: Generacion restringida" << endl;
    cout << "N = 5 y N = 6, P = 200 kg" << endl;
    cout << "Poblacion = 10" << endl;
    cout << "========================================" << endl;

    // Parte C con N=5
    N = 5;
    PESO_MAX = 200;
    POBLACION_INICIAL = 10;

    mostrarMapa();
    algoritmoGenetico(true);

    // Parte C con N=6
    N = 6;
    mostrarMapa();
    algoritmoGenetico(true);
}

int main() {
    srand(time(NULL));

    cout << "=== PROBLEMA DEL ROBOT MONTACARGA ===" << endl;
    cout << "Movimientos permitidos: Derecha (0) y Abajo (1)" << endl;
    cout << "Objetivo: Maximizar peso sin exceder limite P" << endl;

    inicializar();

    return 0;
}