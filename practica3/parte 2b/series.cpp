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
	//ahora creamos la serie
	//miramos cantidad para particion
	int size = serie_raw.size();
	//preparamos fichero para escribir
	ofstream escribir(nombre_salida.c_str());
	//creamos vector de entrenamiento
	std::vector<Par> training;

	//escribimos la informacion sobre los datos
	escribir << np << 1 << endl;
	for (int i = 0; i < size -np; ++i)
	{
		Par training_pair;
		std::vector<float> v;
		float clase;
		for(int j = 0; j <= np; j++){
			if(j == np){

				clase = serie_raw[i+j];
				escribir << clase;
			}else{
				//cout << " " << serie_raw[i+j];
				escribir << serie_raw[i+j];
				v.push_back(serie_raw[i+j]);
			}
			//cout << clase << endl;
		}
		escribir << endl;
		training_pair.first = v;
		training_pair.second = clase;
		training.push_back(training_pair);
	}
	//creamos la red neuronal
	perceptron p(nneurons
		,0.5,training, 0.2, true, false);

	//entrenamos
	p.multi_train();	

	//y hacemos el test
	p.multi_test();
	escribir.close();
	return p;
}