/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Restaurante.cpp
 * Author: Lenovo
 * 
 * Created on 13 de mayo de 2025, 09:42 AM
 */

#include <iostream>
#include <iomanip>
#include <cstring>
#include "Restaurante.h"
#include "FuncionesComunes.h"
#include "Cliente.h"
#include "Plato.h"
#include "Cliente.h"

#define INCREMENTO 5
#define NO_ENCONTRADO -1
#define MAX_LIN 166
using namespace std;

Restaurante::Restaurante() {
    incializa();
}

Restaurante::~Restaurante() {
    eliminar();
}

void Restaurante::incializa(){
    clientes = nullptr;
    platos = nullptr;
    cantidadDeClientes = 0;
    capacidadDeClientes = 0;
    cantidadDePlatos = 0;
    capacidadDePlatos = 0;
}

void Restaurante::eliminar(){
    if(clientes != nullptr)delete []clientes;
    if(platos != nullptr)delete[] platos;
}

void Restaurante::SetCapacidadDePlatos(int capacidadDePlatos) {
    this->capacidadDePlatos = capacidadDePlatos;
}

int Restaurante::GetCapacidadDePlatos() const {
    return capacidadDePlatos;
}

void Restaurante::SetCantidadDePlatos(int cantidadDePlatos) {
    this->cantidadDePlatos = cantidadDePlatos;
}

int Restaurante::GetCantidadDePlatos() const {
    return cantidadDePlatos;
}

void Restaurante::SetCapacidadDeClientes(int capacidadDeClientes) {
    this->capacidadDeClientes = capacidadDeClientes;
}

int Restaurante::GetCapacidadDeClientes() const {
    return capacidadDeClientes;
}

void Restaurante::SetCantidadDeClientes(int cantidadDeClientes) {
    this->cantidadDeClientes = cantidadDeClientes;
}

int Restaurante::GetCantidadDeClientes() const {
    return cantidadDeClientes;
}

//Sobrecargas
//Clientes
void Restaurante::operator <(const char*nombArch){ //Clientes.csv
    ifstream arch(nombArch, ios::in);
    verificar_Apertura_I(arch, nombArch);
    
    class Cliente cliente; //1 solo cliente, este llama al constructor
    while (true) { //Si se instancia en el while, va a estar creando y destruyendo -> Ineficiente
        arch>>cliente; //Aqui se pone el descuento, ya que en la siguiente iteracion va a sobreescribir sobre la misma clase, por eso es necesario igualar a 0.0 el descuento
        if(arch.eof())break;
        if(cantidadDeClientes == capacidadDeClientes)incrementarEspaciosCli();
        clientes[cantidadDeClientes] = cliente; //La cantidad de cliente lo tenemos como dato
        cantidadDeClientes++; //Si tenemos la cantidad de clientes y la capacidad no es necesario el terminador
    }
} 

void Restaurante::incrementarEspaciosCli(){
    class Cliente *aux;
    capacidadDeClientes += INCREMENTO;
    if(clientes == nullptr){
        clientes = new class Cliente[capacidadDeClientes]{};
    }
    else{
        aux = new class Cliente[capacidadDeClientes]{};
        for (int i = 0; i < cantidadDeClientes; i++) {
            aux[i] = clientes[i]; //Esta sobrecarga garantiza que los punteros no apunten al mismo dato
        }
        delete []clientes; //Para destruir todos los elementos del otro lado
        clientes = aux;
    }
}

//Platos
void Restaurante::operator <=(const char *nombArch){ //PlatosOfrecidos.csv
    ifstream arch(nombArch, ios::in);
    verificar_Apertura_I(arch, nombArch);
    
    class Plato plato; 
    while (true) { 
        arch>>plato;
        if(arch.eof())break;
        if(cantidadDePlatos == capacidadDePlatos)incrementarEspaciosPla();
        platos[cantidadDePlatos] = plato;
        cantidadDePlatos++;
    }
} 

void Restaurante::incrementarEspaciosPla(){
    class Plato *aux;
    capacidadDePlatos += INCREMENTO;
    if(platos == nullptr){
        platos = new class Plato[capacidadDePlatos]{};
    }
    else{
        aux = new class Plato[capacidadDePlatos]{};
        for (int i = 0; i < cantidadDePlatos; i++) {
            aux[i] = platos[i];
        }
        delete []platos;
        platos = aux;
    }
}

//Pedidos
/*
 961419,77324146,SA53764,9,AD90766,4,EN90758,1
 804501,71422479,PA39475,3,BR15760,1
*/

