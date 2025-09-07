/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file_header.cc to edit this template
 */

/* 
 * File:   FuncionesAuxiliares.cpp
 * Author: Lenovo
 * 
 * Created on 1 de julio de 2025, 09:37 PM
 */

#include <iostream>
#include <iomanip>
#include <ratio>
#include "ArbolBB.h"
#include "funcionesABB.h"
#include "funcionesAB.h"
#include "Elemento.h"
#include "Cola.h"
#include "funcionesCola.h"
#include "Pila.h"
#include "funcionesPila.h"
#include "FuncionesAuxiliares.h"
using namespace std;


////////////////////////////////////////////////////////////////////////////////
//////////////////Recorrido en Amplitud

NodoArbol *buscarNodo(NodoArbol *pArbol, int numero){
    if(pArbol == nullptr)return nullptr;
    
    while (pArbol) {
        if(pArbol->elemento.numero == numero)return pArbol;
        if(pArbol->elemento.numero < numero){
            pArbol = pArbol->derecha;
            
        }
        else{
            pArbol = pArbol->izquierda;
        }
    }
    return pArbol;
}

void recorridoEnAmplitud(ArbolBinarioBusqueda arbol){
    Cola cola;
    construir(cola);
    
    if(esArbolVacio(arbol.arbolBinario))return;
    
    NodoArbol *pRec = arbol.arbolBinario.raiz;
    Elemento temp;
    encolar(cola, pRec->elemento);
    
    while (!esColaVacia(cola)) {
        temp = desencolar(cola);
        pRec = buscarNodo(arbol.arbolBinario.raiz, temp.numero);
        
        if(pRec->izquierda)encolar(cola, pRec->izquierda->elemento);
        if(pRec->derecha)encolar(cola, pRec->derecha->elemento);
        
        cout << temp.numero <<endl;
    }

}

void recorridoEnAmplitud(){  
    struct ArbolBinarioBusqueda arbol;
    construir(arbol);
    
    Elemento temp;
    
    temp.numero = 10;
    insertar(arbol, temp);
    temp.numero = 8;
    insertar(arbol, temp);
    temp.numero = 13;
    insertar(arbol, temp);
    temp.numero = 12;
    insertar(arbol, temp);
    temp.numero = 14;
    insertar(arbol, temp);
    temp.numero = 7;
    insertar(arbol, temp);
    temp.numero = 9;
    insertar(arbol, temp);
    
    recorridoEnAmplitud(arbol);
}

////////////////////////////////////////////////////////////////////////////////
//////////////////Recorrido en Amplitud inverso

NodoArbol *buscarAmpli(NodoArbol *pArbol, int numero){
    if(pArbol == nullptr)return nullptr;
    
    while (pArbol) {
        if(pArbol->elemento.numero == numero)return pArbol;
        if(pArbol->elemento.numero < numero){
            pArbol = pArbol->derecha;
        }
        else{
            pArbol = pArbol->izquierda;
        }
    }
    return pArbol;

}
void recorridoEnAmplitudInverso(ArbolBinarioBusqueda arbol){
    if(esArbolVacio(arbol.arbolBinario))return;
    
    Cola cola;
    construir(cola);
    
    NodoArbol *pRec = arbol.arbolBinario.raiz;
    encolar(cola, pRec->elemento);
    
    Elemento temp;
    
    while (!esColaVacia(cola)) {
        temp = desencolar(cola);
        pRec = buscarAmpli(arbol.arbolBinario.raiz, temp.numero);
        
        if(pRec->derecha)encolar(cola, pRec->derecha->elemento);
        if(pRec->izquierda)encolar(cola, pRec->izquierda->elemento);
        
        cout << temp.numero << endl;
    }

}
void recorridoEnAmplitudInverso(){
    struct ArbolBinarioBusqueda arbol;
    construir(arbol);
    
    Elemento temp;
    
    temp.numero = 10;
    insertar(arbol, temp);
    temp.numero = 8;
    insertar(arbol, temp);
    temp.numero = 13;
    insertar(arbol, temp);
    temp.numero = 12;
    insertar(arbol, temp);
    temp.numero = 14;
    insertar(arbol, temp);
    temp.numero = 7;
    insertar(arbol, temp);
    temp.numero = 9;
    insertar(arbol, temp);
    
    
    recorridoEnAmplitudInverso(arbol);
}

////////////////////////////////////////////////////////////////////////////////
//////////////////Recorrido en Diagonal

