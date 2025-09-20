#include <iostream>
#include <iomanip>
using namespace std;

// Función que EXPLÍCITAMENTE verifica que ambas sumas sean iguales
bool puedeParticionarEnDos(int arr[], int n) {
    // Calcular suma total
    int sumaTotal = 0;
    for (int i = 0; i < n; i++) {
        sumaTotal += arr[i];
    }

    cout << "=== VERIFICACIÓN EXPLÍCITA ===" << endl;
    cout << "Suma total: " << sumaTotal << endl;

    // Si es impar, imposible
    if (sumaTotal % 2 != 0) {
        cout << "Suma impar → IMPOSIBLE partir en dos subconjuntos iguales" << endl;
        return false;
    }

    int objetivo = sumaTotal / 2;
    cout << "Objetivo: cada subconjunto debe sumar " << objetivo << endl;

    // DP para subset sum
    bool dp[n + 1][objetivo + 1];

    // Inicializar
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= objetivo; j++) {
            dp[i][j] = false;
        }
    }

    // Primera columna: suma 0 siempre posible
    for (int i = 0; i <= n; i++) {
        dp[i][0] = true;
    }

    // Llenar tabla
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= objetivo; j++) {
            dp[i][j] = dp[i-1][j]; // No incluir elemento
            if (j >= arr[i-1]) {
                dp[i][j] = dp[i][j] || dp[i-1][j - arr[i-1]]; // Incluir elemento
            }
        }
    }

    bool puedeFormarObjetivo = dp[n][objetivo];
    cout << "¿Existe subconjunto que suma " << objetivo << "? " << (puedeFormarObjetivo ? "SÍ" : "NO") << endl;

    if (!puedeFormarObjetivo) {
        cout << "No se puede formar subconjunto con suma " << objetivo << endl; //Es decir no hahy suma que de la mitad de la suma total
        return false;
    }

    // AQUÍ ESTÁ LA VERIFICACIÓN EXPLÍCITA QUE PEDÍAS
    cout << "\n--- VERIFICACIÓN MATEMÁTICA ---" << endl;
    cout << "Si existe subconjunto S1 que suma " << objetivo << endl;
    cout << "Entonces subconjunto S2 (resto) suma: " << sumaTotal << " - " << objetivo << " = " << (sumaTotal - objetivo) << endl;
    cout << "¿Son iguales? " << objetivo << " == " << (sumaTotal - objetivo) << " → " << (objetivo == sumaTotal - objetivo ? "SÍ" : "NO") << endl;

    return (objetivo == sumaTotal - objetivo);
}

// Función que encuentra los subconjuntos Y verifica sus sumas
void encontrarYVerificarSubconjuntos(int arr[], int n) {
    int sumaTotal = 0;
    for (int i = 0; i < n; i++) {
        sumaTotal += arr[i];
    }

    if (sumaTotal % 2 != 0) {
        cout << "No se puede particionar (suma impar)" << endl;
        return;
    }

    int objetivo = sumaTotal / 2;
    bool dp[n + 1][objetivo + 1];

    // Llenar tabla DP
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= objetivo; j++) {
            dp[i][j] = false;
        }
    }

    for (int i = 0; i <= n; i++) {
        dp[i][0] = true;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= objetivo; j++) {
            dp[i][j] = dp[i-1][j];
            if (j >= arr[i-1]) {
                dp[i][j] = dp[i][j] || dp[i-1][j - arr[i-1]];
            }
        }
    }

    if (!dp[n][objetivo]) {
        cout << "No existe subconjunto que sume " << objetivo << endl;
        return;
    }

    // Reconstruir subconjunto 1
    cout << "\n=== RECONSTRUCCIÓN Y VERIFICACIÓN EXPLÍCITA ===" << endl;

    int subconjunto1[n], subconjunto2[n];
    int tam1 = 0, tam2 = 0;
    bool usado[n];

    for (int i = 0; i < n; i++) {
        usado[i] = false;
    }

    // Backtrack
    int i = n, j = objetivo;
    cout << "Reconstruyendo subconjunto que suma " << objetivo << ":" << endl;
    while (i > 0 && j > 0) {
        if (dp[i-1][j]) {
            // No incluir arr[i-1]
            cout << "  No incluir " << arr[i-1] << " (viene de dp[" << (i-1) << "][" << j << "])" << endl;
        } else {
            // Incluir arr[i-1]
            cout << "  Incluir " << arr[i-1] << " (necesario para formar suma)" << endl;
            subconjunto1[tam1++] = arr[i-1];
            usado[i-1] = true;
            j -= arr[i-1];
        }
        i--;
    }

    // Formar subconjunto 2 con elementos restantes
    for (int k = 0; k < n; k++) {
        if (!usado[k]) {
            subconjunto2[tam2++] = arr[k];
        }
    }

    // VERIFICACIÓN EXPLÍCITA DE SUMAS
    cout << "\n--- VERIFICACIÓN EXPLÍCITA DE SUMAS ---" << endl;

    int suma1 = 0, suma2 = 0;

    cout << "Subconjunto 1: { ";
    for (int k = 0; k < tam1; k++) {
        cout << subconjunto1[k] << " ";
        suma1 += subconjunto1[k];
    }
    cout << "}" << endl;
    cout << "Suma del subconjunto 1: " << suma1 << endl;

    cout << "Subconjunto 2: { ";
    for (int k = 0; k < tam2; k++) {
        cout << subconjunto2[k] << " ";
        suma2 += subconjunto2[k];
    }
    cout << "}" << endl;
    cout << "Suma del subconjunto 2: " << suma2 << endl;

    // AQUÍ ESTÁ LA VERIFICACIÓN EXPLÍCITA
    cout << "\n🔍 VERIFICACIÓN FINAL:" << endl;
    cout << "¿suma1 == suma2? → " << suma1 << " == " << suma2 << " → " << (suma1 == suma2 ? "✅ SÍ" : "❌ NO") << endl;
    cout << "suma1 + suma2 = " << (suma1 + suma2) << " (debe ser " << sumaTotal << ")" << endl;

    if (suma1 == suma2 && suma1 + suma2 == sumaTotal) {
        cout << "✅ PARTICIÓN VÁLIDA CONFIRMADA" << endl;
    } else {
        cout << "❌ ERROR EN LA PARTICIÓN" << endl;
    }
}

