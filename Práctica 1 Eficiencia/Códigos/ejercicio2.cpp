#include <iostream>
#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <fstream> // Para usar ficheros


using namespace std;

void OrdenarInserccion(int v[], int utiles){
	int a_desplazar;
   	int i;

	for (int izda = 1; izda <= utiles; izda++){ //recorremos el vector del inicio al final 
		a_desplazar = v[izda]; //establezco el elemento candidato a desplazarse

		for (i = izda; i > 0 && a_desplazar < v[i-1]; i--) //recorro del final al inicio el vector y si se cumple la condicion de
														// que el elemento seleccionado es menor que el ultimo elemento del vector
			v[i] = v[i-1]; //realizo el intercambio

		v[i] = a_desplazar; //establezco mi nuevo elemento a desplazar 
	}
}

void EliminaOcurrencias(int v[], int &utiles){
    const int max = utiles;
    int aux[utiles];
    int util = 0;

    //Recorre el vector hasta utiles -1 porque el último valor no se comparará con ninguno
    for (int i=0; i<utiles-1; i++){
        //Para i=0, se inicializa el auxiliar con el primer elemento del vector original para ir
        //comparando elementos.
        if(i==0){
            aux[i] = v[i];
            util++; 
            //Compara el primer valor del vector con el siguiente, y si el siguiente es mayor, se añadiría al vector aux
            if (v[i] < v[i+1]){
                aux[util] = v[i+1];
                util++;
            }
        }

        //Para i>1, va comparando con el valor siguiente (i+1) y como suponemos que el vector de entrada está ordenado,
        //si v[i] < v[i+1] se añade v[i+1], pues  significará que es un nuevo elemento.
        else{
            if (v[i] < v[i+1]){
                aux[util] = v[i+1];
                util++;   
            }
        } 
    }

    //Redimensionamos utiles a util
    utiles = util;

    //Volcamos el vector original
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
		//Ordenamos el vector para que se cumpla la precondicion
		OrdenarInserccion(v,n);
		
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
