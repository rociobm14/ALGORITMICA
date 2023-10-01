// Clase nodo
#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <string>
#include <cstdlib>
#include <valarray>
#include <sstream>
#include <assert.h>

using namespace std;
// Un nodo se caracteriza por su identificador(que en nuestro caso será el numero del mismo) y por el grado que este tenga
class Nodo
{
private:
	int n;
	int grado;

public:
	Nodo()
	{
		n = 0;
		grado = 0;
	}
	// Constructor de la clase que inicializa un nodo, asignandole un valor y un grado
	Nodo(int n1, int g)
	{
		n = n1;
		grado = g;
	}
	// Metodo que devuelve el grado de un nodo
	int getGrado()
	{
		return grado;
	}
	// Metodo que devuelve el valor del nodo
	int getNumNodo()
	{
		return n;
	}
	// Metodo que crea un nodo dados unos parametros
	void setNodo(int n1, int g)
	{
		n = n1;
		grado = g;
	}
	//Metodo que introduce el identificador del nodo
	void setNum(int i)
	{
		n = i;
	}
};
//--------------------------------------------------------------
// Una arista une dos nodos, se representará mediante el pair de nodos que enlaza
class Arista
{
private:
	pair<Nodo, Nodo> enlace;

public:
	// Constructores
	Arista()
	{
		enlace.first.setNodo(0, 0);
		enlace.second.setNodo(0, 0);
	}

	Arista(Nodo nodo1, Nodo nodo2)
	{
		enlace.first = nodo1;
		enlace.second = nodo2;
	}
	// Metodo get
	std::pair<Nodo, Nodo> getEnlace()
	{
		return enlace;
	}

	// Metodo set
	void setArista(Nodo nodo1, Nodo nodo2)
	{
		enlace.first = nodo1;
		enlace.second = nodo2;
	}
};
//--------------------------------------------------------------
class MatrizA
{
private:
	static const int TAM = 10;
	int matriz[TAM][TAM];
	int utiles = 0;
	bool imprimir = false; //modificando eso podemos ver la matriz que se crea en cada iteracion

public:
	//Sobrecarga del operador ()
	int &operator()(const int f, const int c)
	{
		assert(f >= 0 && f < TAM && c >= 0 && c < TAM);
		return matriz[f][c];
	}

	// Constructor por defecto, inicializa la matriz sin conexiones
	MatrizA()
	{
		for (int i = 0; i < TAM; i++)
		{
			for (int j = 0; j < TAM; j++)
			{
				matriz[i][j] = 0;
			}
		}
	}

	// Constructor que inicializa la matriz dado un vector de aristas
	MatrizA(vector<Arista> conexiones)
	{
		auto iter = conexiones.end();
		iter--;
		utiles = iter->getEnlace().first.getNumNodo();

		for (int i = 0; i < utiles; i++)
		{
			for (int j = 0; j < utiles; j++)
			{
				matriz[i][j] = 0;
			}
		}

		for (int i = 0; i < conexiones.size(); i++)
		{
			matriz[conexiones[i].getEnlace().first.getNumNodo()][conexiones[i].getEnlace().second.getNumNodo()] = 1;
		}
	}

	// Metodo que me devuelve el tamaño de la matriz
	int tam()
	{
		return utiles;
	}

	// Metodo que guarda una fila de la matriz
	vector<int> obtenerFila(int k)
	{
		vector<int> resultado;

		if (k < 0 and k > utiles)
		{
			cout << "Valor fuera de rango: " << k << endl;
			return resultado;
		}

		for (int i = 0; i < utiles; i++)
		{
			for (int j = 0; j < utiles; j++)
			{
				if (i == k)
				{
					resultado.push_back(matriz[i][j]);
				}
			}
		}
		return resultado;
	}

	//Metodo que introduce un valor en la matriz
	void setValores(int f, int c, int valor)
	{
		matriz[f][c] = valor;
	}
	
	//Metodo q
	void setNumFilas(int filas)
	{
		utiles = filas;
	}

