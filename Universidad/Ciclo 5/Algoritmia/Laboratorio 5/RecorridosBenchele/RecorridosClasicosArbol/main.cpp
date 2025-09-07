/* 
 * File:   main.cpp
 * Author: Lenovo
 */

#include <iostream>
#include "ArbolBB.h"
#include "funcionesABB.h"
#include "Elemento.h"
#include "funcionesAB.h"
#include "Cola.h"
#include "funcionesCola.h"
#include "FuncionesAuxiliares.h"
using namespace std;

/*
 *  ARBOLES BINARIOS
 *  Clase ABB
 */



int main(int argc, char** argv) {

    //recorridoPreOrden(); //RID  //10 8 7 9 13 12 14
    //recorridoEnOrden(); //IRD   //7 8 9 10 12 13 14
    recorridoPostOrden(); //IDR   //7 9 8 12 14 13 10

    //Arbol usado
    /*  10
       /  \
      8    13
     / \   / \
    7  9 12 14
    */
    
    //I: Izquierda
    //R: Raíz
    //D: Derecha
    
    return 0;
}
