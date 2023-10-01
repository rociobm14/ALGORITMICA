
#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <iostream>
#include <fstream> // Para usar ficheros
#include<vector>
using namespace std;

void EliminaOcurrencias(int v[], int &utiles){
    
    const int max = utiles;
    int aux[max];
    int util = 0;

    for (int i=0; i<utiles; i++){

		//Si la i es 0, se inicializará el vector auxiliar y añadimos el primer valor
		//para ir comparando valores
        if (i == 0){
            aux[i] = v[i];
            util++;

        }

		//Cuando la i>0, se irá seleccionando qué elementos se van añadiendo al vector auxiliar
		//en función de si están o no repetidos en el vector auxiliar.
        else{

			//utilizamos un booleano para comprobar que el elemento de v[] que estamos analizando
			//no coincide con ningún elemento de los que se encuentran en aux[]
            bool repetido = false;
            for (int j=0; j<util && !repetido; j++){

				//Si coinciden, significa que es un valor repetido, por tanto no se añadirá al vector auxiliar.
                if(aux[j] == v[i])
                    repetido = true;

            }

			//Si el booleano sigue a false, significa que ese elemento de v[] no se encuentra en el vector aux
			//por tanto, se añadirá ya que no sería un elemento repetido
            if (!repetido){
                aux[util] = v[i];
                    util++; //aumentamos el valor de util ya que hemos añadido un nuevo elemento al vector
            }
            
        }
    }
	//Redimensionamos utiles al valor de util, para rellenar v[] con los valores necesarios de aux[]
    utiles = util;

	//Volcamos los elementos de aux[] en v[]
    for (int i=0; i<utiles; i++){
        v[i] = aux[i];
    }
             
}

int main(int argc, char *argv[]) {
	
	int *v;
	int n, i, argumento;
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
	double tejecucion; // tiempo de ejecucion del algoritmo en ms
	unsigned long int semilla;
	ofstream fsalida;
	
	if (argc <= 3) {
		cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
		cerr<<argv[0]<<" NombreFicheroSalida Semilla tamCaso1 tamCaso2 ... tamCasoN\n\n";
		return 0;
	}
	
	// Abrimos fichero de salida
	fsalida.open(argv[1]);
	if (!fsalida.is_open()) {
		cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
		return 0;
	}
	
	// Inicializamos generador de no. aleatorios
	semilla = atoi(argv[2]);
	srand(semilla);
	int utiles_final = 0;
	
	// Pasamos por cada tamaÒo de caso
	for (argumento= 3; argumento<argc; argumento++) {
		
		// Cogemos el tamanio del caso
		n= atoi(argv[argumento]);
		
		// Reservamos memoria para el vector
		v= new int[n];
		
		// Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
		for (i= 0; i<n; i++)
			v[i]= rand()%n;
		
		cerr << "Ejecutando EliminaOcurrencias para tam. caso: " << n << endl;
		
		t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
		EliminaOcurrencias(v, n); // Ejecutamos el algoritmo para tamaÒo de caso tam
		tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
	

		unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
		
		cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< n<<endl;
		
		// Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida<<n<<" "<<tejecucion<<"\n";
		
		
		// Liberamos memoria del vector
		delete [] v;
	}
	
	// Cerramos fichero de salida
	fsalida.close();
	
	return 0;
}


