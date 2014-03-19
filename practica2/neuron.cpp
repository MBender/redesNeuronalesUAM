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

float Neuron::evalNeuron(void* context, float(*eval)(void*, float)){
	out_value = eval(context, in_value);
	return out_value;
}


//class Link
Link::Link(){
	//weight = ((double) rand() / (RAND_MAX) );
	weight = 0;
	to = NULL;
	from = NULL;
}

float Link::sumLink(){
	if(to == NULL || from == NULL) return 0; 
	int value = from->in_value * weight;
	to->in_value += value;
	return from->in_value * weight;
}


