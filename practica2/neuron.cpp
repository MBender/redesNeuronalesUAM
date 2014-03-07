/*
 * @author Daniel & Matias
 * 
 *	Functions of the neuron module.
 *
**/
#include <stdio.h>
#include <stdlib.h>
#include "neuron.h"

using namespace std;

Neuron::Neuron(){
	in_value = 0;
	out_value = 0;
	delta_value = 0;
}

float Neuron::evalNeuron(void* context, float & threshold, float(*eval)(void*, float, float)){
	out_value = eval(context, in_value, threshold);
	return out_value;
}


//class Link
Link::Link(){
	//weight = ((double) rand() / (RAND_MAX) );
	weight = 0;
}

float Link::sumLink(){
	to->in_value += from->in_value * weight;
	return from->in_value * weight;
}


