#include "perceptron.h"

//class perceptron

	float sigmoidal(void* context, float in_value, float threshold){
		if(in_value > threshold) return 1;
		else if(in_value <= -threshold) return 0;
		else return -1;	
	}
        
        //usamos esto, porque suponemos multiclase, no solo biclase, y con multiples neuronas de salida
    float sigmoidal_simple(float in_value, float threshold){
		if(in_value > threshold) return 1;
		else if(in_value <= threshold) return 0;
	}

	perceptron::perceptron(int num_hidden, Test data_training, float rate){
		num_att = data_training[0].first.size();
		num_class = data_training[0].second.size();

                int c = 0;
                for(; c < data_training.size()*(2/3); c++){
                    training_data.push_back(data_training[c]);
                }
                for(; c < data_training.size(); c++){
                    testing_data.push_back(data_training[c]);
                }
		//create the neurons
			//input
		for (int i = 0; i < num_att; ++i)
		{
			input.push_back(Neuron());
		}
		//add a Bias
			Neuron in_bias;
			in_bias.in_value = 1;
			input.push_back(in_bias);
			//hidden
		for (int i = 0; i < num_hidden; ++i)
		{
			z.push_back(Neuron());
		}
		//if there is a hidden layer, dont add bias neuron
		if(z.size()!=0){
			Neuron z_bias;
			z_bias.in_value = 1;
			z.push_back(z_bias);
		}

		//input.push_back(new Neuron());
			//output
                //solo una neurona de salida
		//for (int i = 0; i < num_class; ++i)
		//{
        y.push_back(Neuron());
		//}

		//create the links
		//TODO comprobar estos for
		if(z.size()==0){//if it is a single perceptron
			//output
			for (std::vector<Neuron>::iterator i = input.begin(); i != input.end(); ++i)
			{
				for (std::vector<Neuron>::iterator j = y.begin(); j != y.end(); ++j)
				{
					Link l;
					l.from = &i[0];
					l.to = &j[0];
					l_y.push_back(l);
				}
				
			}
		}
	}




	void perceptron::test(){
            int ndata = 0;
            int countOK = 0;
            for(Test::iterator i = testing_data.begin(); i!=testing_data.end(); ++i){
                for(vector<Neuron>::iterator in_n = input.begin(); in_n != input.end(); ++in_n){
                    in_n[0].in_value= i[0].first[ndata];
                }
                for(vector<Link>::iterator in_link = l_z.begin(); in_link != l_z.end(); ++in_link){
                    in_link[0].sumLink();
                }
                int clase = 0;
                int c = 0;
                float sal = y[0].evalNeuron(0, threshold, &sigmoidal);
                if(sal == 1){
                    clase = 1;
                }else if(sal == -1){
                    clase = 2;
                }
                //now, check the correctness of classifier
                int trueClass = 0;
                c = 1;
                for(vector<int>::iterator class_i = i->second.begin(); class_i != i->second.end(); ++class_i){
                    if(*(class_i)==1){
                        trueClass = c;
                    }
                    c++;
                }
                if(clase != 0){
                    if(clase == trueClass){
                        countOK++;
                    }
                }
                ndata++;
            }
	}
     
        
    void perceptron::train(){
		//si es simple, simple_train
		//if(z.size() == 0) return simple_train();
		//si es complejo, multi_train
		//else multi_train();
		return simple_train();
	}

	void perceptron::simple_train(){
		//el numero de clases es el tamanio de un dato, menos numAtt
		bool stop_cond = false;
                int epoch = 0;
		while(!stop_cond){
                        stop_cond = false;
			int numOk=0;
			int numInstance=0;
			for (vector<Caso>::iterator caso = training_data.begin(); caso != training_data.end(); ++caso)
			{
				numInstance++;
				//por cada caso de entrenamiento, inicializar neuronas
				int i=0;
				//TODO comprobar estos dos
                                
				for (std::vector<float>::iterator att = caso[0].first.begin(); att != caso[0].first.end(); ++att)
				{
					input[i].in_value = *att;
				}
				//e interpretamos la clase
				int clase=0;
				for (std::vector<int>::iterator citr = caso[0].second.begin(); citr != caso[0].second.end(); ++citr)
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
				int pred_class = 0;
				int cnt = 0;
                //solo una neurona de salida en este caso, 2 clases (codigo simple)
                float sal = y[0].evalNeuron(0, threshold, &sigmoidal);
                if(sal == 1){
                    pred_class = 1;
                }else if(sal == -1){
                    pred_class = 2;
                }
                                
                /* este caso es para multiples neuronas de salida, por simplicidad de codigo, queda descartado
				for (std::vector<Neuron>::iterator out = y.begin(); out != y.end(); ++out)
				{
					float sal = out->evalNeuron(sigmoidal_simple);
					if(sal == 1){
						if(pred_class != -1){
							pred_class = -2;
							continue;
						}else{
							pred_class = cnt;
						}
					} 
					cnt++;
				}*/

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
                        epoch++;
		}
                //print epoch counter
	}

	
        
  
