#include <iostream>
using namespace std;

// Función para verificar si un estado (máscara) es válido
bool esEstadoValido(int mask) {
    // Un estado es válido si no hay celdas sueltas
    // Todas las celdas vacías deben poder ser llenadas por bloques verticales (grupos de 4)
    int contador = 0;
    for (int i = 0; i < 4; i++) {
        if ((mask & (1 << i)) == 0) { // Si la posición i está vacía
            contador++;
        } else {
            // Si encontramos una celda ocupada, verificar que el contador sea múltiplo de 4
            if (contador % 4 != 0) return false;
            contador = 0;
        }
    }
    // Verificar el último grupo
    return (contador % 4 == 0);
}

// Función principal usando DP con bitmask
int contarFormasConMatriz(int n) {
    if (n == 0) return 1;

    // dp[fila][mask] = número de formas de llenar hasta la fila 'fila'
    // con el estado 'mask' en la fila actual
    // mask: cada bit representa si esa columna está ocupada por un bloque anterior
    int dp[n + 1][16]; // 16 = 2^4 (todos los estados posibles para 4 columnas)

    // Inicializar todo en 0
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < 16; j++) {
            dp[i][j] = 0;
        }
    }

    // Estado inicial: fila 0, ninguna columna ocupada
    dp[0][0] = 1;

    cout << "=== PROCESO DE LLENADO FILA POR FILA ===" << endl;
    cout << "Estados: 0=libre, 1=ocupado por bloque anterior" << endl;
    cout << "Área total a llenar: " << (n * 4) << " celdas" << endl;
    cout << "Cada bloque 1x4 ocupa 4 celdas" << endl << endl;

    for (int fila = 0; fila < n; fila++) {
        cout << "Procesando fila " << fila << ":" << endl;

        for (int maskActual = 0; maskActual < 16; maskActual++) {
            if (dp[fila][maskActual] == 0) continue;

            cout << "  Estado actual mask=" << maskActual << " (";
            for (int i = 3; i >= 0; i--) {
                cout << ((maskActual & (1 << i)) ? 1 : 0);
            }
            cout << ") con " << dp[fila][maskActual] << " formas" << endl;

            // Generar todos los posibles estados siguientes
            int maskSiguiente = 0;
            bool esValido = true;

            // Probar todas las combinaciones de llenar la fila actual
            for (int llenar = 0; llenar < 16; llenar++) {
                maskSiguiente = 0;
                esValido = true;

                // Verificar que no hay conflictos
                if ((maskActual & llenar) != 0) continue; // Conflicto: tratar de llenar celda ya ocupada

                int estadoCompleto = maskActual | llenar; // Estado después de colocar bloques

                // Verificar que todas las celdas están llenas
                if (estadoCompleto != 15) continue; // 15 = 1111 en binario

                // Calcular máscara para la siguiente fila
                for (int col = 0; col < 4; col++) {
                    if ((llenar & (1 << col)) && fila + 1 < n) {
                        // Esta posición fue llenada, puede generar estados futuros
                        // Por ahora, asumimos bloques horizontales (no afectan fila siguiente)
                    }
                }

                dp[fila + 1][maskSiguiente] += dp[fila][maskActual];

                cout << "    -> Transición a mask=" << maskSiguiente << " agregando " << dp[fila][maskActual] << " formas" << endl;
            }
        }
        cout << endl;
    }

    cout << "=== TABLA DP FINAL ===" << endl;
    cout << "Fila\\Mask\t";
    for (int j = 0; j < 16; j++) {
        cout << j << "\t";
    }
    cout << endl;

    for (int i = 0; i <= n; i++) {
        cout << i << "\t\t";
        for (int j = 0; j < 16; j++) {
            cout << dp[i][j] << "\t";
        }
        cout << endl;
    }

    return dp[n][0]; // Al final, no debe haber celdas ocupadas pendientes
}

