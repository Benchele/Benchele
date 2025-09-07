/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file_header.cc to edit this template
 */

/* 
 * File:   FuncionesAuxiliares.cpp
 * Author: Lenovo
 * 
 * Created on 8 de julio de 2025, 12:03 PM
 */

#include <iostream>
#include <iomanip>
#include <ratio>
#include <climits>
#include "FuncionesAuxiliares.h"
using namespace std;

int encontrar_solitario(int *arr, int ini, int fin){
    if(ini == fin)return arr[ini]; //El ultimo que queda es el solitario
    int med = (ini + fin)/2;
    
    //Opcion 1
    if(med % 2 != 0){ //SI es impar le resta uno para que apunte a un par
        med--;
    }
    
    if(med % 2 == 0){//Par
        if(arr[med] == arr[med + 1]){//Se va a la derecha
            return encontrar_solitario(arr, med + 2, fin);
        }
        else{
            return encontrar_solitario(arr, ini, med); //Se va a la izquierda
        }
    }
    
    //Opcion 2
//    if(med % 2 == 0){//Par
//        if(arr[med] == arr[med + 1]){//Se va a la derecha
//            return encontrar_solitario(arr, med + 2, fin);
//        }
//        else{
//            return encontrar_solitario(arr, ini, med); //Se va a la izquierda
//        }
//    }
//    else{//Impar
//        if(arr[med] == arr[med + 1]){ //Se va a la izquierda
//            return encontrar_solitario(arr, ini, med - 1);
//        }
//        else{
//            return encontrar_solitario(arr, med + 1, fin); //Se va a la derecha
//        }
//        
//    }
}
void ejercicio1(){//Parejas
    //int arr[] = {1, 1, 3, 3, 4, 5, 5, 7, 7, 8, 8};
    //int arr[] = {1, 1, 3};
    //int arr[] = {1, 1, 2, 3, 3, 5, 5, 6, 6};
    int arr[] = {1, 1, 2, 3, 3, 5, 5};
    
    int n = sizeof(arr)/sizeof(arr[0]);
    
    cout << "El numero solitario es: "<<encontrar_solitario(arr, 0, n - 1)<<endl;
    
    //Complejidad log(n)   
}
////////////////////////////////////////////////////////////////////////////////

//A la derecha
int contar_ceros_A_la_derecha(int *arr, int ini, int fin, int cont){
    if(ini > fin)return cont; //Retorna lo que tiene contado hasta ese momento
    
    int med = (ini + fin)/2;
    
    if(arr[med] == 0){
        return contar_ceros_A_la_derecha(arr, ini, med - 1, cont + fin - med + 1);
    }
    else{
        return contar_ceros_A_la_derecha(arr, med + 1, fin, cont);
    }
}

//A la izquierda
int contar_ceros_A_la_izquierda(int *arr, int ini, int fin, int cont){
    if(ini > fin)return cont; //Retorna lo que tiene contado hasta ese momento
    
    int med = (ini + fin)/2;
    
    if(arr[med] == 1){
        return contar_ceros_A_la_izquierda(arr, med + 1, fin, cont + med - ini + 1);
    }
    else{
        return contar_ceros_A_la_izquierda(arr, ini, med - 1, cont);
    }
}
void ejercicio2(){//Cuenta cero    
    //int arr[] = {1, 1, 1, 0, 0, 0, 0};
    //int arr[] = {1, 1, 1, 1, 0, 0, 0};
    //int arr[] = {1, 1, 1, 1, 1, 1, 1};
    //int arr[] = {0, 0, 0, 0, 0, 0, 0};
    //int arr[] = {1, 0, 0, 0, 0, 0, 0};
    int arr[] = {1, 1, 1, 1, 1, 1, 0};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    //A la derecha
    cout << "Hay " << contar_ceros_A_la_derecha(arr, 0, n - 1, 0) << " ceros" << endl;
    //A la izquierda
    cout << "Hay " << contar_ceros_A_la_izquierda(arr, 0, n - 1, 0) << " unos" << endl;
    
    //Complejidad log(n)
}
////////////////////////////////////////////////////////////////////////////////

int encontrar_rotado(int *arr, int ini, int fin){

    if(ini >= fin) return arr[ini]; //Caso lo encuentra al final
    
    int med = (ini + fin)/2;
    
    if(arr[med] < arr[med - 1]){
        return arr[med]; //Caso lo encuentra antes de recorrer todo el arreglo
    }
    
    if(arr[0] < arr[med]){
        return encontrar_rotado(arr, med + 1, fin);
    }
    else{
        return encontrar_rotado(arr, ini, med - 1);
    }
    
    ////////////////////////////
    //Otra forma
//    if(ini == fin) return arr[ini];
//    int med = (ini + fin)/2;
//    if(arr[med] < arr[fin])
//     El maximo esta en la parte izquierda (incluyendo med)
//        return encontrar_rotado(arr, ini, med);
//    else
//     El maximo esta en la parte derecha (excluyendo med)
//        return encontrar_rotado(arr, med + 1, fin);

    
}
void ejercicio3(){//Rotado
    //int arr[] = {5, 6, 1, 2, 3, 4};
    //int arr[] = {7, 8, 9, 10, 11, 12, 3};
    int arr[] = {7, 8, 9, 10, 11, 1, 2, 3};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    cout << "El elemento minimo es: " << encontrar_rotado(arr, 0, n - 1);
    
    //Complejidad log(n)
}
////////////////////////////////////////////////////////////////////////////////

