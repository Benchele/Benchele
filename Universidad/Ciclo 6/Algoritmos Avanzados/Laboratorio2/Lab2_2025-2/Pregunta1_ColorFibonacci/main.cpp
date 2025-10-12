#include <iomanip>
#include <iostream>
using namespace std;

/*
 * ============================================================================
 * PROBLEMA: PINTAR FRANJAS CON RESTRICCIONES
 * ============================================================================
 *
 * Colores disponibles: Blanco (B), Azul (A), Rojo (R)
 *
 * Restricciones:
 * 1. No dos franjas consecutivas del mismo color
 * 2. El color Azul SIEMPRE debe estar entre Rojo-Blanco o Blanco-Rojo
 *    Es decir: ...R-A-B... o ...B-A-R... (el azul debe estar "entre" dos colores)
 *
 * ============================================================================
 * ESTRATEGIA: PROGRAMACIÓN DINÁMICA - DESCUBRIMIENTO DE PATRÓN FIBONACCI
 * ============================================================================
 *
 * ESTRUCTURA DE DATOS:
 * --------------------
 * f[n+1] donde:
 * - f[i] = número de formas distintas de pintar i franjas cumpliendo restricciones
 * - Usamos tamaño n+1 para incluir f[0] = 0 (caso base)
 *
 * OBSERVACIÓN CLAVE 1: EL ÚLTIMO COLOR NUNCA ES AZUL
 * -----------------------------------------------------
 * El azul debe estar "entre" dos colores diferentes, por lo tanto:
 * - Si n=1: solo puede ser B o R (no A)
 * - Si n≥2: el último color solo puede ser B o R (nunca A)
 *
 * OBSERVACIÓN CLAVE 2: SIMETRÍA ENTRE BLANCO Y ROJO
 * ---------------------------------------------------
 * Por las restricciones, el problema es SIMÉTRICO para B y R:
 * - Número de formas terminando en B = Número de formas terminando en R
 * - Por lo tanto: f(n) = 2 × (formas terminando en Blanco)
 *
 * DEDUCCIÓN DE LA FÓRMULA RECURSIVA:
 * -----------------------------------
 * Fijemos que la última franja (franja n) es BLANCA.
 * ¿Qué puede ser la franja anterior (franja n-1)?
 *
 * CASO 1: La franja n-1 es ROJA
 *     [...(n-2 franjas)...][R][B]
 *                           ↑  ↑
 *                         n-1  n
 *
 *     - Separamos la última franja B
 *     - Nos quedan n-1 franjas que deben terminar en R
 *     - Por simetría, formas que terminan en R = f(n-1)/2
 *     - Contribución: f(n-1)/2
 *
 * CASO 2: La franja n-1 es AZUL
 *     [...(n-2 franjas)...][R][A][B]
 *                           ↑  ↑  ↑
 *                         n-2 n-1 n
 *
 *     - El azul en n-1 DEBE venir después de R (para formar R-A-B)
 *     - Separamos las últimas 2 franjas [A][B]
 *     - Nos quedan n-2 franjas que deben terminar en R
 *     - Por simetría, formas que terminan en R = f(n-2)/2
 *     - Contribución: f(n-2)/2
 *
 * CASO 3: La franja n-1 es BLANCA
 *     [...][B][B]  ❌ INVÁLIDO (mismo color consecutivo)
 *
 * FÓRMULA:
 * --------
 * Formas terminando en Blanco = f(n-1)/2 + f(n-2)/2
 *
 * Como f(n) = 2 × (formas terminando en Blanco):
 * f(n) = 2 × [f(n-1)/2 + f(n-2)/2]
 * f(n) = f(n-1) + f(n-2)  ← ¡Secuencia de Fibonacci!
 *
 * CASOS BASE:
 * -----------
 * f(0) = 0  (no hay franjas, no hay formas)
 * f(1) = 2  (solo B o R, no puede ser A porque debe estar "entre" dos colores)
 *
 * ============================================================================
 */

int main() {
    //Sea f la función en donde se guardarán los resultados de la función
    //Debido a que necesito el f(0)=0, agregué un espacio a la cantidad de resultados que son posibles
    //de guardar.
    long long f[46]{};
    int n=45;

    //Casos bases
    f[0]=0; // 0 franjas → 0 formas
    f[1]=2; // 1 franja → 2 formas (B o R, no A)

    //Fórmula: f(n) = f(n-1) + f(n-2)
    // Interpretación:
    // - f(n-1): Formas donde agregamos una franja sin azul al final (B o R)
    // - f(n-2): Formas donde agregamos dos franjas al final con azul en medio
    //           (formando R-A-B o B-A-R)

    for(int k = 2; k <= n; k++) {
        f[k] = f[k-1] + f[k-2];
    }

    cout << f[n] << endl;

    int pruebas[5] = {1, 2, 3, 10, 45};

    cout << "Input  | Output" << endl;
    cout << "-------|---------------" << endl;
    for (int k = 0; k < 5; k++) {
        cout << setw(4) << pruebas[k] << "   | ";
        cout << setw(12) << f[pruebas[k]] << endl;
    }

    return 0;
}