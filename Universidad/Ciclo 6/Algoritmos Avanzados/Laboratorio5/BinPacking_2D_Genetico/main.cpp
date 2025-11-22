#include <iostream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
using namespace std;

#define ITERACIONES 10
#define IND 20
#define TSELECCION 0.5
#define TCASAMIENTO 0.5


struct Objeto {
    char id;
    int h;
    int w;
};

int Wtotal, Htotal;
vector<struct Objeto> objetosAuxiliar;

bool compara(const struct Objeto &a,const struct Objeto &b) {
    return a.h*a.w > b.h*b.w;
}


bool validarEntro(int posY, int posX, const Objeto &obj, vector<vector<char>> matriz) {
    // Verificar límites
    if (posY + obj.w > Wtotal || posX + obj.h > Htotal) return false;

    // Recorrer el área del objeto
    for (int fila = posX; fila < posX + obj.h; fila++) {
        for (int col = posY; col < posY + obj.w; col++) {
            if (matriz[fila][col] != '0') return false;
        }
    }
    return true;
}

bool aberracion(vector<int>cromo,vector<Objeto>objetos) {
    int areaTotal = 0;

    for (int i=0;i<cromo.size();i++) {
        areaTotal += cromo[i]*objetos[i].w*objetos[i].h;
    }
    if (areaTotal > Wtotal*Htotal)
        return true;

    vector<vector<char>> matrizAuxiliar;
    vector<char> fila;
    fila.assign(Wtotal,'0');
    matrizAuxiliar.assign(Htotal,fila);

    for (int i=0;i<cromo.size();i++) {
        if (cromo[i]) {
            bool seColoco = false;
            // Buscar posición válida
            for (int col = 0; col < Wtotal && !seColoco; col++) {
                for (int fila = 0; fila < Htotal && !seColoco; fila++) {
                    if (validarEntro(col, fila, objetos[i], matrizAuxiliar)) {
                        // Marcar área ocupada
                        for (int f = fila; f < fila + objetos[i].h; f++) {
                            for (int c = col; c < col + objetos[i].w; c++) {
                                matrizAuxiliar[f][c] = objetos[i].id;
                            }
                        }
                        seColoco = true;
                    }
                }
            }
            if (!seColoco)
                return true;
        }
    }
    return false;

}

void generaPoblacionInicial(vector<vector<int>>&poblacion,vector<Objeto>objetos) {
    int cont=0;
    srand(time(NULL));
    while (cont<IND) {
        vector<int>cromo;
        for (int i=0;i<objetos.size();i++)
            cromo.push_back(rand()%2);
        if (!aberracion(cromo,objetos)) {
            poblacion.push_back(cromo);
            cont++;
        }
    }
}

int calculafitness(vector<int>cromo,vector<Objeto>objetos) {
    int cont=0;
    for (int i=0;i<cromo.size();i++)
        cont+=cromo[i]*objetos[i].w*objetos[i].h;
    return cont;
}

void calcularsupervivencia(vector<vector<int>>poblacion,vector<int>&vsupervivencia,vector<Objeto>objetos) {
    int suma=0;
    for (int i=0;i<poblacion.size();i++)
        suma+=calculafitness(poblacion[i],objetos);
    for (int i=0;i<poblacion.size();i++) {
        int porsup = round(100*(double)calculafitness(poblacion[i],objetos)/suma);
        vsupervivencia.push_back(porsup);
    }
}

void cargaruleta(int *ruleta,vector<int>vsupervivencia) {
    int cont=0;
    for (int i=0;i<vsupervivencia.size();i++)
        for (int j=0;j<vsupervivencia[i];j++)
            ruleta[cont++]=i;
}

void seleccion(vector<vector<int>>&padres,vector<vector<int>>poblacion,vector<Objeto>objetos) {
    int ruleta[100];
    for(int i=0;i<100;i++)
        ruleta[i]=-1;
    vector<int>vsupervivencia;
    calcularsupervivencia(poblacion,vsupervivencia,objetos);
    cargaruleta(ruleta,vsupervivencia);
    int nSeleccionados = TSELECCION*poblacion.size();
    for(int i=0;i<nSeleccionados;i++) {
        int posR = rand()%100;
        if (ruleta[posR]>-1)
            padres.push_back(poblacion[ruleta[posR]]);
    }
}

void engendrarChocherita(vector<int>viejo,vector<int>viejita,vector<int>&chocherita) {
    int pos = round(viejo.size()*TCASAMIENTO);
    for (int i=0;i<pos;i++)
        chocherita.push_back(viejo[i]);
    for (int i=pos;i<viejita.size();i++)
        chocherita.push_back(viejita[i]);
}

