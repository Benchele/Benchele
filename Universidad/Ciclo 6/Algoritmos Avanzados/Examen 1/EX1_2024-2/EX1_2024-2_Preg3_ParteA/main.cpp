#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

struct Subconjunto {
    int id;
    vector<int> elementos;
};

/*
 * ALGORITMO VORAZ PARA SET COVER
 *
 * Estrategia Greedy:
 * 1. Mantener un conjunto de elementos aún no cubiertos
 * 2. En cada iteración, seleccionar el subconjunto que cubra
 *    la MAYOR CANTIDAD de elementos nuevos (no cubiertos)
 * 3. Marcar esos elementos como cubiertos
 * 4. Repetir hasta cubrir todos los elementos
 *
 * Criterio voraz: Maximizar la cobertura en cada paso
 *
 * Complejidad: O(n * m * k) donde:
 * - n = número de subconjuntos
 * - m = tamaño del universo
 * - k = tamaño promedio de subconjuntos
 */

// Función para imprimir los resultados
void imprimirSolucion(vector<struct Subconjunto> solucion) {
    cout << "\n========================================" << endl;
    cout << "           SOLUCION ENCONTRADA          " << endl;
    cout << "========================================" << endl;

    // Mostrar cantidad de subconjuntos en la solución
    cout << "Cantidad de subconjuntos seleccionados: " << solucion.size() << endl;

    cout << "Subconjuntos elegidos:" << endl;
    for (Subconjunto s : solucion) {
        cout << "S" << s.id << " = {";
        // Imprimir elementos del subconjunto
        for (int j = 0; j < s.elementos.size(); j++) {
            if (j > 0) cout << ", ";  // Coma separadora (excepto antes del primero)
            cout << s.elementos[j];
        }
        cout << "}" << endl;
    }
}

int seleccionarConjuntos(int *universo, int tamUniverso, Subconjunto *subconjuntos, int n) {
    // Vector para rastrear qué elementos del universo ya están cubiertos
    // cubierto[i] = true significa que el elemento i ya fue cubierto
    vector<bool> cubierto(tamUniverso + 1, false); // tam + 1 para indexar directamente por valor

    // Contador de cuántos elementos ya cubrimos
    int elementosCubiertos = 0;

    // Vector para almacenar los subconjuntos seleccionados (STRUCT COMPLETO)
    vector<Subconjunto> solucion;

    // Vector para marcar qué subconjuntos ya fueron usados
    // usado[i] = true significa que subconjuntos[i] ya fue seleccionado
    vector<bool> usado(n, false);

    // LOOP PRINCIPAL: Repetir mientras falten elementos por cubrir
    while (elementosCubiertos < tamUniverso) {

        // Variables para rastrear el mejor subconjunto en esta iteración
        int mejorSubconjunto = -1;      // Índice del mejor subconjunto (-1 = ninguno)
        int maxNuevos = 0;              // Máximo de elementos nuevos cubiertos

        // FASE 1: Buscar el subconjunto que cubra MÁS elementos NUEVOS (elementos que aún no han sido cubiertos)
        for (int i = 0; i < n; i++) {
            if (usado[i]) continue; // Saltar subconjuntos que ya fueron seleccionados previamente

            // Contar cuántos elementos NUEVOS (no cubiertos) tiene este subconjunto
            int conteoNuevos = 0;

            // Revisar cada elemento del subconjunto actual
            for (int elemento : subconjuntos[i].elementos) {
                if (!cubierto[elemento]) { // Si este elemento AÚN NO está cubierto, contarlo
                    conteoNuevos++;
                }
            }

            // CRITERIO VORAZ: Si este subconjunto cubre más elementos nuevos que el mejor encontrado hasta ahora, actualizarlo
            if (conteoNuevos > maxNuevos) {
                maxNuevos = conteoNuevos;
                mejorSubconjunto = i;
            }
        }

        // FASE 2: Verificar si encontramos algún subconjunto útil
        // Si no encontramos ninguno (mejorSubconjunto == -1), significa que no podemos cubrir el universo completo con los subconjuntos dados
        if (mejorSubconjunto == -1) {
            cout << "ERROR: No se puede cubrir el universo completo" << endl;
            break;
        }

        // FASE 3: Guardar el mejor subconjunto encontrado
        solucion.push_back(subconjuntos[mejorSubconjunto]);

        // Marcarlo como usado para no volver a seleccionarlo
        usado[mejorSubconjunto] = true;

        // FASE 4: Actualizar el estado - marcar todos los elementos de este subconjunto como cubiertos
        for (int elemento : subconjuntos[mejorSubconjunto].elementos) {
            if (!cubierto[elemento]) { // Solo actualizar si el elemento NO estaba cubierto antes (evita contar duplicados)
                cubierto[elemento] = true;      // Marcar como cubierto
                elementosCubiertos++;           // Incrementar contador
            }
        }

        // Continuar al siguiente ciclo hasta cubrir todos los elementos
    }

    // Imprimir solución
    imprimirSolucion(solucion);

    return solucion[0].id;
}

void imprimirEncabezadoYDatos(int *universo, int tamUniverso, struct Subconjunto *subconjuntos, int n) {
    cout << "Set Cover Problem - Algoritmo Voraz" << endl;
    cout << "=====================================" << endl << endl;

    cout << "Universo U = {";
    for (int i = 0; i < tamUniverso; i++) {
        if (i > 0) cout << ", ";
        cout << universo[i];
    }
    cout << "}" << endl << endl;

    cout << "Subconjuntos disponibles:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "S" << subconjuntos[i].id << " = {";
        for (int j = 0; j < subconjuntos[i].elementos.size(); j++) {
            if (j > 0) cout << ", ";
            cout << subconjuntos[i].elementos[j];
        }
        cout << "}" << endl;
    }
    cout << endl;
}

int main() {
    int universo[] = {1, 2, 3, 4, 5, 6, 7};
    int tamUniverso = sizeof(universo) / sizeof(universo[0]);

    Subconjunto subconjuntos[] = {
        {1, {1, 2, 3}},
        {2, {2, 4, 5}},
        {3, {3, 5, 6}},
        {4, {6, 7}}
    };

    int n = sizeof(subconjuntos) / sizeof(subconjuntos[0]);

    imprimirEncabezadoYDatos(universo, tamUniverso, subconjuntos, n);

    // Resolver el problema
    seleccionarConjuntos(universo, tamUniverso, subconjuntos, n);

    return 0;
}