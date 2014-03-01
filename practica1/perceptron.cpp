#include <vector>

using namespace std;

class perceptron{

public:

	perceptron(int num_hidden, Test data_training, float rate){
		num_att = data_training[0].first.size();
		num_class = data_training[0].second.size();

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

		//input.push_back(new Neuron());
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
					l.from = i;
					l.to = j;
					l_y.push_back(l);
				}
				
			}
		}
	}

	

	

	void multi_train(){

	};


	void test(){
            int ndata = 0;
            for(vector<vector>::iterator i = testing_data.begin(); i!=testing_data.end(); ++i){
                for(vector<Neuron>::iterator in_n = input.begin(); in_n != input.end(); ++in_n){
                    in_n->in_value= *i[ndata];
                }
                for(vector<Link>::iterator in_link = l_z.begin(); in_link != l_z.end(); ++in_link){
                    in_link->sumLink();
                }
                int trueVal = 0;
                bool evaled = false;
                for(vector<Neuron>::iterator out_n = y.begin(); out_n != y.end(); ++out_n){
                    trueVal = out_n->evalNeuron();
                    if(trueVal == 1 && evaled == false){
                        //mirar aqui la condicion habitual
                    }
                        
                }
                
                ndata++;
            }
	}
        
        
	void test(vector<float> v){
                
	}
        
        void train(){
		//si es simple, simple_train
		if(z.size() == 0) return simple_train();
		//si es complejo, multi_train
		else multi_train();
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
        //data for test
        vector<vector> testing_data;
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
                        stop_cond = false;
			int numOk=0;
			int numInstance=0;
			for (vector<>::iterator caso = training_data.begin(); caso != training_data.end(); ++caso)
			{
				numInstance++;
				//por cada caso de entrenamiento, inicializar neuronas
				int i=0;
				//TODO comprobar estos dos
                                
				for (std::vector<float>::iterator att = ((Caso)caso).first.begin(); att != ((Caso)caso).first.end(); ++att)
				{
					input[i].in_value = *att;
				}
				//e interpretamos la clase
				int clase=0;
				for (std::vector<int>::iterator citr = ((Caso)caso).second.begin(); citr != ((Caso)caso).second.end(); ++citr)
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
					float sal = out->evalNeuron(sigmoidal);
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
					numOk++;
                                        stop_cond = true;
					//acierto. no entrena
				}else{
					//error
					for (vector<Link>::iterator links = l_y.begin(); links != l_y.end(); ++links){
						links->weight = links->weight 
                                                        + learn_rate*links->from->in_value;
					}
				}


			}
		}
	}

	float sigmoidal(float in_value){
		if(in_value > threshold) return 1;
		else if(in_value <= -threshold) return 0;
		else return -1;	
	}
        
        
};