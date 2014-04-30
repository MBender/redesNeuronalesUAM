using namespace std;

#include "perceptron.h"
#include <iostream>
#include <cstdio>
//invocacion de main:
//  ./perceptron <neuronas> <constante entrenamiento> <particion entrenamiento> <nombre archivo entrada> <nombre arhcivo salida> <np>
//  ./perceptron <particion entrenamiento> <nombre archivo entrada> <nombre arhcivo salida> <np>
// o
//  ./perceptron <fichero> 
// dejo la estandar por comodidad
int main(int argc, char **argv){
	if(argc ==4) {
		//neuronas y constante y particion, son constantes
		//check parameters
		std::string arg = argv[3];
		float part = ::atof(arg.c_str());
		vector<float>  raw_data;
		perceptron p = adapta_fichero_serie(argv[1],argv[2],part, 15, &raw_data);

		raw_data = read_serie(argv[1]);

		p.procesar_recursiva(raw_data, part);
	}else if(argc==5){
		std::string arg = argv[3];
		float part = ::atof(arg.c_str());
		vector<float>  raw_data;
		arg = argv[4];
		float nneu = ::atof(arg.c_str());
		perceptron p = adapta_fichero_serie(argv[1],argv[2],part, nneu, &raw_data);

		raw_data = read_serie(argv[1]);

		p.procesar_recursiva(raw_data, part);
	}

    return 0;
}