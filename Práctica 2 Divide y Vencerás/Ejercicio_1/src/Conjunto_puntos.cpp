
#include "Conjunto_puntos.h"

//Constructor --> Construye un conjunto de puntos dadas unos puntos
Conjunto_puntos::Conjunto_puntos(){}

//Inserta un punto en el conjunto
void Conjunto_puntos::add(Punto p){
    puntos.push_back(p);
}

//Busca un punto del conjunto devolviendo su posición
int Conjunto_puntos::buscaPunto(Punto p){
    if(!puntos.empty()){
        for(int i = 0; i < puntos.size(); i++){
            if(puntos[i].coord() == p.coord()){
                return i;
            }
        }
        return -1;
    }
    return -1;
}

//Devuelve el punto que hay en determinada posición
Punto Conjunto_puntos::get(int pos){
    return puntos[pos];
}

//Devuelve el tamaño del conjunto
int Conjunto_puntos::tamanio(){
    return puntos.size();
}

//Devuelve el tamaño del vector resultante de puntos dominantes
int Conjunto_puntos::tamanioRes(){
    return resultado.size();
}

//Vacía el conjunto de puntos
void Conjunto_puntos::vaciar(){
    while(!puntos.empty()){
        puntos.pop_back();
    }
}

void Conjunto_puntos::vaciarResultado(){
	resultado.clear();
}
//Añade los puntos dominantes al vector de puntos dominantes
void Conjunto_puntos::aniade_dom(){
    bool no_dominado;
    for (int i=0; i<puntos.size(); i++){
        no_dominado = true;;
        for (int j=0; j<puntos.size() && no_dominado; j++){
            if (i!=j){

                if(puntos[i].ledomina(puntos[j]))
                    no_dominado = false;

            }
        }

        if(no_dominado)
            resultado.push_back(puntos[i]);
    }
}

//Obtiene el punto que hay en la posición indicada
Punto Conjunto_puntos::getresultado(int pos){
    return resultado[pos];
}




