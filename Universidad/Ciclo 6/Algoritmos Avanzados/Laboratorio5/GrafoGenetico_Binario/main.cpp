#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <map>
using namespace std;

#define GENERACIONES 1000
#define NUM_INDIVIDUOS 20
#define TSELECCION 0.5
#define PCASAMIENTO 0.8
#define PMUTACION 0.3
#define K 20

const int NUM_CIUDADES = 4;
const int NUM_MOTORIZADOS = 5;

int costoCiudad[NUM_CIUDADES] = {16, 15, 12, 18};
int costoMotorizado[NUM_MOTORIZADOS][NUM_CIUDADES] = {
    {3, 4, 5, 6},
    {5, 2, 3, 4},
    {7, 5, 4, 2},
    {8, 7, 5, 1},
    {4, 3, 7, 5}
};
char nombresCiudades[NUM_CIUDADES] = {'A', 'B', 'C', 'D'};

// Tipo de cromosoma: matriz 5×4
typedef vector<vector<int>> Cromosoma;

////////////////////////////////////////////////////
// Obtener motorizado asignado a una ciudad
// Estrategia: Buscar en la columna (ciudad) qué fila (motorizado) tiene 1
int obtenerMotorizado(Cromosoma cromosoma, int ciudad) {
    for (int mot = 0; mot < NUM_MOTORIZADOS; mot++) {
        if (cromosoma[mot][ciudad] == 1) {
            return mot;
        }
    }
    return -1;  // No asignado (aberración)
}

// Calcular fitness (costo total)
int calculaFitness(Cromosoma cromosoma) {
    int costoTotal = 0;

    for (int ciudad = 0; ciudad < NUM_CIUDADES; ciudad++) {
        int motorizado = obtenerMotorizado(cromosoma, ciudad);
        if (motorizado != -1) {
            costoTotal += costoCiudad[ciudad] + costoMotorizado[motorizado][ciudad];
        } else {
            return INT_MAX;  // Penalizar
        }
    }

    return costoTotal;
}

// Verificar que cada ciudad tenga exactamente 1 motorizado
// Estrategia: Sumar cada columna, debe dar 1
bool todasCiudadesAsignadas(Cromosoma cromosoma) {
    for (int ciudad = 0; ciudad < NUM_CIUDADES; ciudad++) {
        int suma = 0;
        for (int mot = 0; mot < NUM_MOTORIZADOS; mot++) {
            suma += cromosoma[mot][ciudad];
        }
        if (suma != 1) {
            return false;
        }
    }
    return true;
}

// Verificar restricción K
bool cumpleRestriccionK(Cromosoma cromosoma) {
    for (int ciudad = 0; ciudad < NUM_CIUDADES; ciudad++) {
        int motorizado = obtenerMotorizado(cromosoma, ciudad);
        if (motorizado != -1) {
            int costo = costoCiudad[ciudad] + costoMotorizado[motorizado][ciudad];
            if (costo > K) {
                return false;
            }
        }
    }
    return true;
}

// Detectar aberraciones
bool esAberracion(Cromosoma cromosoma) {
    return !todasCiudadesAsignadas(cromosoma) || !cumpleRestriccionK(cromosoma);
}

// Generar individuo aleatorio válido
// Estrategia: Para cada ciudad, asignar un motorizado válido
Cromosoma generarIndividuoAleatorio() {
    // Inicializar matriz en 0
    Cromosoma individuo(NUM_MOTORIZADOS, vector<int>(NUM_CIUDADES, 0));

    for (int ciudad = 0; ciudad < NUM_CIUDADES; ciudad++) {
        // Buscar motorizados válidos
        vector<int> motorizadosValidos;

        for (int mot = 0; mot < NUM_MOTORIZADOS; mot++) {
            if (costoCiudad[ciudad] + costoMotorizado[mot][ciudad] <= K) {
                motorizadosValidos.push_back(mot);
            }
        }

        if (motorizadosValidos.size() > 0) {
            int motElegido = motorizadosValidos[rand() % motorizadosValidos.size()];
            individuo[motElegido][ciudad] = 1;  // Asignar
        }
    }

    return individuo;
}