// Versión más simple: considerar solo el área total
int contarFormasSimple(int n) {
    cout << "\n=== ANÁLISIS POR ÁREA ===" << endl;

    int areTotal = n * 4;
    int areaPorBloque = 4; // Cada bloque 1x4 ocupa 4 celdas

    cout << "Área total de la tabla: " << n << " x 4 = " << areTotal << " celdas" << endl;
    cout << "Área por bloque: 1 x 4 = " << areaPorBloque << " celdas" << endl;

    if (areTotal % areaPorBloque != 0) {
        cout << "IMPOSIBLE: El área total no es divisible por el área del bloque" << endl;
        return 0;
    }

    int numBloques = areTotal / areaPorBloque;
    cout << "Número de bloques necesarios: " << numBloques << endl << endl;

    // dp[i] = formas de llenar área i
    int dp[areTotal + 1];
    for (int i = 0; i <= areTotal; i++) dp[i] = 0;

    dp[0] = 1; // Una forma de llenar área 0

    cout << "Calculando formas por área:" << endl;
    for (int area = 0; area <= areTotal; area++) {
        if (dp[area] == 0) continue;

        cout << "Área " << area << ": " << dp[area] << " formas" << endl;

        // Colocar un bloque (ocupa 4 celdas)
        if (area + 4 <= areTotal) {
            dp[area + 4] += dp[area];
            cout << "  -> Colocar bloque: área " << (area + 4) << " += " << dp[area] << endl;
        }
    }

    return dp[areTotal];
}

// Función correcta usando DP de estados
int contarFormasCorrecta(int n) {
    cout << "\n=== SOLUCIÓN CORRECTA CON ESTADOS ===" << endl;

    // dp[i] = número de formas de llenar las primeras i filas completamente
    int dp[n + 1];
    for (int i = 0; i <= n; i++) dp[i] = 0;

    dp[0] = 1; // Una forma de llenar 0 filas

    for (int i = 1; i <= n; i++) {
        cout << "Calculando dp[" << i << "]:" << endl;

        // Opción 1: Colocar bloques horizontales (1x4 cada uno)
        // Un bloque horizontal llena una fila completa
        dp[i] += dp[i - 1];
        cout << "  Bloques horizontales: dp[" << i << "] += dp[" << (i-1) << "] = " << dp[i-1] << endl;

        // Opción 2: Colocar bloques verticales
        // Como cada bloque es 1x4, necesitamos rotarlo
        // Un bloque 1x4 rotado se convierte en 4x1
        // Para llenar 4 columnas, necesitamos 4 bloques 4x1, ocupando 4 filas
        if (i >= 4) {
            dp[i] += dp[i - 4];
            cout << "  Bloques verticales (4x1): dp[" << i << "] += dp[" << (i-4) << "] = " << dp[i-4] << endl;
        }

        cout << "  Total: dp[" << i << "] = " << dp[i] << endl << endl;
    }

    return dp[n];
}

int main() {
    cout << "=== PROBLEMA: Llenar tabla n x 4 con bloques 1 x 4 ===" << endl << endl;

    // Ejemplos del problema
    int ejemplos[] = {1, 2, 3, 4, 5};
    int numEjemplos = sizeof(ejemplos) / sizeof(ejemplos[0]);

    cout << "Verificando ejemplos dados:" << endl;
    for (int i = 0; i < numEjemplos; i++) {
        int n = ejemplos[i];
        int resultado = contarFormasCorrecta(n);
        cout << "n = " << n << ": " << resultado << " formas" << endl;
    }

    cout << "\n" << string(60, '=') << endl;

    // Análisis detallado para un caso específico
    cout << "\nAnálisis detallado para n = 5:" << endl;
    contarFormasSimple(5);

    cout << "\n" << string(60, '=') << endl;

    // Explicación de por qué necesitamos considerar áreas
    cout << "\n=== ¿POR QUÉ IMPORTAN LAS ÁREAS? ===" << endl;
    cout << "1. Cada bloque 1x4 ocupa exactamente 4 celdas" << endl;
    cout << "2. La tabla nxv4 tiene n*4 celdas totales" << endl;
    cout << "3. Para que sea posible llenarla, n*4 debe ser divisible por 4" << endl;
    cout << "4. Necesitamos n bloques en total para llenar la tabla" << endl;
    cout << "5. Los bloques pueden colocarse:" << endl;
    cout << "   - Horizontalmente: 1x4 (llena 1 fila)" << endl;
    cout << "   - Verticalmente: 4x1 (llena 4 filas, necesita 4 bloques)" << endl;

    return 0;
}