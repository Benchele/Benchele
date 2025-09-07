/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   funciones.h
 * Author: alulab14
 *
 * Created on 11 de abril de 2025, 09:37 AM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

void leerDatos(int * dni,struct CadenaDeCaracteres* conductor,
        struct CadenaDeCaracteres* placa,int &numDat,const char* nomb);
void imprimirRep(int * dni,struct CadenaDeCaracteres* conductor,
        struct CadenaDeCaracteres* placa,int numDat,const char* nomb);
void imprimirLinea(ofstream &archR,int len,char c);
void ordenarDatos(int * dni,struct CadenaDeCaracteres* conductor,
        struct CadenaDeCaracteres* placa,int &numDat);
void mayusMinus(char *cad);
#endif /* FUNCIONES_H */