	//Metodo que imprime la matriz por pantalla teniendo en cuenta el booleano que hay en los métodos privados
	void imprimirMatriz()
	{
		if (imprimir == true)
		{
			cout << "Matriz: " << endl;
			for (int i = 0; i < utiles; i++)
			{
				for (int j = 0; j < utiles; j++)
				{
					cout << matriz[i][j] << " ";
				}
				cout << endl;
			}
		}
	}
};

//--------------------------------------------------------------
	//Metodo que realiza la funcion de seleccion del algoritmo Greedy, el siguiente nodo será el que tenga mayor grado
Arista SeleccionArista(vector<Arista> ar, Nodo v)
{
	int max_gr = 0;
	Arista resultado;
	// Miro con que nodos se conecta v y escojo el que mayor grado tenga
	for (int i = 0; i < ar.size(); i++)
	{
		if (ar[i].getEnlace().first.getNumNodo() == v.getNumNodo()) // encuento la conexion v con el nodo n
		{												  
			max_gr = ar[i].getEnlace().second.getGrado(); // obtengo el grado del nodo con el que se relaciona
			resultado = ar[i];// lo selecciono como la solucion provisional
		}
	}
	// Busco si hay mas conexiones con mi nodo v
	for (int j = 0; j < ar.size(); j++)
	{
		if (ar[j].getEnlace().first.getNumNodo() == v.getNumNodo() and max_gr < ar[j].getEnlace().second.getGrado()) // si el grado de la nueva coincidencia es mayor que el de la anterior
		{ 
			max_gr = ar[j].getEnlace().second.getGrado();
			resultado = ar[j]; // cambio de arista seleccionada
		}
	}

	return resultado;
}
//--------------------------------------------------------------
 	//Funcion auxiliar que me dice que un grafo sigue siendo conexo quitando esa arista o no
bool Factible(vector<Arista> ar)
{
	if (ar.size() == 0) //si no me quedan aristas he llegado al final 
	{
		return true;
	}

	MatrizA nuevoG(ar); // creo un nuevo grafo con las conexiones que me pasan

	nuevoG.imprimirMatriz(); //si queremos podemos ver como se va comprobando la matriz y como va decreciendo conforme se quitan aristas de la misma

	if (nuevoG.tam() <= 1) // si la matriz tiene un tamaño menor o igual a uno solo me quedara una conexion que recorrer
	{
		return true;
	}

	for (int i = 0; i < nuevoG.tam(); i++) // miro si alguna fila de mi matriz esta completa con 0s
	{
		vector<int> fila = nuevoG.obtenerFila(i); // obtengo una fila de la matriz
		bool f = false;
		for (int j = 0; j < fila.size() and f == false; j++) // recorro esa fila, si el bool se pone a true paro de recorrer ya que se que sera factible
		{
			if (fila[j] == 1) // si el valor es 1 pongo el bool a true
			{
				f = true;
			}
		}
		if (f == false)
		{
			return false;
		}
	}
	
	return true;
}
//--------------------------------------------------------------
// Funcion que busca el camino de Euler de un grafo dado partiendo de un nodo, v, dado
vector<Arista> caminosEulerGreedy(MatrizA g, Nodo v, vector<Arista> a)
{
	g.imprimirMatriz();
	vector<Arista> solucion;
	vector<Arista> candidatas = a;

	// Caso base -> el grafo solo contiene un nodo
	if (a.size() == 0)
	{					 // si solo tengo un nodo el vector de aristas sera de tamaño 0 ya que no tengo ninguna conexion
		return solucion; // devuelvo un camino vacío
	}

	while (candidatas.size() > 0) // mientas que tenga aristas por las que pasar y el nodo no sea la solucion
	{
		// selecciono la arista que me lleve desde v al nodo con mayor grado
		Arista x = SeleccionArista(candidatas, v);

		pair<Nodo, Nodo> n = x.getEnlace();
		// Quito la arista seleccionada de la lista de candidatos
		for (auto it = candidatas.begin(); it != candidatas.end();) // recorro el vector de candidatos
		{
			if ((*it).getEnlace().first.getNumNodo() == x.getEnlace().first.getNumNodo() and (*it).getEnlace().second.getNumNodo() == x.getEnlace().second.getNumNodo())
			{						  // cuando encuentro la que he seleccionado
				candidatas.erase(it); // borro lo que hay en esa posicion del vector
			}
			// Borro el nodo simetrico
			else if ((*it).getEnlace().second.getNumNodo() == x.getEnlace().first.getNumNodo() and (*it).getEnlace().first.getNumNodo() == x.getEnlace().second.getNumNodo())
			{						  // cuando encuentro la simetrica a la que he seleccionado
				candidatas.erase(it); // borro lo que hay en esa posicion del vector
			}
			else if (it != candidatas.end())
			{
				it++; //modifico el iterador cuando no se cumplan alguna de las condiciones anteriores, esto se realiza asi ya que cuando tengo la simetrica y el original uno detras de otro nos salimos del tamaño del vector si dejamos el iterador en la cabecera del for 
			}
		}
		
		// Miro si es factible la arista seleccionada, será factible si quitandola se mantiene que el grafo es conexo
		if (Factible(candidatas))
		{
			solucion.push_back(x);	  // la añado al vector solucion
			v = x.getEnlace().second; // actucalizacion de la v, es decir, paso al siguiente nodo
		}
	}

	// Si al finalizar mi conjunto de aristas solucion esta relleno lo devuelvo
	if (solucion.size() > 0){
		return solucion;
	}
}

