#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

using namespace std;

void llenarFila(vector<vector<bool > > & tabla, int i, int n, bool valor) {
	for(int j=0; j < n; j++)
		tabla[i][j] = valor;
}

void llenarColumna(vector<vector<bool > > & tabla, int j, int n, bool valor) {
	for(int i=0; i < n; i++)
		tabla[i][j] = valor;
}

void imprimirBipolar(vector<vector<bool > > & tabla, int n, ofstream & escribir) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(tabla[i][j])
				escribir << 0.9 << " ";
			else
				escribir << -0.9 << " ";
		}	
	}
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(tabla[i][j])
				escribir << 0.9 << " ";
			else
				escribir << -0.9 << " ";
		}
	}
	escribir << endl;
}

void imprimir10(vector<vector<bool > > & tabla, int n, ofstream & escribir) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {

		}	
	}
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			escribir << tabla[i][j] << " ";
		}
	}
	escribir << endl;
}

void construye_bd_autoencoder_particular(int n, string archivo, void (* imprimir)(vector<vector<bool > > & tabla, int n, ofstream & escribir) ) {
	ofstream escribir;
	escribir.open(archivo.c_str());
	escribir << n*n << ' ' << n*n << endl;
	vector<vector<bool > > actual (n, vector<bool> (n, 0));
	
	//imprimir en 0
	imprimir(actual, n, escribir);

	//Lleno la fila i
	for(int i=0; i < n; i++) {
		llenarFila(actual, i, n, 1);
		imprimir(actual, n, escribir);
		llenarFila(actual, i, n, 0);
	}

	//Lleno la columna j
	for(int j=0; j<n; j++) {
		llenarColumna(actual, j, n, 1);
		imprimir(actual, n, escribir);
		llenarColumna(actual, j, n, 0);
	}

	//Lleno las combinaciones
	for(int i=0; i < n; i++) {
		//primero fila
		llenarFila(actual, i, n, 1);
		for(int k=i+1; k<n; k++) {
			llenarFila(actual, k, n, 1);
			imprimir(actual, n, escribir);
			llenarFila(actual, k, n, 0);
		}
		//primero columna
		for(int k=0; k<n; k++) {
			llenarFila(actual, i, n, 1);
			llenarColumna(actual, k, n, 1);
			imprimir(actual, n, escribir);
			llenarColumna(actual, k, n, 0);
		}
		llenarFila(actual, i, n, 0);
	}

	//Lleno las combinaciones de columnas
	for(int i=0; i < n; i++) {
		llenarColumna(actual, i, n, 1);
		for(int k=i+1; k<n; k++) {
			llenarColumna(actual, k, n, 1);
			imprimir(actual, n, escribir);
			llenarColumna(actual, k, n, 0);
		}
		llenarColumna(actual, i, n, 0);
	}

	escribir.flush();
	escribir.close();
}

void construye_bd_autoencoder(int n, string archivo) {
	construye_bd_autoencoder_particular(n, archivo, imprimir10);
}

int main(int argc, char **argv) {
	if(argc > 3) {
		if (atoi(argv[2]) == 0)
			construye_bd_autoencoder(atoi(argv[1]), argv[3]);
		else
			construye_bd_autoencoder_particular(atoi(argv[1]), argv[3], imprimirBipolar);
	} else {
		cout << "Forma de uso:" << endl;
		cout << "\t ./creador <#Pixeles de alto> <Codificacion> <Archivo de salida>" << endl;
		cout << "Importante: la codificacion puede ser \n\t Con 1s y 0s (ingresar '0') \n\t Con '-0.9' y '0.9' (ingresar '1')" << endl;
	}

	return 0;
}