void Restaurante::operator <<=(const char *nombArch){//Pedidos.csv
    ifstream arch(nombArch, ios::in);
    verificar_Apertura_I(arch, nombArch);
    
    int numPed, dni, posCLi;
    while (true) {
        arch>>numPed;
        if(arch.eof())break;
        arch.get();
        arch>>dni;
        arch.get();
        posCLi = buscarCliente(dni);
        if(posCLi != NO_ENCONTRADO){
            completarAtributos(arch, posCLi);
        }
        else{
            while (arch.get() != '\n'); //Si no se encuentra al cliente pasa al siguiente
        }
    }
}

int Restaurante::buscarCliente(int dni){
    for (int i = 0; i < cantidadDeClientes; i++) {
        if(dni == clientes[i].GetDni())return i;
    }
    return NO_ENCONTRADO;
}

void Restaurante::completarAtributos(ifstream &arch, int posCLi){
    char codPla[8];
    int cant, posPla, cuantoQuedaPla, aten, noAten;
    
    while (true) {
        arch.getline(codPla, 8, ',');
        arch>>cant;
        posPla = buscarPlato(codPla);
        if(posPla != NO_ENCONTRADO){
            cuantoQuedaPla = platos[posPla].GetPreparados() - platos[posPla].GetAtendidos();
            if(cuantoQuedaPla < cant){
                aten = cuantoQuedaPla;
                noAten = cant - cuantoQuedaPla;
            }
            else{
                aten = cant;
                noAten = 0;
            }
        }
        
        clientes[posCLi].modifica(aten, platos[posPla].GetDescuento(), platos[posPla].GetPrecio());
        //En cliente se crea un metodo "modifica" que se encargue de cambiar los atributos correspondientes
        platos[posPla].modifica(aten, noAten, clientes[posCLi].GetDescuento());
        //En platos se crea un metodo "modifica" que se encargue de cambiar los atributos correspondientes
        
        //if(arch.get() == '\n')break;
        if(arch.get() != ',')break;
    }
}

int Restaurante::buscarPlato(char *codPla){
    char cod[8];
    for (int i = 0; i < cantidadDePlatos; i++) {
        platos[i].GetCodigo(cod);
        if(strcmp(codPla, cod) == 0)return i;
    }
    return NO_ENCONTRADO;
}

void Restaurante::operator>>(const char*nombArch){
    ofstream arch(nombArch, ios::out);
    if(not arch.is_open()){
        cout<<"ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    
    //arch<<fixed<<setprecision(2);
    arch.precision(2);
    arch<<fixed;
    
    arch<<setw(90)<<"RESTAURANTE 1INF25"<<endl;
    arch<<setw(88)<<"VENTAS DEL DIA"<<endl;
    
    //Imprime los platos
    imprimirLinea(arch, '=');
    arch<<setw(94)<<"RELACION DE PLATOS VENDIDOS"<<endl;
    imprimirLinea(arch, '=');
    
    arch<<right<<setw(112)<<"PLATOS"<<setw(37)<<"TOTAL"<<endl;
    arch<<left<<"No.  "<<setw(10)<<"CODIGO"<<setw(50)<<"NOMBRE"<<setw(9)
    <<"PRECIO"<<setw(12)<<"CATEGORIA"<<setw(11)<<"DESCUENTO"
    <<setw(12)<<"PREPARADOS"<<setw(11)<<"ATENDIDOS"
    <<setw(13)<<"NO ATENDIDOS"<<setw(12)<<"ESPERADO"
    <<setw(10)<<"BRUTO"<<setw(11)<<"NETO"<<endl;
    imprimirLinea(arch, '=');
    
    for (int i = 0; i <cantidadDePlatos; i++){
        arch<<right<<setw(3)<<i+1<<") ";
        arch<<platos[i];
    }
    
    //Imprime los clientes
    imprimirLinea(arch, '=');
    arch<<setw(96)<<"RELACION DE CLIENTES ATENDIDOS"<<endl;
    imprimirLinea(arch, '=');
    
    arch<<left<<"No.  "<<setw(10)<<"DNI"<<setw(38)<<"NOMBRE"
    <<setw(26)<<"DISTRITO"<<setw(11)<<"DESCUENTO"
    <<setw(10)<<"TOTAL PAGADO"<<endl;
    
    for (int i = 0; i <cantidadDeClientes; i++) {
        arch<<right<<setw(3)<<i+1<<") ";
        arch<<clientes[i];
    }
    
    imprimirLinea(arch, '=');
}

void Restaurante::imprimirLinea(ofstream &arch, char linea){
    for (int i = 0; i < MAX_LIN; i++)arch.put(linea);
    arch<<endl;
}
