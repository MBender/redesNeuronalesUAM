using namespace std;

#include "cargar.h"
#include "perceptron.h"
#include "series.h"
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
		vector<float> * raw_data;
		perceptron p = adapta_fichero_serie(argv[1],argv[2],part, 5, &raw_data);
		procesar_recursiva(*raw_data, part);
		p.train();
		p.multi_test(); //MAL. no necesita ahora mismo clasificar, solo necesita c
	}else if(argc==7){
		/*std::string arg = argv[2];
		float learn_rate = ::atof(arg.c_str());
		arg = argv[3];
		float part = ::atof(arg.c_str());
		bool is_part = true;
		if(part==0)is_part = false;
		arg = argv[1];
		int znum = ::atoi(arg.c_str());
		Test t = cargar(argv[4]);
		perceptron p ( znum, part,t, learn_rate, is_part, false);
		p.train();
		if(is_part==false)p.multi_test(t);
		else p.multi_test();
		 */
	}

    return 0;
}