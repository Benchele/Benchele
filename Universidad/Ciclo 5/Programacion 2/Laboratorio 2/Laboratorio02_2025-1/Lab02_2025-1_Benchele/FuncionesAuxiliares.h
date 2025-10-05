/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FuncionesAuxiliares.h
 * Author: alulab14
 *
 * Created on 25 de abril de 2025, 08:12 AM
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

#include <fstream>
using namespace std;

//Para leer archivos
void verificarApeerturaI(ifstream &arch, const char*nombArch);
void verificarApeerturaO(ofstream &arch, const char*nombArch);

//Comunes
char *leerCadenaExacta(ifstream &arch, char delimitador = '\n');

//Cargar conductores
void cargarConductores(const char*nombArch, struct Conductores &conductores);
void operator+=(struct Conductores &conductores, const char*nombArch);
void cargarArreglos(struct Conductores &conductores, struct Conductores buffCon, int numDat);

//Cargar infracciones
void cargarInfracciones(const char*nombArch, struct Infracciones &infracciones);
void operator+=( struct Infracciones &infracciones, const char*nombArch);
void actualizarBuffer(struct Infracciones &buffInfr, int numDat, int cod, char *des, 
                      char *tip, double val);
void cargarArreglos(struct Infracciones &infracciones, struct Infracciones buffInfr, 
                    int numDat);

//Pregunta 2
//Cargar faltas
void cargar_faltas_de_los_conductores(const char*nombArch, const struct Conductores &conductores, 
                                      const struct Infracciones &infracciones, struct Faltas &faltas);
int buscarConductor(int dniCon, const struct Conductores &conductores);
void agregarPlacasInfra(char **&placas, int &capacidad, int &nd, char* placa);
void incremetarCapPlacasConInfra(char **&placas, int &capacidad, int &numDat);
void actualizarValores(char **placas, char *placa, int nd);
void cargaArreglos(struct Faltas &faltas, struct Faltas buffFaltas, int cantidadConductores);

//Pregunta 3
//IMpresion
void imprimir_faltas_de_los_conductores(const char*nombArch, const struct Faltas &faltas);
void imprimirEncabezado(ofstream &arch);
void imprimirLinea(ofstream &arch, char linea);
void imprimirConductorYCantFaltas(ofstream &arch, const int dniConductor, const char *nombConductor,
                                  char **placas);

#endif /* FUNCIONESAUXILIARES_H */
