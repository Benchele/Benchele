/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Cliente.cpp
 * Author: Lenovo
 * 
 * Created on 13 de mayo de 2025, 09:22 AM
 */

#include <iostream>
#include <iomanip>
#include <cstring>
#include "Cliente.h"
#include "Restaurante.h"
using namespace std;

Cliente::Cliente() {
    inicializa();
}

Cliente::Cliente(const Cliente& orig) {
    //Constructor copia -> Primero inicializar
    inicializa();
    *this = orig;
    
    //this es un puntero al objeto actual → tipo Cliente*
    //*this es una referencia al objeto actual → tipo Cliente&
}

Cliente::~Cliente() {
}

//Operaciones

void Cliente::inicializa(){
    nombre = nullptr;
    distrito = nullptr;
    descuento = 0.0;
    totalPagado = 0.0;    
}

void Cliente::elimina(){
    if(nombre != nullptr)delete nombre;
    if(distrito != nullptr)delete distrito;
}

void Cliente::operator = (const Cliente& orig){
    char aux[100];
    dni = orig.dni; 
    //Sacamos el nombre
    orig.GetNombre(aux);
    SetNombre(aux);
    orig.GetDistrito(aux);
    SetDistrito(aux);
    
    descuento = orig.descuento;
    totalPagado = orig.totalPagado;
}

void Cliente::SetTotalPagado(double totalPagado) {
    this->totalPagado = totalPagado;
}

double Cliente::GetTotalPagado() const {
    return totalPagado;
}

void Cliente::SetDescuento(double descuento) {
    this->descuento = descuento;
}

double Cliente::GetDescuento() const {
    return descuento;
}

void Cliente::SetDistrito(const char* dist) {
    if(distrito != nullptr){
        delete distrito;
    }
    distrito = new char[strlen(dist) + 1];
    strcpy(distrito, dist);
}

void Cliente::GetDistrito(char *dist) const {
    if(distrito == nullptr)dist[0] = 0;
    else strcpy(dist, distrito);
}

void Cliente::SetNombre(const char* nomb) {
    if(nombre != nullptr){
        delete nombre;
    }
    nombre = new char[strlen(nomb) + 1];
    strcpy(nombre, nomb);
}

void Cliente::GetNombre(char *nomb) const {
    if(nombre == nullptr)nomb[0] = 0;
    else strcpy(nomb, nombre);
}

void Cliente::SetDni(int dni) {
    this->dni = dni;
}

int Cliente::GetDni() const {
    return dni;
}

/*
 90367684,CORONEL CHUMPITAZ HELI,Villa Maria del Triunfo,S,13.04%
 99774549,HENRIQUEZ ESPINO BEATRIZ,San Borja,S,17.38%
 51465986,CAMACHO AGUERO ELIA ROSA,La Molina,N
*/

void operator >>(ifstream &arch, class Cliente &cliente){
    int dni;
    char aux[100]; //No está dentro de la clase cliente -> No tiene acceso a los atributos privados, todo a traves de los metodos selectores
    double desc;
    arch>>dni;
    if(arch.eof())return;
    arch.get();
    cliente.SetDni(dni);
    arch.getline(aux, 100, ',');
    cliente.SetNombre(aux);
    arch.getline(aux, 100, ',');
    cliente.SetDistrito(aux);
    if(arch.get() == 'S'){
        arch.get();
        arch>>desc;
        arch.get();
    }
    else{
        desc = 0.0; //Limpiar ya que puede haber quedado la lectura de otro descuento
    }
    cliente.SetDescuento(desc);
}

void Cliente::modifica(int aten, double desc, double prec){
    totalPagado += prec*aten*(1-desc/100.0)*(1-descuento/100.0);
}

void operator <<(ofstream &arch, class Cliente &cliente){ //&: Para no llamar al constructor copia porque si no despues se destruye todo por el destructor
    char nomb[60], dist[60];
    arch.precision(2);
    arch<<fixed;
    cliente.GetNombre(nomb);
    cliente.GetDistrito(dist);
    arch<<left<<setw(10)<<cliente.GetDni()<<setw(38)<<nomb<<setw(25)<<dist
        <<right<<setw(8)<<cliente.GetDescuento()<<'%'<<setw(13)
        <<cliente.GetTotalPagado()<<endl;
}