NodoArbol *buscarNodoIterativo(NodoArbol *pArbol, int numero){
    if(pArbol == nullptr)return nullptr;
    
    while (pArbol) {
        if(pArbol->elemento.numero == numero)return pArbol;
        if(pArbol->elemento.numero < numero){
            pArbol = pArbol->derecha;
        }
        else{
            pArbol = pArbol->izquierda;
        }
    }
    return pArbol;
}
void recorridoDiagonal(ArbolBinarioBusqueda &arbol){
    Cola cola1;
    Cola cola2;
    
    if(esArbolVacio(arbol.arbolBinario))return;
    
    construir(cola1);
    construir(cola2);
    
    NodoArbol *pRec = arbol.arbolBinario.raiz;
    encolar(cola2, pRec->elemento);
    
    Elemento temp;
    
    while (!esColaVacia(cola2)) {
        temp = desencolar(cola2);
        pRec = buscarNodoIterativo(arbol.arbolBinario.raiz, temp.numero);
        
        while (pRec) {
            encolar(cola1, pRec->elemento);
            if(pRec->izquierda){
                encolar(cola2, pRec->izquierda->elemento);
            }
            pRec = pRec->derecha;
        }

    }
        
    while (!esColaVacia(cola1)) {
        temp = desencolar(cola1);
        cout << temp.numero << endl;
    }
}

void recorridoEnDiagonal(){
    struct ArbolBinarioBusqueda arbol;
    struct Elemento elemento;
    construir(arbol);
    
    elemento.numero = 100;
    insertar(arbol, elemento);
    elemento.numero = 50;
    insertar(arbol, elemento);
    elemento.numero = 150;
    insertar(arbol, elemento);
    elemento.numero = 125;
    insertar(arbol, elemento);
    elemento.numero = 175;
    insertar(arbol, elemento);
    elemento.numero = 200;
    insertar(arbol, elemento);
    elemento.numero = 25;
    insertar(arbol, elemento);
    elemento.numero = 75;
    insertar(arbol, elemento);
    elemento.numero = 40;
    insertar(arbol, elemento);
    
    //enOrden(arbol);
    
    recorridoDiagonal(arbol);
    
    cout << endl;
}


////////////////////////////////////////////////////////////////////////////////
//////////////////Recorrido en Diagonal Inverso

NodoArbol * buscarNodoIterativoOtro(NodoArbol *pArbol, int numero){
    if(pArbol == nullptr)return pArbol;
    
    while (pArbol) {
        if(pArbol->elemento.numero == numero)return pArbol;
        if(pArbol->elemento.numero < numero){
            pArbol = pArbol->derecha;
        }
        else{
            pArbol = pArbol->izquierda;
        }
    }
    return pArbol;

}
void recorridoEnDiagonalInverso(ArbolBinarioBusqueda arbol){
    if(esArbolVacio(arbol.arbolBinario))return;
    
    struct Cola cola;
    struct Pila pila;
    construir(cola);
    construir(pila);
    
    NodoArbol * pRec = arbol.arbolBinario.raiz;
    encolar(cola, pRec->elemento);
    
    Elemento temp;
    while (!esColaVacia(cola)) {
        temp = desencolar(cola);
        pRec = buscarNodoIterativoOtro(arbol.arbolBinario.raiz, temp.numero);
        
        while (pRec) {
            apilar(pila, pRec->elemento);
            if(pRec->izquierda)encolar(cola, pRec->izquierda->elemento);
            pRec = pRec->derecha;
        }
        
    }
    
    while (!esPilaVacia(pila)) {
        temp = desapilar(pila);
        cout << temp.numero << endl;
    }
}
void recorridoEnDiagonalInverso(){
    struct ArbolBinarioBusqueda arbol;
    struct Elemento elemento;
    construir(arbol);
    
    elemento.numero = 100;
    insertar(arbol, elemento);
    elemento.numero = 50;
    insertar(arbol, elemento);
    elemento.numero = 150;
    insertar(arbol, elemento);
    elemento.numero = 125;
    insertar(arbol, elemento);
    elemento.numero = 175;
    insertar(arbol, elemento);
    elemento.numero = 200;
    insertar(arbol, elemento);
    elemento.numero = 25;
    insertar(arbol, elemento);
    elemento.numero = 75;
    insertar(arbol, elemento);
    elemento.numero = 40;
    insertar(arbol, elemento);
    
    recorridoEnDiagonalInverso(arbol);
}