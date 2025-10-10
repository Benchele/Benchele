#include <iostream>
#include <iomanip>
using namespace std;

int calcularCombinaciones(int n) {
    // Estados: 0 = CC, 1 = CA, 2 = AC
    // dp[columna][estado] = número de formas de llenar hasta esa columna terminando en ese estado
    // Ahora los índices van de 0 a n-1 (columna 0 = primera columna real)
    int dp[n][3];

    // Caso base: primera columna (índice 0) puede tener cualquiera de los 3 estados
    dp[0][0] = 1; // CC
    dp[0][1] = 1; // CA
    dp[0][2] = 1; // AC

    // Matriz de transiciones válidas
    // transiciones[estado_anterior][estado_actual] = 1 si es válido, 0 si no
    int transiciones[3][3] = {
        {1, 1, 1},  // Desde CC puede ir a: CC, CA, AC
        {1, 0, 1},  // Desde CA puede ir a: CC, --, AC (no CA porque A-A horizontal)
        {1, 1, 0}   // Desde AC puede ir a: CC, CA, -- (no AC porque A-A horizontal)
    };

    // Llenar la tabla desde la segunda columna (índice 1) en adelante
    for (int columna = 1; columna < n; columna++) {
        for (int estado_actual = 0; estado_actual < 3; estado_actual++) {
            dp[columna][estado_actual] = 0; // Inicializar en 0

            // Sumar las formas de llegar desde cada estado anterior válido
            for (int estado_anterior = 0; estado_anterior < 3; estado_anterior++) {
                if (transiciones[estado_anterior][estado_actual] == 1) {
                    dp[columna][estado_actual] += dp[columna - 1][estado_anterior];
                }
            }
        }
    }

    // Impresión de la tabla
    cout << "Tabla de Programacion Dinamica:" << endl;
    cout << "Columna |  CC  |  CA  |  AC  | Total" << endl;
    cout << "--------|------|------|------|------" << endl;

    for (int col = 0; col < n; col++) {
        cout << setw(4) << (col + 1) << "    | ";
        int total = 0;
        for (int estado = 0; estado < 3; estado++) {
            cout << setw(4) << dp[col][estado] << " | ";
            total += dp[col][estado];
        }
        cout << setw(4) << total << endl;
    }
    cout << endl;

    // La respuesta está en la última columna (índice n-1)
    return dp[n-1][0] + dp[n-1][1] + dp[n-1][2];
}

int main() {
    int n;

    cout << "=== PROBLEMA DE JAULAS DE AVES ===" << endl;
    cout << "Estados por columna:" << endl;
    cout << "  CC = Canario arriba, Canario abajo" << endl;
    cout << "  CA = Canario arriba, Agapornis abajo" << endl;
    cout << "  AC = Agapornis arriba, Canario abajo" << endl;
    cout << "  AA = INVALIDO (agapornis adyacentes verticalmente)" << endl;
    cout << endl;
    cout << "Restriccion: No puede haber 2 agapornis adyacentes" << endl;
    cout << "(ni horizontal ni verticalmente)" << endl;
    cout << endl;

    cout << "Ingrese el numero de columnas (n): ";
    cin >> n;
    cout << endl;

    if (n <= 0) {
        cout << "El numero de columnas debe ser mayor a 0" << endl;
        return 1;
    }

    int combinaciones = calcularCombinaciones(n);

    cout << "Con n = " << n << " columnas se pueden formar " << combinaciones;
    if (combinaciones == 1) {
        cout << " combinacion valida" << endl;
    } else {
        cout << " combinaciones validas" << endl;
    }

    return 0;
}