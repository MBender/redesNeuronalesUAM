using namespace std;

#include "cargar.h"
#include "perceptron.h"

int main(int argc, char **argv){
	//check parameters
	Test t = cargar(argv[1]);
	perceptron p(0,t,0.8);
	p.train(argv[1]);
	p.test(argv[2]);
       
    return 0; 
}