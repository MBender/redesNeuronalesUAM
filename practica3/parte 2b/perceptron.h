#ifndef __PERCEPTRON_H__
#define __PERCEPTRON_H__

#include "neuron.h"
#include "series.h"
#include <vector>
#include <cmath> 

using namespace std;

typedef pair<vector<float>, float> Par;;


float binary_sigmoidal(void* context, float in_value);
float bipolar_sigmoidal(void* context, float in_value);

class perceptron{

public:
	perceptron();

	perceptron(int num_hidden, float part, vector<Par> data_training, float rate, bool shift, bool norm);

	void multi_train();

//	void simple_train();

//	void simple_test();
        
//    void simple_test(Test data_testing);

    void multi_test();

    void multi_test(vector<Par> data_testing);
      
    void procesar_recursiva(vector<float> raw_data);

    double exploit_epoch(vector<float> in_data);

    void procesar_recursiva(vector<float> raw_data, int num_pred);
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
	std::vector<Par>  training_data;
    //data for test
    std::vector<Par>  testing_data;
	//number of atts and classes
	int num_att;
	int num_class;
	//learning rate
	float learn_rate;
	//umbral
	float threshold;
	//Normalizar
	bool normalizar;
	
	vector<float> promedio;
	vector<float> desvioEstandar;

	float preProcesar(float, int);


};
#endif