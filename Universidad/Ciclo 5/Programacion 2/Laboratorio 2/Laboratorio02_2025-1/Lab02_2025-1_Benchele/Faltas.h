/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   faltas.h
 * Author: alulab14
 *
 * Created on 25 de abril de 2025, 08:10 AM
 */

#ifndef FALTAS_H
#define FALTAS_H

#include "Conductores.h"
#include "Infracciones.h"

struct Faltas{
    Conductores conductores;
    Infracciones infracciones;
    char ***placas;
    int *capacidades;
};

#endif /* FALTAS_H */

