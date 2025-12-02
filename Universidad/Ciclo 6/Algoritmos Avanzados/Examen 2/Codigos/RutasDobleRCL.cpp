#include <iostream>
#include <iomanip>
#include <ctime>
#include <climits>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

#define ITERACIONES 1000
#define alfa 0.3

enum ciu{A, B, C, D};

struct Ciudad {
    int id;
    int costo;
};

struct Motorizado {
    int id;
    vector<int> costos;
};

struct MotorizadoPorCiudad {
    int id;
    int costo;
};

struct Solucion {
    int ciudad;
    int motorizado;
};

bool compara(struct Ciudad k, struct Ciudad g) {
    return k.costo > g.costo; //Descendente (Mayor a menor)
}

bool comparaM(struct MotorizadoPorCiudad k, struct MotorizadoPorCiudad g) {
    return k.costo < g.costo; //Ascendente (Menor a mayor)
}

bool comparaImpresion(struct Solucion k, struct Solucion g) {
    return k.ciudad < g.ciudad; //Ascendente (Menor a mayor)
}

int buscarIndice(vector<Ciudad> vCiudad, double RCL) {
    int cont = 0;

    for (int k = 0; k < vCiudad.size(); k++) {
        if (vCiudad[k].costo >= RCL) {
            cont++;
        }
    }

    return cont;
}

int buscarIndice(vector<MotorizadoPorCiudad> motorizadosPorCiudad, double RCL) {
    int cont = 0;

    for (int k = 0; k < motorizadosPorCiudad.size(); k++) {
        if (motorizadosPorCiudad[k].costo <= RCL) {
            cont++;
        }
    }

    return cont;
}

void asigacion(struct Ciudad *ciudades, int n, struct Motorizado *motorizados, int m, int limiteCosto) {
    vector<Solucion> mejorSolucion;

    int menorCosto = INT_MAX;

    srand(time(NULL)); //Semilla

    for (int k = 0; k < ITERACIONES; k++) {
        vector<Solucion> resultado;
        vector<Ciudad> vCiudad;
        vector<Motorizado> vMotorizados;

        //Copiamos
        vCiudad.insert(vCiudad.begin(), ciudades, ciudades + n);
        vMotorizados.insert(vMotorizados.begin(), motorizados, motorizados + m);

        int costoTotal = 0;

        //Ordenamos ciudad de mayor a menor costo
        sort(vCiudad.begin(), vCiudad.end(), compara);
        while (!vCiudad.empty()) {

            //Ciudades
            int betaCiudad = vCiudad[0].costo;
            int tauCiudad = vCiudad[vCiudad.size() - 1].costo;

            double RCLCiudad = betaCiudad - alfa * (betaCiudad - tauCiudad);

            int indCiudad = buscarIndice(vCiudad, RCLCiudad);

            if (indCiudad == 0) indCiudad = 1; // Evitando errores
            int indAleCiudad = rand() % indCiudad;

            struct Ciudad ciudadSeleccionada = vCiudad[indAleCiudad];

            //Elegir motorizado

            vector<MotorizadoPorCiudad> motorizadosPorCiudad;
            for (auto m : vMotorizados) { //Hallar todos los motorizados en la ciudad seleccionada
                motorizadosPorCiudad.push_back({m.id, m.costos[ciudadSeleccionada.id - 1]});
            }

            //Ordenamos de menor a mayor costo
            sort(motorizadosPorCiudad.begin(), motorizadosPorCiudad.end(), comparaM);

            int mejorCostoMotorizadoPorCiudad = INT_MAX;

            struct MotorizadoPorCiudad motorizadoElegido{};

            while (!motorizadosPorCiudad.empty()) { //GRASP para elegir el mejor motorizado
                int betaMotor = motorizadosPorCiudad[0].costo;
                int tauMotor = motorizadosPorCiudad[motorizadosPorCiudad.size() - 1].costo;

                double RCLMotor = betaMotor + alfa * (tauMotor - betaMotor);

                int indMotor = buscarIndice(motorizadosPorCiudad, RCLMotor);

                if (indMotor == 0) indMotor = 1;
                int indAleMotor = rand() % indMotor;

                //Verificar si cumple
                int costoParcial = (ciudadSeleccionada.costo + motorizadosPorCiudad[indAleMotor].costo);

                //Si es el mejor costo y no supera el limite
                if (costoParcial < mejorCostoMotorizadoPorCiudad and costoParcial <= limiteCosto) {
                    motorizadoElegido = motorizadosPorCiudad[indAleMotor];
                    mejorCostoMotorizadoPorCiudad = costoParcial;
                }

                //Eliminamos al motorizado
                motorizadosPorCiudad.erase(motorizadosPorCiudad.begin() + indAleMotor);
            }

            resultado.push_back({ciudadSeleccionada.id, motorizadoElegido.id});
            costoTotal = mejorCostoMotorizadoPorCiudad;

            //Eliminamos la ciudad con el envio completado
            vCiudad.erase(vCiudad.begin() + indAleCiudad);
        }

        //Hallar el mejor
        if (costoTotal < menorCosto) {
            menorCosto = costoTotal;
            mejorSolucion.clear();
            mejorSolucion.insert(mejorSolucion.begin(), resultado.begin(), resultado.end());
            //O simplemente
            //mejorSolucion = resultado;
        }

        //El profe dijo que si es GRASP xd
    }

    //Impresion

    //Ordenamos por id ciudad
    sort(mejorSolucion.begin(), mejorSolucion.end(), comparaImpresion);

    string letras = {'A', 'B', 'C', 'D'};
    cout << "Ciudad" << setw(20) << "Motorizado" << endl;

    for (int k = 0; k < mejorSolucion.size(); k++) {
        cout << letras[mejorSolucion[k].ciudad - 1] << ": " << setw(18) << mejorSolucion[k].motorizado << endl;
    }
}

int main() {
    //Primer paso ciudad
    //Segundo paso motorizado

    struct Ciudad ciudades[] = {
        {1, 16},
        {2, 15},
        {3, 12},
        {4, 18}
    };

    int n = sizeof(ciudades)/sizeof(ciudades[0]);

    struct Motorizado motorizados[] = {
        {1, {3, 4, 5, 6}},
        {2, {5, 2, 3, 4}},
        {3, {7, 5, 4, 2}},
        {4, {8, 7, 5, 1}},
        {5, {4, 3, 7, 5}}
    };

    int m = sizeof(motorizados)/sizeof(motorizados[0]);

    int k = 20;

    asigacion(ciudades, n, motorizados, m, k);

    return 0;
}