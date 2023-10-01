#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;
//Clase acciones
class Accion {
private:
	double precio;
	double beneficio;
	double comision;
public:
	//Constructor por defecto con todo a 0
	Accion() {
		precio = 0;
		beneficio = 0;
		comision = 0;
	}
	//Constructor con par�metros
	Accion(double p, double b, double c) {
		precio = p;
		beneficio = b;
		comision = c;
	}
	//Consultores 
	double Beneficio() {
		return beneficio;
	}

	double Precio() {
		return precio;
	}

	double Comision() {
		return comision;
	}

	//Modificadores
	void SetBeneficio(double x) {
		beneficio = x;
	}
	void SetPrecio(double p) {
		precio = p;
	}
	void SetComision(double c) {
		comision = c;
	}
};

//Algoritmo de fuerza bruta
double invertirBolsa(vector<Accion> A, int X) {
	double valor=0.0;
	//Casos base
	if (X == 0) {
		cout << "Base 1" << endl;

		return 0;
	}
	else if (A.size() == 0) {
		cout << "Base 2" << endl;

		return 0;
	}

	else {
		for(int i = 1; i < A.size();i++){
			for(int j = 1; j < X; j++){
				
				double valor1=0, valor2 = 0;
				valor1 = A[i].Precio()*A[i].Beneficio();
				valor2 = A[i].Precio()*A[i].Beneficio() + (j-A[i].Precio()-A[i].Comision());

				if(j < A[i].Precio()) //En el caso de que no tenga dinero suficiente 
					valor = valor1; //tomo el valor del beneficio de la accion anterior.

				if(valor1 > valor2)
					valor = valor1;
				else	
					valor = valor2;
				cout << valor << endl;
			}
			
		}
		
	}
	return valor;
}

//Algoritmo PD
void invertirBolsaPD(vector<Accion> A, int X) {
	double **T; //creacion de la matriz dinamica

	T = new double* [A.size()]; //reservo las filas
	for (int i = 0; i < A.size(); i++) {
		T[i] = new double[X + 1]; //reservo las columnas
	}

	//Relleno del caso base de la matriz -> solo puedo comprar una accion -> me quedo con el beneficio de esa accion
	for (int j = 0; j < X; j++) {
		if(A[0].Precio()+A[0].Comision() > j)
			T[0][j] = 0;
		else
			T[0][j] = A[0].Precio()*A[0].Beneficio()-A[0].Comision();
	}
	
	//Relleno del caso base de la matriz -> No tengo dinero
	for (int i = 0; i < A.size(); i++) {
		T[i][0] = 0;
	}


	//Caso general 
	for (int i = 1; i < A.size(); i++) {
		for (int j = 1; j <= X; j++) {
			//Calculo las partes de la recurrencia
			double aux1=0, aux2=0;
			aux1 = T[i - 1][j];
			
			//calculo de la parte de la ecuacion recurrente en el caso de que se compre la accion i 
			double a1 = (A[i].Beneficio() * A[i].Precio());
			int a2 = j - A[i].Comision() - A[i].Precio();
			aux2 = a1 + T[i - 1][a2];
			//Si la posicion de j es una a la que no puedo acceder la pongo la anterior
			if(a2 < 0){	
				T[i][j] = aux1;
			}
			//Si puedo pagar la accion, me quedo con el maximo
			if(A[i].Precio() + A[i].Comision() < j)
				T[i][j] = max(aux1,aux2);
			//Si no la puedo pagar
			else
				T[i][j] = aux1;
		}
	}
	
	//Muestro por pantalla la matriz con los calculos realizados
	cout << "Matriz de beneficios:" << endl;
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < X; j++) {
			cout << T[i][j] << ' ';
		}
		cout << endl;
	}
	
	cout << "\nBeneficio Maximo con PD: " << T[A.size()-1][X-1] << endl;
	
	//Liberacion de la memoria
	for(int i = 0; i < A.size(); i++){
		delete [] T[i];
	}
	delete [] T;
}

//Programa principal 
int  main(int argc, char **argv) {

	ifstream entrada;

	if(argc < 3){
		cerr << "<\nError: El programa debe ser: ./ejecutable fichero dinero\n";
		return 0;

	}

	int dinero = stoi(argv[2]);
	if(dinero < 7){
		cerr << "Necesitas una cantidad minima de 10 para poder invertir en esta empresa" << endl;
		return 0;
	}
	vector <Accion> acciones;
	string linea;
	//abrimos el fichero
	entrada.open(argv[1]);
	if(entrada.is_open()){
		//mientras sigan habiendo líneas en el fichero, las va leyendo
		while(getline(entrada, linea)){
			//fracciona cada elemento de la línea que se está analizando
			stringstream fraccion(linea);
			//datos que obtendremos de la lectura de cada línea
			double precio, comision;
			double beneficio;
			//los lee
			fraccion >> precio >> beneficio >> comision;
			//va creando objetos de acciones y los va metiendo al vector de acciones.
			Accion a(precio, beneficio, comision);
			acciones.push_back(a);
		}
		
	}

	//Comprobación de que se guardan bien los datos en el vector de acciones
	cout << "Fichero de forma: <precio> <beneficio> <comision>" << endl;
	for (int i=0; i<acciones.size(); i++){
		cout << acciones[i].Precio() << " " << acciones[i].Beneficio() << " " << acciones[i].Comision() << endl;
	}
	
	cout << endl; 
	
	cout << "-----Llamada al algortimo de Fuerza Bruta-----" << endl;
	cout << "Beneficio Maximo: " << invertirBolsa(acciones,dinero) << endl;
	
	cout << "-----Llamada al metodo de PD-----" << endl;
	invertirBolsaPD(acciones,dinero);

	return 0;
	
}
