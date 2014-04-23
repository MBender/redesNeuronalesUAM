#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cstdlib>

vector<double> read_serie(string archivo){
	ifstream leer;
	leer.open(archivo.c_str());
	std::vector<double> in_raw; 
	while(!leer.eof()) {
		double number;
		leer >> number;
		in_raw.push_back(number);
	}
	leer.close();
	return in_raw;
}

static void adapta_fichero_serie(string nombre_entrada, string nombre_salida, int np){

	std::vector<double> serie_raw = read_serie(nombre_entrada);

	//ahora creamos la serie
	//miramos cantidad para particion
	int size = serie_raw.size();

	//calculamos cantidad de test
	int size_train = size*0.25;

	//creamos vector de entrenamiento
	std::vector<pair> training;
	for (int i = 0; i < size_train; ++i)
	{
		std::pair<vector, double> training_pair;
		std::vector<double> v;
		double clase;
		for(int j = 0; j <= np; j++){
			if(j = np){
				clase = serie_raw[i+j];
			}else{
				v.push_back(serie_raw[i+j]);
			}
		}
		training_pair.first = v;
		training_pair.second = clase;
		training.push_back(training_pair);
	}

	//creamos la red neuronal


	//primero creamos un perceptron, con una salida, y un numero de entradas igual a np.
	//Tras eso, habrá que crear la serie de predicción.
	//usaremos el fichero, leyendolo y cogiendo las N primeras lineas para predecir la enesima.
	//generamos así el sistema de predicciones.
	//generaremos la serie de la siguiente manera: crearemos el vector de vectores inicial, de training.

	//ahora, procederemos a realizar el entrenamiento. Intentaremos predecir dentro de nuestra serie.

	//para ello, habra que crear serie de training. Consistira en la predicción de M valores, cogiendo en total 
	//hasta el valor M + np.

	//tras ello, habrá que entrenar la red neuronal. Llamaremos a la función de training pasandole los valores.

	//por ultimo, realizar el test

}