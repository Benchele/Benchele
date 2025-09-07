/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: alulab14
 *
 * Created on 11 de abril de 2025, 08:00 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;
#include "Estructura.h"
#include "Operadores.h"
#include <cstring>
#include "funciones.h"
/*
 * 
 */
int main(int argc, char** argv) {
    int dni[120];
    struct CadenaDeCaracteres conductor[120],placa[120];
    
    int numDat=0;
    
    leerDatos(dni,conductor,placa,numDat,"Infracciones de transito.txt");
    ordenarDatos(dni,conductor,placa,numDat);
    imprimirRep(dni,conductor,placa,numDat,"Reporte.txt");
    

    return 0;
}

