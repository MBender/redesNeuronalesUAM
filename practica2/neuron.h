#ifndef __NEURON_H__
#define __NEURON_H__

using namespace std;

class Neuron{

public:
	int nlayer; 
	float in_value; 
	float out_value;
	float delta_value;
	Neuron();
	float evalNeuron(void* context, float(*eval)(void*, float));
};


class Link{
public:

	Link();

	float weight;
	Neuron *from;
	Neuron *to;

	float sumLink();

};

#endif