// Demostración de por qué la verificación implícita funciona
void demostrarLogicaMatematica() {
    cout << "\n=== ¿POR QUÉ LA VERIFICACIÓN IMPLÍCITA FUNCIONA? ===" << endl;
    cout << "Teorema: Si suma_total es par y existe S1 ⊆ Array tal que sum(S1) = suma_total/2," << endl;
    cout << "entonces S2 = Array - S1 también suma suma_total/2" << endl << endl;

    cout << "Demostración:" << endl;
    cout << "1. Sea suma_total = suma de todos los elementos" << endl;
    cout << "2. Sea S1 un subconjunto que suma suma_total/2" << endl;
    cout << "3. Sea S2 = Array - S1 (elementos restantes)" << endl;
    cout << "4. sum(S1) + sum(S2) = suma_total (todos los elementos)" << endl;
    cout << "5. sum(S1) = suma_total/2 (por hipótesis)" << endl;
    cout << "6. Entonces: suma_total/2 + sum(S2) = suma_total" << endl;
    cout << "7. Por tanto: sum(S2) = suma_total - suma_total/2 = suma_total/2" << endl;
    cout << "8. Conclusión: sum(S1) = sum(S2) = suma_total/2 ✅" << endl << endl;

    cout << "Por eso NO necesitamos verificar explícitamente que sean iguales:" << endl;
    cout << "¡Es matemáticamente imposible que NO sean iguales!" << endl;
}

int main() {
    cout << "=== PARTITION EQUAL SUBSET SUM ===" << endl;
    cout << "Problema: Partir arreglo en dos subconjuntos de suma igual" << endl << endl;

    cout << string(60, '=') << endl;

    // Caso de prueba 1: POSIBLE
    cout << "\n--- CASO 1: PARTICIÓN POSIBLE ---" << endl;
    int arr1[] = {1, 5, 11, 5};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);

    cout << "Arreglo: { ";
    for (int i = 0; i < n1; i++) {
        cout << arr1[i] << " ";
    }
    cout << "}" << endl;

    bool resultado1 = puedeParticionarEnDos(arr1, n1);
    cout << "¿Se puede particionar? " << (resultado1 ? "SÍ" : "NO") << endl;

    if (resultado1) {
        encontrarYVerificarSubconjuntos(arr1, n1);
    }

    cout << "\n" << string(60, '=') << endl;

    // Caso de prueba 2: IMPOSIBLE (suma impar)
    cout << "\n--- CASO 2: PARTICIÓN IMPOSIBLE (suma impar) ---" << endl;
    int arr2[] = {1, 2, 3, 5};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

    cout << "Arreglo: { ";
    for (int i = 0; i < n2; i++) {
        cout << arr2[i] << " ";
    }
    cout << "}" << endl;

    bool resultado2 = puedeParticionarEnDos(arr2, n2);
    cout << "¿Se puede particionar? " << (resultado2 ? "SÍ" : "NO") << endl;

    cout << "\n" << string(60, '=') << endl;

    // Caso de prueba 3: IMPOSIBLE (suma par pero no existe subconjunto)
    cout << "\n--- CASO 3: PARTICIÓN IMPOSIBLE (no existe subconjunto) ---" << endl;
    int arr3[] = {1, 2, 5};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);

    cout << "Arreglo: { ";
    for (int i = 0; i < n3; i++) {
        cout << arr3[i] << " ";
    }
    cout << "}" << endl;

    bool resultado3 = puedeParticionarEnDos(arr3, n3);
    cout << "¿Se puede particionar? " << (resultado3 ? "SÍ" : "NO") << endl;

    cout << "\n=== CONCLUSIÓN ===" << endl;
    cout << "✅ Usamos programación dinámica (subset sum)" << endl;
    cout << "✅ Reducimos el problema: encontrar subconjunto que sume suma_total/2" << endl;
    cout << "✅ Complejidad: O(n × suma_total/2)" << endl;
    cout << "✅ Espacio: O(n × suma_total/2)" << endl;

    return 0;
}