// Generar población inicial
void generarPoblacion(vector<Cromosoma> &poblacion) {
    srand(time(NULL));

    int cont = 0;
    int intentos = 0;
    while (cont < NUM_INDIVIDUOS && intentos < 10000) {
        Cromosoma individuo = generarIndividuoAleatorio();

        if (!esAberracion(individuo)) {
            poblacion.push_back(individuo);
            cont++;
        }
        intentos++;
    }
}

// Convertir matriz a decimal para matar clones
// Estrategia: Aplanar matriz y convertir a decimal
long long matrizADecimal(Cromosoma cromosoma) {
    long long num = 0;
    long long potencia = 1;

    for (int mot = 0; mot < NUM_MOTORIZADOS; mot++) {
        for (int ciudad = 0; ciudad < NUM_CIUDADES; ciudad++) {
            num += cromosoma[mot][ciudad] * potencia;
            potencia *= 2;
        }
    }

    return num;
}

// Eliminar clones
void matarClones(vector<Cromosoma> &poblacion) {
    map<long long, Cromosoma> indunicos;

    for (int i = 0; i < poblacion.size(); i++) {
        int dec = matrizADecimal(poblacion[i]);
        indunicos[dec] = poblacion[i];  // Si ya existe, lo reemplaza (elimina clon)
    }

    poblacion.clear();

    for (auto p : indunicos) {
        poblacion.push_back(p.second);
    }
}

// Calcular supervivencia (invertir porque minimizamos)
void calculaSupervivencia(vector<Cromosoma> poblacion, vector<int> &supervivencia) {
    int peorFitness = 0;

    for (int i = 0; i < poblacion.size(); i++) {
        int fitness = calculaFitness(poblacion[i]);
        if (fitness < INT_MAX && fitness > peorFitness) {
            peorFitness = fitness;
        }
    }

    int sumaInvertida = 0;
    vector<int> fitnessInvertido;

    for (int i = 0; i < poblacion.size(); i++) {
        int fitness = calculaFitness(poblacion[i]);
        int invertido = (fitness < INT_MAX) ? (peorFitness - fitness + 1) : 1;
        fitnessInvertido.push_back(invertido);
        sumaInvertida += invertido;
    }

    if (sumaInvertida == 0) {
        int porcentajeIgual = 100 / poblacion.size();
        for (int i = 0; i < poblacion.size(); i++) {
            supervivencia.push_back(porcentajeIgual);
        }
        return;
    }

    for (int i = 0; i < poblacion.size(); i++) {
        int porcentaje = round(100.0 * fitnessInvertido[i] / sumaInvertida);
        supervivencia.push_back(porcentaje);
    }
}

// Cargar ruleta
void cargarRuleta(vector<int> supervivencia, int *ruleta) {
    int indiceRuleta = 0;

    for (int i = 0; i < supervivencia.size(); i++) {
        for (int j = 0; j < supervivencia[i]; j++) {
            if (indiceRuleta < 100) {
                ruleta[indiceRuleta++] = i;
            }
        }
    }

    while (indiceRuleta < 100) {
        ruleta[indiceRuleta++] = 0;
    }
}

