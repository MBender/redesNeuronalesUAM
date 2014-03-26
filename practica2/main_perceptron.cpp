using namespace std;

#include "cargar.h"
#include "perceptron.h"
#include <iostream>
#include <cstdio>

int main(int argc, char **argv){
	if(argc > 1) {
		//check parameters
		Test t = cargar(argv[1]);
		perceptron p ( 10, 0.25,t, 0.5, true);
		p.train();
		p.multi_test(); //MAL. no necesita ahora mismo clasificar, solo necesita c
	}
    return 0;
}