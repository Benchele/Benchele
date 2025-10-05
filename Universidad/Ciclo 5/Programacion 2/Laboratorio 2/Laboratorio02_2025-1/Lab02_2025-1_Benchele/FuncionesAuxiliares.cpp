/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FuncionesAuxiliares.cpp
 * Author: alulab14
 * 
 * Created on 25 de abril de 2025, 08:12 AM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "FuncionesAuxiliares.h"
#include "Conductores.h"
#include "Infracciones.h"
#include "Faltas.h"
#define NO_ENCONTRADO -1
#define INCREMENTO 2
#define MAX_LINEA 120
using namespace std;


//Comunes
char *leerCadenaExacta(ifstream &arch, char delimitador){
    char buff[200], *cad;
    arch.getline(buff, 200, delimitador);
    if(arch.eof())return nullptr;
    cad = new char[strlen(buff) + 1];
    strcpy(cad, buff);
    return cad;
}

//Para leer archivos
void verificarApeerturaI(ifstream &arch, const char*nombArch){
    if(not arch.is_open()){
        cout<<"ERROR: NO se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
}
void verificarApeerturaO(ofstream &arch, const char*nombArch){
    if(not arch.is_open()){
        cout<<"ERROR: NO se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
}

//Pregunta 1
//Cargar conductores
void cargarConductores(const char*nombArch, struct Conductores &conductores){  
    conductores += nombArch;
}

void operator+=(struct Conductores &conductores, const char*nombArch){
    ifstream arch(nombArch, ios::in);
    verificarApeerturaI(arch, nombArch);
    struct Conductores buffCon;
    
    //Buffers
    buffCon.dnis = new int[150]{};
    buffCon.nombres = new char*[150]{};
    //Auxiliares
    int dni;
    char *nomb;
    int numDat = 0;
    
    //Lectura archivo
    //12270502;CUEVA FUENTES CINTHIA DELIA
    while (true) {
        arch>>dni;
        if(arch.eof())break;
        arch.get();
        nomb = leerCadenaExacta(arch);
        buffCon.dnis[numDat] = dni;
        buffCon.nombres[numDat] = nomb;
        numDat++;
    }
    
    //Cargar arreglos
    cargarArreglos(conductores, buffCon, numDat);
}

void cargarArreglos(struct Conductores &conductores, struct Conductores buffCon, int numDat){
    conductores.dnis = new int[numDat+1]{};
    conductores.nombres = new char*[numDat+1]{};
    conductores.cantidad = numDat;
    for (int i = 0; i < numDat; i++) {
        conductores.dnis[i] = buffCon.dnis[i];
        conductores.nombres[i] = buffCon.nombres[i];
    }
    delete buffCon.dnis;
    delete buffCon.nombres;
}

//Cargar infracciones
void cargarInfracciones(const char*nombArch, struct Infracciones &infracciones){
    infracciones += nombArch;
}

void operator+=( struct Infracciones &infracciones, const char*nombArch){
    ifstream arch(nombArch, ios::in);
    verificarApeerturaI(arch, nombArch);
    
    //Buffer
    struct Infracciones buffInfr;
    buffInfr.codigos  = new int[150]{};
    buffInfr.descripciones  = new char*[150]{};
    buffInfr.tipos  = new char*[150]{};
    buffInfr.valores  = new double[150]{};
    
    //Auxiliares
    int cod;
    char *des, *tip;
    double val;
    int numDat = 0;
    
    //Lectura archivo
    //333;Operar maquinaria especial por la vía pública.;Muy Grave;474.00
    while (true) {
        arch>>cod;
        if(arch.eof())break;
        arch.get();
        des = leerCadenaExacta(arch, ';');
        tip = leerCadenaExacta(arch, ';');
        arch>>val;
        actualizarBuffer(buffInfr, numDat, cod, des, tip, val);
        numDat++;
    }
    
    //Cargar arreglos
    cargarArreglos(infracciones, buffInfr, numDat);
}

void actualizarBuffer(struct Infracciones &buffInfr, int numDat, int cod, char *des, 
                      char *tip, double val){
    buffInfr.codigos[numDat] = cod;
    buffInfr.descripciones[numDat] = des;
    buffInfr.tipos[numDat] = tip;
    buffInfr.valores[numDat] = val;
}

void cargarArreglos(struct Infracciones &infracciones, struct Infracciones buffInfr, 
                    int numDat){
    infracciones.codigos  = new int[numDat+1]{};
    infracciones.descripciones  = new char*[numDat+1]{};
    infracciones.tipos  = new char*[numDat+1]{};
    infracciones.valores  = new double[numDat+1]{};
    infracciones.cantidad = numDat;
    for (int i = 0; i < numDat; i++) {
        infracciones.codigos[i] = buffInfr.codigos[i];
        infracciones.descripciones[i] = buffInfr.descripciones[i];
        infracciones.tipos[i] = buffInfr.tipos[i];
        infracciones.valores[i] = buffInfr.valores[i];
    }
    delete buffInfr.codigos;
    delete buffInfr.descripciones;
    delete buffInfr.tipos;
    delete buffInfr.valores;
}

//Pregunta 2
//Cargar faltas
void cargar_faltas_de_los_conductores(const char*nombArch, const struct Conductores &conductores, 
                                      const struct Infracciones &infracciones, struct Faltas &faltas){
    ifstream arch(nombArch, ios::in);
    verificarApeerturaI(arch, nombArch);
    faltas.conductores = conductores;
    faltas.infracciones = infracciones;
    faltas.capacidades = nullptr;  //No es necesario
    faltas.placas = nullptr; //No es necesario
    
    //buff
    //Como ya tenemos la cantidad exacta de conductores, y como es falta por conductor
    faltas.placas = new char**[conductores.cantidad + 1]{};
    faltas.capacidades = new int[conductores.cantidad + 1]{};
    
    //Contadores
    int nd[conductores.cantidad + 1]{};
    //Aux
    int dniCon, codInfra, posCond;
    char *placa, c;
    int dd, mm, aa;
    
    //Lectura del archivo
    //81485316;J5T-691;24/12/2020;128
    while (true) {
        arch>>dniCon;
        if(arch.eof())break;
        arch.get();
        placa = leerCadenaExacta(arch, ';');
        arch>>dd>>c>>mm>>c>>aa>>c>>codInfra;
        posCond = buscarConductor(dniCon, conductores);
        if(posCond != NO_ENCONTRADO){
            //cout<<posCond<<endl;
            agregarPlacasInfra(faltas.placas[posCond], faltas.capacidades[posCond], nd[posCond],
                               placa);
        }
    }
}

int buscarConductor(int dniCon, const struct Conductores &conductores){
    for (int i = 0; conductores.dnis[i]; i++) {
        if(dniCon == conductores.dnis[i])return i;
    }
    return NO_ENCONTRADO;
}

void agregarPlacasInfra(char **&placas, int &capacidad, int &nd, char* placa){
    if(nd == capacidad){
        incremetarCapPlacasConInfra(placas, capacidad, nd);
    }
    actualizarValores(placas, placa, nd);
    nd++;
}

void incremetarCapPlacasConInfra(char **&placas, int &capacidad, int &numDat){
    char **aux;
    capacidad += INCREMENTO;
    if(placas == nullptr){
        placas = new char*[capacidad]{};
        numDat = 1;
    }
    else{
        aux = new char*[capacidad]{};
        for (int i = 0; i < numDat; i++)aux[i] = placas[i];
        delete placas;
        placas = aux;
    }
}

void actualizarValores(char **placas, char *placa, int nd){
    placas[nd - 1] = placa;
    //placas[nd] = nullptr; //No es necesario porque inicializo todo el arreglo con {}
}

//Pregunta 3
//IMpresion
void imprimir_faltas_de_los_conductores(const char*nombArch, const struct Faltas &faltas){
    ofstream arch(nombArch, ios::out);
    verificarApeerturaO(arch, nombArch);
    arch<<fixed<<setprecision(2);
    imprimirEncabezado(arch);
    for (int i = 0; i < faltas.conductores.cantidad; i++) {
        imprimirConductorYCantFaltas(arch, faltas.conductores.dnis[i], faltas.conductores.nombres[i],
                                     faltas.placas[i]);
    }
    imprimirLinea(arch, '=');
}

void imprimirConductorYCantFaltas(ofstream &arch, const int dniConductor, const char *nombConductor,
                                  char **placas){
    int cantInfra = 0;
    if(placas != nullptr){ //Si tiene placas
        while (placas[cantInfra])cantInfra++; 
    }

    arch<<dniConductor<<setw(8)<<" "<<left<<setw(60)<<nombConductor<<cantInfra<<endl;
}

void imprimirEncabezado(ofstream &arch){
    arch<<setw((MAX_LINEA+7)/2)<<"Reporte"<<endl;
    imprimirLinea(arch, '=');
    arch<<setw(8)<<"DNI"<<setw(16)<<"CLIENTE"<<setw(60)<<"CANT VEHICULOS"<<endl;
    imprimirLinea(arch, '-');
}

void imprimirLinea(ofstream &arch, char linea){
    for (int i = 0; i < MAX_LINEA; i++) arch.put(linea);
    arch<<endl;
}