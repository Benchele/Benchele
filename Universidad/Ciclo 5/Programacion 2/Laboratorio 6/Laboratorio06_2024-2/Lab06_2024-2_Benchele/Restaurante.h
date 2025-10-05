/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   Restaurante.h
 * Author: Lenovo
 *
 * Created on 13 de mayo de 2025, 09:42 AM
 */

#ifndef RESTAURANTE_H
#define RESTAURANTE_H

#include "Cliente.h"
#include "Plato.h"

class Restaurante {
private:
    class Cliente *clientes; //Un arreglo, puede tener cientos de clientes
    int cantidadDeClientes;
    int capacidadDeClientes;
    class Plato *platos; //Un arreglo, puede tener cientos de platos
    int cantidadDePlatos;
    int capacidadDePlatos; 
    
public:
    Restaurante();
    
    //Clase maestra -> Se va a encargar de hacer toda la tarea
    
    virtual ~Restaurante();
    
    //Primero
    void incializa();
    void eliminar();
    
    //Metodos selectores
    //Los platos y clientes no tienen getters ni setters
    void SetCapacidadDePlatos(int capacidadDePlatos);
    int GetCapacidadDePlatos() const;
    void SetCantidadDePlatos(int cantidadDePlatos);
    int GetCantidadDePlatos() const;
    void SetCapacidadDeClientes(int capacidadDeClientes);
    int GetCapacidadDeClientes() const;
    void SetCantidadDeClientes(int cantidadDeClientes);
    int GetCantidadDeClientes() const;
    
    //Sobrecargas
    //Clientes
    void operator <(const char*); //Clientes.csv
    void incrementarEspaciosCli();
    
    //Platos
    void operator <=(const char *); //PlatosOfrecidos.csv
    void incrementarEspaciosPla();
    
    //Pedidos
    void operator <<=(const char *); //Pedidos.csv
    
    //Operaciones
    int buscarCliente(int dni);
    void completarAtributos(ifstream &arch, int posCLi);
    int buscarPlato(char *codPla);
    
    //Reporte
    void operator>>(const char*nombArch);
    void imprimirLinea(ofstream &arch, char linea);
};

#endif /* RESTAURANTE_H */

