using namespace std;

#include "cargar.h"
#include "perceptron.h"
#include <iostream>
#include <cstdio>
//invocacion de main:
//  ./perceptron <neuronas> <constante entrenamiento> <particion entrenamiento> <nombre archivo train> <OPCIONAL:nombre arhcivo test>
// o
//  ./perceptron <fichero> 
// dejo la estandar por comodidad
int main(int argc, char **argv){
	if(argc ==2) {
		//check parameters
		Test t = cargar(argv[1]);
		perceptron p ( 15, 0.25,t, 0.5, true, true);
		p.train();
		p.multi_test(); //MAL. no necesita ahora mismo clasificar, solo necesita c
	}else if(argc==5){
		std::string arg = argv[2];
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
		 
	}else if(argc==6){
		std::string arg = argv[2];
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
		Test t2 = cargar(argv[5]);
		//se testea con el propio archivo
		if(is_part==false)p.multi_test(t);
		else p.multi_test();
		//y ahora con el otro
		p.multi_test(t2);
		
	}

    return 0;
}