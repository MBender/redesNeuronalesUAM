#ifndef __NEURON_H__
#define __NEURON_H__

using namespace std;

class Neuron{

public:
	int nlayer; 
	float in_value; 
	float out_value;
	float delta_value;
	float is_bias;
	Neuron();
	float evalNeuron(void* context, float(*eval)(void*, float));
};


class Link{
public:

	Link();

	float weight;
	float weight_update;
	Neuron *from;
	Neuron *to;

	float sumLink();
	float sumDelta();
};

#endif