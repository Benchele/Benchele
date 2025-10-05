/* 
 * Archivo: ConjuntoDeRepartidores.cpp
 * Autor: Andrés Melgar
 * Fecha: 31 de agosto de 2024, 00:44
 */

#include <iostream>
#include <fstream>
#include "ConjuntoDeRepartidores.hpp"
#include "AperturaDeArchivos.h"

using namespace std;

void cargar_conjunto_de_repartidores(ConjuntoDeRepartidores &conjuntoDeRepartidores, const char *nombre_de_archivo){
    ifstream archivo_de_repartidores;
    AperturaDeUnArchivoDeTextosParaLeer(archivo_de_repartidores, nombre_de_archivo);
    archivo_de_repartidores >> conjuntoDeRepartidores;
    archivo_de_repartidores.close();
}

void operator>>(istream &archivo_de_repartidores, ConjuntoDeRepartidores &conjuntoDeRepartidores){   
    //1.- Declarar buffer
    struct Repartidor buffRep[50]{};
    int i = 0;
    
    //2.- Lectura del archivo
    while (archivo_de_repartidores>>buffRep[i])i++;
    int n = i;
    
    //3.- Carga arreglo
    conjuntoDeRepartidores.conjunto_de_datos = new struct Repartidor[n];
    for (int i = 0; i < n; i++) {
        conjuntoDeRepartidores.conjunto_de_datos[i] = buffRep[i];
    }
    conjuntoDeRepartidores.cantidad = n;
}

void liberar_conjunto_de_repartidores(ConjuntoDeRepartidores &conjuntoDeRepartidores){
    if(conjuntoDeRepartidores.conjunto_de_datos != nullptr){
        for (int i = 0; i < conjuntoDeRepartidores.cantidad; i++) {
            delete conjuntoDeRepartidores.conjunto_de_datos[i].codigo;
            delete conjuntoDeRepartidores.conjunto_de_datos[i].nombre;
            delete conjuntoDeRepartidores.conjunto_de_datos[i].vehiculo;
        }
        delete conjuntoDeRepartidores.conjunto_de_datos;
        conjuntoDeRepartidores.cantidad = 0;
    }
}