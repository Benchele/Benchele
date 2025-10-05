/* 
 * Archivo: ConjuntoDePlatos.cpp
 * Autor: Andrés Melgar
 * Fecha: 30 de agosto de 2024, 22:50
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include "ConjuntoDePlatos.hpp"
#include "AperturaDeArchivos.h"

using namespace std;

void cargar_conjunto_de_platos(ConjuntoDePlatos &conjuntoDePlatos, const char *nombre_de_archivo) {
    ifstream archivo_de_platos;
    AperturaDeUnArchivoDeTextosParaLeer(archivo_de_platos, nombre_de_archivo);
    archivo_de_platos >> conjuntoDePlatos;
    archivo_de_platos.close();
}

void operator>>(istream &archivo_de_platos, ConjuntoDePlatos &conjuntoDePlatos) {
    //1.- Declarar buffer
    struct Plato buffPlato[150]{};

    //2.- Lectura del archivo
    int i = 0;
    while (archivo_de_platos>>buffPlato[i])i++;
    //for (i = 0;archivo_de_platos>>buffPlato[i]; i++);
    
    //3.- Cargar arreglos
    int n = i;
    conjuntoDePlatos.conjunto_de_datos = new struct Plato[n + 1]{};
    for (int i = 0; i < n; i++) {
        conjuntoDePlatos.conjunto_de_datos[i] = buffPlato[i];
    }
    conjuntoDePlatos.cantidad = n;
}

void liberar_conjunto_de_platos(ConjuntoDePlatos &conjuntoDePlatos) {
    if(conjuntoDePlatos.conjunto_de_datos != nullptr){
        for (int i = 0; i < conjuntoDePlatos.cantidad; i++) {
            delete conjuntoDePlatos.conjunto_de_datos[i].codigo;
            delete conjuntoDePlatos.conjunto_de_datos[i].nombre;
            delete conjuntoDePlatos.conjunto_de_datos[i].tipo;
        }
        delete conjuntoDePlatos.conjunto_de_datos;
        conjuntoDePlatos.cantidad = 0;
    }
}

double operator+=(const ConjuntoDePlatos &conjuntoDePlatos, const char *codigo) {    
    for (int i = 0; i < conjuntoDePlatos.cantidad; i++) {
        if (strcmp(conjuntoDePlatos.conjunto_de_datos[i].codigo, codigo) == 0)
            return conjuntoDePlatos.conjunto_de_datos[i].precio;
    }
}

char* operator==(const ConjuntoDePlatos &conjuntoDePlatos, const char *codigo) {
    for (int i = 0; i < conjuntoDePlatos.cantidad; i++) {
        if (strcmp(conjuntoDePlatos.conjunto_de_datos[i].codigo, codigo) == 0)
            return conjuntoDePlatos.conjunto_de_datos[i].nombre;
    }
    return nullptr;
}