void meCasoONo(vector<vector<int>>padres,vector<vector<int>>&poblacion,vector<Objeto>objetos){
    for(int i=0;i<padres.size();i++)
        for(int j=0;j<padres.size();j++)
            if (i!=j) {
                vector<int>chocherita;
                engendrarChocherita(padres[i],padres[j],chocherita);
                if (!aberracion(chocherita,objetos))
                    poblacion.push_back(chocherita);
            }
}

int calculaDecimalPelao(vector<int>cromo) {
    int suma=0;
    for (int i=0;i<cromo.size();i++)
        suma+=cromo[i]*pow(2,i);
    return suma;
}

void mataGiles3000(vector<vector<int>>&poblacion) {
    map<int,vector<int>>mapaPelao;
    for(int i=0;i<poblacion.size();i++) {
        int base10ArquiComp = calculaDecimalPelao(poblacion[i]);
        mapaPelao[base10ArquiComp]=poblacion[i];
    }
    poblacion.clear();
    //GUANIRA REGRESAAAAA GAAAAAAA
    for (map<int,vector<int>>::iterator it=mapaPelao.begin();it!=mapaPelao.end();it++)
        poblacion.push_back(it->second);
}

bool comparaPelao(vector<int>a,vector<int>b) {
    int fifaA = calculafitness(a,objetosAuxiliar);
    int fifaB = calculafitness(b,objetosAuxiliar);
    return fifaA>fifaB;
}

void generaPremiunConoNorte(vector<vector<int>>&poblacion) {
    sort(poblacion.begin(),poblacion.end(),comparaPelao);
    if (poblacion.size()>IND)
        poblacion.erase(poblacion.begin()+IND,poblacion.end());
}

void muestraChocheritas(vector<vector<int>>poblacion,vector<Objeto>objetos) {
    for(int i=0;i<poblacion.size();i++) {
        for (int j=0;j<poblacion[i].size();j++) {
            cout<<poblacion[i][j]<<" ";
        }
        cout<<"Desperdicié?="<<Wtotal*Htotal-calculafitness(poblacion[i],objetos)<<endl;
    }
    cout<<endl;
}

void muestraMatriz(vector<int>cromosoma, vector<Objeto>objetos) {
    cout<<"La mejor solución: "<<endl;
    vector<vector<char>>matriz;
    vector<char>fila;
    fila.assign(Wtotal,'0');
    matriz.assign(Htotal,fila);

    for (int k=0;k<cromosoma.size();k++) {
        if (cromosoma[k]) {
            bool seColoco = false;
            for (int col = 0; col < Wtotal && !seColoco; col++) {
                for (int fila = 0; fila < Htotal && !seColoco; fila++) {
                    if (validarEntro(col, fila, objetos[k], matriz)) {
                        // Colocar objeto
                        for (int f = fila; f < fila + objetos[k].h; f++) {
                            for (int c = col; c < col + objetos[k].w; c++) {
                                matriz[f][c] = objetos[k].id;
                            }
                        }
                        seColoco = true;
                    }
                }
            }
        }
    }
    // Imprimir contenedor
    for (int fila = 0; fila < matriz.size(); fila++) {
        for (int col = 0; col < matriz[fila].size(); col++) {
            cout << matriz[fila][col] << " ";
        }
        cout << endl;
    }
}


void algoritmoGenetico(vector<Objeto>objetos) {
    vector<vector<int>> poblacion;
    generaPoblacionInicial(poblacion,objetos);
    for (int i=0;i<ITERACIONES;i++) {
        vector<vector<int>>padres;
        seleccion(padres,poblacion,objetos);
        meCasoONo(padres,poblacion,objetos);
        mataGiles3000(poblacion);
        generaPremiunConoNorte(poblacion);
        cout<<"Mejor desperdicio hasta ahora"<<Wtotal*Htotal-calculafitness(poblacion[0],objetos)<<endl<<endl;
    }
    muestraChocheritas(poblacion,objetos);
    muestraMatriz(poblacion[0],objetos);
}


int main() {
    Wtotal = Htotal = 10;
    vector<Objeto>objetos{{'A',6,5},{'B',4,5},{'C',3,3},{'D',5,5},{'E',2,2}};
    sort(objetos.begin(),objetos.end(),compara); //esto solo es pa meter primero los más grandes. Porque empezaré de izquierda

    objetosAuxiliar=objetos;
    algoritmoGenetico(objetos);
    return 0;
}