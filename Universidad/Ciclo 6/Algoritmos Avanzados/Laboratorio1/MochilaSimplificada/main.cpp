#include <iostream>
using namespace std;

// Variables globales para guardar soluciones
int lista[50];   // almacena los elementos del subconjunto actual
int y = 0;       // índice para "lista"
int x = 0;       // contador de soluciones

// Función backtracking (Subset Sum)
int empaca(int i, int n, int peso, int p[]) {
    // Caso de corte: fuera de rango o peso negativo
    if (i == n || peso < 0)
        return 0;

    // Caso solución directa: encontramos un elemento que completa el peso
    if (p[i] == peso) {
        lista[y] = p[i];
        cout << "Resultado " << ++x << ": ";
        for (int k = 0; k <= y; k++)
            cout << lista[k] << " ";
        cout << endl;
    }

    // Incluimos el elemento actual en la lista // Agrego p[i] a la lista
    lista[y++] = p[i];
    empaca(i + 1, n, peso - p[i], p);  // rama "con p[i]" // Exploro con ese elemento incluido
    y--;  // retrocedemos // Retroceso: lo saco de la lista

    // Excluimos el elemento actual
    empaca(i + 1, n, peso, p);  // rama "sin p[i]"

    return 0;
}

// Programa principal
int main() {
    int n, peso;

    cout << "Ingrese cantidad de elementos: ";
    cin >> n;

    int p[n];
    cout << "Ingrese los elementos: ";
    for (int i = 0; i < n; i++) cin >> p[i];

    cout << "Ingrese peso objetivo: ";
    cin >> peso;

    cout << "\nSubconjuntos que suman " << peso << ":\n";
    empaca(0, n, peso, p);

    if (x == 0)
        cout << "No se encontro ningun subconjunto." << endl;

    return 0;
}