//--------------------------------------------------------------
int main(int argc, char **argv)
{
	ifstream fsalida;
	
	//Comprobacion del numero de argumentos
	if (argc < 3)
	{
		cerr << "\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
		return 0;
	}

	int N = atoi(argv[2]);
	
	// Abrimos fichero de salida
	fsalida.open(argv[1]);
	
	//Comprobacion de la apertura del fichero
	if (!fsalida.is_open())
	{
		cerr << "Error: No se pudo abrir fichero" << argv[1] << "\n\n";
		return 0;
	}


	vector<Arista> v;
	pair<Nodo, Nodo> nodo;
	MatrizA mA;
	mA.setNumFilas(N);
	string extraccion, tam;
	
	//Si puedo abirir el fichero relleno la matriz de adyacencia del grafo
	if (fsalida.is_open())
	{
		for (int i = 0; i < N; ++i)
		{
			int num = 0;
			getline(fsalida, extraccion);
			for (int j = 0; j < N; ++j)
			{
				int pos = extraccion.find(' '); // devuelve la posicion en el string del primer espacio
				num = stoi(extraccion.substr(0, pos));
				extraccion = extraccion.substr(pos + 1, extraccion.length() - pos - 1);
				mA.setValores(i, j, num);
			}
		}
	}
	
	//Creo el vector de aristas que contiene las conexiones entre nodos
	for (int i = 0; i < mA.tam(); ++i)
	{
		for (int j = 0; j < mA.tam(); ++j)
		{
			if (mA(i, j) == 1)
			{
				nodo.first.setNum(i);
				nodo.second.setNum(j);
				Arista aux(nodo.first, nodo.second);
				v.push_back(aux);
			}
		}
	}

	//Llamada a la funcion greedy
	vector<Arista> resultado = caminosEulerGreedy(mA, v[0].getEnlace().first, v);
	
	//Sacamos el camino por pantalla mostrando los enlaces que se han seguido para pasar por todas las aristas 
	cout << "Resultado: " << endl;
	for (int i = 0; i < resultado.size(); ++i)
	{
		cout << resultado[i].getEnlace().first.getNumNodo() << "->" << resultado[i].getEnlace().second.getNumNodo() << endl;
	}

	cout << endl;
	
	//Cerramos el fichero del que leemos la matriz
	fsalida.close();

	return 0;
}
