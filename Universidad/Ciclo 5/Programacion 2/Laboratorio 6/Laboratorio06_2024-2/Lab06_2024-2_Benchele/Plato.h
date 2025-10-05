/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   Plato.h
 * Author: Lenovo
 *
 * Created on 13 de mayo de 2025, 09:44 AM
 */

#ifndef PLATO_H
#define PLATO_H

#include <fstream>
using namespace std;

class Plato {
private:
    char *codigo;
    char *nombre;
    double precio;
    char *categoria;
    int preparados;
    double descuento;
    int atendidos;
    int noAtendidos;
    double totalEsperado;
    double totalBruto;
    double TotalNeto;
public:
    Plato();
    Plato(const Plato& orig);
    virtual ~Plato();
    
    //Operaciones fundamentales
    void inicializa();
    void elimina();
    void operator =(const class Plato &orig);
    
    //Getters y setters
    void SetTotalNeto(double TotalNeto);
    double GetTotalNeto() const;
    void SetTotalBruto(double totalBruto);
    double GetTotalBruto() const;
    void SetTotalEsperado(double totalEsperado);
    double GetTotalEsperado() const;
    void SetNoAtendidos(int noAtendidos);
    int GetNoAtendidos() const;
    void SetAtendidos(int atendidos);
    int GetAtendidos() const;
    void SetDescuento(double descuento);
    double GetDescuento() const;
    void SetPreparados(int preparados);
    int GetPreparados() const;
    void SetCategoria(const char* categoria);
    void GetCategoria(char *) const;
    void SetPrecio(double precio);
    double GetPrecio() const;
    void SetNombre(const char* nombre);
    void GetNombre(char *) const;
    void SetCodigo(const char* codigo);
    void GetCodigo(char *) const;

    void modifica(int atend, int noAtend, double desc);
};

void operator >>(ifstream &arch, class Plato &plato);
void operator<<(ofstream &arch, class Plato &plato); //&: Para no llamar al constructor copia

#endif /* PLATO_H */

