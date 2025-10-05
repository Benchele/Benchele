/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: alulab14
 *
 * Created on 25 de abril de 2025, 08:06 AM
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "FuncionesAuxiliares.h"
#include "Conductores.h"
#include "Infracciones.h"
#include "Faltas.h"
using namespace std;

/*
 * Nombre: Benjhamin Ruiz VIgo
 * Codigo: 20232242
 */

int main(int argc, char** argv) {
    //Declaracion structs
    struct Conductores conductores;
    struct Infracciones infracciones;
    struct Faltas faltas;
    
    //Pregunta 1
    //Cargar conductores
    //conductores += "conductores.csv";
    cargarConductores("conductores.csv", conductores); 
    
    //Cargar infracciones
    //infracciones += "infracciones.csv";
    cargarInfracciones("infracciones.csv", infracciones);
    
    //Pregunta 2
    //Cargar faltas
    cargar_faltas_de_los_conductores("faltas.csv", conductores, infracciones, faltas);
    
    //Pregunta 3
    //IMpresion
    imprimir_faltas_de_los_conductores("Reporte.txt", faltas);
    
    return 0;
}

