#ifndef __SERIES_H__
#define __SERIES_H__

#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cstdlib> 
#include "perceptron.h"

using namespace std;


class perceptron;

//typedef std::unique_ptr<perceptron> perceptronPtr;

perceptron adapta_fichero_serie(string nombre_entrada, string nombre_salida, int np, 
	int nneurons, std::vector<float> *v);

vector<float> read_serie(string archivo);

#endif