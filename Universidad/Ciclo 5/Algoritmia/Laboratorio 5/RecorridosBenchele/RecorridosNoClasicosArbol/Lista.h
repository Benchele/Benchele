/* 
 * File:   Lista.h
 * Author: Lenovo
 */

#ifndef LISTA_H
#define LISTA_H

#include "Nodo.h"
struct Lista {
    struct Nodo * cabeza; /*apunta al inicio de la lista*/
    struct Nodo * cola; /*NEW   apunta al final de la lista*/
    int longitud; /*guarda la longitud de la lista*/
};

#endif /* LISTA_H */

