#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

////////////////////////////////////////////////////////////////////
/////Version implicito

void generarParentesisImplicito(int n, int abiertos, int cerrados, string actual, vector<string> &resultado) {
    // CASO BASE: cuando tenemos 2*n caracteres (n aperturas + n cierres)
    if (actual.length() == 2 * n) {
        resultado.push_back(actual);  // Guardamos la combinación válida
        return;
    }

    // DECISIÓN 1: ¿Podemos agregar un paréntesis de apertura '('?
    // Regla: Solo si aún no hemos usado todos los n paréntesis de apertura
    if (abiertos < n) {
        // TODO: Llamada recursiva agregando '('
        generarParentesisImplicito(n, abiertos + 1, cerrados, actual + '(', resultado);
    }

    // DECISIÓN 2: ¿Podemos agregar un paréntesis de cierre ')'?
    // Regla: Solo si hay más aperturas que cierres (para mantener balance)
    if (cerrados < abiertos) {
        // TODO: Llamada recursiva agregando ')'
        generarParentesisImplicito(n, abiertos, cerrados + 1, actual + ')', resultado);
    }
}

////////////////////////////////////////////////////////////////////
/////Version explicito

void generarParentesisExplicito(int n, int abiertos, int cerrados, string &actual, vector<string> &resultado) {
    // CASO BASE: cuando tenemos 2*n caracteres (n aperturas + n cierres)
    if (actual.length() == 2 * n) {
        resultado.push_back(actual);  // Guardamos la combinación válida
        return;
    }

    // DECISIÓN 1: ¿Podemos agregar un paréntesis de apertura '('?
    // Regla: Solo si aún no hemos usado todos los n paréntesis de apertura
    if (abiertos < n) {
        // TODO: Llamada recursiva agregando '('
        actual += '(';  // Modifica
        generarParentesisExplicito(n, abiertos + 1, cerrados, actual, resultado);
        actual.pop_back();
    }

    // DECISIÓN 2: ¿Podemos agregar un paréntesis de cierre ')'?
    // Regla: Solo si hay más aperturas que cierres (para mantener balance)
    if (cerrados < abiertos) {
        // TODO: Llamada recursiva agregando ')'
        actual += ')';  // Modifica
        generarParentesisExplicito(n, abiertos, cerrados + 1, actual, resultado);
        actual.pop_back();
    }
}

int main() {
    int n = 3;  // Número de pares de paréntesis
    vector<string> resultado;  // Vector para guardar todas las combinaciones
    string actual = "";  // String vacío inicial

    // Llamada inicial: 0 abiertos, 0 cerrados, string vacío

    //Version backtracking implicito
    //generarParentesisImplicito(n, 0, 0, "", resultado);

    //Version backtracking explicito
    generarParentesisExplicito(n, 0, 0, actual, resultado);

    // Imprimir resultados
    cout << "Combinaciones para n = " << n << ":" << endl;
    for (int i = 0; i < resultado.size(); i++) {
        cout << resultado[i] << endl;
    }
    cout << "Total: " << resultado.size() << " combinaciones" << endl;

    return 0;
}