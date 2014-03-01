/*
 * @author Daniel & Matias
 * 
 *	Functions of the neuron module.
 *
**/
#include <stdio.h>
#include <stdlib.h>
//#include "neuron.h"

using namespace std;

class Neuron{
public:
	int nlayer; //generable not needed
	float in_value; //only usable in some algorithms, or biases
	float out_value;

	float evalNeuron(float(*eval)(float)){
		out_value = eval(in_value);
		return out_value;
	}
};


class link{

public:


};

class Link{
public:

	Link(){
		weight = rand();
	}

	float weight;
	Neuron *from;
	Neuron *to;

	float sumLink(){
		to->in_value = from->out_value * weight;
	}

};