// Selección por ruleta
void seleccion(vector<Cromosoma> poblacion, vector<Cromosoma> &padres) {
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

// Casamiento: Cruce por filas (motorizados)
// Estrategia: Intercambiar filas completas entre padres
void casamiento(vector<Cromosoma> &poblacion, vector<Cromosoma> padres) {
    for (int i = 0; i < padres.size(); i++) {
        for (int j = i + 1; j < padres.size(); j++) {
            if ((rand() % 100) < (PCASAMIENTO * 100)) {
                Cromosoma hijo1 = padres[i];
                Cromosoma hijo2 = padres[j];

                // Intercambiar algunas filas (motorizados)
                int puntoCorte = rand() % NUM_MOTORIZADOS;

                for (int mot = puntoCorte; mot < NUM_MOTORIZADOS; mot++) {
                    hijo1[mot] = padres[j][mot];
                    hijo2[mot] = padres[i][mot];
                }

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

// Mutación: Cambiar asignación de una ciudad
// Estrategia: Seleccionar ciudad y cambiar su motorizado
void mutacion(vector<Cromosoma> &poblacion, vector<Cromosoma> padres) {
    for (int i = 0; i < padres.size(); i++) {
        if ((rand() % 100) < (PMUTACION * 100)) {
            Cromosoma mutante = padres[i];

            // Seleccionar ciudad aleatoria
            int ciudad = rand() % NUM_CIUDADES;

            // Apagar motorizado actual
            for (int mot = 0; mot < NUM_MOTORIZADOS; mot++) {
                mutante[mot][ciudad] = 0;
            }

            // Buscar motorizados válidos
            vector<int> motorizadosValidos;
            for (int mot = 0; mot < NUM_MOTORIZADOS; mot++) {
                if (costoCiudad[ciudad] + costoMotorizado[mot][ciudad] <= K) {
                    motorizadosValidos.push_back(mot);
                }
            }

            // Asignar nuevo motorizado
            if (motorizadosValidos.size() > 0) {
                int nuevoMot = motorizadosValidos[rand() % motorizadosValidos.size()];
                mutante[nuevoMot][ciudad] = 1;

                if (!esAberracion(mutante)) {
                    poblacion.push_back(mutante);
                }
            }
        }
    }
}

// Regenerar población
void regenerarPoblacion(vector<Cromosoma> &poblacion) {
    matarClones(poblacion);

    sort(poblacion.begin(), poblacion.end(),
        [](const Cromosoma &a, const Cromosoma &b) {
            return calculaFitness(a) < calculaFitness(b);
        }
    );

    if (poblacion.size() > NUM_INDIVIDUOS) {
        poblacion.erase(poblacion.begin() + NUM_INDIVIDUOS, poblacion.end());
    }
}

// Mostrar cromosoma como matriz
void mostrarCromosoma(Cromosoma cromosoma) {
    cout << "Matriz de asignación:" << endl;
    cout << "    ";
    for (int c = 0; c < NUM_CIUDADES; c++) {
        cout << nombresCiudades[c] << " ";
    }
    cout << endl;

    for (int mot = 0; mot < NUM_MOTORIZADOS; mot++) {
        cout << "M" << (mot+1) << ": ";
        for (int ciudad = 0; ciudad < NUM_CIUDADES; ciudad++) {
            cout << cromosoma[mot][ciudad] << " ";
        }
        cout << endl;
    }
}

// Mostrar mejor solución
void mostrarMejor(vector<Cromosoma> poblacion, int generacion) {
    Cromosoma mejor = poblacion[0];

    cout << "\n=== GENERACION " << generacion << " ===" << endl;
    cout << "Costo total minimo: " << calculaFitness(mejor) << " soles" << endl;
    cout << "\nAsignaciones:" << endl;
    cout << "Ciudad\tMotorizado\tCosto" << endl;

    for (int ciudad = 0; ciudad < NUM_CIUDADES; ciudad++) {
        int motorizado = obtenerMotorizado(mejor, ciudad);
        int costo = costoCiudad[ciudad] + costoMotorizado[motorizado][ciudad];
        cout << nombresCiudades[ciudad] << "\t"
             << (motorizado + 1) << "\t\t" << costo << endl;
    }

    cout << "\n";
    mostrarCromosoma(mejor);
}

// Algoritmo genético principal
void courierGenetico() {
    vector<Cromosoma> poblacion;

    generarPoblacion(poblacion);

    cout << "=== POBLACION INICIAL ===" << endl;
    mostrarMejor(poblacion, 0);

    for (int gen = 1; gen <= GENERACIONES; gen++) {
        vector<Cromosoma> padres;

        seleccion(poblacion, padres);
        casamiento(poblacion, padres);
        mutacion(poblacion, padres);
        regenerarPoblacion(poblacion);

        if (gen % 100 == 0 || gen == GENERACIONES) {
            mostrarMejor(poblacion, gen);
        }
    }

    cout << "\n=== SOLUCION FINAL ===" << endl;
    mostrarMejor(poblacion, GENERACIONES);
}

int main() {
    courierGenetico();
    return 0;
}