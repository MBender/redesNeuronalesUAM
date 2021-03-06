using namespace std;

#include "cargar.h"
#include "perceptron.h"

int main(int argc, char **argv){
	//check parameters
	Test t = cargar(argv[1]);
	perceptron p(0,t,0.8);
	if(argc == 2){
		p.train();
		p.test();
    }else if(argc == 3){
    	p.train(t);
    	t = cargar_static(argv[2]);
		p.test(t);
    }   
    return 0; 
}