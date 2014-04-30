#include "perceptron.h"
#include <stdio.h>

	

	float binary_sigmoidal(void* context, float in_value){
		return (float)1/(1+exp(-in_value));
	}
      
    float bipolar_sigmoidal(void* context, float in_value){
		return ((float)2/(1+exp(-in_value))) - 1;
	}

	double derivadaSigmoideBipolar (double x) {
		return (double)1/2*(1+bipolar_sigmoidal(0,x))*(1-bipolar_sigmoidal(0,x));
	}

	perceptron::perceptron(){}

	perceptron::perceptron(int num_hidden, float part, vector<Par> data_training, float rate, bool shift, bool norm){

		learn_rate = rate;

		num_att = data_training[0].first.size();
		num_class = 1;

        int c = 0;
        float top = data_training.size()*part;
	    if(shift){
	        for(c=0; c < top; c++){
            	training_data.push_back(data_training[c]);
	        }
	        for(; c < data_training.size(); c++){
	            testing_data.push_back(data_training[c]);
	        }
	            //training_data = data_training;
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
		in_bias.out_value = 1;
		in_bias.is_bias = 1;
		input.push_back(in_bias);
			//hidden
		for (int i = 0; i < num_hidden; ++i)
		{
			z.push_back(Neuron());
		}
		//if there is not a hidden layer, dont add bias neuron

		threshold = 2;
        for(int i = 0; i < 1;i++){
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


		//Normalización
			//al ser salida no normalizada, no tiene sentido normalizar entrada. 
				//de todas formas, probar :D
		normalizar = norm;
		/*normalizar = norm;
		if(normalizar) {
			//for(int indice = 0; indice < num_att; indice++) {
				promedio.push_back(0);
				for(std::vector<Par>::iterator it = training_data.begin(); 	it != training_data.end(); ++it) {
					promedio[0] += it->first[0];
				}
				promedio[0] /= training_data.size();
				float diffCuadradas = 0;
				for(std::vector<Par>::iterator it = training_data.begin(); 	it != training_data.end(); ++it) {
					diffCuadradas += (it->first[0]-promedio[0]) * (it->first[0]-promedio[0]);
				}
				diffCuadradas /= training_data.size() - 1;
				desvioEstandar.push_back(sqrt(diffCuadradas));
			//}
		}*/
	}

	float perceptron::preProcesar (float x, int indice) {
		//if(!normalizar)
			return x;
		//cout << desvioEstandar[0] << endl;
		//return (x-promedio[0])/desvioEstandar[0];
	}

	float perceptron::denormalizar (float x, int indice) {
		//if(!normalizar)
			return x;
		//return (x*desvioEstandar[0])+promedio[0];
	}

	void perceptron::multi_test(){
		multi_test(testing_data);
	}

	void perceptron::multi_test(vector<Par> data_testing){
            testing_data = data_testing;
            ofstream of("salida_perceptron.txt");
            int ndata = 0;
            int nok = 0;
            float anterior = 0;
            float ecm = 0;
            float ecm_anterior = 0;
            for(vector<Par>::iterator i = testing_data.begin(); i!=testing_data.end(); ++i){

            	Par instance = i[0];

            	//obtenemos la clase
            	float clase=1;
				clase = instance.second;


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
                    input[cin++].out_value = preProcesar(in_n[0], cin);
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
                float pred_class = y[0].in_value;
                
                //Calcula ECM
                ecm += (clase - pred_class)*(clase - pred_class);
                ecm_anterior+=(clase - anterior)*(clase - anterior);
				
                //escribe la clase predicha en un fichero
				string out_string = "";
				char buff[100];
				//string data = std::to_string(pred_class);
				sprintf(buff, "%lf", pred_class);

				//of << out_string << buff << endl;
                anterior = clase;
                ndata++;
            }
            of.close();
            cout << "ECM: " << ((float)ecm / ndata) << endl;
            cout << "ECM ANTERIOR: " << ((float)ecm_anterior / ndata) << endl;
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
			float pred_class = 0;
			float clase = 0;
			//cout << training_data.size() << endl;
			for (vector<Par>::iterator caso = training_data.begin(); caso != training_data.end(); ++caso)
			{
				Par instance = caso[0];
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
					input[i].out_value = preProcesar(att[0],i);
					i++;
					//if(input[i].is_bias=1) input[i].out_value = 1;
					
				}
				

				//e interpretamos la clase
				clase = instance.second;
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
				//float pred_class = 0;
				//miramos salida de la neurona
				y[0].out_value = y[0].in_value;
				pred_class = y[0].out_value;				
				//pred_class = y[0].evalNeuron(0,&bipolar_sigmoidal);
				//no hacer esto
				if(abs(clase - denormalizar(pred_class,1))<0.1){
					//if(pred_class == 3)cout << "epoch: " << epoch << "pred: " <<pred_class << "value: "<< max_value<< endl;
					numOk++;	
				}else{
					error = true;
				}
					//BACKPROPAGATION:
				
				//primero hallamos los delta value de las neuronas de salida
				float ecm_contr = 0;
				for (vector<Neuron>::iterator 	neuy = 	y.begin(); 	neuy != 	y.end(); ++	neuy)
				{
					float val = clase;
					neuy[0].delta_value = (val - neuy[0].out_value);
					//neuy[0].delta_value = (preProcesar(val,1)-neuy[0].out_value);//*
									//(0.5*(1-neuy[0].out_value)*(1+neuy[0].out_value)); //BIPOLAR
									//comprobarlo!! quizas necesito la derivada de la funcion linear
									//(neuy[0].out_value*(1-neuy[0].out_value)); //BINARY
									//(neuy[0].out_value/(1+neuy[0].out_value*neuy[0].out_value));//ARTAN
					ecm_contr += (preProcesar(val,1) - neuy[0].out_value)*(preProcesar(val,1) - neuy[0].out_value);
				}

				sum_ecm += ecm_contr;
				//vemos actualizacion pesos de salida
				for (vector<Link>::iterator 	link_y = 	l_y.begin(); 	link_y != 	l_y.end(); ++link_y)
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
					neuz[0].delta_value *= derivadaSigmoideBipolar(neuz[0].in_value);//0.5*(1+neuz[0].out_value)*(1-neuz[0].out_value); //BIPOLAR
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
			//cout << "Epoca num:"<<epoch <<" ecm: " << sum_ecm << "\n" << endl;
			//cout << "dato oficial:" << clase << " dato obtenido:" << pred_class <<endl;
            of_stat << epoch << "\t" << 100 - ((float)(numOk)/training_data.size())*100 << "\t" << sum_ecm << endl;
            if(epoch >= 1000) break;
            epoch++;
		}
			cout << "\ntotal epocas :" << epoch << "\n";
			of_stat.close();
	}

	double perceptron::exploit_epoch(vector<float> in_data){

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
            for(vector<float>::iterator in_n = in_data.begin(); in_n != in_data.end(); ++in_n){
                input[cin].out_value = in_n[0];
                cin++;
            }
            input[input.size()-1].out_value = 1;	                  
				

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
            double pred_class = y[0].in_value;

            return pred_class;
	}

	void perceptron::procesar_recursiva(vector<float> raw_data, int num_pred){
	
		vector<float> values;
		ofstream of("serie_predicha.txt");
		for(int i = 0; i < num_att; i++){
			values.push_back(raw_data[i]);
		}
		
		for(int epoch = 0; epoch < raw_data.size()-num_pred; epoch++){
			float pred = exploit_epoch(values);
			//actualización de valores
			for(int i = 0; i <num_att-1; i++){
				values[i] = preProcesar(values[i+1],0);
			}
			values[num_att-1] = preProcesar(pred,0);

			of << pred << endl;
		}

		of.close();
	}