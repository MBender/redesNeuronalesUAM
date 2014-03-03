using namespace std;

#include "cargar.h"
#include "adaline.h"

int main(int argc, char **argv){
	//check parameters
	Test t = cargar(argv[1]);
	adaline a(0,t,0.8);
	a.train();
	a.test();
       
    return 0; 
}