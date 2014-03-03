#include "adaline.h"
#include <stdio.h>
//class adaline

	float sigmoidal(void* context, float in_value, float threshold){
		if(in_value >= threshold) return 1;
		else if(in_value < -threshold) return -1;
		else return 0;	
	}
        
        //usamos esto, porque suponemos multiclase, no solo biclase, y con multiples neuronas de salida
    float sigmoidal_simple(float in_value, float threshold){
		if(in_value > threshold) return 1;
		else if(in_value <= threshold) return 0;
	}

	adaline::adaline(int num_hidden, Test data_training, float rate){

		learn_rate = 1;

		num_att = data_training[0].first.size();
		num_class = data_training[0].second.size();

        int c = 0;
        float top = data_training.size()*2/3;
        for(c=0; c < top; c++){
            training_data.push_back(data_training[c]);
        }
        for(; c < data_training.size(); c++){
            testing_data.push_back(data_training[c]);
        }
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
		threshold = 2;
        y.push_back(Neuron());
		//}

		//create the links
		//TODO comprobar estos for
		if(z.size()==0){//if it is a single adaline
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

	void adaline::test(Test data_testing){
		testing_data = data_testing;
		ofstream of("salida_adaline.txt");
        int ndata = 0;
        int countOK = 0;
        for(Test::iterator i = testing_data.begin(); i!=testing_data.end(); ++i){
        	y[0].in_value = 0;
        	int cin = 0;
            for(vector<float>::iterator in_n = i->first.begin(); in_n != i->first.end(); ++in_n){
                input[cin++].in_value = in_n[0];
            }
            for(vector<Link>::iterator in_link = l_y.begin(); in_link != l_y.end(); ++in_link){
                in_link[0].sumLink();
            }
            int clase = 0;
            
            float sal = y[0].evalNeuron(0, threshold, &sigmoidal);
            if(sal == 1){
                clase = 1;
            }else if(sal == -1){
                clase = 2;
            }

            //escribe la clase predicha en un fichero.
            of << clase << endl;
            ndata++;
        }
        of.close();
	}


	void adaline::test(){
            int ndata = 0;
            int countOK = 0;
            for(Test::iterator i = testing_data.begin(); i!=testing_data.end(); ++i){
            	y[0].in_value = 0;
            	int cin = 0;
                for(vector<float>::iterator in_n = i->first.begin(); in_n != i->first.end(); ++in_n){
                    input[cin++].in_value = in_n[0];
                }
                for(vector<Link>::iterator in_link = l_y.begin(); in_link != l_y.end(); ++in_link){
                    in_link[0].sumLink();
                }
                int clase = 0;
                
                float sal = y[0].evalNeuron(0, threshold, &sigmoidal);
                if(sal == 1){
                    clase = 1;
                }else if(sal == -1){
                    clase = 2;
                }
                //now, check the correctness of classifier
                int trueClass = 0;
                int c = 1;
                for(vector<int>::iterator class_i = i->second.begin(); class_i != i->second.end(); ++class_i){
                    if((class_i[0])==1){
                        trueClass = c;
                        break;
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
            cout << "Porcentaje de acierto:" << ((double)(countOK)/testing_data.size())*100 << "\n";
	}
     
        
    void adaline::train(){
		return simple_train();
	}

	void adaline::train(Test data_training){
		training_data = data_training;
		return simple_train();
	}

	void adaline::simple_train(){
		ofstream of_stat("adaline_train_stat.txt");
		//el numero de clases es el tamanio de un dato, menos numAtt
		bool stop_cond = false;
		bool error = false;
        int epoch = 0;
		while(!stop_cond){
            stop_cond = false;
            error = false;
			int numOk=0;
			int numInstance=0;
			float ecm_sum = 0;
            float ecm_media = 0;

			for (vector<Caso>::iterator caso = training_data.begin(); caso != training_data.end(); ++caso)
			{
				y[0].in_value = 0;
				numInstance++;
				//por cada caso de entrenamiento, inicializar neuronas
				int i=0;                   
				for (std::vector<float>::iterator att = caso[0].first.begin(); att != caso[0].first.end(); ++att)
				{
					input[i++].in_value = att[0];
				}
				//e interpretamos la clase
				int clase=1;
				for (std::vector<int>::iterator citr = caso[0].second.begin(); citr != caso[0].second.end(); ++citr)
				{
					if(citr[0] == 1) break;
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
                //ecm_sum += sal;
                int t = 0;
						if(clase == 1) t = 1;
						else t = -1;
				ecm_sum += (clase - pred_class);
				if(pred_class == clase){
					numOk++;
                    for (vector<Link>::iterator links = l_y.begin(); links != l_y.end(); ++links){
						links->weight += learn_rate*((t-sal)*(links->from->in_value));
					}
					//acierto.
				}else{
					error = true;
					//error
					for (vector<Link>::iterator links = l_y.begin(); links != l_y.end(); ++links){
						links->weight += learn_rate*((t-sal)*(links->from->in_value));
					}
				}


			}
			//if(epoch % 5 == 0)
			//	cout << "Epoca num:"<<epoch <<" correctness: " <<((double)(numOk)/training_data.size())*100 << "\n";

            float ecm = (ecm_sum*ecm_sum)/(2*training_data.size());
            of_stat << epoch << "\t" << 100-((double)(numOk)/training_data.size())*100 << "\t" << ecm << endl;
            if(error == false) break;
            if(epoch > 10000) break;
            epoch++;
		}
			cout << "\ntotal epocas :" << epoch << "\n";
                //print epoch counter
	}

	
        
  
