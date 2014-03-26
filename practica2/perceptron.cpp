#include "perceptron.h"
#include <stdio.h>

	float binary_sigmoidal(void* context, float in_value){
		return (float)1/(1+exp(-in_value));
	}
      
    float bipolar_sigmoidal(void* context, float in_value){
		return ((float)2/(1+exp(-in_value))) - 1;
	}

	perceptron::perceptron(int num_hidden, float part,Test data_training, float rate, bool shift){

		learn_rate = 0.5;

		num_att = data_training[0].first.size();
		num_class = data_training[0].second.size();

        int c = 0;
        float top = data_training.size()*part;
	    if(shift){
	        for(c=0; c < top; c++){
	            training_data.push_back(data_training[c]);
	        }
	        for(; c < data_training.size(); c++){
	            testing_data.push_back(data_training[c]);
	        }
	    }else{
	    	training_data = data_training;
			//input
	    }
		for (int i = 0; i < num_att; ++i)
		{
			input.push_back(Neuron());
		}
		//add a Bias
		Neuron in_bias;
		in_bias.in_value = 1;
		in_bias.is_bias = 1;
		input.push_back(in_bias);
			//hidden
		for (int i = 0; i < num_hidden; ++i)
		{
			z.push_back(Neuron());
		}
		//if there is not a hidden layer, dont add bias neuron
		

		threshold = 2;
        for(int i = 0; i < data_training[0].second.size();i++){
        	y.push_back(Neuron());
        }

		//create the links
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

			Neuron n;
			n.in_value = 1;
			n.out_value = 0;
			n.is_bias = 1;
			z.push_back(n);

			for (std::vector<Neuron>::iterator a = z.begin(); a != z.end(); ++a)
			{
				for (std::vector<Neuron>::iterator b = y.begin(); b != y.end(); ++b)
				{
					Link l;
					l.from = &a[0];
					l.to = &b[0];
					l_y.push_back(l);
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
            int nok = 0;
            for(Test::iterator i = testing_data.begin(); i!=testing_data.end(); ++i){

            	Caso instance = i[0];
            	int clase=1;
				for (std::vector<int>::iterator citr = instance.second.begin(); citr != instance.second.end(); ++citr)
				{
					if(citr[0] == 1) break;
					clase++;
				}
				//cout << "clase: " << clase << endl;

                //Inicializamos las neuronas
                for (std::vector<Neuron>::iterator itr = y.begin(); itr != y.end(); ++itr)
				{
					itr[0].in_value=0;
				}

				for (std::vector<Neuron>::iterator itr = z.begin(); itr != z.end(); ++itr)
				{
					if(itr[0].is_bias == 1)continue;
					itr[0].in_value = 0;
				}

                int cin = 0;
                for(vector<float>::iterator in_n = i->first.begin(); in_n != i->first.end(); ++in_n){
                    //input[cin].in_value = in_n[0];
                    input[cin++].out_value = in_n[0];
                }

                //Propagamos a la capa Z
                for(vector<Link>::iterator in_link = l_z.begin(); in_link != l_z.end(); ++in_link){
                    in_link[0].sumLink();
                }

                //Calculamos salida de la capa Z
                for (vector<Neuron>::iterator 	neuronasZ = z.begin(); 	neuronasZ != z.end(); ++neuronasZ)
				{
					if(neuronasZ[0].is_bias==1) neuronasZ[0].out_value = 1;
					else neuronasZ[0].evalNeuron(0, &bipolar_sigmoidal);
				}

                //Propagamos a la capa Y
                for(vector<Link>::iterator in_link = l_y.begin(); in_link != l_y.end(); ++in_link){
                    in_link[0].sumLink();
                }

                //Calcula las respuestas
                //vector<float> respuesta (y.size(), 0);
                int pred_class = 0;
				int cnt = 1;
				float max_value = -9999;
				//tenemos que ver cual es la neurona activada, en caso de dos, dar error
				for (std::vector<Neuron>::iterator 	neuy = 	y.begin(); 	neuy != 	y.end(); ++	neuy)
				{
						if(neuy[0].evalNeuron(0,&bipolar_sigmoidal)>= max_value){
							pred_class = cnt;
							max_value = neuy[0].out_value;
						}
						//if(cnt==3)cout << "salida y:" << neuy[0].out_value << "\n";
						cnt++;	

				}
				if(clase == pred_class) nok++;
                of << pred_class << endl;
                //escribe la clase predicha en un fichero.
                ndata++;
            }
            of.close();
            cout << "Acierto: " << ((float)nok / ndata) * 100 << endl;
    }
 
    void perceptron::train(){
		return multi_train();
	}

	void perceptron::train(Test data_training){
		training_data = data_training;
		//if(z.size() == 0)return simple_train();
		return multi_train();
	}


	void perceptron::multi_train(){

		ofstream of_stat("perceptron_train_stat.txt");
		cout << "iniciando perceptron multicapa";
		//el numero de clases es el tamanio de un dato, menos numAtt
        int epoch = 0;
   		while(true){
   			float sum_ecm = 0;
            bool error = false;
			int numOk=0;
			int numInstance = 0;
			for (vector<Caso>::iterator caso = training_data.begin(); caso != training_data.end(); ++caso)
			{
				Caso instance = caso[0];
				numInstance++;
				//Se reinician los valores de entrada y regla delta
				for (std::vector<Neuron>::iterator itr = y.begin(); itr != y.end(); ++itr)
				{
					itr[0].in_value=0;
					itr[0].delta_value = 0;
				}

				for (std::vector<Neuron>::iterator itr = z.begin(); itr != z.end(); ++itr)
				{

					itr[0].delta_value = 0;
					if(itr[0].is_bias == 1)continue;
					itr[0].in_value = 0;
				}

				//FEEDFORWARD
				//por cada caso de entrenamiento, inicializar neuronas
				int i=0;                   
				for (std::vector<float>::iterator att = instance.first.begin(); att != instance.first.end(); ++att)
				{
					//input[i].in_value = att[0];

					input[i].out_value = att[0];

					i++;
					if(input[i].is_bias==1){
						//input[i++].out_value = 1;
					}
				}
				//for (std::vector<Neuron>::iterator layer_in = input.begin(); layer_in != input.end(); ++layer_in)
				//{
				//	if(layer_in[0].is_bias == 1) layer_in[0].out_value = 1;
				//	else layer_in[0].out_value = instance.first[i++];
				//}

				//e interpretamos la clase
				int clase=1;
				for (std::vector<int>::iterator citr = instance.second.begin(); citr != instance.second.end(); ++citr)
				{
					if(citr[0] == 1) break;
					clase++;
				}
				//ahora, procedemos a calcular las salidas
					//propagamos las entradas
				for (std::vector<Link>::iterator link = l_z.begin(); link != l_z.end(); ++link)
				{
					link[0].sumLink();
					
				}

					//calculamos valor de capa media, aplicando la bipolar para calcular la salida
				for (std::vector<Neuron>::iterator 	neuz = 	z.begin(); 	neuz != 	z.end(); ++	neuz)
				{
					if(neuz[0].is_bias==1) neuz[0].out_value = 1; //si es el sesgo, solo ponemos 1 en salida
					else neuz[0].evalNeuron(0, &bipolar_sigmoidal);
					//cout << "salida neurona z" << neuz[0].out_value << endl;
				}
					//propagamos a la salida
				for (std::vector<Link>::iterator 	link_y = 	l_y.begin(); 	link_y != 	l_y.end(); ++	link_y)
				{
					link_y[0].sumLink();
				}
					//calculamos las salidas, y vemos la clase respuesta
				int pred_class = 0;
				int cnt = 1;
				float max_value = -9999;
				//tenemos que ver cual es la neurona activada, en caso de dos, dar error
				for (std::vector<Neuron>::iterator 	neuy = 	y.begin(); 	neuy != 	y.end(); ++	neuy)
				{
						if(neuy[0].evalNeuron(0,&bipolar_sigmoidal)>= max_value){
							pred_class = cnt;
							max_value = neuy[0].out_value;
						}
						//cout << "salida y:" << neuy[0].out_value << "\n";
						cnt++;	

				}
				if(pred_class == clase){
					//if(pred_class == 3)cout << "epoch: " << epoch << "pred: " <<pred_class << "value: "<< max_value<< endl;

					numOk++;	
				}else{
					error = true;
				}


					//BACKPROPAGATION:
				
				//primero hallamos los delta value de las neuronas de salida
				cnt = 0;
				float ecm_contr = 0;
				for (vector<Neuron>::iterator 	neuy = 	y.begin(); 	neuy != 	y.end(); ++	neuy, cnt++)
				{
					float val = -0.9;

					if(instance.second[cnt]==1){ //para ver si es valor teorico 1 o -1 la neurona de salidas
						val = 0.9;
					}

					neuy[0].delta_value = (val-neuy[0].out_value)*
									(0.5*(1-neuy[0].out_value)*(1+neuy[0].out_value)); //BIPOLAR
									//(neuy[0].out_value*(1-neuy[0].out_value)); //BINARY
					ecm_contr += (val - neuy[0].out_value)*(val - neuy[0].out_value);
				}

				ecm_contr /= y.size();
				sum_ecm += ecm_contr;
				//vemos actualizacion pesos de salida
				cnt = 0;
				for (vector<Link>::iterator 	link_y = 	l_y.begin(); 	link_y != 	l_y.end(); ++link_y,cnt++)
				{
						if(link_y[0].from->is_bias == 1){
							link_y[0].weight_update += learn_rate*link_y[0].to->delta_value;
						}else {
							link_y[0].weight_update += learn_rate*link_y[0].to->delta_value
										*link_y[0].from->out_value;
						}
				}

				//propagamos el valor delta
				for (vector<Link>::iterator link_y = l_y.begin(); link_y != l_y.end(); ++link_y)
				{
						link_y[0].sumDelta();
				}

				//ahora calculamos la rectificacion de delta para las capas intermedias
				for (std::vector<Neuron>::iterator 	neuz = 	z.begin(); 	neuz != 	z.end(); ++	neuz)
				{
					neuz[0].delta_value *= 0.5*(1+neuz[0].out_value)*(1-neuz[0].out_value); //BIPOLAR
					//neuz[0].delta_value *= neuz[0].out_value*(1-neuz[0].out_value); //BINARY
				}
				//rectificamos pesos de entrada
				for (std::vector<Link>::iterator 	link_z = 	l_z.begin(); 	link_z != 	l_z.end(); ++	link_z)
				{
					if(link_z[0].from->is_bias == 0)
						link_z[0].weight_update += learn_rate*link_z[0].to->delta_value
										*link_z[0].from->in_value;
					else
						link_z[0].weight_update += learn_rate*link_z[0].to->delta_value;
				}

				//rectificamos pesos
				for (std::vector<Link>::iterator link_y = l_y.begin(); link_y != l_y.end(); ++link_y)
				{
					link_y[0].weight+=link_y[0].weight_update;
					link_y[0].weight_update = 0;
				}

				for (std::vector<Link>::iterator link_z = l_z.begin(); link_z != l_z.end(); ++link_z)
				{
					link_z[0].weight+=link_z[0].weight_update;
					link_z[0].weight_update = 0;
				}
			}
			//if(epoch % 5 == 0)
			sum_ecm = sum_ecm/(training_data.size());
			cout << "Epoca num:"<<epoch <<" correctness: " <<((double)(numOk)/training_data.size())*100 << "\n";
            of_stat << epoch << "\t" << 100 - ((double)(numOk)/training_data.size())*100 << "\t" << sum_ecm << endl;
           // if(numOk == (training_data.size()-1)) break;
            if(error == false) break;
            if(epoch >= 1000) break;
            epoch++;
		}
			cout << "\ntotal epocas :" << epoch << "\n";
			of_stat.close();
	}