/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   Cliente.h
 * Author: Lenovo
 *
 * Created on 13 de mayo de 2025, 09:22 AM
 */

#ifndef CLIENTE_H
#define CLIENTE_H

#include <fstream>
using namespace std;

class Cliente {
    
private:
    int dni;
    char *nombre;
    char *distrito;
    double descuento;
    double totalPagado;
public:
    Cliente();
    Cliente(const Cliente& orig);
    virtual ~Cliente();
    
    //Operaciones
    void inicializa();
    void elimina();
    void operator = (const Cliente& orig);
    
    //Getters y setters
    void SetTotalPagado(double totalPagado);
    double GetTotalPagado() const;
    void SetDescuento(double descuento);
    double GetDescuento() const;
    void SetDistrito(const char* dist);
    void GetDistrito(char *dist) const;
    void SetNombre(const char* nomb);
    void GetNombre(char*nomb) const;
    
    void SetDni(int dni);
    int GetDni() const;

    void modifica(int aten, double desc, double prec);
};

void operator >>(ifstream &arch, class Cliente &cliente);
void operator <<(ofstream &arch, class Cliente &cliente); //&: Para no llamar al constructor copia porque si no despues se destruye todo por el destructor

#endif /* CLIENTE_H */

