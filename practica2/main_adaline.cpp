using namespace std;

#include "cargar.h"
#include "adaline.h"

int main(int argc, char **argv){
	//check parameters
	Test t = cargar(argv[1]);
	adaline a(0,t,0.8);
	if(argc == 2){
		a.train();
		a.test();
    }else if(argc == 3){
    	a.train(t);
    	Test t2 = cargar_static(argv[2]);
    	cout << "procediendo a clasificar lo desconocido\n";
		a.test(t2);
    }
       
    return 0; 
}