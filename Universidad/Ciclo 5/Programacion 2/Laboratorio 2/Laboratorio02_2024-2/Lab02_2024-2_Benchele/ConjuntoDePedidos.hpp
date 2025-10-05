/* 
 * Archivo: ConjuntoDePedidos.hpp
 * Autor: Andrés Melgar
 * Fecha: 31 de agosto de 2024, 09:59
 */

#ifndef CONJUNTODEPEDIDOS_HPP
#define CONJUNTODEPEDIDOS_HPP

#include <iostream>
#include <fstream>
#include "Pedido.hpp"
#define CLIENTE_NO_ENCONTRADO -1
#define MAXIMO_POR_LINEA 40

using namespace std;

struct ConjuntoDePedidos{
    int **enteros;
    char ***cadenas;
    double **reales;    
};

void cargar_conjunto_de_pedidos(ConjuntoDePedidos &conjuntoDePedidos, const char *nombre_de_archivo);

void operator>>(istream &archivo_de_pedidos, ConjuntoDePedidos &conjuntoDePedidos); //Leer datos

void inicializar_buffer_de_conjunto_de_pedidos(ConjuntoDePedidos &conjuntoDePedidos, int cantidad);

void operator<<(ConjuntoDePedidos &buffer_de_conjuntoDePedidos, const Pedido &pedido); //Incluir un pedido

void operator>>(const ConjuntoDePedidos &buffer_de_conjuntoDePedidos, ConjuntoDePedidos &conjuntoDePedidos); //Crea memoria exacta

int buscar_cliente(const ConjuntoDePedidos &conjuntoDePedidos, int dni);

void operator++(ConjuntoDePedidos &conjuntoDePedidos);

void operator++(ConjuntoDePedidos &conjuntoDePedidos, int);

void liberar_conjunto_de_pedidos(ConjuntoDePedidos &conjuntoDePedidos);

void operator!(ConjuntoDePedidos &conjuntoDePedidos);

void operator*(const ConjuntoDePedidos &conjuntoDePedidos);

void obtener_nombre_archivo(char *nombre_archivo, int dni_numero);

void imprimir_linea(ofstream &archDeReporte, char c = '=');

int obtener_cantidad_cliente(const ConjuntoDePedidos &conjuntoDePedidos);

//Auxiliares
void agregarCLiente(int *&enteros, char**&cadenas, const struct Pedido &pedido);
char *asignarCadena(const char *cad);
void modificarCliente(int *&enteros, char**&cadenas, const struct Pedido &pedido);
void copiarEnteros(int *&enteros, int *buffEnteros);
void copiarCadenas(char **&cadenas, char **buffCadenas);

void imprimirCOnjuntoPedidoss(const char*nombArch, const struct ConjuntoDePedidos &conjuntoDePedidos);
void imprimirLinea(ofstream &arch, char linea);
void imprimirDatos(ofstream &arch, int *enteros, char **cadenas);

int contarDatosPed(int *enteros);
void hallarPrecio(int *enteros, char **cadenas, double *reales, int numDat, struct ConjuntoDePlatos platos);

void cambiarCodANom(char **cadenas, struct ConjuntoDePlatos platos, int numDat);
void imprimirDetalle(ofstream &arch,int *enteros, char **cadenas, double *reales);

#endif /* CONJUNTODEPEDIDOS_HPP */

