#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include "Punto.h"
#include <stdlib.h>
#include "Conjunto_puntos.h"
#include <fstream> // Para usar ficheros

using namespace std;
/*
	Modo de ejecucion ./programa 0 90 95 100 150... (el 0 es el nombre del archivo)
*/

//Método DyV con el conjunto dividido a la mitad
vector<Punto> DominantesMitad(Conjunto_puntos conjunto, int inicio, int final){
    //Miro si el conjunto esta compuesto solo por dos componenetes
    Conjunto_puntos c;
    if((final-inicio) == 2){ //si solo tiene dos estoy en el caso base
    	cout << "Caso base " << endl;
    	conjunto.aniade_dom();//Miro cual es el dominante de los dos
    	return conjunto.getResultado();//devuelvo ese resultado
    }
    else if(final-inicio < 2)//si solo tengo un punto
    	return c.getResultado();//devuelvo ese punto
    
    int medio = (inicio+final+1)/2; //calculamos la mitad del vector

    c.addVector(DominantesMitad(conjunto,inicio,medio));//Buscamos los puntos en la mitad izda

    c.addVector(DominantesMitad(conjunto,medio+1,final));//Buscamos los puntos en la mitad dcha

    c.aniade_dom(); //saco los dominantes de la fusion de los subapartados
    return c.getResultado();//devuelvo el conjunto resultante

}


int main(int argc, char* argv[]){


    //Comprobamos que los parámetros sean correctos
    if (argc <= 3){
        cerr << "Número incorrecto de parámetros" << endl;
        cerr << "Uso correcto: <./ejecutable> <fichero> <tamaños de caso>" << endl;
        return 0;
    }    

    int numPuntos = stoi(argv[1]);
    ofstream fsalida;
    
    // Abrimos fichero de salida
	fsalida.open(argv[1]);
	if (!fsalida.is_open()) {
		cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
		return 0;
	}
	

    int K=10;

    Punto p;
    
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
    double tejecucion; // tiempo de ejecucion del algoritmo en ms
    
    Conjunto_puntos conjuntoP;
	
    std::srand(std::time(nullptr));
    
   // Pasamos por cada tamanio de caso
	for (int argumento= 2; argumento<argc; argumento++) {
	    
	    int numPuntos = atoi(argv[argumento]);
		 //Se inicializan los puntos
	    for (int i=0; i<numPuntos; i++){
		for(int j=0; j<K; j++){
		    //Genera numero aleatorio entre 1 y 10
		    int random = std::rand() % 100 +1;
		    p.setcoord(random);
		}

		conjuntoP.add(p);
		p.clear();
	    }
		cout << "--------------------------------------------------------------------------------------\n";
		cerr << "Ejecutando para tam. caso: " << numPuntos << endl;
		cout  << "Los puntos son los siguientes: " << endl;
	    for (int i=0; i<numPuntos; i++){
		cout << "Punto " << i+1 << ": ";
		//Para cada vector recorre sus coordenadas
		for (int j=0; j<K; j++){

		    cout << conjuntoP.get(i).get(j) << " ";
		}

		cout << endl;
	    }
		t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
		vector<Punto> resultado = DominantesMitad(conjuntoP,0,conjuntoP.tamanio()-1); // Ejecutamos el algoritmo para tamanio de caso tam
		tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
	
		cout << "Tamaño del conjunto tras sacar los dominados " << conjuntoP.tamanio() << endl;
		unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
		//Imprimimos por pantalla los puntos dominantes a partir del vector resultante
		cout <<  endl << "Los puntos no dominados son los siguientes: " << endl;
		
	       for (int i=0; i<resultado.size(); i++){
		    cout << "Punto " << i+1 << ": ";
		    for (int j=0; j<K; j++){
			 cout << resultado[i].get(j) << " ";
		    }

	          cout << endl;
		}
		cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< numPuntos <<endl;
		cout << "--------------------------------------------------------------------------------------\n";

		
		// Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida<<numPuntos<<" "<<tejecucion<<"\n";
		
		resultado.clear();
		conjuntoP.vaciar();

	}
	
	// Cerramos fichero de salida
	fsalida.close();
	
	return 0;
	
}

