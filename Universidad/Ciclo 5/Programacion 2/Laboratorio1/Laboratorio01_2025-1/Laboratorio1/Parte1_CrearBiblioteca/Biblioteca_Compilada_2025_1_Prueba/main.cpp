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
/*
 * 
 */
int main(int argc, char** argv) {
    int dni[10];
    struct CadenaDeCaracteres nomb[10],placa[10];
    struct CadenaDeCaracteres buff;
    int numDat=0;
    ifstream arch("Infracciones de transito.txt",ios::in);
    if(not arch.is_open()) exit(1);
    while(true){
        !nomb[numDat];
        !placa[numDat];
        arch>>dni[numDat];
        if(arch.eof()) break;
        int i=0;
        !buff;
        while((arch>>buff)==0){
            if(i==0) nomb[numDat]<=buff;
            else {
                nomb[numDat]+="_";
                nomb[numDat]+=buff;
            }
            
            i++;
        }
        arch>>placa[numDat];
        
        if(numDat==3) break;
        numDat++;
    }
    if(placa[0]>placa[1] or placa[0]>"W7C-957")
        placa[0]&&placa[1];
    if(placa[0]<placa[1] or placa[0]<"W7C-957")
        placa[0]&&placa[2];
    if(placa[0]==placa[1] or placa[0]=="W7C-957")
        placa[1]&&placa[2];
    
    ofstream archR("RepPrueba.txt",ios::out);
    archR<<dni[0]<<endl;
    archR<<nomb[0]<<endl;
    archR<<placa[0]<<endl;
    return 0;
}