int suma_centro(int *arr, int ini, int med, int fin){
    int sumaMaxIzq = INT_MIN, sumaMaxDer = INT_MIN, suma = 0;
    
    //Suma maxima izquierda
    for (int i = med; i >= ini; i--) {
        suma += arr[i];
        if(sumaMaxIzq < suma){
            sumaMaxIzq = suma;
        }
    }
    
    //Suma maxima derecha
    suma = 0;
    for (int i = med + 1; i <= fin; i++) {
        suma += arr[i];
        if(sumaMaxDer < suma){
            sumaMaxDer = suma;
        }
    }
    
    //cout << endl << sumaMaxDer + sumaMaxIzq << endl;
    return sumaMaxDer + sumaMaxIzq;
}
int suma_centro_Con_rango(int *arr, int ini, int med, int fin, int &iniRan, int &finRan){
    int sumaMaxIzq = INT_MIN, sumaMaxDer = INT_MIN, suma = 0;
    
    //Suma maxima izquierda
    for (int i = med; i >= ini; i--) {
        suma += arr[i];
        if(sumaMaxIzq < suma){
            sumaMaxIzq = suma;
            iniRan = i;
        }
    }
    
    //Suma maxima derecha
    suma = 0;
    for (int i = med + 1; i <= fin; i++) {
        suma += arr[i];
        if(sumaMaxDer < suma){
            sumaMaxDer = suma;
            finRan = i;
        }
    }
    //cout << endl << sumaMaxDer + sumaMaxIzq << endl;
    return sumaMaxDer + sumaMaxIzq;
}
int maxSum(int k, int g){
    if(k > g)return k;
    return g;
}
int suma_maxima(int *arr, int ini, int fin){
    if(ini == fin)return arr[ini];
    
    int med = (ini + fin)/2;
    
    int izq = suma_maxima(arr, ini, med);
    int der = suma_maxima(arr, med + 1, fin);
    int centro = suma_centro(arr, ini, med, fin);
    
    return maxSum(maxSum(izq, der), centro);
}

int suma_maxima_Con_rango(int *arr, int ini, int fin, int &iniRan, int &finRan){
    if(ini == fin){
        //... (*)
        iniRan = ini;
        finRan = ini;
        return arr[ini];
    }
    
    int med = (ini + fin)/2;
    
    //int iniIzq = ini, finIzq = med; //Para evitar esto hacer ... (*)
    int iniIzq, finIzq;
    int izq = suma_maxima_Con_rango(arr, ini, med, iniIzq, finIzq);
    
    //int iniDer = med + 1, finDer = fin;//Para evitar esto hacer ... (*)
    int iniDer, finDer;
    int der = suma_maxima_Con_rango(arr, med + 1, fin, iniDer, finDer);
    
    //int iniCen = ini, finCen = fin;//Para evitar esto hacer ... (*)
    int iniCen, finCen;
    int centro = suma_centro_Con_rango(arr, ini, med, fin, iniCen, finCen);
    
    int maxima = maxSum(maxSum(izq, der), centro);
    
    if(maxima == izq){
        iniRan = iniIzq;
        finRan = finIzq;
    }
    if(maxima == der){
        iniRan = iniDer;
        finRan = finDer;
    }
    if(maxima == centro){
        iniRan = iniCen;
        finRan = finCen;
    }
    
    return maxSum(maxSum(izq, der), centro);
}
void ejercicio4(){//Mayor suma
    //Merge
    //int arr[] = {-2, -5, 6, -2,  -3, 1, 5, -6};
    //int arr[] = {-2, -5, 6, -2,  -3, 1, 5, 6};
    //int arr[] = {7, -5, 6, -2,  -3, 1, 5, 6};
    int arr[] = {7, -5, -6, -2,  -3, 1, -5, 6};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    //cout << "La suma maxima: " << suma_maxima(arr, 0, n - 1);
    
    //Complejidad n*log(n)
    
    //Con rango 
    int iniRan = 0, finRan = 0;
    
    cout << "La suma maxima: " << suma_maxima_Con_rango(arr, 0, n - 1, iniRan, finRan) << endl;
    cout << "Los elementos que suman el máximo son: ";
    
    cout << endl << iniRan << " " << finRan << endl;
    
    for (int i = iniRan; i <= finRan; i++) {
        cout << arr[i] << " ";
    }
    for (int i = 0; i <= 0; i++) {
        cout << "Entra" << endl;
    }
}
////////////////////////////////////////////////////////////////////////////////

