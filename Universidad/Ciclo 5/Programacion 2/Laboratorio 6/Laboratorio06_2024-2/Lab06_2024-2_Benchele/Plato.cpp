/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Plato.cpp
 * Author: Lenovo
 * 
 * Created on 13 de mayo de 2025, 09:44 AM
 */

#include <iostream>
#include <iomanip>
#include <cstring>
#include <ratio>
#include "Plato.h"
using namespace std;

Plato::Plato() {
    inicializa();
}

Plato::Plato(const Plato& orig) {
    inicializa();
    *this = orig; //Sobre el objeto que lo llamó, *this llama al operador para copiar todos los datos
}

Plato::~Plato() {
    elimina();
}

//Operaciones fundamentales
void Plato::inicializa(){
    codigo = nullptr;
    nombre = nullptr;
    categoria = nullptr;
    atendidos = 0;
    noAtendidos = 0;
    totalEsperado = 0.0;
    totalBruto = 0.0;
    TotalNeto = 0.0;
}

void Plato::elimina(){
    if(codigo != nullptr)delete codigo;
    if(nombre != nullptr)delete nombre;
    if(categoria != nullptr)delete categoria;
}

void Plato::operator =(const class Plato &orig){
    char aux[100];
    orig.GetNombre(aux);
    SetNombre(aux);
    orig.GetCategoria(aux);
    SetCategoria(aux);
    orig.GetCodigo(aux);
    SetCodigo(aux);
    precio = orig.precio;
    preparados = orig.preparados;
    descuento = orig.descuento;
    atendidos = orig.atendidos;
    noAtendidos = orig.noAtendidos;
    totalEsperado = orig.totalEsperado;
    totalBruto = orig.totalBruto;
    TotalNeto = orig.TotalNeto;
}

void Plato::SetTotalNeto(double TotalNeto) {
    this->TotalNeto = TotalNeto;
}

double Plato::GetTotalNeto() const {
    return TotalNeto;
}

void Plato::SetTotalBruto(double totalBruto) {
    this->totalBruto = totalBruto;
}

double Plato::GetTotalBruto() const {
    return totalBruto;
}

void Plato::SetTotalEsperado(double totalEsperado) {
    this->totalEsperado = totalEsperado;
}

double Plato::GetTotalEsperado() const {
    return totalEsperado;
}

void Plato::SetNoAtendidos(int noAtendidos) {
    this->noAtendidos = noAtendidos;
}

int Plato::GetNoAtendidos() const {
    return noAtendidos;
}

void Plato::SetAtendidos(int atendidos) {
    this->atendidos = atendidos;
}

int Plato::GetAtendidos() const {
    return atendidos;
}

void Plato::SetDescuento(double descuento) {
    this->descuento = descuento;
}

double Plato::GetDescuento() const {
    return descuento;
}

void Plato::SetPreparados(int preparados) {
    this->preparados = preparados;
}

int Plato::GetPreparados() const {
    return preparados;
}

void Plato::SetCategoria(const char* cat) {
    if(categoria != nullptr){
        delete categoria;
    }
    categoria = new char[strlen(cat) + 1];
    strcpy(categoria, cat);
}

void Plato::GetCategoria(char *cat) const {
    if(categoria == nullptr){
        cat[0] = 0;
    }
    else{
        strcpy(cat, categoria);
    }
}

void Plato::SetPrecio(double precio) {
    this->precio = precio;
}

double Plato::GetPrecio() const {
    return precio;
}

void Plato::SetNombre(const char* nomb){
    if(nombre != nullptr){
        delete nombre;
    }
    nombre = new char[strlen(nomb) + 1];
    strcpy(nombre, nomb);
}

void Plato::GetNombre(char *nomb)  const {
    if(nombre == nullptr){
        nomb[0] = 0;
    }
    else{
        strcpy(nomb, nombre);
    }
}

void Plato::SetCodigo(const char* cod) {
    if(codigo != nullptr){
        delete codigo;
    }
    codigo = new char[strlen(cod) + 1];
    strcpy(codigo, cod);
}

void Plato::GetCodigo(char *cod) const {
    if(codigo == nullptr){
        cod[0] = 0;
    }
    else{
        strcpy(cod, codigo);
    }
}

/*
 AP31796,ANTICUCHO DE CORAZON AL PLATO,31.90,APERITIVO,43,19.94%
 EN77156,ENSALADA COSIDA GRANDE,22.90,ENSALADAS,54,13.52%
 AD31815,MOLLEJITAS AL PLATO,30.90,ADICIONAL,71
*/

void operator >>(ifstream &arch, class Plato &plato){
    int numPla;
    char aux[100], c; 
    double desc = 0.0; //No olvidarse porque siempre se tiene que inicializar para asegurarle un valor
    double precio;
    arch.getline(aux, 100, ',');
    if(arch.eof())return;
    plato.SetCodigo(aux);
    arch.getline(aux, 100, ',');
    plato.SetNombre(aux);
    arch>>precio;
    arch.get();
    plato.SetPrecio(precio);
    arch.getline(aux, 100, ',');
    plato.SetCategoria(aux);
    arch>>numPla;
    plato.SetPreparados(numPla);
    //if(arch.get() != '\n'){
    if(arch.get() == ','){
        arch>>desc;
        arch.get();
        arch.get();
    }
    
    plato.SetDescuento(desc);
    plato.SetTotalEsperado(numPla*precio);
}

void Plato::modifica(int atend, int noAtend, double desc){
    atendidos+=atend;
    noAtendidos += noAtend;
   totalBruto += atend*precio;
   TotalNeto += atend*precio*(1-desc/100.0)*(1-descuento/100.0);
   //Total esperado en la lectura
}

void operator<<(ofstream &arch, class Plato &plato){ //&: Para no llamar al constructor copia
    char cod[8],nomb[60], cat[20];
    arch.precision(2);
    arch<<fixed;
    plato.GetCodigo(cod);
    plato.GetNombre(nomb);
    plato.GetCategoria(cat);
    arch<<left<<setw(10)<<cod<<setw(47)<<nomb<<right<<setw(9)
        <<plato.GetPrecio()<<"   "<<left<<setw(12)<<cat<<right
        <<setw(7)<<plato.GetDescuento()<<'%'<<setw(10)<<plato.GetPreparados()
        <<setw(11)<<plato.GetAtendidos()<<setw(12)<<plato.GetNoAtendidos()
        <<setw(14)<<plato.GetTotalEsperado()<<setw(10)<<plato.GetTotalBruto()
        <<setw(10)<<plato.GetTotalNeto()<<endl;
}

