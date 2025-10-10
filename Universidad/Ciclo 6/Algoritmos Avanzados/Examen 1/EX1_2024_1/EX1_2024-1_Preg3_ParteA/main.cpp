#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

struct Pedido {
    int id;
    int dimension;
    int cantidad;
    int ganancia;
    double rentabilidad; // Ganancia por metro total del pedido
};

struct Barra {
    int id;
    int espacioDisponible;
    int desperdicio;
    vector<int> cortesRealizados; // Dimensiones de cortes realizados
};

// Comparador para ordenar pedidos por rentabilidad descendente
bool comparaPedido(struct Pedido k, struct Pedido g) {
    return k.rentabilidad > g.rentabilidad or
           (k.rentabilidad == g.rentabilidad and k.ganancia > g.ganancia); //Descendente (Mayor a menor)
}

// Comparador para imprimir barras por ID ascendente
bool comparaBarraId(struct Barra k, struct Barra g) {
    return k.id < g.id;
}

// Calcula la rentabilidad balanceando ganancia total y eficiencia
// Prioriza pedidos con buena ganancia pero también considera su tamaño
void calcularRentabilidad(struct Pedido *pedidos, int cantPedidos) {
    for (int i = 0; i < cantPedidos; i++) {
        // Usar ganancia total con un peso, y penalizar levemente pedidos muy pequeños
        // Esto balancea entre tomar pedidos rentables y pedidos con buena ganancia absoluta
        pedidos[i].rentabilidad = pedidos[i].ganancia * 1.0;
    }
}

// Verifica si realmente se puede atender el pedido usando el algoritmo real de empaque
// Esto evita problemas de fragmentación
bool puedeAtenderPedido(const Pedido& pedido, const Barra* barras, int cantBarras, int longitudBarra) {
    if (pedido.dimension > longitudBarra) {
        return false;
    }

    // Crear copia de barras con vector
    vector<Barra> barrasCopia;
    barrasCopia.insert(barrasCopia.begin(), barras, barras + cantBarras);

    int cantidadRestante = pedido.cantidad;

    // Simular el empaque con Best-Fit
    while (cantidadRestante > 0) {
        int mejorBarra = -1;
        int menorDesperdicio = longitudBarra + 1;

        for (int i = 0; i < cantBarras; i++) {
            if (barrasCopia[i].espacioDisponible >= pedido.dimension) {
                int desperdicioResultante = barrasCopia[i].espacioDisponible - pedido.dimension;
                if (desperdicioResultante < menorDesperdicio) {
                    menorDesperdicio = desperdicioResultante;
                    mejorBarra = i;
                }
            }
        }

        if (mejorBarra == -1) {
            return false; // No cabe en ninguna barra
        }

        // Simular el corte
        barrasCopia[mejorBarra].espacioDisponible -= pedido.dimension;
        cantidadRestante--;
    }

    return true;
}

// Atiende el pedido usando algoritmo Best-Fit para minimizar desperdicio
void atenderPedido(struct Pedido pedido, struct Barra *barras, int cantBarras) {
    int cantidadRestante = pedido.cantidad;

    // Para cada pieza del pedido, buscar la mejor barra (Best-Fit)
    while (cantidadRestante > 0) {
        int mejorBarra = -1;
        int menorDesperdicio = 1000000; // Valor inicial grande

        // Buscar la barra que deje el menor desperdicio al cortar esta pieza
        for (int i = 0; i < cantBarras; i++) {
            if (barras[i].espacioDisponible >= pedido.dimension) {
                int desperdicioResultante = barras[i].espacioDisponible - pedido.dimension;

                // Queremos minimizar el desperdicio resultante
                if (desperdicioResultante < menorDesperdicio) {
                    menorDesperdicio = desperdicioResultante;
                    mejorBarra = i;
                }
            }
        }

        // Realizar el corte en la mejor barra (debe existir porque ya validamos con puedeAtenderPedido)
        if (mejorBarra != -1) {
            barras[mejorBarra].cortesRealizados.push_back(pedido.dimension);
            barras[mejorBarra].espacioDisponible -= pedido.dimension;
            cantidadRestante--;
        } else {
            // Seguridad: si no hay barra disponible, salir del ciclo
            // Esto no debería ocurrir si puedeAtenderPedido funciona correctamente
            break;
        }
    }
}

