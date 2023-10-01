
#ifndef DESCARGAS_CONJUNTO_PUNTOS_H
#define DESCARGAS_CONJUNTO_PUNTOS_H
#include "Punto.h"
#include <stdlib.h>

/**
 * @brief La clase Conjunto_puntos almacena un número determinado de puntos con el fin de poder obtener aquellos dominantes
 */
class Conjunto_puntos {
private:
    vector <Punto> puntos;
    vector <Punto> resultado;
public:
    /**
     * @brief Constructor --> Construye un conjunto de puntos dadas unos puntos
     */
    Conjunto_puntos();

    /**
     * @brief Inserta un punto en el conjunto
     * @param p Punto a insertar
     */
    void add(Punto p);
    void addVector(vector<Punto> p);

    /**
     * @brief Busca un punto del conjunto devolviendo su posición
     * @param p Punto a buscar
     * @return Devuelve la posición del Punto p si está o -1 si no se encuentra
     */
    int buscaPunto(Punto p);

    /**
     * @brief Devuelve el punto que hay en determinada posición
     * @param pos Posición del punto a obtener
     * @return Devuelve un punto
     */
    Punto get(int pos);

    /**
     * @brief Devuelve el tamaño del conjunto
     * @return Tamaño del conjunto
     */
    int tamanio();

    /**
     * @brief Devuelve el tamaño del vector resultante
     * @return Tamaño del vector resultante
     */
    int tamanioRes();

    /**
     * @brief Vacía el conjunto de puntos
     */
    void vaciar();
    void vaciarResultado();

    /**
     * @brief Añade los puntos dominantes al vector de puntos dominantes
     */
    void aniade_dom();

    /**
     * @brief Obtiene el punto que hay en la posición indicada
     * @param pos Posición del vector donde está el punto que queremos obtener
     * @return Un punto del vector resultado
     */
    Punto getresultado(int pos);
    
    //Funcion que me devuelve el vector tras sacar los no dominados
    vector<Punto> getResultado();

};


#endif //DESCARGAS_CONJUNTO_PUNTOS_H
