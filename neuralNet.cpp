#include <vector>

class NeuralNet{
protected:

public:

	int _nlayer;
	int _nInput;
	int _nOutput;

	std::vector<Neuron> _neurons;
	std::vector<Link> _links;


private:
	virtual float evalFun(float value);

	virtual void setInputs(float *inputs){
		//busca las neuronas de capa 0, y agrega en orden
		int c = 0;
		for (std::vector<Neuron>::iterator i = _neurons.begin(); i != _neurons.end(); ++i)
		{
			if(i.nlayer != 0) continue;
			i.in_value = inputs[c++]; 
		}
	}

	virtual void executeLayer(int nlayer){
		for (std::vector<Neuron>::iterator i = _neurons.begin(); i != _neurons.end(); ++i)
		{
			if(i.nlayer != nlayer) continue;
			i.evalNeuron(evalFun); 
		}
	}

	virtual void executeLinks(){
		for (std::vector<Link>::iterator i = _links.begin(); i != _links.end(); ++i)
		{
			i.sumLink();
		}
	}
}