int encontrar_Maximo(int *arr, int ini, int fin){
    if(ini == fin)return arr[ini];
    
    int med = (ini + fin)/2;
    
    if(arr[med] < arr[med + 1]){
        return encontrar_Maximo(arr, med + 1, fin);
    }
    else{
        return encontrar_Maximo(arr, ini, med);
    }
}
void ejercicio5(){//Maximo
    //int arr[] = {8, 10, 20, 80, 100, 200, 400, 500, 3, 2, 1};
    //int arr[] = {8, 10, 5, 4, 3, 2, 1};
    //int arr[] = {8, 10, 11, 14, 23, 32, 41};
    int arr[] = {1, 2, 3, 4, 5, 4, 3};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    cout << "El maximo numero es: " << encontrar_Maximo(arr, 0, n - 1);
}
////////////////////////////////////////////////////////////////////////////////

int contar_centro(int *arr, int ini, int med, int fin){
    int n1, n2, k = 0, g = 0;
    n1 = med - ini + 1;
    n2 = fin - med;
    
    int K[n1 + 1];
    int G[n2 + 1];
    
    
    for (int i = ini; i <= med; i++)K[i - ini] = arr[i];
    for (int i = med + 1; i <= fin; i++)G[i - med - 1] = arr[i];
    K[n1] = INT_MAX;
    G[n2] = INT_MAX;
    
    int inversiones = 0;
    for (int i = ini; i <= fin; i++) {
        if(K[k] < G[g]){
            arr[i] = K[k++];
        }
        else{
            arr[i] = G[g++];
            inversiones += n1 - k;
        }

    }
    return inversiones;

}
int contar_Inversiones(int *arr, int ini, int fin){
    if(ini == fin)return 0;
    
    int med = (ini + fin)/2;
    
    int izq = contar_Inversiones(arr, ini, med);
    int der = contar_Inversiones(arr, med + 1, fin);
    int centro = contar_centro(arr, ini, med, fin);
    
    return izq + centro + der;
}
void ejercicio6(){//Numero inversiones
    int arr[] = {1, 20, 6, 4, 5, 25, 10, 12}; 
    int n = sizeof(arr)/sizeof(arr[0]);
    
    cout << "El número de inversiones es: " << contar_Inversiones(arr, 0, n - 1) << endl;
    //Imprimir el arreglo resultante (queda ordenado)
    cout << "Arreglo después de conteo de inversiones: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
}


///////////////////////////////////////////////////////////////////Ordenamientos

void mergeCentro(int *arr, int ini, int med, int fin){
    int n1, n2, k = 0, g = 0;
    n1 = med - ini + 1;
    n2 = fin - med;
    
    int K[n1 + 1];
    int G[n2 + 1];
    
    for (int i = ini; i <= med; i++)K[i - ini] = arr[i];
    for (int i = med + 1; i <= fin; i++)G[i - med - 1] = arr[i];
    
    K[n1] = INT_MAX;
    G[n2] = INT_MAX;
    
    for (int i = ini; i <= fin; i++) {
        if(K[k] < G[g]){
            arr[i] = K[k++];
        }
        else{
            arr[i] = G[g++];
        }

    }
}

void ordenamientoMerge(int *arr, int ini, int fin){
    if(ini == fin)return;
    
    int med = (ini + fin)/2;
    
    ordenamientoMerge(arr, ini, med);
    
    ordenamientoMerge(arr, med + 1, fin);
    
    mergeCentro(arr, ini, med, fin);
}
void ordenamientoMerge(){ //Merge sort
    int arr[] = {42, 17, 8, 23, 56, 4, 91, 30, 12, 67};
    int n=sizeof(arr)/sizeof(arr[0]);
    
    ordenamientoMerge(arr, 0, n - 1);
    
    cout << endl << "Merge sort: " << endl;
    for (int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
}

/////////////////////////

void intercambiar(int &k, int &g){
    int aux;
    aux = k;
    k = g;
    g = aux;
}

void ordenamientoQuick(int *arr, int ini, int fin){
    if(ini >= fin)return;
    
    int med = (ini + fin)/2;
    
    intercambiar(arr[ini], arr[med]);
    
    int limite = ini;
    
    for (int i = ini + 1; i <= fin; i++){
        if(arr[i] < arr[ini]){
            intercambiar(arr[++limite], arr[i]);
        }
    }
    intercambiar(arr[ini], arr[limite]);
    
    ordenamientoQuick(arr, ini, limite - 1);
    ordenamientoQuick(arr, limite + 1, fin);

}
void ordenamientoQuick(){ //Quick sort
    int arr[] = {7, 2, 9, 10, 16, 10, 13, 8, 2, 10};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    ordenamientoQuick(arr, 0, n - 1);
    
    cout << endl << "Quick sort: " << endl;
    for (int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
}