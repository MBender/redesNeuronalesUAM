using namespace std;

#include "cargar.h"
#include "adaline.h"

int main(int argc, char **argv){
	//check parameters
	Test t = cargar(argv[1]);
	adaline a(0,t,0.8);
	a.train(argv[1]);
	a.test(argv[2]);
       
    return 0; 
}