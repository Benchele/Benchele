#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

struct Proyecto {
    int id;
    int costo;
    int ganancia;
    int beneficio;
    vector<int> predecesores;
};

bool compara(struct Proyecto k, struct Proyecto g) {
    return (double)k.ganancia*k.beneficio/k.costo > (double)g.ganancia*g.beneficio/g.costo; //Descendente (Mayor a menor)
}

bool verifica(struct Proyecto proyecto, vector<int> solucion) {
    if (!proyecto.predecesores.size()) { //Si no tiene predecesores
        //Tambien puede ser if(proyecto.predecesores.empty())
        return true;
    }

    int contador = 0; //Contador de predecesores encontrados en la solucion

    for (int k = 0; k < proyecto.predecesores.size(); k++) {
        for (int g = 0; g < solucion.size(); g++) {
            if (proyecto.predecesores[k] == solucion[g]) {
                contador++;
            }
        }
    }

    return contador == proyecto.predecesores.size(); //True: Si se encontraron todos los predecesores
}

int seleccionaProyectos(struct Proyecto *proyectos, int presupuesto, int n) {
    //Ordenamos de mayor a menor
    sort(proyectos, proyectos + n, compara);

    //Caso base
    int k = 0; //Indice del proyecto actual
    int costoParcial = 0;
    int ganancia = 0;

    vector<int> solucion; //Proyectos seleccionados - Se guarda el id

    //Con este metodo te ahorras un doble for

    //Copiamos los proyectos
    vector<struct Proyecto> cartera;
    cartera.insert(cartera.begin(), proyectos, proyectos + n); //Copia los proyectos al vector cartera

    //Mientras haya proyectos, el presupuesto no se haya agotado y la cartera no esté vacía
    while (k < n and costoParcial < presupuesto and !cartera.empty()) { //O cartera.size() > 0
        if (verifica(cartera[k], solucion) and (costoParcial + cartera[k].costo) <= presupuesto) {
            costoParcial += cartera[k].costo;
            ganancia += cartera[k].ganancia;
            solucion.push_back(cartera[k].id); //Agregamos el id del proyecto
            cartera.erase(cartera.begin() + k); //Eliminamos el proyecto de la cartera
            k = 0; //Reiniciamos el indice
        }
        else {
            k++; //Pasamos al siguiente proyecto
        }
    }

    cout << "Proyectos seleccionados: ";
    for (int g = 0; g < solucion.size(); g++) {
        cout << solucion[g] << " ";
    }
    cout << endl;

    cout << "Ganancia = " << ganancia << endl;

    return ganancia;
}
int main() {
    //Lo que se maximiza/lo que se minimiza

    struct Proyecto cartera[] = { //Cartera = conjunto de proyectos
        {1, 80, 150, 2, {}},
        {2, 20, 80, 5, {4}},
        {3, 100, 300, 1, {1, 2}},
        {4, 100, 150, 4, {}},
        {5, 50, 80, 2, {}},
        {6, 10, 50, 1, {2}},
        {7, 50, 120, 2, {6}},
        {8, 50, 150, 4, {6}},
    };

    int n = sizeof(cartera) / sizeof(cartera[0]);

    int presupuesto = 250;

    seleccionaProyectos(cartera, presupuesto, n);

    return 0;
}