int resolverProblema(struct Barra *barras, int cantBarras, struct Pedido *pedidos, int cantPedidos, int longitudBarra) {
    // Calcular rentabilidad (en este caso, priorizamos por ganancia total)
    calcularRentabilidad(pedidos, cantPedidos);

    // Ordenar pedidos por ganancia total descendente
    sort(pedidos, pedidos + cantPedidos, comparaPedido);

    int gananciaTotal = 0;
    vector<int> pedidosAtendidos;

    // Procesar cada pedido en orden de prioridad
    for (int i = 0; i < cantPedidos; i++) {
        // Verificar si se puede atender el pedido simulando el empaque real
        if (puedeAtenderPedido(pedidos[i], barras, cantBarras, longitudBarra)) {
            atenderPedido(pedidos[i], barras, cantBarras);
            gananciaTotal += pedidos[i].ganancia;
            pedidosAtendidos.push_back(pedidos[i].id);
        }
    }

    // Calcular desperdicios de barras usadas
    int barrasUsadas = 0;
    for (int i = 0; i < cantBarras; i++) {
        if (barras[i].espacioDisponible < longitudBarra) {
            barras[i].desperdicio = barras[i].espacioDisponible;
            barrasUsadas++;
        }
    }

    // IMPRIMIR RESULTADOS
    cout << "Ganancia Total: $" << gananciaTotal << " K" << endl;
    cout << "Pedidos Atendidos: ";
    for (int i = 0; i < pedidosAtendidos.size(); i++) {
        if (i != 0) cout << ", ";
        cout << pedidosAtendidos[i];
    }
    cout << endl;
    cout << "Barras Utilizadas: " << barrasUsadas << " de " << cantBarras << endl;

    cout << endl << "DESPERDICIO DE BARRAS UTILIZADAS" << endl;

    // Ordenar barras por ID para mostrar en orden
    sort(barras, barras + cantBarras, comparaBarraId);

    // Imprimir encabezado de tabla
    cout << "Barras      | ";
    for (int i = 0; i < min(15, barrasUsadas); i++) {
        cout << setw(3) << (i + 1) << " | ";
    }
    if (barrasUsadas > 15) cout << "...";
    cout << endl;

    cout << "Desperdicio | ";
    int desperdicioTotal = 0;
    int contadorBarras = 0;
    for (int i = 0; i < cantBarras && contadorBarras < barrasUsadas; i++) {
        if (barras[i].espacioDisponible < longitudBarra) {
            cout << setw(3) << barras[i].desperdicio << " | ";
            desperdicioTotal += barras[i].desperdicio;
            contadorBarras++;
            if (contadorBarras >= 15) {
                cout << "...";
                // Sumar desperdicios restantes
                for (int j = i + 1; j < cantBarras; j++) {
                    if (barras[j].espacioDisponible < longitudBarra) {
                        desperdicioTotal += barras[j].desperdicio;
                    }
                }
                break;
            }
        }
    }
    cout << endl;

    int metrosUtilizados = barrasUsadas * longitudBarra - desperdicioTotal;

    cout << endl << "RESUMEN" << endl;
    cout << "Metros utilizados: " << metrosUtilizados << " m" << endl;
    cout << "Desperdicio total: " << desperdicioTotal << " m" << endl;

    return gananciaTotal;
}

int main() {
    int longitudBarra = 10;
    int numBarras = 20;

    struct Barra barras[20]{};
    for (int i = 0; i < numBarras; i++) {
        barras[i].id = i + 1;
        barras[i].espacioDisponible = longitudBarra;
        barras[i].desperdicio = 0;
    }

    struct Pedido pedidos[] = {
        {1, 10, 5, 10, 0.0},   // Pedido 1: 10m x 5 unidades, $10K
        {2, 20, 10, 20, 0.0},  // Pedido 2: 20m x 10 unidades, $20K (imposible)
        {3, 1, 18, 15, 0.0},   // Pedido 3: 1m x 18 unidades, $15K
        {4, 3, 1, 5, 0.0},     // Pedido 4: 3m x 1 unidad, $5K
        {5, 1, 1, 2, 0.0}      // Pedido 5: 1m x 1 unidad, $2K
    };

    int numPedidos = sizeof(pedidos) / sizeof(pedidos[0]);

    cout << "Longitud de barra: " << longitudBarra << " m" << endl;
    cout << "Barras disponibles: " << numBarras << endl;
    cout << "Pedidos a procesar: " << numPedidos << endl;
    cout << endl;

    resolverProblema(barras, numBarras, pedidos, numPedidos, longitudBarra);

    return 0;
}