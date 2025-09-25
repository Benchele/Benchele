#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int CalcularSuma(vector<int> const &tareas,int cantTareas,int limite){
    vector<vector<int>> horario(cantTareas+1,vector<int>(limite+1,0));
    for(int i=1;i<=limite;i++){
        for(int j=1;j<=cantTareas;j++){
            if(tareas[j-1] <= i){
                horario[j][i] = max(horario[j-1][i],tareas[j-1] + horario[j-1][i-tareas[j-1]]);
            }else{
                horario[j][i] = horario[j-1][i];
            }
        }
    }

    for (int i = 0; i <= cantTareas; i++) {
        for (int j = 0; j <= limite; j++) {
            cout << horario[i][j] << " ";
        }
        cout << endl;
    }
    return horario[cantTareas][limite];
}

int main(int argc, char const *argv[])
{
    vector<int> tareas = {1,3,6,10,16};
    int cantTareas = tareas.size();
    // ingresar el tiempo maximo de horario
    cout<<"Para turno ma;ana se puede sumar como maximo: "<<CalcularSuma(tareas,cantTareas,8)<<endl;
    cout<<"Para turno ma;ana y tarde se puede sumar como maximo: "<<CalcularSuma(tareas,cantTareas,16)<<endl;
    cout<<"Para turno ma;ana, tarde y noche se puede sumar como maximo: "<<CalcularSuma(tareas,cantTareas,24)<<endl;
    return 0;
}