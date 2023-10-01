
#ifndef PUNTO_H
#define PUNTO_H
#include <vector>
#include <iostream>
using namespace std;

/**
 * @brief Clase Punto --> Describe un punto
 */
class Punto {
private:
    vector<int> coordenadas;
public:

    /**
     * @brief Constructor por defecto --> Construye un punto
     */
    Punto();

    /**
     * @brief Constructor --> Construye un punto dadas unas coordenadas
     * @param c Vector de coordenadas (a priori no sabemos si son 1 o más, aunque se especifica en este caso que será 10, un vector de 10 coordenadas)
     */
    Punto(vector<int> c);

    /**
     * @brief Función que indica si un punto domina a otro
     * @param otro Referencia a otro punto
     * @return Devuelve un booleano que si es verdadero lo domina, y en caso contrario, no lo domina
     */
    bool ledomina (Punto otro);

    /**
     * @brief Consultor del tamaño
     * @return Devuelve el número de coordenadas de un punto
     */
    int tamanio();

    /**
     * @brief Consultor de las coordenadas
     * @return Devuelve las coordenadas de un punto
     */
    vector<int> coord();

    /**
     * @brief Añade las coordenadas a un punto
     * @param c Vector de coordenadas
     * @param num Número de coordenadas a añadir
     */
    void setcoord(int num);

    /**
     * @brief Borra los elementos de un vector
     * 
     */
    void clear();

    /**
     * @brief Devuelve un elemento del vector
     * @param pos posición a la que se quiere acceder
     * @return Devuelve elemento de la posición indicada del vector
    */
    int get(int pos);

};


#endif //PUNTO_H
