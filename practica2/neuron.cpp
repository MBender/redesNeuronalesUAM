/*
 * @author Daniel & Matias
 * 
 *	Functions of the neuron module.
 *
**/
#include <stdio.h>
#include <stdlib.h>
#include "neuron.h"
#include "cargar.h"
using namespace std;

Neuron::Neuron(){
	in_value = 0;
	out_value = 0;
	delta_value = 0;
	is_bias = 0;
}

float Neuron::evalNeuron(void* context, float(*eval)(void*, float)){
	out_value = (float)eval(context, in_value);
	return out_value;
}


//class Link
Link::Link(){
	weight = ((double) rand() / (RAND_MAX) )*1.5;
	weight-=1;	
	weight_update = 0;
	to = NULL;
	from = NULL;
}

float Link::sumLink(){
	if(to == NULL || from == NULL) return 0; 
	float value = (float)from->out_value * weight;
	to->in_value += (float)value;
	return from->out_value * weight;
}

float Link::sumDelta(){
	if(to == NULL || from == NULL) return 0; 
	float value = (float)to->delta_value * weight;
	from->delta_value += (float)value;
	return to->delta_value * weight;	
}