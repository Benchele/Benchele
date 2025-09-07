/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Operadores.h
 * Author: alulab14
 *
 * Created on 11 de abril de 2025, 08:01 AM
 */

#ifndef OPERADORES_H
#define OPERADORES_H

void operator ! (struct CadenaDeCaracteres &cadena);
void operator <= (struct CadenaDeCaracteres &cadena,const char* cad);
void operator <= (struct CadenaDeCaracteres &cadena, int espacio);
void operator <= (struct CadenaDeCaracteres &cad1,
        struct CadenaDeCaracteres cad2);
bool operator += (struct CadenaDeCaracteres &cadena,const char* cad);
bool operator += (struct CadenaDeCaracteres &cad1,
        struct CadenaDeCaracteres cad2);
int compare (struct CadenaDeCaracteres &cadena,const char* cad);
bool operator == (struct CadenaDeCaracteres &cadena,const char* cad);
bool operator > (struct CadenaDeCaracteres &cadena,const char* cad);
bool operator < (struct CadenaDeCaracteres &cadena,const char* cad);
int compare (struct CadenaDeCaracteres &cad1,
        struct CadenaDeCaracteres &cad2);
bool operator == (struct CadenaDeCaracteres &cad1,
        struct CadenaDeCaracteres &cad2);
bool operator > (struct CadenaDeCaracteres &cad1,
        struct CadenaDeCaracteres &cad2);
bool operator < (struct CadenaDeCaracteres &cad1,
        struct CadenaDeCaracteres &cad2);
int operator >> (ifstream &arch,struct CadenaDeCaracteres &cadena);
void operator && (struct CadenaDeCaracteres &cad1,
        struct CadenaDeCaracteres &cad2);
ofstream& operator << (ofstream &arch,struct CadenaDeCaracteres cadena);
#endif /* OPERADORES_H */

