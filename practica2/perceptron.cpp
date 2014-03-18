#include "perceptron.h"
#include <stdio.h>
//class perceptron

	float binary_sigmoidal(void* context, float in_value){
		return 1/(1+exp(-in_value));
	}
      
    float bipolar_sigmoidal(void* context, float in_value){
		return 2/(1+exp(-in_value)) - 1;
	}


	perceptron::perceptron(int num_hidden, Test data_training, float rate){

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
        for(int i = 0; i < data_training[0].second.size();i++){
        	y.push_back(Neuron());
        }
		//}""

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
		}else{ //multicapa
			for (std::vector<Neuron>::iterator i = input.begin(); i != input.end(); ++i)
			{
				for (std::vector<Neuron>::iterator j = z.begin(); j != z.end(); ++j)
				{
					Link l;
					l.from = &i[0];
					l.to = &j[0];
					l_z.push_back(l);

				}
			}

			for (std::vector<Neuron>::iterator a = z.begin(); a != z.end(); ++a)
			{
				for (std::vector<Neuron>::iterator b = y.begin(); b != y.end(); ++b)
				{
					Link l;
					l.from = &a[0];
					l.to = &b[0];
					l_z.push_back(l);
				}
			}
		}
	}
	void perceptron::multi_test(){
		multi_test(testing_data);
	}

	void perceptron::multi_test(Test data_testing){
            testing_data = data_testing;
            ofstream of("salida_perceptron.txt");
            int ndata = 0;
            int countOK = 0;
            for(Test::iterator i = testing_data.begin(); i!=testing_data.end(); ++i){

                //Inicializamos las neuronas

                int cin = 0;
                for(vector<float>::iterator in_n = i->first.begin(); in_n != i->first.end(); ++in_n){
                    input[cin++].in_value = in_n[0];
                }
                for(vector<Neuron>::iterator neuronasZ = z.begin(); neuronasZ != z.end(); neuronasZ++) {
                    neuronasZ[0].in_value = 0;
                }
                for(vector<Neuron>::iterator neuronasY = y.begin(); neuronasY != y.end(); neuronasY++) {
                    neuronasY[0].in_value = 0;
                }

                //Propagamos a la capa Z

                for(vector<Link>::iterator in_link = l_z.begin(); in_link != l_z.end(); ++in_link){
                    in_link[0].sumLink();
                }

                //Propagamos a la capa Y
                for(vector<Link>::iterator in_link = l_y.begin(); in_link != l_y.end(); ++in_link){
                    in_link[0].sumLink();
                }

                //Calcula las respuestas
                vector<float> respuesta (y.size(), 0);
                cin = 0;
                for(vector<Neuron>::iterator neuronasY = y.begin(); neuronasY != y.end(); neuronasY++) {
                    respuesta[cin++] = neuronasY[0].evalNeuron(0, &binary_sigmoidal);
                    of << respuesta[cin-1] << endl;
                }

                //escribe la clase predicha en un fichero.
                ndata++;
            }
            of.close();
    }


	void perceptron::simple_test(Test data_testing){
			testing_data = data_testing;
			ofstream of("salida_perceptron.txt");
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
                
                float sal = y[0].evalNeuron(0, &binary_sigmoidal);
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

	void perceptron::simple_test(){
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
                
                float sal = y[0].evalNeuron(0, &binary_sigmoidal);
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
     
        
    void perceptron::train(){
		return simple_train();
	}

	void perceptron::train(Test data_training){
		training_data = data_training;
		return simple_train();
	}

	void perceptron::simple_train(){
		ofstream of_stat("perceptron_train_stat.txt");
		cout << "iniciando perceptron simple";
		//el numero de clases es el tamanio de un dato, menos numAtt
		bool stop_cond = false;
		bool error = false;
                int epoch = 0;
   		while(!stop_cond){
   			float ecm_sum = 0;

            stop_cond = false;
            error = false;
			int numOk=0;
			int numInstance=0;
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
                float sal = y[0].evalNeuron(0, &binary_sigmoidal);
                if(sal == 1){
                    pred_class = 1;
                }else if(sal == -1){
                    pred_class = 2;
                }

                ecm_sum += (clase-pred_class);

				if(pred_class == clase){
					numOk++;
                	//acierto. no entrena
				}else{
					//error
					error = true;
					for (vector<Link>::iterator links = l_y.begin(); links != l_y.end(); ++links){
						//cout << "antes: "<<links->from->in_value << "\n";
						double antes = links->weight;
						int t = 0;
						if(clase == 1) t = 1;
						else t = -1;
						links->weight += learn_rate*t*links->from->in_value; 
						//cout << "var: "<< links->weight<< "\n";
					}
				}


			}
			//if(epoch % 5 == 0)
			ecm_sum = (ecm_sum*ecm_sum)/(2*training_data.size());
				//cout << "Epoca num:"<<epoch <<" correctness: " <<((double)(numOk)/training_data.size())*100 << "\n";
            of_stat << epoch << "\t" << 100 - ((double)(numOk)/training_data.size())*100 << "\t" << ecm_sum << endl;
           // if(numOk == (training_data.size()-1)) break;
            if(error == false) break;
            if(epoch > 10000) break;
            epoch++;
		}
			cout << "\ntotal epocas :" << epoch << "\n";
			of_stat.close();
                //print epoch counter
	}



	void perceptron::multi_train(){
		ofstream of_stat("perceptron_train_stat.txt");
		cout << "iniciando perceptron simple";
		//el numero de clases es el tamanio de un dato, menos numAtt
		bool stop_cond = false;
		bool error = false;
                int epoch = 0;
   		while(!stop_cond){
   			float ecm_sum = 0;

            stop_cond = false;
            error = false;
			int numOk=0;
			int numInstance=0;
			for (vector<Caso>::iterator caso = training_data.begin(); caso != training_data.end(); ++caso)
			{
				for (std::vector<Neuron>::iterator i = y.begin(); i != y.end(); ++i)
				{
					i[0].in_value=0;
				}

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
				for (std::vector<Link>::iterator link = l_z.begin(); link != l_y.end(); ++link)
				{
					link->sumLink();
				}
					//calculamos valor de capa media
				for (std::vector<Neuron>::iterator 	neuz = 	z.begin(); 	neuz != 	z.end(); ++	neuz)
				{
						neuz[0].evalNeuron(0, &binary_sigmoidal);
				}
					//propagamos a la salida
				for (std::vector<Link>::iterator 	link_y = 	l_y.begin(); 	link_y != 	l_y.end(); ++	link_y)
				{
						link_y[0].sumLink();
				}

					//calculamos las salidas, y vemos la clase respuesta
				int pred_class = -1;
				int cnt = 0;

                //solo una neurona de salida en este caso, 2 clases (codigo simple)
				//tenemos que ver cual es la neurona activada, en caso de dos, dar error
				for (std::vector<Neuron>::iterator 	neuy = 	y.begin(); 	neuy != 	y.end(); ++	neuy)
				{

						if(neuy[0].evalNeuron(0, &binary_sigmoidal)==1){
							if(pred_class != -1){
								pred_class = -1;
								break;
							}
							pred_class = cnt;
						}
						cnt++;
				}
                ecm_sum += (clase-pred_class);

				if(pred_class == clase){
					numOk++;
				}
					//BACKPROPAGATION:
				//primero hallamos los delta value de las neuronas de salida
				for (std::vector<Neuron>::iterator 	neuz = 	y.begin(); 	neuz != 	y.end(); ++	neuz)
				{
						neuz[0].delta_value = (clase - pred_class)*
										((1-neuz[0].in_value)*(1+neuz[0].in_value)*pred_class);

				}
				//actualizamos pesos de salida
				for (std::vector<Link>::iterator 	link_y = 	l_y.begin(); 	link_y != 	l_y.end(); ++	link_y)
				{
						link_y[0].weight += learn_rate*link_y[0].to->delta_value
										*link_y[0].from->out_value;
						link_y[0].from->delta_value=0;
				}

				//preparamos el sumatorio
				for (std::vector<Link>::iterator link_y = l_y.begin(); link_y != l_y.end(); ++link_y)
				{
						link_y[0].from->delta_value+=link_y[0].to->delta_value * link_y[0].weight;
				}
				//ahora calculamos la rectificacion de delta para las capas intermedias
				for (std::vector<Neuron>::iterator 	neuz = 	z.begin(); 	neuz != 	z.end(); ++	neuz)
				{
					neuz[0].delta_value *= (1-neuz[0].in_value)*(1+neuz[0].in_value)*neuz[0].out_value; 
				}

				//rectificamos pesos de entrada
				for (std::vector<Link>::iterator 	link_z = 	l_z.begin(); 	link_z != 	l_z.end(); ++	link_z)
				{
						link_z[0].weight += learn_rate*link_z[0].to->delta_value
										*link_z[0].from->out_value;
						link_z[0].from->delta_value=0;
				}


			}
			//if(epoch % 5 == 0)
			ecm_sum = (ecm_sum*ecm_sum)/(2*training_data.size());
				//cout << "Epoca num:"<<epoch <<" correctness: " <<((double)(numOk)/training_data.size())*100 << "\n";
            of_stat << epoch << "\t" << 100 - ((double)(numOk)/training_data.size())*100 << "\t" << ecm_sum << endl;
           // if(numOk == (training_data.size()-1)) break;
            if(error == false) break;
            if(epoch > 10000) break;
            epoch++;
		}
			cout << "\ntotal epocas :" << epoch << "\n";
			of_stat.close();
                //print epoch counter
	}

	
        
  
