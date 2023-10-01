
#include "Punto.h"

//Constructor por defecto
Punto::Punto() {
    coordenadas = {};
}

//Constructor --> Construye un punto dadas unas coordenadas
Punto::Punto(vector<int> c) {
    for(int i = 0; i < c.size()-1; i++){
        coordenadas[i] = c[i];
    }
}

//Función que indica si a un punto le domina otro.
bool Punto::ledomina(Punto otro){
    
    bool ledomina = true;
    for (int i=0; i<coordenadas.size() &&ledomina; i++){

        if (coordenadas[i] >= otro.coordenadas[i])
            ledomina = false;
    }

    return ledomina;

}


//Consultor del tamaño
int Punto::tamanio(){
    return coordenadas.size();
}

//Consultor de las coordenadas
vector<int> Punto::coord(){
    return coordenadas;
}

//Añade las coordenadas a un punto
void Punto::setcoord(int num) {
    coordenadas.push_back(num);
}

//Elimina los elementos de un vector
void Punto::clear(){
    coordenadas.clear();
}

//Devuelve una coordenada de una posición específica del punto
int Punto::get(int pos){
    return coordenadas.at(pos);
}

