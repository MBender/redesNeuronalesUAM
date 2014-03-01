#include <vector>

using namespace std;

class adaline{

public:

	adaline(int num_hidden, Test data_training, int num_classes, float rate){
		num_att = data_training[0].size() - num_classes;
		num_class = num_classes;

		training_data = data_training;

		//create the neurons
			//input
		for (int i = 0; i < num_att; ++i)
		{
			input.push_back(new Neuron());
		}
		//add a Bias
			Neuron in_bias = new Neuron();
			in_bias.in_value = 1;
			input.push_back(in_bias);
			//hidden
		for (int i = 0; i < num_hidden; ++i)
		{
			z.push_back(new Neuron());
		}
		//if there is a hidden layer, dont add bias neuron
		if(z.size()!=0){
			Neuron z_bias = new Neuron();
			z_bias.in_value = 1;
			z.push_back(z_bias);
		}

		//input.push_back(new N)
			//output
		for (int i = 0; i < num_class; ++i)
		{
			y.push_back(new Neuron());
		}

		//create the links
		//TODO comprobar estos for
		if(z.size()==0){//if it is a single perceptron
			//output
			for (std::vector<Neuron>::iterator i = input.begin(); i != input.end(); ++i)
			{
				for (std::vector<Neuron>::iterator j = y.begin(); j != y.end(); ++j)
				{
					Link l = new Link();
					l.from = *((Neuron*)(i));
					l.to = *((Neuron*)(j));
					l_y.push_back(l);
				}
				
			}
		}
	}

	void train(){
		//si es simple, simple_train
		if(z.size() == 0) return simple_train();
		//si es complejo, multi_train
		else multi_train();
	}

	

	void multi_train(){

	};


	void test(){

	}

private:

	/*The elements of the perceptron*/
	//neurons
	std::vector<Neuron> input; 
	std::vector<Neuron> z;
	std::vector<Neuron> y;
	//links
	//std::std::vector<Link> l_input;
	std::vector<Link> l_z;
	std::vector<Link> l_y;
	//data for training
	Test training_data;
	//number of atts and classes
	int num_att;
	int num_class;
	//learning rate
	float learn_rate;
	//umbral
	float threshold;

	void simple_train(){
		//el numero de clases es el tamanio de un dato, menos numAtt
		bool stop_cond = false;
		while(!stop_cond){
			int numOK=0;
			int numInstance=0;
			for (std::vector<Caso>::iterator caso = training_data.begin(); caso != training_data.end(); ++caso)
			{
				numInstance++;
				//por cada caso de entrenamiento, inicializar neuronas
				int i=0;
				//TODO comprobar estos dos
				for (std::vector<vector<float>::iterator att = caso->first.begin(); att != caso->first.end(); ++att)
				{
					input[i].in_value = att;
				}
				//e interpretamos la clase
				int clase=0;
				for (std::vector<vector<int>::iterator citr = caso->second.begin(); citr != caso->second.end(); ++citr)
				{
					if(*citr == 1) return;
					clase++;
				}

				//ahora, procedemos a calcular las salidas
					//propagamos las entradas
				for (std::vector<Link>::iterator link = l_y.begin(); link != l_y.end(); ++link)
				{
					link->sumLink();
				}
					//calculamos las salidas, y vemos la clase respuesta
				int pred_class = -1;
				int cnt = 0;
				for (std::vector<Neuron>::iterator out = y.begin(); out != y.end(); ++out)
				{
					float sal = ((Neuron*)(out))->evalNeuron(identity);
					if(sal == 1f){
						if(pred_class != -1){
							pred_class = -2;
							continue;
						}else{
							pred_class = cnt;
						}
					} 
					cnt++;
				}

				if(pred_class == clase){
					numOK++;
					//acierto. no entrena
				}else{
					//error
					for (vector<Link>::iterator links = l_y.begin(); links != l_y.end(); ++links){
						links->weight = links->weight + learn_rate*links->from.in_value;
					}
				}


			}
		}
	}

	float identity(float in_value){
		return in_value;
	}
};
