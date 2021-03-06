#ifndef __ADALINE_H__
#define __ADALINE_H__

#include "neuron.h"
#include "cargar.h"
#include <vector>

using namespace std;

float sigmoidal(void* context, float in_value, float threshold);

class adaline{

public:

	adaline(){ }

	adaline(int num_hidden, Test data_training, float rate);

	void multi_train();


	void test();
        
	void test(Test data_testing);
        
    void train();

    void train(Test data_training);

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
        Test testing_data;
	//number of atts and classes
	int num_att;
	int num_class;
	//learning rate
	float learn_rate;
	//umbral
	float threshold;

	void simple_train();

	
        
    float sigmoidal_simple(float in_value, float threshold);
        
        
};
#endif