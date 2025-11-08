#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>
#include <ctime>
using namespace std;
#define ALFA 0.4
#define ITER 1000

struct Paquete {
    int id;
    int ancho;
    int alto;
};

struct Contenedor {
    int alto;
    int ancho;
};

struct Colocado {
    int id;
    int x;
    int y;
    int w;
    int h;
    int numFila;
};

struct Solucion {
    vector<Colocado> colocados;
    int area_usada;
    int estante;
};

bool cmpArea (const Paquete&a,const Paquete&b) {
    return a.ancho*a.alto > b.ancho*b.alto;
}

bool cmpAlto (const Paquete&a,const Paquete&b) {
    if (a.alto != b.alto) return a.alto > b.alto;
    else return a.ancho > b.ancho;
}

bool cmpAncho (const Paquete&a,const Paquete&b) {
    if (a.ancho != b.ancho) return a.ancho > b.ancho;
    else return a.alto > b.alto;
}

int buscarIndiceAlto(double rcl,vector<Paquete>&paq) {
    int contador=0;
    for (int i=0;i<paq.size();i++) {
        if (paq[i].alto >= rcl) {
            contador++;
        }
    }
    return contador;
}

int buscarIndiceAncho(double rcl,vector<Paquete>&paq) {
    int contador=0;
    for (int i=0;i<paq.size();i++) {
        if (paq[i].ancho >= rcl) {
            contador++;
        }
    }
    return contador;
}

void buscarCandidatos(vector<Paquete>&cand,vector<Paquete>&paq,int filaH,int anchoRest) {
    for (int i=0;i<paq.size();i++) {
        if (paq[i].alto <= filaH and paq[i].ancho <= anchoRest) {
            cand.push_back(paq[i]);
        }
    }
}

void buscarCandidatosAltura(vector<Paquete>&cand,vector<Paquete>&paq,int altura) {
    for (int i=0;i<paq.size();i++) {
        if (paq[i].alto <= altura) {
            cand.push_back(paq[i]);
        }
    }
}

void borrarUsado(int id,vector<Paquete>&paq) {
    for (int i=0;i<paq.size();i++) {
        if (paq[i].id==id) {
            paq.erase(paq.begin()+i);
            break;
        }
    }
}

Solucion llenarContenedor(vector<Paquete>paqv,Contenedor cont) {
    Solucion best;
    best.area_usada=INT_MIN;
    sort(paqv.begin(),paqv.end(),cmpArea);
    srand(time(NULL));
    for (int i=0;i<ITER;i++) {
        vector<Paquete>paq = paqv;
        Solucion solu{{},0,0};
        int y=0;
        while (!paq.empty() and y<cont.alto) {
            sort(paq.begin(),paq.end(),cmpAlto);
            int betaH = paq[0].alto;
            int tauH = paq[paq.size()-1].alto;
            double rclH = betaH-ALFA*(betaH-tauH);
            int indMaxH = buscarIndiceAlto(rclH,paq);
            int indaleH = rand()%indMaxH;
            int filaH = paq[indaleH].alto;
            int x=0;
            int anchoRest=cont.ancho;
            int entro=0;
            while (anchoRest>0) {
                vector<Paquete>candidatos;
                buscarCandidatos(candidatos,paq,filaH,anchoRest);
                if (candidatos.empty())break;
                sort(candidatos.begin(),candidatos.end(),cmpAncho);
                int betaW = candidatos[0].ancho;
                int tauW = candidatos[candidatos.size()-1].ancho;
                double rclW = betaW-ALFA*(betaW-tauW);
                int indMaxW = buscarIndiceAncho(rclW,candidatos);
                int indaleW = rand()%indMaxW;
                Colocado colocado {candidatos[indaleW].id,x,y,candidatos[indaleW].ancho,candidatos[indaleW].alto,solu.estante};
                solu.colocados.push_back(colocado);
                solu.area_usada+=candidatos[indaleW].ancho*candidatos[indaleW].alto;
                x += candidatos[indaleW].ancho;
                anchoRest -= candidatos[indaleW].ancho;
                entro=1;
                borrarUsado(candidatos[indaleW].id,paq);
            }
            if (!entro) break;
            y +=filaH;
            solu.estante++;
        }
        if (solu.area_usada > best.area_usada) {
            best = solu;
        }
    }
    return best;
}

int main() {
    vector <Paquete> paq{
            {1,5,4},{2,4,4},{3,3,2},{4,6,3},{5,2,2},
            {6,4,3},{7,1,6},{8,3,5},{9,2,7},{10,5,2}
    };

    Contenedor contenedor {12,10};
    Solucion solu = llenarContenedor(paq,contenedor);

    cout << "Contenedor W="<<contenedor.ancho<<" H="<<contenedor.alto<<"\n";
    cout << "Estantes usados: " << solu.estante << "\n";
    cout << "Area usada: " << solu.area_usada << "\n";
    cout << "Colocaciones (id x y w h shelf):\n";
    for (auto &c: solu.colocados){
        cout << c.id << " " << c.x << " " << c.y << " "
             << c.w << " " << c.h << " " << c.numFila << "\n";
    }
    return 0;
}