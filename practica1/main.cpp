using namespace std;

void main(int argc, void **argv){
	//check parameters
	Test t = cargar(argv[1]);
	perceptron p = new perceptron(0,t,0.8);
	p.train();
	p.test();
        
}