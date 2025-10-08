#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

struct Paquete {
    int id;
    int peso;
};

struct Camion {
    int id;
    int capacidad;
    vector<int> paquetes;
};

bool compara(struct Paquete k, struct Paquete g) {
    return k.peso > g.peso; //Descendente
}

bool compara_2(struct Camion k, struct Camion g) {
    return k.capacidad < g.capacidad; //Ascendente
}

///////////Impresion
bool comparaCamionID(struct Camion k, struct Camion g) { //Para impresion
    return k.id < g.id;
}
bool compara_id(int k, int g) { //Para impresion
    return k < g; //Ascendente
}
////////////

int asignarPaquetes(struct Paquete *paquetes, struct Camion *camiones, int n, int m) {
    //Paquetes: De mayor a menor
    //Camiones: De menor a mayor

    //Ordenamos paquetes
    sort(paquetes, paquetes + n, compara);

    //Copia de los paquetes
    vector<struct Paquete> copia;
    copia.insert(copia.begin(), paquetes, paquetes + n);


    int indCamion = 0;
    int cantAgregados = 0;

    while (copia.size() > 0 and indCamion < m){ //Recorremos hasta que no haya paquetes porque en el enunciado dice "siempre existe la cantidad necesaria de camiones para transportar todos los paquetes"
        cantAgregados = 0;
        int cantPaq = copia.size(); //Actualizamos la cantidad de paquetes

        for (int g = 0; g < cantPaq; g++) { //Por cada paquete
            sort(camiones, camiones + m, compara_2); //Siempre el primer paquete es el minimo
            if (camiones[indCamion].capacidad == 0) { //Si ya no tiene capacidad pasar al siguiente
                indCamion++;
            }
            else {
                if (camiones[indCamion].capacidad - copia[g].peso >= 0) { //Si se puede llenar
                    camiones[indCamion].capacidad -= copia[g].peso;
                    camiones[indCamion].paquetes.push_back(copia[g].id); //Agrega el paquete al camion correspondiente
                    copia.erase(copia.begin() + g); //Saca el paquete porque ya esta dentro de un camion
                    cantAgregados++;
                }
            }
        }

        if (cantAgregados == 0) { //Si no se agregó nada es porque el camion minimo no puede soportor ni un paquete por lo tanto se va al siguiente camion
            indCamion++;
        }
    }


    //Impresion
    sort(camiones, camiones + m, comparaCamionID); //Ordenamos para la impresion
    for (int k = 0; k < m; k++) {
        sort(camiones[k].paquetes.begin(), camiones[k].paquetes.end(), compara_id); //Ordenamos por id para la impresion
        cout << "Camion " << camiones[k].id << ": ";
        if (camiones[k].paquetes.size() > 0) {
            for (int g = 0; g < camiones[k].paquetes.size(); g++) {
                if (g != 0)cout << ", ";
                cout << camiones[k].paquetes[g] << " ";
            }
        }
        else {
            cout << "Nada";
        }
        cout << endl;
    }

    return 1; //Termino la funcion correctamente
}

int main() {
    struct Paquete paquetes[] = {
        {1, 150},
        {2, 100},
        {3, 180},
        {4, 50},
        {5, 120},
        {6, 10}
    };

    int n = sizeof(paquetes)/sizeof(paquetes[0]);

    struct Camion camiones[] = {
        {1, 250, {}},
        {2, 200, {}},
        {3, 200, {}},
        {4, 100, {}},
        {5, 300, {}},
    };

    int m = sizeof(camiones)/sizeof(camiones[0]);

    asignarPaquetes(paquetes, camiones, n, m);

    return 0;
}