/* 
 * Archivo: ConjuntoDePedidos.cpp
 * Autor: Andrés Melgar
 * Fecha: 31 de agosto de 2024, 09:59
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <complex>
#include <cinttypes>
#include "ConjuntoDePedidos.hpp"
#include "Pedido.hpp"
#include "Comunes.hpp"
#include "ConjuntoDePlatos.hpp"
#include "AperturaDeArchivos.h"
#define MAX_LINEA 120
using namespace std;

void cargar_conjunto_de_pedidos(ConjuntoDePedidos &conjuntoDePedidos, const char *nombre_de_archivo) {
    ifstream archivo_de_pedidos;
    AperturaDeUnArchivoDeTextosParaLeer(archivo_de_pedidos, nombre_de_archivo);
    archivo_de_pedidos >> conjuntoDePedidos;
    archivo_de_pedidos.close();
}

void operator>>(istream &archivo_de_pedidos, ConjuntoDePedidos &conjuntoDePedidos) {
    //1.- Declarar buffer
    struct ConjuntoDePedidos buffPed;
    inicializar_buffer_de_conjunto_de_pedidos(buffPed, 200);
    
    //2.- Leer archivo
    struct Pedido auxPed;
    while (archivo_de_pedidos>>auxPed)buffPed<<auxPed;
    
    //3.- Carga de arreglos
    buffPed>>conjuntoDePedidos;
}

void inicializar_buffer_de_conjunto_de_pedidos(ConjuntoDePedidos &conjuntoDePedidos, int cantidad) {
    conjuntoDePedidos.enteros = new int*[cantidad];
    conjuntoDePedidos.cadenas = new char**[cantidad]; 
    conjuntoDePedidos.reales = nullptr; 
    for (int i=0; i<cantidad; i++){
        conjuntoDePedidos.enteros[i] = nullptr;
        conjuntoDePedidos.cadenas[i] = nullptr;
    }
}

void operator<<(ConjuntoDePedidos &buffer_de_conjuntoDePedidos, const Pedido &pedido) {
    int posCli;
    posCli = buscar_cliente(buffer_de_conjuntoDePedidos, pedido.dni_cliente);
    if(posCli != CLIENTE_NO_ENCONTRADO){
        modificarCliente(buffer_de_conjuntoDePedidos.enteros[posCli], buffer_de_conjuntoDePedidos.cadenas[posCli], pedido);
    }
    else{
        posCli = obtener_cantidad_cliente(buffer_de_conjuntoDePedidos);
        agregarCLiente(buffer_de_conjuntoDePedidos.enteros[posCli], buffer_de_conjuntoDePedidos.cadenas[posCli], pedido);
    }
}

void operator>>(const ConjuntoDePedidos &buffer_de_conjuntoDePedidos, ConjuntoDePedidos &conjuntoDePedidos) {
    int cantCli = obtener_cantidad_cliente(buffer_de_conjuntoDePedidos);
    conjuntoDePedidos.enteros = new int *[cantCli + 1]{};
    conjuntoDePedidos.cadenas = new char **[cantCli + 1]{};
    conjuntoDePedidos.reales = nullptr;
    
    for (int i = 0; i < cantCli; i++) {
        copiarEnteros(conjuntoDePedidos.enteros[i], buffer_de_conjuntoDePedidos.enteros[i]);
        copiarCadenas(conjuntoDePedidos.cadenas[i], buffer_de_conjuntoDePedidos.cadenas[i]);
    }
}

int buscar_cliente(const ConjuntoDePedidos &conjuntoDePedidos, int dni) {
    int i=0;
    while (conjuntoDePedidos.enteros[i] != nullptr) {
        int *bloque_de_enteros = conjuntoDePedidos.enteros[i];
        int dni_del_bloque = bloque_de_enteros[0];
        if (dni_del_bloque == dni)
            return i;
        i++;
    }
    return CLIENTE_NO_ENCONTRADO;
}

void operator++(ConjuntoDePedidos &conjuntoDePedidos) {
    struct ConjuntoDePlatos platos;
    cargar_conjunto_de_platos(platos, "platos.csv");
    int nd = 0, cantPed;
    while(conjuntoDePedidos.enteros[nd])nd++;
    conjuntoDePedidos.reales = new double *[nd + 1]{};
    for (int i = 0; conjuntoDePedidos.cadenas[i]; i++) {
        cantPed = contarDatosPed(conjuntoDePedidos.enteros[i]); 
        conjuntoDePedidos.reales[i] = new double[cantPed + 1]{};
        hallarPrecio(conjuntoDePedidos.enteros[i], conjuntoDePedidos.cadenas[i], conjuntoDePedidos.reales[i],
                     cantPed, platos);
    }

    //precio = conjuntoDePedidos += conjuntoDePedidos.
}

void operator++(ConjuntoDePedidos &conjuntoDePedidos, int) {
    ++conjuntoDePedidos;
}

void liberar_conjunto_de_pedidos(ConjuntoDePedidos &conjuntoDePedidos) {

}

void operator!(ConjuntoDePedidos &conjuntoDePedidos) {
    struct ConjuntoDePlatos platos;
    cargar_conjunto_de_platos(platos, "platos.csv");
    int numDat;
    for (int i = 0; conjuntoDePedidos.cadenas[i]; i++) {
        numDat = contarDatosPed(conjuntoDePedidos.enteros[i]);
        cambiarCodANom(conjuntoDePedidos.cadenas[i], platos, numDat);
    }
}

void operator*(const ConjuntoDePedidos &conjuntoDePedidos) {
    ofstream arch;
    int *pedido;
    char **pedCad;
    char nombArch[50];
    for (int i = 0; conjuntoDePedidos.enteros[i]; i++) {
        pedido = conjuntoDePedidos.enteros[i];
        pedCad = conjuntoDePedidos.cadenas[i];
        obtener_nombre_archivo(nombArch, pedido[0]);
        arch.open(nombArch, ios::out);
        arch<<fixed<<setprecision(2);
        imprimir_linea(arch);
        arch << setw(3) << " " << "D.N.I. CLIENTE: " << pedido[0] << endl;
        arch << "CODIGO REPARTIDOR: " << pedCad[0] << endl;
        imprimir_linea(arch);
        arch << "ITEM" << setw(8) << "PLATO" << setw(45) << "CANT" << setw(12)
                << "SUBTOTAL" << endl;
        imprimir_linea(arch, '-');
        imprimirDetalle(arch, conjuntoDePedidos.enteros[i], conjuntoDePedidos.cadenas[i], conjuntoDePedidos.reales[i]);
        arch.close();
    }
}

void obtener_nombre_archivo(char *nombre_archivo, int dni_numero) {
    char dni_cadena[9];
    mi_itoa(dni_numero, dni_cadena);
    strcpy(nombre_archivo, "comprobante/");
    strcat(nombre_archivo, dni_cadena);
    strcat(nombre_archivo, ".txt");
}

void imprimir_linea(ofstream &archDeReporte, char c) {
    for (int i = 0; i < MAXIMO_POR_LINEA; i++)
        archDeReporte << c;
    archDeReporte << endl;
}

int obtener_cantidad_cliente(const ConjuntoDePedidos &conjuntoDePedidos){
    int i=0;
    while (conjuntoDePedidos.enteros[i] != nullptr)
        i++;
    return i;
}

//Auxiliares
void agregarCLiente(int *&enteros, char**&cadenas, const struct Pedido &pedido){
    enteros = new int[10]{};
    enteros[0] = pedido.dni_cliente;
    enteros[1] = 1;
    enteros[2] = pedido.cantidad_platos;
    cadenas = new char*[10]{};
    cadenas[0] = asignarCadena(pedido.codigo_repartidor);
    cadenas[1] = asignarCadena(pedido.codigo_plato);
    //cadenas[1] = mi_strdup(pedido.codigo_plato);
}
char *asignarCadena(const char *cad){
    char *aux = new char[strlen(cad) + 1];
    strcpy(aux, cad);
    return aux;
}

void modificarCliente(int *&enteros, char**&cadenas, const struct Pedido &pedido){
    enteros[1]++;
    int cantTipo = enteros[1];
    
    enteros[cantTipo + 1] = pedido.cantidad_platos;
    
    cadenas[cantTipo] = asignarCadena(pedido.codigo_plato);
}

void copiarEnteros(int *&enteros, int *buffEnteros){
    int cantTipos = buffEnteros[1];
    enteros = new int[cantTipos + 3]{};
    //int nd = 0;
    //while(buffEnteros[++nd]);
    for (int i = 0; i < cantTipos + 2; i++) {
        enteros[i] = buffEnteros[i];
    }
    delete buffEnteros;
}
void copiarCadenas(char **&cadenas, char **buffCadenas){
    int nd = 0;
    while(buffCadenas[nd])nd++;
    cadenas = new char*[nd + 1]{};
    for (int i = 0; i < nd + 1; i++) {
        cadenas[i] = buffCadenas[i];
    }
    delete buffCadenas; 

}

void imprimirCOnjuntoPedidoss(const char*nombArch, const struct ConjuntoDePedidos &conjuntoDePedidos){
    ofstream arch;
    AperturaDeUnArchivoDeTextosParaEscribir(arch, nombArch);
    arch<<fixed<<setprecision(2);
    
    arch<<"Pedido: "<<endl;
    imprimirLinea(arch, '=');
    arch<<right<<setw(11)<<"DNI"<<setw(34)<<"Codigo del repartidor"<<setw(33)<<"Cantidad de tipos de platos"<<endl;
    imprimirLinea(arch, '=');
    for (int i = 0; conjuntoDePedidos.enteros[i]; i++) {
        imprimirDatos(arch, conjuntoDePedidos.enteros[i], conjuntoDePedidos.cadenas[i]);
        imprimirLinea(arch, '-');

    }
}

void imprimirLinea(ofstream &arch, char linea){
    for (int i = 0; i < MAX_LINEA; i++)arch.put(linea);
    arch<<endl;
}

void imprimirDatos(ofstream &arch, int *enteros, char **cadenas){
    arch<<right<<setw(16)<<enteros[0]<<setw(14)<<" "<<left<<setw(8)<<cadenas[0]<<right
        <<setw(26)<<enteros[1]<<endl;
    arch<<setw(96)<<"Cant. Platos: "<<setw(27)<<"Nombre del plato"<<endl;
    for (int i = 2; enteros[i]; i++) {
        arch<<setw(88)<<enteros[i]<<setw(30)<<cadenas[i - 1]<<endl;
    }
}

int contarDatosPed(int *enteros){
    return enteros[1];
}

void hallarPrecio(int *enteros, char **cadenas, double *reales, int numDat, struct ConjuntoDePlatos platos){
    double suma = 0, subtotal;
    for (int i = 1; i < numDat + 1; i++) {
        subtotal = platos += cadenas[i];
        subtotal *= enteros[i + 1];
        suma += subtotal;
        reales[i] = subtotal;
    }
    reales[0] = suma;
}

void cambiarCodANom(char **cadenas, struct ConjuntoDePlatos platos, int numDat){
    char *aux;
    for (int i = 1; i < numDat; i++) {
        aux = platos == cadenas[i];
        delete cadenas[i];
        cadenas[i] = aux;
    }
}

void imprimirDetalle(ofstream &arch,int *enteros, char **cadenas, double *reales){
    int numDat = enteros[1] + 1;
    double igv, total;
    for (int i = 1; i < numDat; i++) {
        arch << setw(2) << setfill('0') << i << setfill(' ') << ")" << setw(4) << " " 
             << left << setfill('.') << setw(45) << cadenas[i] 
             << right <<setw(4) << enteros[i + 1] << setfill(' ') <<setw(12) << reales[i] << endl;
    }
    imprimir_linea(arch, '-');
    igv = reales[0]*0.18;
    total = reales[0] + igv;
    arch << setw(60) << "SUBTOTAL: " << setw(8) << reales[0] << endl;
    arch << setw(60) << "I.G.V.: " << setw(8) <<  igv << endl;
    arch << setw(60) << "TOTAL: " << setw(8) << total << endl;
    imprimir_linea(arch);
}