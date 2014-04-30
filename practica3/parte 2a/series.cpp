#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include "series.h"
#include "perceptron.h"

using namespace std;


vector<float> read_serie(string archivo){
	ifstream leer;
	leer.open(archivo.c_str());
	std::vector<float> in_raw; 
	while(!leer.eof()) {
		float number;
		leer >> number;
		in_raw.push_back(number);
		//cout << number << endl;
	}
	leer.close();
	return in_raw;
}

perceptron adapta_fichero_serie(string nombre_entrada, string nombre_salida, int np, 
	int nneurons, std::vector<float> *datos){

	std::vector<float> serie_raw = read_serie(nombre_entrada);
	datos = &serie_raw;
	
	//abrimos fichero de salida
	ofstream escribir(nombre_salida.c_str());

	//ahora creamos la serie
	//miramos cantidad para particion
	int size = serie_raw.size();

	//calculamos cantidad de test
	int size_train = size*0.25;

	//introducimos los datos sobre la serie
	escribir << np << " " << 2 << endl;

	//creamos vector de entrenamiento
	std::vector<Par> training;
	for (int i = 0; i < size-np; ++i)
	{
		Par training_pair;
		std::vector<float> v;
		std::vector<int> v2;
		float clase;
		for(int j = 0; j <= np; j++){
			if(j == np){
				if(serie_raw[i+j]>serie_raw[i+j-1]){//crece
					v2.push_back(1);
					v2.push_back(0);
					escribir << 1 << " " << 0 << endl;
				}else{ //  no crece
					v2.push_back(0);
					v2.push_back(1);
					escribir << 0 << " " << 1 << endl;
				}
			}else{
				//cout << " " << serie_raw[i+j];
				
				v.push_back(serie_raw[i+j]);
				escribir << serie_raw[i+j] << " ";
			}
			//cout << clase << endl;
		}
		escribir << endl;
		training_pair.first = v;
		training_pair.second = v2;
		training.push_back(training_pair);
	}
	//creamos la red neuronal
	perceptron p(nneurons
		,0.5,training, 0.1, true, false);

	escribir.close();

	//y entrenamos
	p.multi_train();

	//testeamos
	p.multi_test();


	return p;
}