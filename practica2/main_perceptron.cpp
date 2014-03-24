using namespace std;

#include "cargar.h"
#include "perceptron.h"
#include <iostream>
#include <cstdio>

int main(int argc, char **argv){
	if(argc > 1) {
		//check parameters
		Test t = cargar(argv[1]);
		perceptron p ( 10 , t, 0.5, true);
		p.train(t);
		p.multi_test(t); //MAL. no necesita ahora mismo clasificar, solo necesita c
	}
    return 0; 
}